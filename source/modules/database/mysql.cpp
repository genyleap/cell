#if __has_include("mysql.hpp")
#   include "mysql.hpp"
#else
#   error "Cell's "mysql.hpp" was not found!"
#endif

#if defined(USE_MYSQL_MARIADB)

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Database)

void* MySQLDatabaseConnection::get()
{
    auto connection = connectionPool.getConnection();
    if (std::holds_alternative<MySqlPtr>(connection)) {
        return static_cast<void*>(std::get<MySqlPtr>(connection));
    } else {
        throw Exception(Exception::Reason::Database, "Invalid connection type").getRuntimeError();
    }
}

MySQLDatabaseConnection::MySQLDatabaseConnection(MySqlConnectionPool& connectionPool)
    : connectionPool(connectionPool), connection(__cell_nullptr)
{
}

MySQLDatabaseConnection::~MySQLDatabaseConnection()
{
    disconnect();
}

bool MySQLDatabaseConnection::connect()
{
    connection = mysql_init(__cell_nullptr);
    if (!connection) {
        // Handle initialization error
        throw Exception(Exception::Reason::Database, "Failed to initialize 'MySQL' connection.").getRuntimeError();
        return false;
    }

    if (connectionPool.m_poolData.host.has_value()
        && connectionPool.m_poolData.user.has_value()
        && connectionPool.m_poolData.password.has_value()
        && connectionPool.m_poolData.database.has_value()
        && connectionPool.m_poolData.port > 0) {
        if (mysql_real_connect(connection,
                               connectionPool.m_poolData.host.value().c_str(),
                               connectionPool.m_poolData.user.value().c_str(),
                               connectionPool.m_poolData.password.value().c_str(),
                               connectionPool.m_poolData.database.value().c_str(),
                               connectionPool.m_poolData.port, __cell_nullptr, 0) == __cell_nullptr)
        {
            // Handle connection error
            m_mysqlData.lastError = mysql_error(connection);
            mysql_close(connection);
            connection = __cell_nullptr;
            return false;
        }

        if (connectionPool.m_poolData.keyPath.has_value()
            && connectionPool.m_poolData.certPath.has_value()
            && connectionPool.m_poolData.caPath.has_value())
        {
            if (mysql_ssl_set(connection,
                              connectionPool.m_poolData.keyPath.value().c_str(),
                              connectionPool.m_poolData.certPath.value().c_str(),
                              connectionPool.m_poolData.caPath.value().c_str(),
                              __cell_nullptr, __cell_nullptr) != 0)
            {
                // Handle SSL/TLS configuration error
                m_mysqlData.lastError = mysql_error(connection);
                mysql_close(connection);
                connection = __cell_nullptr;
                return false;
            }
        }

        return true;
    }

    return false;
}

bool MySQLDatabaseConnection::disconnect() {
    if (connection) {
        connectionPool.releaseConnection(connection);
        connection = __cell_nullptr;
    }
    return true;
}

std::future<bool> MySQLDatabaseConnection::connectAsync()
{
    // Use std::async to run the connect function asynchronously
    std::future<bool> future = std::async(std::launch::async, [this]() {
        return connect();
    });

    // Return the future to the caller
    return future;
}

std::future<bool> MySQLDatabaseConnection::disconnectAsync()
{
    // Use std::async to run the disconnect function asynchronously
    std::future<bool> future = std::async(std::launch::async, [this]() {
        return disconnect();
    });

    // Return the future to the caller
    return future;
}

bool MySQLDatabaseConnection::isConnected()
{
    return connection != __cell_nullptr && mysql_ping(connection) == 0;
}

bool MySQLDatabaseConnection::isQueryCached(const std::string& sql)
{
    std::unique_lock<std::mutex> lock(m_mysqlData.cacheMutex);
    return m_mysqlData.queryCache.count(sql) > 0;
}

bool MySQLDatabaseConnection::isConnectionAlive()
{
    if (connection == __cell_nullptr) {
        return false;
    }

    int pingResult = mysql_ping(connection);
    return pingResult == 0;
}

int MySQLDatabaseConnection::getActiveConnectionsCount()
{
    if (!isConnected()) {
        return 0;
    }

    int activeConnections = 0;

    // Access the connection pool's data to count active connections
    std::lock_guard<std::mutex> lock(connectionPool.m_poolData.mutex);
    for (const auto& connection : connectionPool.m_poolData.connections) {
        if (std::holds_alternative<MYSQL*>(connection)) {
            MYSQL* mysqlConnection = std::get<MYSQL*>(connection);
            if (mysqlConnection != nullptr && mysql_ping(mysqlConnection) == 0) {
                activeConnections++;
            }
        }
    }

    return activeConnections;
}



std::string MySQLDatabaseConnection::getConnectionHealthStatus()
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (connection == __cell_nullptr) {
        return safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                   engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
    }
    std::string_view statResult = mysql_stat(connection);
    if (statResult == __cell_nullptr) {
        return safeTranslate(language, "exceptions", "failed_server_status");
    }

    std::string statString(statResult);
    return statString;
}


int MySQLDatabaseConnection::getMaxConnectionsCount()
{
    if (!isConnected()) {
        return -1;  // Return a negative value to indicate an error or not connected
    }

    if (mysql_query(connection, "SHOW VARIABLES LIKE 'max_connections'") != 0) {
        // Failed to execute the query
        return -1;  // Return a negative value to indicate an error
    }

    m_result = mysql_store_result(connection);
    if (m_result == __cell_nullptr) {
        // Failed to retrieve the result
        return -1;  // Return a negative value to indicate an error
    }

    MYSQL_ROW row = mysql_fetch_row(m_result);
    if (row == __cell_nullptr || row[1] == __cell_nullptr) {
        // Invalid result or missing value
        mysql_free_result(m_result);
        return -1;  // Return a negative value to indicate an error
    }

    int maxConnections = std::stoi(row[1]);

    mysql_free_result(m_result);

    return maxConnections;
}

std::string MySQLDatabaseConnection::getDatabaseServerVersion()
{
    if (!isConnected()) {
        //! Handle not being connected
        //! Todo...
        return __cell_null_str;
    }

    const char* serverVersion = mysql_get_server_info(connection);
    if (serverVersion) {
        return serverVersion;
    } else {
        // Handle error retrieving server version
        return __cell_null_str;
    }
}


