#if __has_include("psql.hpp")
#   include "psql.hpp"
#else
#   error "Cell's "psql.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if defined(USE_POSTGRESQL)

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Database)

void* PostgreSqlDatabaseConnection::get()
{
    auto connection = connectionPool.getConnection();
    if (std::holds_alternative<PostgreSqlPtr>(connection)) {
        return static_cast<void*>(std::get<PostgreSqlPtr>(connection));
    } else {
        throw Exception(Exception::Reason::Database, "Invalid connection type").getRuntimeError();
    }
}

PostgreSqlDatabaseConnection::PostgreSqlDatabaseConnection(PostgreSqlConnectionPool& connectionPool)
    : connectionPool(connectionPool), connection(__cell_nullptr)
{
}

PostgreSqlDatabaseConnection::~PostgreSqlDatabaseConnection()
{
    disconnect();
}

bool PostgreSqlDatabaseConnection::connect()
{
    if (isConnected()) {
        return true;
    }

    if (connectionPool.m_poolData.host.has_value()
        && connectionPool.m_poolData.port > 0
        && connectionPool.m_poolData.database.has_value()
        && connectionPool.m_poolData.user.has_value()
        && connectionPool.m_poolData.password.has_value()) {

        std::string connectionString = "host=" + connectionPool.m_poolData.host.value() + " port=" + std::to_string(connectionPool.m_poolData.port) + " dbname=" + connectionPool.m_poolData.database.value() + " user=" + connectionPool.m_poolData.user.value() + " password=" + connectionPool.m_poolData.password.value();

        if (connectionPool.m_poolData.keyPath.has_value()
            && connectionPool.m_poolData.certPath.has_value()
            && connectionPool.m_poolData.caPath.has_value()) {

            connectionString += " sslmode=require sslcert=" + connectionPool.m_poolData.certPath.value() + " sslkey=" + connectionPool.m_poolData.keyPath.value() + " sslrootcert=" + connectionPool.m_poolData.caPath.value();
        }

        connection = PQconnectdb(connectionString.c_str());

        if (PQstatus(connection) != CONNECTION_OK) {
            // Handle connection error
            m_PostgreSqlData.lastError = PQerrorMessage(connection);
            PQfinish(connection);
            connection = nullptr;
            return false;
        }

        return true;
    }

    return false;
}


bool PostgreSqlDatabaseConnection::disconnect()
{
    if (connection) {
        connectionPool.releaseConnection(connection);
        connection = __cell_nullptr;
    }
    return true;
}

std::future<bool> PostgreSqlDatabaseConnection::connectAsync()
{
    // Use std::async to run the connect function asynchronously
    std::future<bool> future = std::async(std::launch::async, [this]() {
        return connect();
    });

    // Return the future to the caller
    return future;
}

std::future<bool> PostgreSqlDatabaseConnection::disconnectAsync()
{
    // Use std::async to run the disconnect function asynchronously
    std::future<bool> future = std::async(std::launch::async, [this]() {
        return disconnect();
    });

    // Return the future to the caller
    return future;
}

bool PostgreSqlDatabaseConnection::isConnected()
{
    return connection != __cell_nullptr && PQstatus(connection) == 0;
}

bool PostgreSqlDatabaseConnection::isQueryCached(const std::string& sql)
{
    std::unique_lock<std::mutex> lock(m_PostgreSqlData.cacheMutex);
    return m_PostgreSqlData.queryCache.count(sql) > 0;
}


bool PostgreSqlDatabaseConnection::isConnectionAlive()
{
    if (!isConnected()) {
        return false; // Not connected
    }

    PostgreSqlPtr pgConn = connection;
    return pgConn != nullptr;
}

int PostgreSqlDatabaseConnection::getActiveConnectionsCount()
{
    if (!isConnected()) {
        return 0;
    }

    int activeConnections = 0;

    // Access the connection pool's data to count active connections
    std::lock_guard<std::mutex> lock(connectionPool.m_poolData.mutex);
    for (const auto& connection : connectionPool.m_poolData.connections) {
        if (std::holds_alternative<PGconn*>(connection)) {
            PGconn* pgConnection = std::get<PGconn*>(connection);
            if (pgConnection != nullptr && PQstatus(pgConnection) == CONNECTION_OK) {
                activeConnections++;
            }
        }
    }

    return activeConnections;
}


std::string PostgreSqlDatabaseConnection::getConnectionHealthStatus()
{
    if (connection == __cell_nullptr) {
        return "Not connected to the PostgreSQL server.";
    }

    ConnStatusType status = PQstatus(connection);
    if (status == CONNECTION_OK) {
        return "Connection is healthy.";
    } else {
        return "Connection is unhealthy.";
    }
}

int PostgreSqlDatabaseConnection::getMaxConnectionsCount()
{
    if (connection == __cell_nullptr) {
        return -1; // Connection is not established
    }

    const char* maxConnectionsStr = PQparameterStatus(connection, "max_connections");
    if (maxConnectionsStr == __cell_nullptr) {
        return -1; // Failed to retrieve max_connections parameter
    }

    int maxConnections = std::atoi(maxConnectionsStr);
    return maxConnections;
}

std::string PostgreSqlDatabaseConnection::getDatabaseServerVersion()
{
    if (connection == __cell_nullptr) {
        return "Not connected to the PostgreSQL server.";
    }

    int serverVersion = PQserverVersion(connection);
    if (serverVersion == 0) {
        return "Failed to retrieve server version.";
    }

    std::string versionString = std::to_string(serverVersion);
    return versionString;
}

std::map<std::string, std::string> PostgreSqlDatabaseConnection::getConnectionStatistics()
{
    std::map<std::string, std::string> statistics;

    if (connection == __cell_nullptr) {
        statistics["error"] = "Not connected to the PostgreSQL server.";
        return statistics;
    }

    // Retrieve the connection statistics
    const char* paramNames[] = {
        "backend_start",
        "backend_xmin",
        "backend_xmin_epoch",
        "backend_pid",
        "backend_database",
        // Add more parameters as needed
    };

    int numParams = sizeof(paramNames) / sizeof(paramNames[0]);

    for (int i = 0; i < numParams; i++) {
        const char* paramName = paramNames[i];
        const char* paramValue = PQparameterStatus(connection, paramName);
        if (paramValue != __cell_nullptr) {
            statistics[paramName] = paramValue;
        }
    }

    return statistics;
}

