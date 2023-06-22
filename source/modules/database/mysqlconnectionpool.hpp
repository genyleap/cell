/*!
 * @file        mysqlconnectionpool.hpp
 * @brief       Database MySQL manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_MYSQL_CONNECTION_POOL_HPP
#define CELL_MYSQL_CONNECTION_POOL_HPP

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
 * @brief A connection pool implementation for MySQL database connections.
 *
 * The MySqlConnectionPool class provides a pool of MySQL connections for efficient database operations.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export MySqlConnectionPool : public Abstracts::ConnectionPool
{
public:
    /**
     * @brief Constructs a MySqlConnectionPool object.
     *
     * @param host The host name or IP address of the MySQL server.
     * @param port The port number of the MySQL server.
     * @param user The user name for authentication.
     * @param password The password for authentication.
     * @param database The name of the database.
     * @param poolSize The maximum size of the connection pool.
     */
    MySqlConnectionPool(const std::string& host,
                        const Types::uint port,
                        const std::string& user,
                        const std::string& password,
                        const std::string& database,
                        Types::uint poolSize);

    /**
     * @brief Destroys the MySqlConnectionPool object.
     */
    ~MySqlConnectionPool();

    /**
     * @brief Disable copy construction and assignment for a class.
     */
    CELL_DISABLE_COPY(MySqlConnectionPool)

    /**
     * @brief Declare MySQLDatabaseConnection class as a friend of the specified class.
     */
    CELL_MAKE_FRIEND(MySQLDatabaseConnection)

    /**
     * @brief Initializes the connection pool.
     *
     * This function initializes the MySQL connection pool by establishing initial connections.
     */
    void initialize() __cell_override;

    /**
     * @brief Checks if the connection pool is initialized.
     *
     * @return `true` if the connection pool is initialized, `false` otherwise.
     */
    bool isInitialized() const __cell_override;

    /**
     * @brief Retrieves a MySQL connection from the pool.
     *
     * @return A SqlConnection object representing a MySQL connection.
     */
    Types::SqlConnection getConnection() __cell_override;

    /**
     * @brief Releases a MySQL connection and returns it to the pool.
     *
     * @param connection The SqlConnection object representing the MySQL connection to release.
     */
    void releaseConnection(Types::SqlConnection connection) __cell_override;

    /**
     * @brief Enables encryption for MySQL connections using the specified key, certificate, and CA paths.
     *
     * @param keyPath The path to the private key file for encryption.
     * @param certPath The path to the certificate file for encryption.
     * @param caPath The path to the CA certificate file for encryption.
     */
    void enableEncryption(const std::string& keyPath, const std::string& certPath, const std::string& caPath) __cell_override;

private:
    Abstracts::PoolData m_poolData{}; //!< The pool data used to manage MySQL connections.
};

CELL_NAMESPACE_END

#endif // CELL_MYSQL_CONNECTION_POOL_HPP