std::map<std::string, std::string> MySQLDatabaseConnection::getConnectionStatistics()
{
    std::map<std::string, std::string> stats;

    if (!isConnected()) {
        //! Handle not being connected
        //! Todo...
        return stats;
    }

    const char* connectionStats = mysql_stat(connection);
    if (connectionStats) {
        // Parse the connection stats string
        std::stringstream statsStream(connectionStats);
        std::string line;
        while (std::getline(statsStream, line)) {
            std::size_t delimiterPos = line.find(':');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                stats[key] = value;
            }
        }
    } else {
        // Handle error retrieving connection stats
        m_mysqlData.lastError = mysql_error(connection);
        // You can log the error, throw an exception, or handle it in any other desired way
    }

    return stats;
}


std::chrono::seconds MySQLDatabaseConnection::getConnectionUptime()
{
    if (!isConnected()) {
        //! Handle not being connected
        //! Todo...
        return std::chrono::seconds(0);
    }

    const char* connectionStats = mysql_stat(connection);
    if (connectionStats) {
        // Extract the uptime value from the connection stats string
        std::string statsString(connectionStats);
        std::regex uptimeRegex("Uptime: (\\d+)");
        std::smatch match;
        if (std::regex_search(statsString, match, uptimeRegex)) {
            std::string uptimeString = match[1].str();
            ullong uptime = std::stoull(uptimeString);
            return std::chrono::seconds(uptime);
        }
    } else {
        //! Handle error retrieving connection stats
        //! Todo...
        m_mysqlData.lastError = mysql_error(connection);
        // You can log the error, throw an exception, or handle it in any other desired way
    }

    return std::chrono::seconds(0); // Default to 0 if the uptime is not available or encountered an error
}

std::vector<std::string> MySQLDatabaseConnection::getConnectionActivityLog()
{
    std::vector<std::string> activityLog;

    if (!isConnected()) {
        // Handle not being connected
        return activityLog;
    }

    // Execute query to retrieve connection activity log
    std::string sql = "SELECT argument FROM mysql.general_log WHERE command_type = 'Connect';";
    std::vector<std::vector<std::string>> result = querySync(sql);

    // Process the query result
    for (const auto& row : result) {
        if (!row.empty()) {
            activityLog.push_back(row[0]);
        }
    }

    return activityLog;
}


bool MySQLDatabaseConnection::executePreparedStatementSync(const std::string& sql, const std::vector<std::string>& params)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the statement
    MYSQL_STMT* statement = mysql_stmt_init(mysqlConnection);
    if (!statement) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_initialize_prepared_statement") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    if (mysql_stmt_prepare(statement, sql.c_str(), sql.length()) != 0) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_prepared_statement") + std::string(mysql_error(mysqlConnection));
        mysql_stmt_close(statement);
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    // Bind the parameters
    ulong numParams = mysql_stmt_param_count(statement);
    if (numParams != params.size()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "incorrect_number_of_parameters");
        mysql_stmt_close(statement);
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    std::vector<MYSQL_BIND> bindParams(numParams);
    std::vector<std::string> paramValues(numParams);
    std::vector<ulong> paramLengths(numParams);
    std::vector<my_bool> paramIsNull(numParams);

    for (ulong i = 0; i < numParams; ++i) {
        paramValues[i] = params[i];
        paramLengths[i] = paramValues[i].length();
        paramIsNull[i] = (paramLengths[i] == 0);

        bindParams[i].buffer_type = MYSQL_TYPE_STRING;
        bindParams[i].buffer = const_cast<char*>(paramValues[i].c_str());
        bindParams[i].buffer_length = paramLengths[i];
        bindParams[i].length = &paramLengths[i];
        bindParams[i].is_null = &paramIsNull[i];
    }

    if (mysql_stmt_bind_param(statement, bindParams.data()) != 0) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_bind_parameters") + std::string(mysql_error(mysqlConnection));
        mysql_stmt_close(statement);
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    // Execute the statement
    if (mysql_stmt_execute(statement) != 0) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_execute_prepared_statement") + std::string(mysql_error(mysqlConnection));
        mysql_stmt_close(statement);
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    mysql_stmt_close(statement);
    connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
    return true;
}

std::future<bool> MySQLDatabaseConnection::executePreparedStatementAsync(const std::string& sql, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, sql, params]() {
        return executePreparedStatementSync(sql, params);
    });
}

bool MySQLDatabaseConnection::beginTransaction()
{
    const std::string sql = "BEGIN";
    return executeSync(sql);
}

bool MySQLDatabaseConnection::commitTransaction()
{
    const std::string sql = "COMMIT";
    return executeSync(sql);
}

bool MySQLDatabaseConnection::rollbackTransaction()
{
    const std::string sql = "ROLLBACK";
    return executeSync(sql);
}

bool MySQLDatabaseConnection::executeSync(const std::string& sql)
{
    auto language = createLanguageObject()->getLanguageCode();

    if (!connectionPool.isInitialized()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_bind_parameters");
        return false;
    }

    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    if (mysql_query(mysqlConnection, sql.c_str()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}


std::future<bool> MySQLDatabaseConnection::executeAsync(const std::string& sql)
{
    return std::async(std::launch::async, [this, sql]() {
        return executeSync(sql);
    });
}


bool MySQLDatabaseConnection::executeBatchSync(const std::vector<std::string>& sqlBatch)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Begin the transaction
    if (mysql_autocommit(mysqlConnection, 0) != 0) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_start_transaction") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    // Execute each statement in the batch
    for (const std::string& sql : sqlBatch) {
        if (mysql_query(mysqlConnection, sql.c_str()) != 0) {
            m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_execute_sql_statement") + std::string(mysql_error(mysqlConnection));
            mysql_rollback(mysqlConnection);  // Rollback the transaction
            connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
            return false;
        }
    }

    // Commit the transaction
    if (mysql_commit(mysqlConnection) != 0) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_commit_transaction") + std::string(mysql_error(mysqlConnection));
        mysql_rollback(mysqlConnection);  // Rollback the transaction
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
    return true;
}

std::future<bool> MySQLDatabaseConnection::executeBatchAsync(const std::vector<std::string>& sqlBatch)
{
    return std::async(std::launch::async, [this, sqlBatch]() {
        return executeBatchSync(sqlBatch);
    });
}


bool MySQLDatabaseConnection::executeProcedureSync(const std::string& procedure)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    std::string sql = "CALL " + procedure;
    return executeSync(sql);
}

std::future<bool> MySQLDatabaseConnection::executeProcedureAsync(const std::string& procedure)
{
    return std::async(std::launch::async, [this, procedure]() {
        return executeProcedureSync(procedure);
    });
}