std::chrono::seconds PostgreSqlDatabaseConnection::getConnectionUptime()
{
    if (connection == __cell_nullptr) {
        // Return 0 seconds if not connected
        return std::chrono::seconds(0);
    }

    // Get the connection creation timestamp
    time_t connectionTime = PQconnectPoll(connection);

    if (connectionTime == (time_t)-1) {
        // Failed to retrieve the connection time
        // Return 0 seconds as the default value
        return std::chrono::seconds(0);
    }

    // Calculate the connection uptime
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point connectionTimePoint = std::chrono::system_clock::from_time_t(connectionTime);
    std::chrono::seconds uptime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - connectionTimePoint);

    return uptime;
}

std::vector<std::string> PostgreSqlDatabaseConnection::getConnectionActivityLog()
{
    std::vector<std::string> activityLog;

    if (connection == __cell_nullptr) {
        // Return an empty activity log if not connected
        return activityLog;
    }

    // Execute the query to retrieve the activity log
    PGresult* result = PQexec(connection, "SELECT * FROM pg_stat_activity");
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        // Failed to execute the query, return an empty activity log
        PQclear(result);
        return activityLog;
    }

    // Retrieve the number of rows and columns in the result
    int rowCount = PQntuples(result);
    int columnCount = PQnfields(result);

    // Iterate over the rows and columns to populate the activity log
    for (int row = 0; row < rowCount; ++row) {
        std::string activityEntry;
        for (int col = 0; col < columnCount; ++col) {
            const char* value = PQgetvalue(result, row, col);
            if (value != __cell_nullptr) {
                activityEntry += value;
                activityEntry += " ";
            }
        }
        activityLog.push_back(activityEntry);
    }

    // Clean up the result
    PQclear(result);

    return activityLog;
}

bool PostgreSqlDatabaseConnection::executePreparedStatementSync(const std::string& sql, const std::vector<std::string>& params)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Invalid connection from the pool
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the prepared statement query
    std::string preparedStatement = "PREPARE statement_name AS " + sql;

    // Execute the prepare statement
    PGresult* prepareResult = PQexec(postgreSqlConnection, preparedStatement.c_str());
    if (PQresultStatus(prepareResult) != PGRES_COMMAND_OK) {
        // Failed to prepare the statement
        PQclear(prepareResult);
        connectionPool.releaseConnection(postgreSqlConnection);
        return false;
    }
    PQclear(prepareResult);

    // Construct the parameter binding query
    std::string bindParamsQuery = "EXECUTE statement_name (";
    for (size_t i = 0; i < params.size(); ++i) {
        if (i > 0) {
            bindParamsQuery += ", ";
        }
        bindParamsQuery += "'" + params[i] + "'";
    }
    bindParamsQuery += ")";

    // Execute the parameter binding query
    PGresult* bindParamsResult = PQexec(postgreSqlConnection, bindParamsQuery.c_str());
    if (PQresultStatus(bindParamsResult) != PGRES_COMMAND_OK) {
        // Failed to bind the parameters
        PQclear(bindParamsResult);
        connectionPool.releaseConnection(postgreSqlConnection);
        return false;
    }
    PQclear(bindParamsResult);

    // Deallocate the prepared statement
    PGresult* deallocateResult = PQexec(postgreSqlConnection, "DEALLOCATE statement_name");
    if (PQresultStatus(deallocateResult) != PGRES_COMMAND_OK) {
        // Failed to deallocate the prepared statement
        PQclear(deallocateResult);
        connectionPool.releaseConnection(postgreSqlConnection);
        return false;
    }
    PQclear(deallocateResult);

    // Release the connection back to the pool
    connectionPool.releaseConnection(postgreSqlConnection);

    // The prepared statement execution was successful
    return true;
}

std::future<bool> PostgreSqlDatabaseConnection::executePreparedStatementAsync(const std::string& sql, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, sql, params]() {
        return executePreparedStatementSync(sql, params);
    });
}

bool PostgreSqlDatabaseConnection::beginTransaction()
{
    const std::string sql = "BEGIN";
    return executeSync(sql);
}

bool PostgreSqlDatabaseConnection::commitTransaction()
{
    const std::string sql = "COMMIT";
    return executeSync(sql);
}

bool PostgreSqlDatabaseConnection::rollbackTransaction()
{
    const std::string sql = "ROLLBACK";
    return executeSync(sql);
}

bool PostgreSqlDatabaseConnection::executeSync(const std::string& sql)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection))
    {
        // Failed to acquire a valid connection from the pool
        // Handle the error accordingly
        return false;
    }

    PostgreSqlPtr postgresConnection = std::get<PostgreSqlPtr>(connection);

    // Execute the SQL statement
    PGresult* result = PQexec(postgresConnection, sql.c_str());

    if (PQresultStatus(result) == PGRES_COMMAND_OK)
    {
        PQclear(result);

        // Release the connection back to the pool
        connectionPool.releaseConnection(postgresConnection);

        return true; // SQL statement executed successfully
    }
    else
    {
        // Handle the error if the SQL statement failed to execute
        const char* errorMessage = PQerrorMessage(postgresConnection);
        // You can set an error message or perform additional error handling here
        PQclear(result);

        // Release the connection back to the pool
        connectionPool.releaseConnection(postgresConnection);

        return false;
    }
}

std::future<bool> PostgreSqlDatabaseConnection::executeAsync(const std::string& sql)
{
    return std::async(std::launch::async, [this, sql]() {
        return executeSync(sql);
    });
}

bool PostgreSqlDatabaseConnection::executeBatchSync(const std::vector<std::string>& sqlBatch)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection))
    {
        // Failed to acquire a valid connection from the pool
        // Handle the error accordingly
        return false;
    }

    PostgreSqlPtr postgresConnection = std::get<PostgreSqlPtr>(connection);

    // Start a transaction
    PQexec(postgresConnection, "BEGIN");

    // Execute each SQL statement in the batch
    for (const std::string& sql : sqlBatch)
    {
        PGresult* result = PQexec(postgresConnection, sql.c_str());

        if (PQresultStatus(result) != PGRES_COMMAND_OK)
        {
            // Handle the error if any statement failed to execute
            const char* errorMessage = PQerrorMessage(postgresConnection);
            // You can set an error message or perform additional error handling here
            PQclear(result);

            // Rollback the transaction
            PQexec(postgresConnection, "ROLLBACK");

            // Release the connection back to the pool
            connectionPool.releaseConnection(postgresConnection);

            return false;
        }

        PQclear(result);
    }

    // Commit the transaction
    PQexec(postgresConnection, "COMMIT");

    // Release the connection back to the pool
    connectionPool.releaseConnection(postgresConnection);

    return true; // All SQL statements executed successfully
}

