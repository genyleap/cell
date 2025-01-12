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

#ifndef CELL_DATABASE_ABSTRACT_HPP
#define CELL_DATABASE_ABSTRACT_HPP

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
 * @brief The abstract base class for a database connection.
 */
class DatabaseConnection {
public:
    /**
     * @brief Default constructor and destructor.
     */
    CELL_DEFAULT_INTERFACE_OCTORS(DatabaseConnection)

    /**
     * @brief Get the underlying connection object.
     *
     * @return void* Pointer to the connection object.
     */
    __cell_virtual void* get()  = __cell_zero;

    /**
     * @brief Connect to the database.
     *
     * @return bool True if the connection is successful, false otherwise.
     */
    __cell_virtual bool connect()  = __cell_zero;

    /**
     * @brief Disconnect from the database.
     *
     * @return bool True if the disconnection is successful, false otherwise.
     */
    __cell_virtual bool disconnect()  = __cell_zero;

    /**
     * @brief Asynchronously connect to the database.
     *
     * @return std::future<bool> A future object representing the asynchronous connection result.
     */
    __cell_virtual std::future<bool> connectAsync() = __cell_zero;

    /**
     * @brief Asynchronously disconnect from the database.
     *
     * @return std::future<bool> A future object representing the asynchronous disconnection result.
     */
    __cell_virtual std::future<bool> disconnectAsync() = __cell_zero;

    /**
     * @brief Check if the connection is active and connected.
     *
     * @return bool True if the connection is active, false otherwise.
     */
    __cell_virtual bool isConnected()  = __cell_zero;

    /**
     * @brief Check if the underlying connection is alive.
     *
     * @return bool True if the connection is alive, false otherwise.
     */
    __cell_virtual bool isConnectionAlive() = __cell_zero;

    /**
     * @brief Get the statistics of the current connection.
     *
     * @return std::map<std::string, std::string> A map containing connection statistics.
     */
    __cell_virtual std::map<std::string, std::string> getConnectionStatistics() = __cell_zero;

    /**
     * @brief Get the number of active connections.
     *
     * @return int The count of active connections.
     */
    __cell_virtual int getActiveConnectionsCount() = __cell_zero;

    /**
     * @brief Get the maximum allowed connections.
     *
     * @return int The maximum allowed connections.
     */
    __cell_virtual int getMaxConnectionsCount() = __cell_zero;

    /**
     * @brief Get the health status of the connection.
     *
     * @return std::string The health status of the connection.
     */
    __cell_virtual std::string getConnectionHealthStatus() = __cell_zero;

    /**
     * @brief Get the version of the database server.
     *
     * @return std::string The version of the database server.
     */
    __cell_virtual std::string getDatabaseServerVersion() = __cell_zero;

    /**
     * @brief Get the uptime of the connection.
     *
     * @return std::chrono::seconds The uptime of the connection in seconds.
     */
    __cell_virtual std::chrono::seconds getConnectionUptime() = __cell_zero;

    /**
     * @brief Get the activity log of the connection.
     *
     * @return std::vector<std::string> The activity log of the connection.
     */
    __cell_virtual std::vector<std::string> getConnectionActivityLog() = __cell_zero;

    /**
     * @brief Check if a query is cached.
     *
     * @param sql The SQL query to check.
     * @return bool True if the query is cached, false otherwise.
     */
    __cell_virtual bool isQueryCached(const std::string& sql) = __cell_zero;

    /**
     * @brief Set the connection timeout in seconds.
     *
     * @param timeoutSeconds The timeout value in seconds.
     */
    __cell_virtual void setConnectionTimeout(int timeoutSeconds)  = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_ABSTRACT_HPP