std::vector<std::vector<std::string>> MySQLDatabaseConnection::querySync(const std::string& sql)
{
    auto language = createLanguageObject()->getLanguageCode();

    std::vector<std::vector<std::string>> queryResult;

    // Check if the query result is already cached
    if (isQueryCached(sql)) {
        return m_mysqlData.queryCache[sql];
    }

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return queryResult;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Execute the query
    if (mysql_real_query(mysqlConnection, sql.c_str(), sql.length()) != 0) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_execute_sql_query") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return queryResult;
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_retrieve_query_result") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);  // Release the connection back to the pool
        return queryResult;
    }

    // Get the number of fields in the result set
    uint numFields = mysql_num_fields(m_result);

    // Fetch each row from the result set
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(m_result))) {
        std::vector<std::string> rowResult;

        // Fetch each field value in the row
        for (uint i = 0; i < numFields; ++i) {
            // Check if the field value is NULL
            if (row[i] == __cell_nullptr) {
                rowResult.push_back("NULL");
            } else {
                rowResult.push_back(row[i]);
            }
        }

        queryResult.push_back(rowResult);
    }

    mysql_free_result(m_result);

    // Cache the query result
    m_mysqlData.cacheMutex.lock();
    m_mysqlData.queryCache[sql] = queryResult;
    m_mysqlData.cacheMutex.unlock();

    // Release the connection back to the pool
    connectionPool.releaseConnection(mysqlConnection);

    return queryResult;
}

std::future<std::vector<std::vector<std::string>>> MySQLDatabaseConnection::queryAsync(const std::string& sql)
{
    std::promise<std::vector<std::vector<std::string>>> promise;
    std::future<std::vector<std::vector<std::string>>> future = promise.get_future();

    // Check if the query result is already cached
    if (isQueryCached(sql)) {
        promise.set_value(m_mysqlData.queryCache[sql]);
        return future;
    }

    // Execute the query asynchronously
    std::thread queryThread([sql, promise = std::move(promise), this]() mutable {
        std::vector<std::vector<std::string>> queryResult;

        // Execute the query
        if (!isConnected()) {
            promise.set_value(queryResult);
            return;
        }

        if (mysql_real_query(connection, sql.c_str(), sql.length()) != 0) {
            m_mysqlData.lastError = mysql_error(connection);
            promise.set_value(queryResult);
            return;
        }

        m_result = mysql_store_result(connection);
        if (!m_result) {
            m_mysqlData.lastError = mysql_error(connection);
            promise.set_value(queryResult);
            return;
        }

        // Process the result into a vector of vector of strings
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(m_result))) {
            std::vector<std::string> rowResult;
            uint numFields = mysql_num_fields(m_result);
            for (uint i = 0; i < numFields; ++i) {
                rowResult.push_back(row[i] ? row[i] : "NULL");
            }
            queryResult.push_back(rowResult);
        }

        // Cache the query result
        std::lock_guard<std::mutex> lock(m_mysqlData.cacheMutex);
        m_mysqlData.queryCache[sql] = queryResult;

        mysql_free_result(m_result);

        promise.set_value(queryResult);
    });

    queryThread.detach();

    return future;
}


std::string MySQLDatabaseConnection::escapeString(const std::string& str)
{
    std::string escapedStr;

    // Check if connected to the MySQL server
    if (!isConnected()) {
        return escapedStr;
    }

    // Allocate memory for the escaped string
    ulong length = str.length();
    char* escapedBuffer = new char[length * 2 + 1];

    // Escape the string
    ulong escapedLength = mysql_real_escape_string(connection, escapedBuffer, str.c_str(), length);

    // Check for any errors during string escaping
    if (escapedLength == 0) {
        delete[] escapedBuffer;
        return escapedStr;
    }

    // Set the escaped string and cleanup
    escapedStr.assign(escapedBuffer, escapedLength);
    delete[] escapedBuffer;

    return escapedStr;
}


void MySQLDatabaseConnection::setConnectionTimeout(int timeoutSeconds) {
    m_mysqlData.connectionTimeout = timeoutSeconds;
    if (connection) {
        // Set the connection timeout if the connection is already established
        mysql_options(connection, MYSQL_OPT_CONNECT_TIMEOUT, &m_mysqlData.connectionTimeout);
    }
}

std::vector<std::vector<std::string>> MySQLDatabaseConnection::queryWithParamsSync(const std::string& sql, const std::vector<std::string>& params)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return {};
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Combine the SQL string and parameter values
    std::string preparedSql = sql;
    for (const std::string& param : params) {
        // Replace "?" placeholders in the SQL string with parameter values
        size_t pos = preparedSql.find("?");
        if (pos != std::string::npos) {
            preparedSql.replace(pos, 1, param);
        }
    }

    // Check if the query result is already cached
    std::unique_lock<std::mutex> lock(m_mysqlData.cacheMutex);
    if (m_mysqlData.queryCache.count(preparedSql) > 0) {
        return m_mysqlData.queryCache[preparedSql];
    }

    // Execute the query and retrieve the result
    if (mysql_real_query(mysqlConnection, preparedSql.c_str(), preparedSql.length()) != 0) {
        // Handle query execution error
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return {};
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        // Handle result retrieval error
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return {};
    }

    // Process the result into a vector of vector of strings
    std::vector<std::vector<std::string>> queryResult;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(m_result))) {
        std::vector<std::string> rowResult;
        uint numFields = mysql_num_fields(m_result);
        for (uint i = 0; i < numFields; ++i) {
            rowResult.push_back(row[i] ? row[i] : "NULL");
        }
        queryResult.push_back(rowResult);
    }

    // Cache the query result
    m_mysqlData.queryCache[preparedSql] = queryResult;

    // Release the connection back to the pool
    connectionPool.releaseConnection(mysqlConnection);

    return queryResult;
}

std::future<std::vector<std::vector<std::string>>> MySQLDatabaseConnection::queryWithParamsAsync(const std::string& sql, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, sql, params]() {
        return queryWithParamsSync(sql, params);
    });
}

std::string MySQLDatabaseConnection::sanitizeInput(const std::string& input)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the pool
    SqlConnection connection = connectionPool.getConnection();

    // Use visitor pattern to extract the MySqlPtr pointer from the SqlConnection variant
    MySqlPtr mysqlConnection = std::visit([language](auto&& arg) -> MySqlPtr {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, MySqlPtr>) {
            return arg;
        } else {
            throw std::runtime_error(safeTranslate(language, "exceptions", "invalid_connection_error"));
        }
    }, connection);

    // Allocate a buffer for the sanitized input
    std::string sanitizedInput(input.length() * 2, __cell_null_character);

    // Sanitize the input using mysql_real_escape_string
    ulong sanitizedLength = mysql_real_escape_string(mysqlConnection, sanitizedInput.data(), input.c_str(), input.length());

    // Resize the sanitized string to the actual sanitized length
    sanitizedInput.resize(sanitizedLength);

    // Release the connection back to the pool
    connectionPool.releaseConnection(connection);

    return sanitizedInput;
}