std::future<bool> PostgreSqlDatabaseConnection::executeBatchAsync(const std::vector<std::string>& sqlBatch)
{
    return std::async(std::launch::async, [this, sqlBatch]() {
        return executeBatchSync(sqlBatch);
    });
}


bool PostgreSqlDatabaseConnection::executeProcedureSync(const std::string& procedure)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection))
    {
        // Failed to acquire a valid connection from the pool
        // Handle the error accordingly
        return false;
    }

    PostgreSqlPtr postgresConnection = std::get<PostgreSqlPtr>(connection);

    // Execute the stored procedure
    PGresult* result = PQexec(postgresConnection, procedure.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        // Handle the error if the procedure failed to execute
        const char* errorMessage = PQerrorMessage(postgresConnection);
        // You can set an error message or perform additional error handling here
        PQclear(result);

        // Release the connection back to the pool
        connectionPool.releaseConnection(postgresConnection);

        return false;
    }

    PQclear(result);

    // Release the connection back to the pool
    connectionPool.releaseConnection(postgresConnection);

    return true; // The procedure executed successfully
}


std::future<bool> PostgreSqlDatabaseConnection::executeProcedureAsync(const std::string& procedure)
{
    return std::async(std::launch::async, [this, procedure]() {
        return executeProcedureSync(procedure);
    });
}

std::vector<std::vector<std::string>> PostgreSqlDatabaseConnection::querySync(const std::string& sql)
{
    std::vector<std::vector<std::string>> result;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        return result;  // Invalid connection
    }

    PostgreSqlPtr postgresqlConnection = std::get<PostgreSqlPtr>(connection);

    // Execute the SQL query
    PGresult* queryResult = PQexec(postgresqlConnection, sql.c_str());

    // Check if the query execution was successful
    if (PQresultStatus(queryResult) != PGRES_TUPLES_OK) {
        // Query execution failed
        PQclear(queryResult);
        connectionPool.releaseConnection(postgresqlConnection);
        return result;
    }

    // Get the number of rows and columns in the result set
    int numRows = PQntuples(queryResult);
    int numCols = PQnfields(queryResult);

    // Fetch the column names
    std::vector<std::string> columnNames;
    for (int col = 0; col < numCols; ++col) {
        columnNames.push_back(PQfname(queryResult, col));
    }
    result.push_back(columnNames);

    // Fetch the row data
    for (int row = 0; row < numRows; ++row) {
        std::vector<std::string> rowData;
        for (int col = 0; col < numCols; ++col) {
            rowData.push_back(PQgetvalue(queryResult, row, col));
        }
        result.push_back(rowData);
    }

    // Release the query result
    PQclear(queryResult);

    // Release the connection back to the pool
    connectionPool.releaseConnection(postgresqlConnection);

    return result;
}

std::future<std::vector<std::vector<std::string>>> PostgreSqlDatabaseConnection::queryAsync(const std::string& sql)
{
    return std::async(std::launch::async, [this, sql]() {
        return querySync(sql);
    });
}

std::string PostgreSqlDatabaseConnection::escapeString(const std::string& str)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection pool error
        return "";
    }

    PostgreSqlPtr pgConnection = std::get<PostgreSqlPtr>(connection);

    // Allocate memory for the escaped string
    std::unique_ptr<char, decltype(&PQfreemem)> escapedStr(
        PQescapeLiteral(pgConnection, str.c_str(), str.length()), &PQfreemem);

    if (!escapedStr) {
        // Handle escaping error
        return "";
    }

    // Convert the escaped string to std::string
    std::string escapedString(escapedStr.get());

    // Release the connection back to the pool
    connectionPool.releaseConnection(pgConnection);

    return escapedString;
}

void PostgreSqlDatabaseConnection::setConnectionTimeout(int timeoutSeconds)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection pool error
        return;
    }

    PostgreSqlPtr pgConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the SET statement to update the statement_timeout
    std::string setStatement = "SET statement_timeout = " + std::to_string(timeoutSeconds * 1000);

    // Execute the SET statement
    PGresult* result = PQexec(pgConnection, setStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle error in executing the SET statement
        PQclear(result);
        return;
    }

    // Release the connection back to the pool
    connectionPool.releaseConnection(pgConnection);
}

std::vector<std::vector<std::string>> PostgreSqlDatabaseConnection::queryWithParamsSync(const std::string& sql, const std::vector<std::string>& params)
{
    std::vector<std::vector<std::string>> resultRows;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection pool error
        return resultRows;
    }

    PostgreSqlPtr pgConnection = std::get<PostgreSqlPtr>(connection);

    // Prepare the statement
    const char* stmtName = "";
    int numParams = static_cast<int>(params.size());
    const Oid* paramTypes = nullptr;
    const int* paramLengths = nullptr;
    const int* paramFormats = nullptr;
    int resultFormat = 0;  // 0 means text format
    PGresult* prepareResult = PQprepare(pgConnection, stmtName, sql.c_str(), numParams, paramTypes);
    if (PQresultStatus(prepareResult) != PGRES_COMMAND_OK) {
        // Handle error in preparing the statement
        PQclear(prepareResult);
        connectionPool.releaseConnection(pgConnection);
        return resultRows;
    }
    PQclear(prepareResult);

    // Convert the parameters to an array of const char*
    std::vector<const char*> paramValues(params.size());
    std::vector<int> paramLengthsVec(params.size());
    std::vector<int> paramFormatsVec(params.size(), 0);  // 0 means text format
    for (size_t i = 0; i < params.size(); ++i) {
        paramValues[i] = params[i].c_str();
        paramLengthsVec[i] = static_cast<int>(params[i].length());
    }

    // Execute the statement with the parameters
    PGresult* execResult = PQexecPrepared(pgConnection, stmtName, numParams, paramValues.data(), paramLengthsVec.data(), paramFormatsVec.data(), resultFormat);
    if (PQresultStatus(execResult) != PGRES_TUPLES_OK) {
        // Handle error in executing the statement
        PQclear(execResult);
        connectionPool.releaseConnection(pgConnection);
        return resultRows;
    }

    // Fetch the result rows and store them in the resultRows vector
    int numRows = PQntuples(execResult);
    int numCols = PQnfields(execResult);

    for (int row = 0; row < numRows; ++row) {
        std::vector<std::string> resultRow;
        for (int col = 0; col < numCols; ++col) {
            char* value = PQgetvalue(execResult, row, col);
            resultRow.push_back(value ? value : "");
        }
        resultRows.push_back(resultRow);
    }

    PQclear(execResult);

    // Release the connection back to the pool
    connectionPool.releaseConnection(pgConnection);

    return resultRows;
}

