#if __has_include("psqlconnectionpool.hpp")
#   include "psqlconnectionpool.hpp"
#else
#   error "Cell's "psqlconnectionpool.hpp" was not found!"
#endif

#if defined(USE_POSTGRESQL)

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

PostgreSqlConnectionPool::PostgreSqlConnectionPool(const std::string& host,
                                                   const unsigned int port,
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

PostgreSqlConnectionPool::~PostgreSqlConnectionPool()
{
    for (auto& connection : m_poolData.connections)
    {
        if (std::holds_alternative<PostgreSqlPtr>(connection))
        {
            PostgreSqlPtr& postgresConnection = std::get<PostgreSqlPtr>(connection);
            if (postgresConnection)
            {
                PQfinish(postgresConnection);
                postgresConnection = nullptr;
            }
        }
        // Handle other connection types if necessary
    }
}

void PostgreSqlConnectionPool::initialize()
{
    std::string connectionString = "host=" + m_poolData.host.value() + " port=" + std::to_string(m_poolData.port) + " dbname=" + m_poolData.database.value() + " user=" + m_poolData.user.value() + " password=" + m_poolData.password.value();
    for (int i = 0; i < m_poolData.poolSize; ++i) {
        PostgreSqlPtr connection = PQconnectdb(connectionString.c_str());
        if (PQstatus(connection) == CONNECTION_OK) {
            // Configure SSL/TLS if necessary
            if (m_poolData.keyPath.has_value() && m_poolData.certPath.has_value() && m_poolData.caPath.has_value()) {
                std::string sslModeParam = "sslmode=require sslcert=" + m_poolData.certPath.value() +
                                           " sslkey=" + m_poolData.keyPath.value() +
                                           " sslrootcert=" + m_poolData.caPath.value();
                PQclear(PQexec(connection, sslModeParam.c_str()));
            }

            std::lock_guard<std::mutex> lock(m_poolData.mutex);
            m_poolData.connections.push_back(connection);
        } else {
            // Failed to create or connect to a PostgreSQL connection
            // Handle the error or log the failure
            throw Exception(Exception::Reason::Database, "Failed to create or connect to a PostgreSQL connection.").getRuntimeError();
            PQfinish(connection);
        }
    }
}

bool PostgreSqlConnectionPool::isInitialized() const
{
    return !m_poolData.connections.empty();
}

SqlConnection PostgreSqlConnectionPool::getConnection()
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

void PostgreSqlConnectionPool::releaseConnection(SqlConnection connection)
{
    std::lock_guard<std::mutex> lock(m_poolData.mutex);

    // Add the connection back to the pool
    m_poolData.connections.push_back(connection);

    // Notify a waiting thread about the availability of a connection
    m_poolData.condition.notify_one();
}

void PostgreSqlConnectionPool::enableEncryption(const std::string& keyPath, const std::string& certPath, const std::string& caPath)
{
    this->m_poolData.keyPath = keyPath;
    this->m_poolData.certPath = certPath;
    this->m_poolData.caPath = caPath;
}

CELL_NAMESPACE_END

#endif