bool MySQLDatabaseConnection::executeWithParamsSync(const std::string& sql, const std::vector<std::string>& params)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the pool
    SqlConnection connection = connectionPool.getConnection();

    // Use visitor pattern to extract the MySqlPtr pointer from the SqlConnection variant
    MySqlPtr mysqlConnection = std::visit([language](auto&& arg) -> MySqlPtr {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, MySqlPtr>) {
            return arg;
        } else {
            throw std::runtime_error(safeTranslate(language, "exceptions", "invalid_connection_error"));
        }
    }, connection);

    // Combine the SQL string and parameter values
    std::string preparedSql = sql;
    for (const std::string& param : params) {
        // Replace "?" placeholders in the SQL string with parameter values
        size_t pos = preparedSql.find("?");
        if (pos != std::string::npos) {
            preparedSql.replace(pos, 1, param);
        }
    }

    // Execute the query
    if (mysql_real_query(mysqlConnection, preparedSql.c_str(), preparedSql.length()) != 0) {
        // Handle query execution error
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(connection);
        return false;
    }

    // Release the connection back to the pool
    connectionPool.releaseConnection(connection);

    return true;
}

std::future<bool> MySQLDatabaseConnection::executeWithParamsAsync(const std::string& sql, const std::vector<std::string>& params)
{
    auto language = createLanguageObject()->getLanguageCode();
    return std::async(std::launch::async, [this, sql, params, language]() {
        // Get a connection from the pool
        SqlConnection connection = connectionPool.getConnection();

        // Use visitor pattern to extract the MySqlPtr pointer from the SqlConnection variant
        MySqlPtr mysqlConnection = std::visit([language](auto&& arg) -> MySqlPtr {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, MySqlPtr>) {
                return arg;
            } else {
                throw std::runtime_error(safeTranslate(language, "exceptions", "invalid_connection_pool"));
            }
        }, connection);

        // Combine the SQL string and parameter values
        std::string preparedSql = sql;
        for (const std::string& param : params) {
            // Replace "?" placeholders in the SQL string with parameter values
            size_t pos = preparedSql.find("?");
            if (pos != std::string::npos) {
                preparedSql.replace(pos, 1, param);
            }
        }

        // Execute the query
        if (mysql_real_query(mysqlConnection, preparedSql.c_str(), preparedSql.length()) != 0) {
            // Handle query execution error
            m_mysqlData.lastError = mysql_error(mysqlConnection);
            connectionPool.releaseConnection(connection);
            return false;
        }

        // Release the connection back to the pool
        connectionPool.releaseConnection(connection);

        return true;
    });
}


bool MySQLDatabaseConnection::executeBatchWithParamsSync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the SQL statement
    MYSQL_STMT* stmt = mysql_stmt_init(mysqlConnection);
    if (!stmt) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    if (mysql_stmt_prepare(stmt, sql.c_str(), sql.length()) != 0) {
        m_mysqlData.lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    // Bind parameters and execute the batch
    for (const auto& params : paramsBatch) {
        if (params.size() > 0) {
            MYSQL_BIND bindParams[params.size()];
            std::memset(bindParams, 0, sizeof(bindParams));

            for (size_t i = 0; i < params.size(); ++i) {
                const std::string& param = params[i];
                bindParams[i].buffer_type = MYSQL_TYPE_STRING;
                bindParams[i].buffer = const_cast<char*>(param.c_str());
                bindParams[i].buffer_length = param.length();
                bindParams[i].is_null = 0;
                bindParams[i].length = __cell_nullptr;
            }

            if (mysql_stmt_bind_param(stmt, bindParams) != 0) {
                m_mysqlData.lastError = mysql_stmt_error(stmt);
                mysql_stmt_close(stmt);
                connectionPool.releaseConnection(mysqlConnection);
                return false;
            }
        }

        if (mysql_stmt_execute(stmt) != 0) {
            m_mysqlData.lastError = mysql_stmt_error(stmt);
            mysql_stmt_close(stmt);
            connectionPool.releaseConnection(mysqlConnection);
            return false;
        }

        // Reset the statement for the next batch
        mysql_stmt_reset(stmt);
    }

    // Clean up the statement
    mysql_stmt_close(stmt);

    // Release the connection back to the pool
    connectionPool.releaseConnection(mysqlConnection);

    return true;
}

std::future<bool> MySQLDatabaseConnection::executeBatchWithParamsAsync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch)
{
    auto language = createLanguageObject()->getLanguageCode();
    return std::async(std::launch::async, [this, language, sql, paramsBatch]() {
        // Get a connection from the connection pool
        SqlConnection connection = connectionPool.getConnection();
        MySqlPtr mysqlConnection = std::visit([language](auto&& arg) -> MySqlPtr {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, MySqlPtr>) {
                return arg;
            } else {
                throw std::runtime_error(safeTranslate(language, "exceptions", "invalid_connection_error"));
            }
        }, connection);

        if (!mysqlConnection) {
            m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
            return false;
        }

        // Prepare the SQL statement
        MYSQL_STMT* stmt = mysql_stmt_init(mysqlConnection);
        if (!stmt) {
            m_mysqlData.lastError = mysql_error(mysqlConnection);
            connectionPool.releaseConnection(mysqlConnection);
            return false;
        }

        if (mysql_stmt_prepare(stmt, sql.c_str(), sql.length()) != 0) {
            m_mysqlData.lastError = mysql_stmt_error(stmt);
            mysql_stmt_close(stmt);
            connectionPool.releaseConnection(mysqlConnection);
            return false;
        }

        // Bind parameters and execute the batch
        for (const auto& params : paramsBatch) {
            if (params.size() > 0) {
                MYSQL_BIND bindParams[params.size()];
                std::memset(bindParams, 0, sizeof(bindParams));

                for (size_t i = 0; i < params.size(); ++i) {
                    const std::string& param = params[i];
                    bindParams[i].buffer_type = MYSQL_TYPE_STRING;
                    bindParams[i].buffer = const_cast<char*>(param.c_str());
                    bindParams[i].buffer_length = param.length();
                    bindParams[i].is_null = 0;
                    bindParams[i].length = __cell_nullptr;
                }

                if (mysql_stmt_bind_param(stmt, bindParams) != 0) {
                    m_mysqlData.lastError = mysql_stmt_error(stmt);
                    mysql_stmt_close(stmt);
                    connectionPool.releaseConnection(mysqlConnection);
                    return false;
                }
            }

            if (mysql_stmt_execute(stmt) != 0) {
                m_mysqlData.lastError = mysql_stmt_error(stmt);
                mysql_stmt_close(stmt);
                connectionPool.releaseConnection(mysqlConnection);
                return false;
            }

            // Reset the statement for the next batch
            mysql_stmt_reset(stmt);
        }

        // Clean up the statement
        mysql_stmt_close(stmt);

        // Release the connection back to the pool
        connectionPool.releaseConnection(mysqlConnection);

        return true;
    });
}