std::future<std::vector<std::vector<std::string>>> PostgreSqlDatabaseConnection::queryWithParamsAsync(const std::string& sql, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, sql, params]() {
        return queryWithParamsSync(sql, params);
    });
}

std::string PostgreSqlDatabaseConnection::sanitizeInput(const std::string& input)
{
    // Create a prepared statement with a placeholder for the input value
    const std::string sql = "SELECT $1";

    // Prepare the statement
    PGresult* prepareResult = PQprepare(connection, "", sql.c_str(), 1, NULL);
    if (PQresultStatus(prepareResult) != PGRES_COMMAND_OK) {
        PQclear(prepareResult);
        // Handle the error, return an error message, or throw an exception
        return "Failed to prepare statement";
    }
    PQclear(prepareResult);

    // Create a parameter array with the sanitized input
    const char* paramValues[1] = { input.c_str() };
    const int paramLengths[1] = { static_cast<int>(input.length()) };
    const int paramFormats[1] = { 0 };

    // Execute the prepared statement with the sanitized input
    PGresult* executeResult = PQexecPrepared(connection, "", 1, paramValues, paramLengths, paramFormats, 0);
    if (PQresultStatus(executeResult) != PGRES_TUPLES_OK) {
        PQclear(executeResult);
        // Handle the error, return an error message, or throw an exception
        return "Failed to execute statement";
    }

    // Get the sanitized output from the result
    const char* sanitizedValue = PQgetvalue(executeResult, 0, 0);
    std::string sanitizedInput(sanitizedValue);

    PQclear(executeResult);

    return sanitizedInput;
}

bool PostgreSqlDatabaseConnection::executeWithParamsSync(const std::string& sql, const std::vector<std::string>& params)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle the error, return false, or throw an exception
        return false;
    }

    PostgreSqlPtr postgresqlConnection = std::get<PostgreSqlPtr>(connection);

    // Convert the parameter values to const char* array
    std::vector<const char*> paramValues;
    std::vector<int> paramLengths;
    std::vector<int> paramFormats;
    for (const std::string& param : params) {
        paramValues.push_back(param.c_str());
        paramLengths.push_back(static_cast<int>(param.length()));
        paramFormats.push_back(1); // Binary format
    }

    // Execute the SQL statement with the parameters
    PGresult* result = PQexecParams(postgresqlConnection, sql.c_str(), params.size(), NULL, paramValues.data(), paramLengths.data(), paramFormats.data(), 0);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        PQclear(result);
        connectionPool.releaseConnection(postgresqlConnection);  // Release the connection back to the pool
        // Handle the error, return false, or throw an exception
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgresqlConnection);  // Release the connection back to the pool
    return true;
}

std::future<bool> PostgreSqlDatabaseConnection::executeWithParamsAsync(const std::string& sql, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, sql, params]() {
        return executeWithParamsSync(sql, params);
    });
}

bool PostgreSqlDatabaseConnection::executeBatchWithParamsSync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection from the pool
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Begin the transaction
    if (PQtransactionStatus(postgreSqlConnection) != PQTRANS_ACTIVE) {
        if (PQexec(postgreSqlConnection, "BEGIN") == nullptr) {
            // Handle transaction start failure
            connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
            return false;
        }
    }

    // Prepare the statement
    PGresult* result = PQprepare(postgreSqlConnection, "", sql.c_str(), 0, nullptr);
    if (result == nullptr || PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle statement preparation failure
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }
    PQclear(result);

    // Execute the prepared statement for each set of parameters in the batch
    for (const auto& params : paramsBatch) {
        const int paramCount = params.size();
        const char** paramValues = new const char*[paramCount];
        int* paramLengths = new int[paramCount];
        int* paramFormats = new int[paramCount];

        for (int i = 0; i < paramCount; ++i) {
            paramValues[i] = params[i].c_str();
            paramLengths[i] = params[i].length();
            paramFormats[i] = 0;  // Treat all parameters as text
        }

        result = PQexecPrepared(postgreSqlConnection, "", paramCount, paramValues, paramLengths, paramFormats, 0);
        delete[] paramValues;
        delete[] paramLengths;
        delete[] paramFormats;

        if (result == nullptr || PQresultStatus(result) != PGRES_COMMAND_OK) {
            // Handle statement execution failure
            PQclear(result);
            connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
            return false;
        }
        PQclear(result);
    }

    // Commit the transaction
    if (PQtransactionStatus(postgreSqlConnection) == PQTRANS_ACTIVE) {
        if (PQexec(postgreSqlConnection, "COMMIT") == nullptr) {
            // Handle transaction commit failure
            connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
            return false;
        }
    }

    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

std::future<bool> PostgreSqlDatabaseConnection::executeBatchWithParamsAsync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch)
{
    return std::async(std::launch::async, [this, sql, paramsBatch]() {
        return executeBatchWithParamsSync(sql, paramsBatch);
    });
}

