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

#ifndef CELL_DATABASE_MAINTENANCE_HPP
#define CELL_DATABASE_MAINTENANCE_HPP

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
 * @brief The abstract base class for database maintenance operations.
 */
class DatabaseMaintenance {
public:
    /**
     * @brief Default constructor and destructor.
     */
    CELL_DEFAULT_INTERFACE_OCTORS(DatabaseMaintenance)

    /**
     * @brief Execute a SQL script from a file.
     *
     * This method executes the SQL script located in the specified file.
     *
     * @param filename The name of the script file.
     * @return bool True if the script execution was successful, false otherwise.
     */
    __cell_virtual bool executeScriptFromFile(const std::string& filename)  = __cell_zero;

    /**
     * @brief Backup the database to a file.
     *
     * This method creates a backup of the database and saves it to the specified file.
     *
     * @param backupFilename The name of the backup file.
     * @return bool True if the database backup was successful, false otherwise.
     */
    __cell_virtual bool backupDatabase(const std::string& backupFilename)  = __cell_zero;

    /**
     * @brief Restore the database from a backup file.
     *
     * This method restores the database from the specified backup file.
     *
     * @param backupFilename The name of the backup file.
     * @return bool True if the database restore was successful, false otherwise.
     */
    __cell_virtual bool restoreDatabase(const std::string& backupFilename)  = __cell_zero;

    /**
     * @brief Get a list of databases.
     *
     * This method retrieves a list of names of existing databases.
     *
     * @return std::vector<std::string> The list of database names.
     */
    __cell_virtual std::vector<std::string> getDatabaseList()  = __cell_zero;

    /**
     * @brief Create a new database.
     *
     * This method creates a new database with the specified name.
     *
     * @param databaseName The name of the new database.
     * @return bool True if the database creation was successful, false otherwise.
     */
    __cell_virtual bool createDatabase(const std::string& databaseName)  = __cell_zero;

    /**
     * @brief Drop an existing database.
     *
     * This method deletes an existing database with the specified name.
     *
     * @param databaseName The name of the database to drop.
     * @return bool True if the database deletion was successful, false otherwise.
     */
    __cell_virtual bool dropDatabase(const std::string& databaseName)  = __cell_zero;

    /**
     * @brief Grant privileges to a user for a specific database.
     *
     * This method grants the specified privileges to a user for a particular database.
     *
     * @param username The username to grant privileges to.
     * @param databaseName The name of the database.
     * @param privileges The list of privileges to grant.
     * @return bool True if the privileges were granted successfully, false otherwise.
     */
    __cell_virtual bool grantPrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges)  = __cell_zero;

    /**
     * @brief Revoke privileges from a user for a specific database.
     *
     * This method revokes the specified privileges from a user for a particular database.
     *
     * @param username The username to revoke privileges from.
     * @param databaseName The name of the database.
     * @param privileges The list of privileges to revoke.
     * @return bool True if the privileges were revoked successfully, false otherwise.
     */
    __cell_virtual bool revokePrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges)  = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_MAINTENANCE_HPP