bool MySQLDatabaseConnection::executeProcedureWithParamsSync(const std::string& procedure, const std::vector<std::string>& params)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the statement
    MYSQL_STMT* stmt = mysql_stmt_init(mysqlConnection);
    if (!stmt) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::CALL) + FROM_CELL_STRING(__cell_space) + procedure + "(";
    for (size_t i = 0; i < params.size(); ++i) {
        sql += "?";
        if (i < params.size() - 1) {
            sql += ",";
        }
    }
    sql += ")";

    if (mysql_stmt_prepare(stmt, sql.c_str(), sql.length()) != 0) {
        m_mysqlData.lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    // Bind the parameters
    std::vector<MYSQL_BIND> paramBinds(params.size());
    std::vector<std::string> paramBuffers(params.size());

    for (size_t i = 0; i < params.size(); ++i) {
        paramBuffers[i] = params[i];
        paramBinds[i].buffer_type = MYSQL_TYPE_STRING;
        paramBinds[i].buffer = (void*)paramBuffers[i].c_str();
        paramBinds[i].buffer_length = paramBuffers[i].length();
        paramBinds[i].is_null = 0;
        paramBinds[i].length = &paramBinds[i].buffer_length;
    }

    if (mysql_stmt_bind_param(stmt, paramBinds.data()) != 0) {
        m_mysqlData.lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt) != 0) {
        m_mysqlData.lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    mysql_stmt_close(stmt);
    connectionPool.releaseConnection(mysqlConnection);

    return true;
}

std::future<bool> MySQLDatabaseConnection::executeProcedureWithParamsAsync(const std::string& procedure, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, procedure, params]() {
        return executeProcedureWithParamsSync(procedure, params);
    });
}


std::vector<std::string> MySQLDatabaseConnection::getTableNames()
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    std::vector<std::string> tableNames;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return tableNames;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Execute the SHOW TABLES query
    if (mysql_real_query(mysqlConnection, engine.meta()->returnView(MYSQL_CONSTANTS::SHOW_TABLES), 11) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return tableNames;
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return tableNames;
    }

    // Process the result and extract the table names
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(m_result))) {
        tableNames.push_back(row[0]);
    }

    mysql_free_result(m_result);
    connectionPool.releaseConnection(mysqlConnection);

    return tableNames;
}


std::vector<std::string> MySQLDatabaseConnection::getTableColumns(const std::string& tableName)
{
    auto language = createLanguageObject()->getLanguageCode();

    std::vector<std::string> columnNames;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return columnNames;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the query to retrieve column names
    std::string query = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '";
    query += sanitizeInput(tableName) + "'";

    // Execute the query
    if (mysql_real_query(mysqlConnection, query.c_str(), query.length()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return columnNames;
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return columnNames;
    }

    // Process the result and extract the column names
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(m_result))) {
        columnNames.push_back(row[0]);
    }

    mysql_free_result(m_result);
    connectionPool.releaseConnection(mysqlConnection);

    return columnNames;
}


std::vector<std::string> MySQLDatabaseConnection::getTableColumnTypes(const std::string& tableName)
{
    auto language = createLanguageObject()->getLanguageCode();

    std::vector<std::string> columnTypes;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return columnTypes;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the query to retrieve column types
    std::string query = "SELECT COLUMN_TYPE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '";
    query += sanitizeInput(tableName) + "'";

    // Execute the query
    if (mysql_real_query(mysqlConnection, query.c_str(), query.length()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return columnTypes;
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return columnTypes;
    }

    // Process the result and extract the column types
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(m_result))) {
        columnTypes.push_back(row[0]);
    }

    mysql_free_result(m_result);
    connectionPool.releaseConnection(mysqlConnection);

    return columnTypes;
}

std::string MySQLDatabaseConnection::getTablePrimaryKey(const std::string& tableName)
{
    auto language = createLanguageObject()->getLanguageCode();

    std::string primaryKey;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return primaryKey;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the query to retrieve the primary key column
    std::string query = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE WHERE TABLE_NAME = '";
    query += sanitizeInput(tableName) + "' AND CONSTRAINT_NAME = 'PRIMARY'";

    // Execute the query
    if (mysql_real_query(mysqlConnection, query.c_str(), query.length()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return primaryKey;
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return primaryKey;
    }

    // Process the result and extract the primary key column
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(m_result))) {
        primaryKey = row[0];
    }

    mysql_free_result(m_result);
    connectionPool.releaseConnection(mysqlConnection);

    return primaryKey;
}


std::pair<std::string, std::string> MySQLDatabaseConnection::getTableForeignKey(const std::string& tableName, const std::string& foreignKey)
{
    auto language = createLanguageObject()->getLanguageCode();

    std::pair<std::string, std::string> foreignKeyInfo;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return foreignKeyInfo;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Prepare the query to retrieve the foreign key information
    std::string query = "SELECT COLUMN_NAME, REFERENCED_TABLE_NAME FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE WHERE TABLE_NAME = '";
    query += sanitizeInput(tableName) + "' AND CONSTRAINT_NAME = '";
    query += sanitizeInput(foreignKey) + "'";

    // Execute the query
    if (mysql_real_query(mysqlConnection, query.c_str(), query.length()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return foreignKeyInfo;
    }

    m_result = mysql_store_result(mysqlConnection);
    if (!m_result) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return foreignKeyInfo;
    }

    // Process the result and extract the foreign key details
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(m_result))) {
        foreignKeyInfo.first = row[0];                // Column name
        foreignKeyInfo.second = row[1];               // Referenced table name
    }

    mysql_free_result(m_result);
    connectionPool.releaseConnection(mysqlConnection);

    return foreignKeyInfo;
}

