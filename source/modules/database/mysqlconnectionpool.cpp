#if __has_include("mysqlconnectionpool.hpp")
#   include "mysqlconnectionpool.hpp"
#else
#   error "Cell's "mysqlconnectionpool.hpp" was not found!"
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

MySqlConnectionPool::MySqlConnectionPool(const std::string& host,
                                         const uint port,
                                         const std::string& user,
                                         const std::string& password,
                                         const std::string& database,
                                         uint poolSize)
{

    m_poolData.host = host;
    m_poolData.port = port;
    m_poolData.user = user;
    m_poolData.password = password;
    m_poolData.database = database;
    m_poolData.poolSize = poolSize;
}

MySqlConnectionPool::~MySqlConnectionPool()
{
    for (SqlConnection connection : m_poolData.connections)
    {
        if (std::holds_alternative<MySqlPtr>(connection)) {
            MySqlPtr mysqlConnection = std::get<MySqlPtr>(connection);
            mysql_close(mysqlConnection);
        }
    }
}

void MySqlConnectionPool::initialize()
{
    for (int i = 0; i < m_poolData.poolSize; ++i) {
        MySqlPtr connection = mysql_init(__cell_nullptr);
        if (connection != __cell_nullptr
            && mysql_real_connect(connection,
                                  m_poolData.host.value().c_str(),
                                  m_poolData.user.value().c_str(),
                                  m_poolData.password.value().c_str(),
                                  m_poolData.database.value().c_str(),
                                  m_poolData.port, __cell_nullptr, 0) != __cell_nullptr)
        {
            // Configure SSL/TLS if necessary
            if (m_poolData.keyPath.has_value() && m_poolData.certPath.has_value() && m_poolData.caPath.has_value())
            {
                if (mysql_ssl_set(connection, m_poolData.keyPath.value().c_str(), m_poolData.certPath.value().c_str(), m_poolData.caPath.value().c_str(), __cell_nullptr, __cell_nullptr) != 0)
                {
                    // Handle SSL/TLS configuration error
                    throw Exception(Exception::Reason::Database, "SSL/TLS configuration error occurred.").getRuntimeError();
                    mysql_close(connection);
                    continue;  // Skip this connection and proceed with the next one
                }
            }

            std::lock_guard<std::mutex> lock(m_poolData.mutex);
            m_poolData.connections.push_back(connection);
        } else {
            // Failed to create or connect to a MySQL connection
            // Handle the error or log the failure
            throw Exception(Exception::Reason::Database, "Failed to create or connect to a MySQL connection.").getRuntimeError();
            if (connection != __cell_nullptr) {
                mysql_close(connection);
            }
        }
    }
}

bool MySqlConnectionPool::isInitialized() const
{
    return !m_poolData.connections.empty();
}

SqlConnection MySqlConnectionPool::getConnection()
{
    // Wait until a connection becomes available
    std::unique_lock<std::mutex> lock(m_poolData.mutex);
    while (m_poolData.connections.empty()) {
        m_poolData.condition.wait(lock);
    }

    // Retrieve a connection from the pool
    SqlConnection connection = m_poolData.connections.front();
    m_poolData.connections.pop_front();
    return connection;
}

void MySqlConnectionPool::releaseConnection(SqlConnection connection)
{
    std::lock_guard<std::mutex> lock(m_poolData.mutex);

    // Add the connection back to the pool
    m_poolData.connections.push_back(connection);

    // Notify a waiting thread about the availability of a connection
    m_poolData.condition.notify_one();
}

void MySqlConnectionPool::enableEncryption(const std::string& keyPath, const std::string& certPath, const std::string& caPath)
{
    this->m_poolData.keyPath = keyPath;
    this->m_poolData.certPath = certPath;
    this->m_poolData.caPath = caPath;
}

CELL_NAMESPACE_END

#endif