bool PostgreSqlDatabaseConnection::executeProcedureWithParamsSync(const std::string& procedure, const std::vector<std::string>& params)
{
    // Construct the parameterized SQL statement
    std::string sql = "CALL " + procedure + "(";
    for (size_t i = 0; i < params.size(); ++i) {
        if (i > 0) {
            sql += ", ";
        }
        sql += "'" + escapeString(params[i]) + "'";
    }
    sql += ")";

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Execute the procedure
    auto result = PQexec(postgreSqlConnection, sql.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle execution error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    // Check if any rows were returned
    if (PQntuples(result) > 0) {
        // Handle returned rows if necessary
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

std::future<bool> PostgreSqlDatabaseConnection::executeProcedureWithParamsAsync(const std::string& procedure, const std::vector<std::string>& params)
{
    return std::async(std::launch::async, [this, procedure, params]() {
        return executeProcedureWithParamsSync(procedure, params);
    });
}

std::vector<std::string> PostgreSqlDatabaseConnection::getTableNames()
{
    std::vector<std::string> tableNames;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return tableNames;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Retrieve the table names using a query
    std::string query = "SELECT table_name FROM information_schema.tables WHERE table_schema = 'public'";

    auto result = PQexec(postgreSqlConnection, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return tableNames;
    }

    int rowCount = PQntuples(result);
    for (int i = 0; i < rowCount; ++i) {
        char* tableName = PQgetvalue(result, i, 0);
        tableNames.push_back(tableName);
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return tableNames;
}

std::vector<std::string> PostgreSqlDatabaseConnection::getTableColumns(const std::string& tableName)
{
    std::vector<std::string> columnNames;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return columnNames;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Retrieve the column names using a query
    std::string query = "SELECT column_name FROM information_schema.columns WHERE table_name = '" + tableName + "'";

    auto result = PQexec(postgreSqlConnection, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return columnNames;
    }

    int rowCount = PQntuples(result);
    for (int i = 0; i < rowCount; ++i) {
        char* columnName = PQgetvalue(result, i, 0);
        columnNames.push_back(columnName);
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return columnNames;
}

std::vector<std::string> PostgreSqlDatabaseConnection::getTableColumnTypes(const std::string& tableName)
{
    std::vector<std::string> columnTypes;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return columnTypes;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Retrieve the column types using a query
    std::string query = "SELECT data_type FROM information_schema.columns WHERE table_name = '" + tableName + "'";

    auto result = PQexec(postgreSqlConnection, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return columnTypes;
    }

    int rowCount = PQntuples(result);
    for (int i = 0; i < rowCount; ++i) {
        char* columnType = PQgetvalue(result, i, 0);
        columnTypes.push_back(columnType);
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return columnTypes;
}

std::string PostgreSqlDatabaseConnection::getTablePrimaryKey(const std::string& tableName)
{
    std::string primaryKey;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return primaryKey;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Retrieve the primary key using a query
    std::string query = "SELECT column_name FROM information_schema.key_column_usage WHERE table_name = '" + tableName + "' AND constraint_name LIKE '%_pkey'";

    auto result = PQexec(postgreSqlConnection, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return primaryKey;
    }

    int rowCount = PQntuples(result);
    if (rowCount > 0) {
        primaryKey = PQgetvalue(result, 0, 0);
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return primaryKey;
}


std::pair<std::string, std::string> PostgreSqlDatabaseConnection::getTableForeignKey(const std::string& tableName, const std::string& foreignKey)
{
    std::pair<std::string, std::string> foreignKeyInfo;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return foreignKeyInfo;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Retrieve foreign key information using a query
    std::string query = "SELECT conname, conrelid::regclass, confrelid::regclass FROM pg_constraint WHERE conname = '" + foreignKey + "' AND conrelid::regclass = '" + tableName + "'";

    auto result = PQexec(postgreSqlConnection, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return foreignKeyInfo;
    }

    int rowCount = PQntuples(result);
    if (rowCount > 0) {
        foreignKeyInfo.first = PQgetvalue(result, 0, 0);  // Constraint name
        foreignKeyInfo.second = PQgetvalue(result, 0, 2);  // Referenced table name
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return foreignKeyInfo;
}

bool PostgreSqlDatabaseConnection::createTable(const std::string& tableName, const std::vector<std::string>& columns)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the CREATE TABLE statement
    std::string createStatement = "CREATE TABLE " + tableName + " (";
    for (const std::string& column : columns) {
        createStatement += column + ", ";
    }
    // Remove the trailing comma and space
    createStatement = createStatement.substr(0, createStatement.length() - 2);
    createStatement += ")";

    // Execute the CREATE TABLE statement
    auto result = PQexec(postgreSqlConnection, createStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

bool PostgreSqlDatabaseConnection::dropTable(const std::string& tableName)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the DROP TABLE statement
    std::string dropStatement = "DROP TABLE IF EXISTS " + tableName;

    // Execute the DROP TABLE statement
    auto result = PQexec(postgreSqlConnection, dropStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

bool PostgreSqlDatabaseConnection::addColumn(const std::string& tableName, const std::string& columnName, const std::string& columnType)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the ALTER TABLE statement to add the column
    std::string alterStatement = "ALTER TABLE " + tableName + " ADD COLUMN " + columnName + " " + columnType;

    // Execute the ALTER TABLE statement
    auto result = PQexec(postgreSqlConnection, alterStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

bool PostgreSqlDatabaseConnection::modifyColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnType)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the ALTER TABLE statement to modify the column type
    std::string alterStatement = "ALTER TABLE " + tableName + " ALTER COLUMN " + columnName + " TYPE " + newColumnType;

    // Execute the ALTER TABLE statement
    auto result = PQexec(postgreSqlConnection, alterStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

bool PostgreSqlDatabaseConnection::renameColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnName)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the ALTER TABLE statement to rename the column
    std::string alterStatement = "ALTER TABLE " + tableName + " RENAME COLUMN " + columnName + " TO " + newColumnName;

    // Execute the ALTER TABLE statement
    auto result = PQexec(postgreSqlConnection, alterStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

bool PostgreSqlDatabaseConnection::deleteColumn(const std::string& tableName, const std::string& columnName)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the ALTER TABLE statement to drop the column
    std::string alterStatement = "ALTER TABLE " + tableName + " DROP COLUMN " + columnName;

    // Execute the ALTER TABLE statement
    auto result = PQexec(postgreSqlConnection, alterStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}

bool PostgreSqlDatabaseConnection::optimizeIndexes()
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return false;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Execute the VACUUM ANALYZE command to optimize indexes
    auto result = PQexec(postgreSqlConnection, "VACUUM ANALYZE");
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        // Handle query error
        PQclear(result);
        connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
        return false;
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return true;
}


std::vector<std::string> PostgreSqlDatabaseConnection::getExistingIndexes(const std::string& tableName)
{
    std::vector<std::string> indexes;

    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle invalid connection
        return indexes;
    }

    PostgreSqlPtr postgreSqlConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the query to retrieve the existing indexes
    std::string query = "SELECT indexname FROM pg_indexes WHERE tablename = $1";
    const char* paramValues[1] = { tableName.c_str() };
    int paramLengths[1] = { static_cast<int>(tableName.length()) };
    int paramFormats[1] = { 0 };

    // Execute the query
    auto result = PQexecParams(postgreSqlConnection, query.c_str(), 1, nullptr, paramValues, paramLengths, paramFormats, 0);
    if (PQresultStatus(result) == PGRES_TUPLES_OK) {
        // Retrieve the index names from the query result
        int numRows = PQntuples(result);
        for (int i = 0; i < numRows; ++i) {
            indexes.push_back(PQgetvalue(result, i, 0));
        }
    }

    PQclear(result);
    connectionPool.releaseConnection(postgreSqlConnection);  // Release the connection back to the pool
    return indexes;
}

bool PostgreSqlDatabaseConnection::indexExists(const std::string& tableName, const std::string& indexName)
{
    std::vector<std::string> existingIndexes = getExistingIndexes(tableName);
    return std::find(existingIndexes.begin(), existingIndexes.end(), indexName) != existingIndexes.end();
}

bool PostgreSqlDatabaseConnection::createIndex(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns)
{
    std::string indexColumns;
    for (const std::string& column : columns) {
        indexColumns += column + ",";
    }
    // Remove the trailing comma
    indexColumns = indexColumns.substr(0, indexColumns.length() - 1);

    std::string query = "CREATE INDEX " + indexName + " ON " + tableName + " (" + indexColumns + ")";
    return executeSync(query);
}


bool PostgreSqlDatabaseConnection::dropIndex(const std::string& tableName, const std::string& indexName)
{
    std::string query = "DROP INDEX IF EXISTS " + indexName + " ON " + tableName;
    return executeSync(query);
}

unsigned int PostgreSqlDatabaseConnection::getLastInsertID()
{
    std::string query = "SELECT currval(pg_get_serial_sequence('your_table', 'id'))";
    auto result = querySync(query);

    if (!result.empty() && !result[0].empty()) {
        return std::stoul(result[0][0]);
    }

    return 0; // Return 0 if no insert ID is available
}

std::string PostgreSqlDatabaseConnection::generateCreateIndexSQL(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns)
{
    std::string createIndexSQL = "CREATE INDEX " + indexName + " ON " + tableName + " (";
    for (size_t i = 0; i < columns.size(); ++i) {
        createIndexSQL += columns[i];

        if (i != columns.size() - 1) {
            createIndexSQL += ", ";
        }
    }

    createIndexSQL += ")";
    return createIndexSQL;
}

std::string PostgreSqlDatabaseConnection::generateDropIndexSQL(const std::string& tableName, const std::string& indexName)
{
    std::string dropIndexSQL = "ALTER TABLE " + tableName + " DROP INDEX " + indexName;
    return dropIndexSQL;
}

bool PostgreSqlDatabaseConnection::bulkInsert(const std::string& tableName, const std::vector<std::vector<std::string>>& data)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle the error
        return false;
    }

    PostgreSqlPtr pgConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the INSERT statement
    std::string insertStatement = "INSERT INTO " + tableName + " VALUES ";

    // Construct the VALUES clause with placeholders
    std::string valuesClause;
    for (const auto& row : data)
    {
        valuesClause += "(";
        for (const auto& columnValue : row)
        {
            std::string escapedValue = PQescapeLiteral(pgConnection, columnValue.c_str(), columnValue.length());
            valuesClause += escapedValue;
            valuesClause += ",";
            PQfreemem(const_cast<char*>(escapedValue.c_str()));
        }
        valuesClause.pop_back(); // Remove the trailing comma
        valuesClause += "),";
    }
    valuesClause.pop_back(); // Remove the trailing comma

    // Concatenate the INSERT statement and VALUES clause
    insertStatement += valuesClause;

    // Execute the bulk INSERT statement
    PGresult* result = PQexec(pgConnection, insertStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        // Handle the error
        std::string errorMessage = PQerrorMessage(pgConnection);
        PQclear(result);
        // Log or throw an exception with the error message

        // Release the connection back to the pool
        connectionPool.releaseConnection(pgConnection);
        return false;
    }

    PQclear(result);

    // Release the connection back to the pool
    connectionPool.releaseConnection(pgConnection);

    return true;
}

bool PostgreSqlDatabaseConnection::bulkUpdate(const std::string& tableName, const std::vector<std::vector<std::string>>& data, const std::string& condition)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle the error
        return false;
    }

    PostgreSqlPtr pgConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the UPDATE statement
    std::string updateStatement = "UPDATE " + tableName + " SET ";

    // Get the column names
    std::string columnNames;
    for (const auto& column : data.front())
    {
        columnNames += column + ",";
    }
    columnNames.pop_back(); // Remove the trailing comma

    // Construct the SET clause with column-value pairs
    std::string setClause;
    for (const auto& row : data)
    {
        setClause += "(";
        for (const auto& columnValue : row)
        {
            std::string escapedValue = PQescapeLiteral(pgConnection, columnValue.c_str(), columnValue.length());
            setClause += columnValue + " = " + escapedValue + ",";
            PQfreemem(const_cast<char*>(escapedValue.c_str()));
        }
        setClause.pop_back(); // Remove the trailing comma
        setClause += "),";
    }
    setClause.pop_back(); // Remove the trailing comma

    // Concatenate the UPDATE statement, SET clause, and condition
    updateStatement += setClause + " WHERE " + condition;

    // Execute the bulk UPDATE statement
    PGresult* result = PQexec(pgConnection, updateStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        // Handle the error
        std::string errorMessage = PQerrorMessage(pgConnection);
        PQclear(result);
        // Log or throw an exception with the error message

        // Release the connection back to the pool
        connectionPool.releaseConnection(pgConnection);
        return false;
    }

    PQclear(result);

    // Release the connection back to the pool
    connectionPool.releaseConnection(pgConnection);

    return true;
}

bool PostgreSqlDatabaseConnection::bulkDelete(const std::string& tableName, const std::string& condition)
{
    // Get a connection from the connection pool
    auto connection = connectionPool.getConnection();
    if (!std::holds_alternative<PostgreSqlPtr>(connection)) {
        // Handle the error
        return false;
    }

    PostgreSqlPtr pgConnection = std::get<PostgreSqlPtr>(connection);

    // Construct the DELETE statement
    std::string deleteStatement = "DELETE FROM " + tableName + " WHERE " + condition;

    // Execute the bulk DELETE statement
    PGresult* result = PQexec(pgConnection, deleteStatement.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        // Handle the error
        std::string errorMessage = PQerrorMessage(pgConnection);
        PQclear(result);
        // Log or throw an exception with the error message

        // Release the connection back to the pool
        connectionPool.releaseConnection(pgConnection);
        return false;
    }

    PQclear(result);

    // Release the connection back to the pool
    connectionPool.releaseConnection(pgConnection);

    return true;
}

bool PostgreSqlDatabaseConnection::migrateData(const std::string& sourceTableName, const std::string& destinationTableName)
{
    // Construct the SELECT statement
    std::string selectStatement = "SELECT * FROM " + sourceTableName;

    // Execute the SELECT statement to fetch the data from the source table
    std::vector<std::vector<std::string>> data = querySync(selectStatement);

    // Check if the SELECT query was successful
    if (data.empty())
    {
        // Handle the error
        return false;
    }

    // Construct the INSERT INTO statement
    std::string insertStatement = "INSERT INTO " + destinationTableName + " VALUES ";

    // Iterate over the rows of data and construct the INSERT INTO statement
    for (const auto& row : data)
    {
        std::string values;
        for (const auto& value : row)
        {
            values += "'" + escapeString(value) + "', ";
        }
        values = values.substr(0, values.size() - 2);  // Remove the trailing comma and space

        insertStatement += "(" + values + "), ";
    }
    insertStatement = insertStatement.substr(0, insertStatement.size() - 2);  // Remove the trailing comma and space

    // Execute the INSERT INTO statement to insert the data into the destination table
    return executeSync(insertStatement);
}


std::vector<std::vector<std::string>> PostgreSqlDatabaseConnection::queryWithPagination(const std::string& sql, int pageNumber, int pageSize)
{
    auto& engine = engineController.getEngine();

    // Calculate the offset based on the page number and page size
    int offset = (pageNumber - 1) * pageSize;

    // Append the pagination clause to the SQL query
    std::string paginatedSql = sql + FROM_CELL_STRING(__cell_space) + engine.meta()->returnView(POSTGRESQL_CONSTANTS::LIMIT)
                               + FROM_CELL_STRING(__cell_space) + std::to_string(pageSize)
                               + FROM_CELL_STRING(__cell_space) + engine.meta()->returnView(POSTGRESQL_CONSTANTS::OFFSET)
                               + FROM_CELL_STRING(__cell_space) + std::to_string(offset);
    // Execute the paginated query
    return querySync(paginatedSql);
}

std::string PostgreSqlDatabaseConnection::getLastError()
{
    return m_PostgreSqlData.lastError;
}


int PostgreSqlDatabaseConnection::getRowCount(const std::string& tableName)
{
    // Construct the SQL query to get the row count
    std::string query = "SELECT COUNT(*) FROM " + tableName;

    // Execute the query and retrieve the result
    auto result = querySync(query);
    if (!result.empty() && !result[0].empty()) {
        // Extract the row count from the result
        return std::stoi(result[0][0]);
    }

    // Return 0 if the result is empty or the row count couldn't be extracted
    return 0;
}

std::string PostgreSqlDatabaseConnection::getMaxValue(const std::string& tableName, const std::string& columnName)
{
    // Construct the SQL query to get the maximum value
    std::string query = "SELECT MAX(" + columnName + ") FROM " + tableName;

    // Execute the query and retrieve the result
    auto result = querySync(query);
    if (!result.empty() && !result[0].empty()) {
        // Return the maximum value from the result
        return result[0][0];
    }

    // Return an empty string if the result is empty or the maximum value couldn't be retrieved
    return "";
}

std::string PostgreSqlDatabaseConnection::getMinValue(const std::string& tableName, const std::string& columnName)
{
    // Construct the SQL query to get the minimum value
    std::string query = "SELECT MIN(" + columnName + ") FROM " + tableName;

    // Execute the query and retrieve the result
    auto result = querySync(query);
    if (!result.empty() && !result[0].empty()) {
        // Return the minimum value from the result
        return result[0][0];
    }

    // Return an empty string if the result is empty or the minimum value couldn't be retrieved
    return "";
}

double PostgreSqlDatabaseConnection::getAverageValue(const std::string& tableName, const std::string& columnName)
{
    // Construct the SQL query to calculate the average value
    std::string query = "SELECT AVG(" + columnName + ") FROM " + tableName;

    // Execute the query and retrieve the result
    auto result = querySync(query);
    if (!result.empty() && !result[0].empty()) {
        // Convert the average value from string to double and return it
        return std::stod(result[0][0]);
    }

    // Return 0.0 if the result is empty or the average value couldn't be calculated
    return 0.0;
}

double PostgreSqlDatabaseConnection::getSumValue(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return 0.0;
    }

    // Construct the SQL query to calculate the sum of values
    std::string query = "SELECT SUM(" + columnName + ") FROM " + tableName;

    // Execute the query and retrieve the result
    auto result = querySync(query);
    if (!result.empty() && !result[0].empty()) {
        // Convert the sum value from string to double and return it
        return std::stod(result[0][0]);
    }

    // Return 0.0 if the result is empty or the sum value couldn't be calculated
    return 0.0;
}

std::vector<std::string> PostgreSqlDatabaseConnection::getDistinctValues(const std::string& tableName, const std::string& columnName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    std::vector<std::string> distinctValues;

    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return distinctValues;
    }

    // Construct the SQL query to retrieve distinct values
    std::string query = "SELECT DISTINCT " + columnName + " FROM " + tableName;

    // Execute the query and retrieve the result
    auto result = querySync(query);

    // Extract the distinct values from the result
    for (const auto& row : result) {
        if (!row.empty()) {
            distinctValues.push_back(row[0]);
        }
    }

    return distinctValues;
}


bool PostgreSqlDatabaseConnection::executeScriptFromFile(const std::string& filename)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return false;
    }


    std::ifstream file(filename);
    if (!file.is_open()) {
        m_PostgreSqlData.lastError = safeTranslate(language, "exceptions", "failed_to_open_script_file") + filename;
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

bool PostgreSqlDatabaseConnection::backupDatabase(const std::string& backupFilename)
{
    std::string command = "pg_dump -U <username> -h <hostname> <database_name> > " + backupFilename;

    // Execute the backup command
    int result = std::system(command.c_str());

    // Check the result of the backup command
    if (result == 0) {
        // Backup successful
        return true;
    } else {
        // Backup failed
        return false;
    }
}

bool PostgreSqlDatabaseConnection::restoreDatabase(const std::string& backupFilename)
{
    // Build the command to execute
    std::string command = "pg_restore -U <username> -h <hostname> -p <port> -d <database> " + backupFilename;

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

std::vector<std::string> PostgreSqlDatabaseConnection::getDatabaseList()
{
    std::vector<std::string> databaseList;

    // SQL query to retrieve the database list
    std::string sql = "SELECT datname FROM pg_database WHERE datistemplate = false;";

    // Execute the query
    std::vector<std::vector<std::string>> result = querySync(sql);

    // Extract the database names from the query result
    for (const auto& row : result) {
        databaseList.push_back(row[0]);
    }

    return databaseList;
}

bool PostgreSqlDatabaseConnection::createDatabase(const std::string& databaseName)
{
    // Sanitize the database name to prevent SQL injection
    std::string sanitizedDatabaseName = sanitizeInput(databaseName);

    // SQL statement to create the database
    std::string sql = "CREATE DATABASE " + sanitizedDatabaseName;

    // Execute the query
    bool success = executeSync(sql);

    return success;
}

bool PostgreSqlDatabaseConnection::dropDatabase(const std::string& databaseName)
{
    // Sanitize the database name to prevent SQL injection
    std::string sanitizedDatabaseName = sanitizeInput(databaseName);

    // SQL statement to drop the database
    std::string sql = "DROP DATABASE IF EXISTS " + sanitizedDatabaseName;

    // Execute the query
    bool success = executeSync(sql);

    return success;
}

bool PostgreSqlDatabaseConnection::grantPrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                         engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    // Sanitize the username and database name to prevent SQL injection
    std::string sanitizedUsername = sanitizeInput(username);
    std::string sanitizedDatabaseName = sanitizeInput(databaseName);

    // Construct the list of privileges as a comma-separated string
    std::string privilegesList = "";
    for (const std::string& privilege : privileges) {
        privilegesList += privilege + ", ";
    }
    // Remove the trailing comma and space
    privilegesList = privilegesList.substr(0, privilegesList.size() - 2);

    // SQL statement to grant privileges
    std::string sql = "GRANT " + privilegesList + " ON DATABASE " + sanitizedDatabaseName + " TO " + sanitizedUsername;

    // Execute the query
    bool success = executeSync(sql);

    return success;
}

bool PostgreSqlDatabaseConnection::revokePrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                         engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return false;
    }
    // Sanitize the username and database name to prevent SQL injection
    std::string sanitizedUsername = sanitizeInput(username);
    std::string sanitizedDatabaseName = sanitizeInput(databaseName);

    // Construct the list of privileges as a comma-separated string
    std::string privilegesList = "";
    for (const std::string& privilege : privileges) {
        privilegesList += privilege + ", ";
    }
    // Remove the trailing comma and space
    privilegesList = privilegesList.substr(0, privilegesList.size() - 2);

    // SQL statement to revoke privileges
    std::string sql = "REVOKE " + privilegesList + " ON DATABASE " + sanitizedDatabaseName + " FROM " + sanitizedUsername;

    // Execute the query
    bool success = executeSync(sql);

    return success;
}

int PostgreSqlDatabaseConnection::getTableSize(const std::string& tableName)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return false;
    }

    // Sanitize the table name to prevent SQL injection
    std::string sanitizedTableName = sanitizeInput(tableName);

    // SQL statement to get the table size
    std::string sql = "SELECT pg_size_pretty(pg_total_relation_size('" + sanitizedTableName + "')) AS table_size";

    // Execute the query
    std::vector<std::vector<std::string>> result = querySync(sql);

    // Extract the table size from the result
    if (!result.empty() && result[0].size() > 0) {
        // The table size is in the first row and first column
        std::string sizeString = result[0][0];

        // Parse the size string to an integer
        try {
            int size = std::stoi(sizeString);
            return size;
        } catch (...) {
            // Failed to parse the size, return -1 indicating an error
            return -1;
        }
    }

    // Return -1 if the size could not be retrieved
    return -1;
}