bool MySQLDatabaseConnection::createTable(const std::string& tableName, const std::vector<std::string>& columns)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Construct the CREATE TABLE query
    std::string query = engine.meta()->returnView(MYSQL_CONSTANTS::CREATE_TABLE) + FROM_CELL_STRING(__cell_space);
    query += sanitizeInput(tableName) + " (";
    for (const std::string& column : columns) {
        query += column + ", ";
    }
    // Remove the trailing comma and space
    query = query.substr(0, query.length() - 2);
    query += ")";

    // Execute the query
    if (mysql_real_query(mysqlConnection, query.c_str(), query.length()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}

bool MySQLDatabaseConnection::dropTable(const std::string& tableName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Construct the DROP TABLE query
    std::string query = engine.meta()->returnView(MYSQL_CONSTANTS::DROP_TABLE) + FROM_CELL_STRING(__cell_space);
    query += sanitizeInput(tableName);

    // Execute the query
    if (mysql_real_query(mysqlConnection, query.c_str(), query.length()) != 0) {
        m_mysqlData.lastError = mysql_error(mysqlConnection);
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}


bool MySQLDatabaseConnection::addColumn(const std::string& tableName, const std::string& columnName, const std::string& columnType)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Construct the ALTER TABLE query
    std::string alterQuery = "ALTER TABLE " + sanitizeInput(tableName) + " ADD COLUMN " + sanitizeInput(columnName) + " " + sanitizeInput(columnType);

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Execute the query
    std::vector<std::vector<std::string>> result = querySync(alterQuery);

    // Check if the query execution was successful
    if (result.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_add_column") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}

bool MySQLDatabaseConnection::modifyColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnType)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Construct the ALTER TABLE query
    std::string alterQuery = "ALTER TABLE " + sanitizeInput(tableName) + " MODIFY COLUMN " + sanitizeInput(columnName) + " " + sanitizeInput(newColumnType);

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Execute the query
    std::vector<std::vector<std::string>> result = querySync(alterQuery);

    // Check if the query execution was successful
    if (result.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_modify_column") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}

bool MySQLDatabaseConnection::renameColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnName)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Construct the ALTER TABLE query
    std::string alterQuery = "ALTER TABLE " + sanitizeInput(tableName) + " CHANGE " + sanitizeInput(columnName) + " " + sanitizeInput(newColumnName);

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Execute the query
    std::vector<std::vector<std::string>> result = querySync(alterQuery);

    // Check if the query execution was successful
    if (result.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_rename_column") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}

bool MySQLDatabaseConnection::deleteColumn(const std::string& tableName, const std::string& columnName)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Construct the ALTER TABLE query
    std::string alterQuery = "ALTER TABLE " + sanitizeInput(tableName) + " DROP COLUMN " + sanitizeInput(columnName);

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<MySqlPtr>(connection)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
        return false;
    }

    MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

    // Execute the query
    std::vector<std::vector<std::string>> result = querySync(alterQuery);

    // Check if the query execution was successful
    if (result.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_delete_column") + std::string(mysql_error(mysqlConnection));
        connectionPool.releaseConnection(mysqlConnection);
        return false;
    }

    connectionPool.releaseConnection(mysqlConnection);
    return true;
}

bool MySQLDatabaseConnection::optimizeIndexes()
{
    auto language = createLanguageObject()->getLanguageCode();

    // Get the list of table names
    std::vector<std::string> tableNames = getTableNames();
    if (tableNames.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_retrieve_table_names");
        return false;
    }

    // Iterate over each table and optimize its indexes
    for (const std::string& tableName : tableNames) {
        // Construct the OPTIMIZE TABLE query
        std::string optimizeQuery = "OPTIMIZE TABLE " + sanitizeInput(tableName);

        // Get a connection from the connection pool
        auto connection = connectionPool.getConnection();
        if (!std::holds_alternative<MySqlPtr>(connection)) {
            m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_connection_pool");
            return false;
        }

        MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);

        // Execute the query
        std::vector<std::vector<std::string>> result = querySync(optimizeQuery);

        // Check if the query execution was successful
        if (result.empty()) {
            m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_optimize_indexes_table") + tableName + ": " + std::string(mysql_error(mysqlConnection));
            connectionPool.releaseConnection(mysqlConnection);
            return false;
        }

        connectionPool.releaseConnection(mysqlConnection);
    }

    return true;
}


std::vector<std::string> MySQLDatabaseConnection::getExistingIndexes(const std::string& tableName)
{
    std::vector<std::string> indexNames;
    std::string sql = "SHOW INDEXES FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);

    for (const auto& row : result) {
        if (!row.empty()) {
            indexNames.push_back(row[2]);
        }
    }

    return indexNames;
}


bool MySQLDatabaseConnection::indexExists(const std::string& tableName, const std::string& indexName)
{
    std::vector<std::string> existingIndexes = getExistingIndexes(tableName);
    return std::find(existingIndexes.begin(), existingIndexes.end(), indexName) != existingIndexes.end();
}


bool MySQLDatabaseConnection::createIndex(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns)
{
    auto language = createLanguageObject()->getLanguageCode();
    // Check if the index already exists
    if (indexExists(tableName, indexName))
    {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "index_already_exist_table"), indexName, tableName);
        return false;
    }

    // Generate the SQL statement to create the index
    std::string createIndexSQL = generateCreateIndexSQL(tableName, indexName, columns);

    // Execute the SQL statement to create the index
    if (!executeSync(createIndexSQL)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_to_create_index") + getLastError();
        return false;
    }

    return true;
}

bool MySQLDatabaseConnection::dropIndex(const std::string& tableName, const std::string& indexName)
{
    auto language = createLanguageObject()->getLanguageCode();
    // Check if the index exists before dropping
    if (!indexExists(tableName, indexName)) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "index_does_not_exist_table"), indexName, tableName);
        return false;
    }

    // Generate the SQL statement to drop the index
    std::string dropIndexSQL = generateDropIndexSQL(tableName, indexName);

    // Execute the SQL statement to drop the index
    if (!executeSync(dropIndexSQL)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_to_drop_index") + getLastError();
        return false;
    }

    return true;
}

