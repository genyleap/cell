/*!
 * @file        database.hpp
 * @brief       Database interface for the Cell Engine.
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

#ifndef CELL_DATABASE_CONNECTION_POOL_ABSTRACT_HPP
#define CELL_DATABASE_CONNECTION_POOL_ABSTRACT_HPP

#if defined(USE_MYSQL_MARIADB) && defined(USE_POSTGRESQL) && defined(USE_SQLITE) && defined(USE_MSSQL) && defined(USE_ORACLE)

//! Cell's Common.
#if __has_include(<common>)
#   include <common>
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Core (Core Only).
#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's requirements was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @brief Represents the data required for configuring a connection pool.
 */
struct PoolData final
{
    Types::OptionalString host      {}; //!< Optional host name or IP address of the database server.
    Types::uint           port      {}; //!< Port number on which the database server is running.
    Types::OptionalString user      {}; //!< Optional username for authenticating the database connection.
    Types::OptionalString password  {}; //!< Optional password for the database user.
    Types::OptionalString database  {}; //!< Optional name of the database to connect to.
    Types::uint           poolSize  {}; //!< Maximum number of connections in the pool.

    Types::DbConnectionQueue connections    {}; //!< Queue of available database connections.
    Types::ConditionVariable condition      {}; //!< Condition variable for managing connection availability.

    Types::OptionalString keyPath   {}; //!< Optional file path to the private key for SSL/TLS connection.
    Types::OptionalString certPath  {}; //!< Optional file path to the certificate for SSL/TLS connection.
    Types::OptionalString caPath    {}; //!< Optional file path to the CA certificate for SSL/TLS connection.

    Types::Mutex mutex              {}; //!< Mutex for ensuring thread-safe access to the connection pool.
};

/**
 * @brief The abstract base class for a connection pool.
 */
class ConnectionPool {
public:
    /**
     * @brief Default constructor and destructor.
     */
    CELL_DEFAULT_INTERFACE_OCTORS(ConnectionPool)

    /**
     * @brief Initialize the connection pool.
     */
    __cell_virtual void initialize() = __cell_zero;


    __cell_virtual bool isInitialized() const = __cell_zero;

    /**
     * @brief Get a connection from the pool.
     *
     * @return SqlConnection Pointer to a connection object.
     */
    __cell_virtual Types::SqlConnection getConnection() = __cell_zero;

    /**
     * @brief Release a connection back to the pool.
     *
     * @param connection Pointer to the connection object to release.
     */
    __cell_virtual void releaseConnection(Types::SqlConnection connection) = __cell_zero;

    /**
     * @brief Enable encryption for the connections in the pool.
     *
     * @param keyPath Path to the private key file for encryption.
     * @param certPath Path to the certificate file for encryption.
     * @param caPath Path to the CA (Certificate Authority) file for encryption.
     */
    __cell_virtual void enableEncryption(const std::string& keyPath, const std::string& certPath, const std::string& caPath) = __cell_zero;
};


CELL_NAMESPACE_END

#endif

#endif  // CELL_DATABASE_ABSTRACT_HPP