void PostgreSqlDatabaseConnection::executeNonQuery(const std::string& sql)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                         engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return;
    }

    executeSync(sql);
}

void PostgreSqlDatabaseConnection::importTable(const std::string& tableName, const std::string& filePath)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return;
    }

    // Construct the COPY command
    std::string copyCommand = "COPY " + tableName + " FROM '" + filePath + "'";

    // Execute the COPY command
    executeNonQuery(copyCommand);
}


void PostgreSqlDatabaseConnection::exportTable(const std::string& tableName, const std::string& filePath)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    if (!isConnected()) {
        m_PostgreSqlData.lastError = safeFormat()->print(safeTranslate(language, "exceptions", "not_connected_to_server"),
                                                    engine.meta()->returnView(POSTGRESQL_CONSTANTS::DRIVER_NAME));
        return;
    }
    // Construct the COPY command
    std::string copyCommand = "COPY " + tableName + " TO '" + filePath + "'";

    // Execute the COPY command
    executeNonQuery(copyCommand);
}


bool PostgreSqlDatabaseConnection::validateSqlQuery(const std::string& query)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    // Check if the query is empty
    if (query.empty()) {
        m_PostgreSqlData.lastError = "SQL query is empty.";
        return false;
    }

    // Check for any potentially harmful keywords or statements
    // For example, let's check for "DROP", "DELETE", and "TRUNCATE" statements
    std::string upperQuery = query;
    std::transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);

    if (upperQuery.find("DROP") != std::string::npos ||
        upperQuery.find("DELETE") != std::string::npos ||
        upperQuery.find("TRUNCATE") != std::string::npos) {
        m_PostgreSqlData.lastError = safeTranslate(language, "exceptions", "invalid_sql_query_harmful");
        return false;
    }

    // You can add more specific checks based on your requirements
    // For example, validating table or column names, checking for specific patterns, etc.

    // If the query passes all checks, it is considered valid
    return true;
}

bool PostgreSqlDatabaseConnection::validateParams(const std::vector<std::string>& params)
{
    auto language = createLanguageObject()->getLanguageCode();

    // Check if the parameters vector is empty
    if (params.empty()) {
        m_PostgreSqlData.lastError = safeTranslate(language, "exceptions", "query_parameters_are_empty");
        return false;
    }

    // Iterate over each parameter and perform validation checks
    for (const std::string& param : params) {
        // Check if a parameter is empty
        if (param.empty()) {
            m_PostgreSqlData.lastError = safeTranslate(language, "exceptions", "empty_query_parameter_detected");
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