uint MySQLDatabaseConnection::getLastInsertID()
{
    // Generate the SQL statement to get the last insert ID
    std::string lastInsertIDSQL = "SELECT LAST_INSERT_ID()";

    // Execute the SQL statement and retrieve the result
    if (executeSync(lastInsertIDSQL)) {
        std::vector<std::vector<std::string>> result = querySync(lastInsertIDSQL);
        if (!result.empty() && !result[0].empty()) {
            // Convert the last insert ID from string to uinteger
            return std::stoul(result[0][0]);
        }
    }

    // Return 0 if the last insert ID retrieval failed
    return 0;
}



std::string MySQLDatabaseConnection::generateCreateIndexSQL(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns) {
    std::string createIndexSQL = "CREATE INDEX " + indexName + " ON " + tableName + " (";

    // Append the column names to the SQL statement
    for (size_t i = 0; i < columns.size(); ++i) {
        createIndexSQL += columns[i];
        if (i < columns.size() - 1) {
            createIndexSQL += ", ";
        }
    }

    createIndexSQL += ")";

    return createIndexSQL;
}

std::string MySQLDatabaseConnection::generateDropIndexSQL(const std::string& tableName, const std::string& indexName)
{
    const std::string dropIndexSQL = "ALTER TABLE " + tableName + " DROP INDEX " + indexName;
    return dropIndexSQL;
}

bool MySQLDatabaseConnection::bulkInsert(const std::string& tableName, const std::vector<std::vector<std::string>>& data)
{
    auto language = createLanguageObject()->getLanguageCode();
    // Check if the data is empty
    if (data.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "no_data_provided_for_bulk_insert");
        return false;
    }

    // Prepare the SQL statement for bulk insert
    std::string sql = "INSERT INTO " + tableName + " VALUES ";

    // Prepare the parameter values for bulk insert
    std::vector<std::string> params;
    for (const auto& row : data) {
        // Construct the row values string
        std::string rowValues;
        for (const auto& value : row) {
            rowValues += "'" + sanitizeInput(value) + "',";
        }
        // Remove the trailing comma
        rowValues.pop_back();

        // Append the row values to the SQL statement
        sql += "(" + rowValues + "),";
    }
    // Remove the trailing comma
    sql.pop_back();

    // Execute the bulk insert query
    if (!executeSync(sql)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_perform_bulk_insert") + getLastError();
        return false;
    }

    return true;
}


bool MySQLDatabaseConnection::bulkUpdate(const std::string& tableName, const std::vector<std::vector<std::string>>& data, const std::string& condition)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    // Check if the data is empty
    if (data.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "no_data_provided_bulk_update");
        return false;
    }

    // Prepare the SQL statement for bulk update
    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::UPDATE) + FROM_CELL_STRING(__cell_space) + tableName + " SET ";

    // Prepare the parameter values for bulk update
    std::vector<std::string> params;
    for (const auto& row : data) {
        // Check if the row has the correct number of values
        if (row.size() < 2) {
            m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_data_format_bulk_update");
            return false;
        }

        // Get the column name and value from the row
        const std::string& columnName = row[0];
        const std::string& columnValue = row[1];

        // Append the column name and value to the SQL statement
        sql += columnName + " = '" + sanitizeInput(columnValue) + "', ";
    }
    // Remove the trailing comma and space
    sql = sql.substr(0, sql.size() - 2);

    // Append the condition to the SQL statement
    sql += FROM_CELL_STRING(__cell_space) + engine.meta()->returnView(MYSQL_CONSTANTS::WHERE) + FROM_CELL_STRING(__cell_space) + condition;

    // Execute the bulk update query
    if (!executeSync(sql)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_perform_bulk_update") + getLastError();
        return false;
    }

    return true;
}

bool MySQLDatabaseConnection::bulkDelete(const std::string& tableName, const std::string& condition)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    // Construct the SQL statement for bulk delete
    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::DELETE_FROM)
                      + FROM_CELL_STRING(__cell_space) + tableName
                      + FROM_CELL_STRING(__cell_space) + engine.meta()->returnView(MYSQL_CONSTANTS::WHERE)
                      + FROM_CELL_STRING(__cell_space) + condition;

    // Execute the bulk delete query
    if (!executeSync(sql)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_perform_bulk_delete") + getLastError();
        return false;
    }

    return true;
}

bool MySQLDatabaseConnection::migrateData(const std::string& sourceTableName, const std::string& destinationTableName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    // Construct the SQL statement for data migration
    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::INSERT_INTO) + FROM_CELL_STRING(__cell_space) + destinationTableName + " SELECT * FROM " + sourceTableName;

    // Execute the data migration query
    if (!executeSync(sql)) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_to_migrate_data") + getLastError();
        return false;
    }

    return true;
}

std::vector<std::vector<std::string>> MySQLDatabaseConnection::queryWithPagination(const std::string& sql, int pageNumber, int pageSize)
{
    auto& engine = engineController.getEngine();
    // Calculate the offset for pagination
    int offset = (pageNumber - 1) * pageSize;

    // Append the LIMIT and OFFSET clauses to the SQL query
    std::string paginatedSql = sql + FROM_CELL_STRING(__cell_space) + engine.meta()->returnView(MYSQL_CONSTANTS::LIMIT)
                               + FROM_CELL_STRING(__cell_space) + std::to_string(pageSize)
                               + FROM_CELL_STRING(__cell_space) + engine.meta()->returnView(MYSQL_CONSTANTS::OFFSET)
                               + FROM_CELL_STRING(__cell_space) + std::to_string(offset);

    // Execute the paginated query
    std::vector<std::vector<std::string>> result = querySync(paginatedSql);

    return result;
}

std::string MySQLDatabaseConnection::getLastError()
{
    return m_mysqlData.lastError;
}


int MySQLDatabaseConnection::getRowCount(const std::string& tableName)
{
    // Generate the SQL statement to count the rows in the table
    std::string countSQL = "SELECT COUNT(*) FROM " + tableName;

    // Execute the SQL statement and retrieve the result
    if (executeSync(countSQL)) {
        std::vector<std::vector<std::string>> result = querySync(countSQL);
        if (!result.empty() && !result[0].empty()) {
            // Convert the count value from string to integer
            return std::stoi(result[0][0]);
        }
    }

    // Return -1 if the count retrieval failed
    return -1;
}


std::string MySQLDatabaseConnection::getMaxValue(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return __cell_null_str;
    }

    std::string sql = "SELECT MAX(" + columnName + ") FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }

    return __cell_null_str;
}

std::string MySQLDatabaseConnection::getMinValue(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return __cell_null_str;
    }

    std::string sql = "SELECT MIN(" + columnName + ") FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }

    return __cell_null_str;
}

