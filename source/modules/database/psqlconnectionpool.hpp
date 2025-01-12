/*!
 * @file        psqlconnectionpool.hpp
 * @brief       Database PostgreSql manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2025 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_PSQL_CONNECTION_POOL_HPP
#define CELL_PSQL_CONNECTION_POOL_HPP

#if defined(USE_POSTGRESQL)

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("abstract-includer.hpp")
#   include "abstract-includer.hpp"
#else
#   error "Cell's "abstract-includer.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Database)

/**
 * @brief A connection pool implementation for PostgreSql database connections.
 *
 * The PostgreSqlConnectionPool class provides a pool of PostgreSql connections for efficient database operations.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export PostgreSqlConnectionPool : public Abstracts::ConnectionPool
{
public:
    /**
     * @brief Constructs a PostgreSqlConnectionPool object.
     *
     * @param host The host name or IP address of the PostgreSql server.
     * @param port The port number of the PostgreSql server.
     * @param user The user name for authentication.
     * @param password The password for authentication.
     * @param database The name of the database.
     * @param poolSize The maximum size of the connection pool.
     */
    PostgreSqlConnectionPool(const std::string& host,
                        const Types::uint port,
                        const std::string& user,
                        const std::string& password,
                        const std::string& database,
                        Types::uint poolSize);

    /**
     * @brief Destroys the PostgreSqlConnectionPool object.
     */
    ~PostgreSqlConnectionPool();

    /**
     * @brief Disable copy construction and assignment for a class.
     */
    CELL_DISABLE_COPY(PostgreSqlConnectionPool)

    /**
     * @brief Declare PostgreSqlDatabaseConnection class as a friend of the specified class.
     */
    CELL_MAKE_FRIEND(PostgreSqlDatabaseConnection)

    /**
     * @brief Initializes the connection pool.
     *
     * This function initializes the PostgreSql connection pool by establishing initial connections.
     */
    void initialize() __cell_override;

    /**
     * @brief Checks if the connection pool is initialized.
     *
     * @return `true` if the connection pool is initialized, `false` otherwise.
     */
    bool isInitialized() const __cell_override;

    /**
     * @brief Retrieves a PostgreSql connection from the pool.
     *
     * @return A SqlConnection object representing a PostgreSql connection.
     */
    Types::SqlConnection getConnection() __cell_override;

    /**
     * @brief Releases a PostgreSql connection and returns it to the pool.
     *
     * @param connection The SqlConnection object representing the PostgreSql connection to release.
     */
    void releaseConnection(Types::SqlConnection connection) __cell_override;

    /**
     * @brief Enables encryption for PostgreSql connections using the specified key, certificate, and CA paths.
     *
     * @param keyPath The path to the private key file for encryption.
     * @param certPath The path to the certificate file for encryption.
     * @param caPath The path to the CA certificate file for encryption.
     */
    void enableEncryption(const std::string& keyPath, const std::string& certPath, const std::string& caPath) __cell_override;

private:
    Abstracts::PoolData m_poolData{}; //!< The pool data used to manage PostgreSql connections.
};
CELL_NAMESPACE_END

#endif

#endif // CELL_PSQL_CONNECTION_POOL_HPP