double MySQLDatabaseConnection::getAverageValue(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return 0.0;
    }

    std::string sql = "SELECT AVG(" + columnName + ") FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);
    if (!result.empty() && !result[0].empty()) {
        return std::stod(result[0][0]);
    }

    return 0.0;
}

double MySQLDatabaseConnection::getSumValue(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return 0.0;
    }

    std::string sql = "SELECT SUM(" + columnName + ") FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);
    if (!result.empty() && !result[0].empty()) {
        return std::stod(result[0][0]);
    }

    return 0.0;
}

std::vector<std::string> MySQLDatabaseConnection::getDistinctValues(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    std::vector<std::string> distinctValues;

    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return distinctValues;
    }

    std::string sql = "SELECT DISTINCT " + columnName + " FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);
    for (const std::vector<std::string>& row : result) {
        if (!row.empty()) {
            distinctValues.push_back(row[0]);
        }
    }

    return distinctValues;
}

bool MySQLDatabaseConnection::executeScriptFromFile(const std::string& filename)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "failed_to_open_script_file") + filename;
        return false;
    }

    std::string line;
    std::string script;
    while (std::getline(file, line)) {
        script += line + __cell_newline;
    }

    file.close();

    return executeSync(script);
}

bool MySQLDatabaseConnection::backupDatabase(const std::string& backupFilename)
{
    // Build the command to execute
    std::string command = "mysqldump -u <username> -h <hostname> -P <port> -p<password> <database> > " + backupFilename;

    // Execute the command
    int result = std::system(command.c_str());

    // Check the result of the command execution
    if (result == 0) {
        // Backup successful
        return true;
    } else {
        // Backup failed
        return false;
    }
}

bool MySQLDatabaseConnection::restoreDatabase(const std::string& backupFilename)
{
    // Build the command to execute
    std::string command = "mysql -u <username> -p<password> -h <hostname> -P <port> <database> < " + backupFilename;

    // Execute the command
    int result = std::system(command.c_str());

    // Check the result of the command execution
    if (result == 0) {
        // Restoration successful
        return true;
    } else {
        // Restoration failed
        return false;
    }
}


std::vector<std::string> MySQLDatabaseConnection::getDatabaseList()
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    std::vector<std::string> databaseList;

    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return databaseList;
    }

    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::SHOW_DATABASE);
    std::vector<std::vector<std::string>> result = querySync(sql);
    for (const std::vector<std::string>& row : result) {
        if (!row.empty()) {
            databaseList.push_back(row[0]);
        }
    }

    return databaseList;
}

bool MySQLDatabaseConnection::createDatabase(const std::string& databaseName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }
    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::CREATE_DATABASE) + FROM_CELL_STRING(__cell_space) + databaseName;
    return executeSync(sql);
}

bool MySQLDatabaseConnection::dropDatabase(const std::string& databaseName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::DROP_DATABASE)
                      + FROM_CELL_STRING(__cell_space) + databaseName;
    return executeSync(sql);
}

bool MySQLDatabaseConnection::grantPrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    std::string privStr = __cell_null_str;
    for (const std::string& privilege : privileges) {
        privStr += privilege + ",";
    }
    privStr = privStr.substr(0, privStr.length() - 1);  // Remove trailing comma

    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::GRANT) + FROM_CELL_STRING(__cell_space) + privStr + " ON " + databaseName + ".* TO '" + username + "'@'localhost'";
    return executeSync(sql);
}

bool MySQLDatabaseConnection::revokePrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    std::string privStr = __cell_null_str;
    for (const std::string& privilege : privileges) {
        privStr += privilege + ",";
    }
    privStr = privStr.substr(0, privStr.length() - 1);  // Remove trailing comma

    std::string sql = engine.meta()->returnView(MYSQL_CONSTANTS::REVOKE)
                      + FROM_CELL_STRING(__cell_space) + privStr + " ON " + databaseName + ".* FROM '" + username + "'@'localhost'";
    return executeSync(sql);
}

int MySQLDatabaseConnection::getTableSize(const std::string& tableName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return -1;
    }

    std::string sql = "SELECT COUNT(*) FROM " + tableName;
    std::vector<std::vector<std::string>> result = querySync(sql);
    if (!result.empty() && !result[0].empty()) {
        return std::stoi(result[0][0]);
    }

    return -1;
}

void MySQLDatabaseConnection::executeNonQuery(const std::string& sql)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return;
    }

    executeSync(sql);
}

void MySQLDatabaseConnection::importTable(const std::string& tableName, const std::string& filePath)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return;
    }

    std::string sql = "LOAD DATA INFILE '" + filePath + "' INTO TABLE " + tableName;
    executeSync(sql);
}

void MySQLDatabaseConnection::exportTable(const std::string& tableName, const std::string& filePath)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_mysqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(MYSQL_CONSTANTS::DRIVER_NAME));
        return;
    }

    std::string sql = "SELECT * INTO OUTFILE '" + filePath + "' FROM " + tableName;
    executeSync(sql);
}

bool MySQLDatabaseConnection::validateSqlQuery(const std::string& query)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    // Check if the query is empty
    if (query.empty()) {        
        m_mysqlData.lastError = "SQL query is empty.";
        return false;
    }

    // Check for any potentially harmful keywords or statements
    // For example, let's check for "DROP", "DELETE", and "TRUNCATE" statements
    std::string upperQuery = query;
    std::transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);
    if (upperQuery.find("DROP") != std::string::npos || upperQuery.find("DELETE") != std::string::npos || upperQuery.find("TRUNCATE") != std::string::npos)
    {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "invalid_sql_query_harmful");
        return false;
    }

    // You can add more specific checks based on your requirements
    // For example, validating table or column names, checking for specific patterns, etc.

    // If the query passes all checks, it is considered valid
    return true;
}

bool MySQLDatabaseConnection::validateParams(const std::vector<std::string>& params)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Check if the parameters vector is empty
    if (params.empty()) {
        m_mysqlData.lastError = safeTranslate(language, "exceptions", "query_parameters_are_empty");
        return false;
    }

    // Iterate over each parameter and perform validation checks
    for (const std::string& param : params) {
        // Check if a parameter is empty
        if (param.empty()) {
            m_mysqlData.lastError = safeTranslate(language, "exceptions", "empty_query_parameter_detected");
            return false;
        }

        // Add more specific checks based on your requirements
        // For example, validating data types, length restrictions, patterns, etc.
        // You may consider using regular expressions or dedicated validation libraries for more complex validations.
    }

    // If all parameters pass the validation checks, they are considered valid
    return true;
}

CELL_NAMESPACE_END

#endif
