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
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_DATABASE_MANAGEMENT_ABSTRACT_HPP
#define CELL_DATABASE_MANAGEMENT_ABSTRACT_HPP

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
 * @brief The abstract base class for database management operations.
 */
class DatabaseManagement {
public:
    /**
     * @brief Default constructor and destructor.
     */
    CELL_DEFAULT_INTERFACE_OCTORS(DatabaseManagement)

    /**
     * @brief Import a table from a file.
     *
     * This method imports the specified table from a file into the database.
     *
     * @param tableName The name of the table to import.
     * @param filePath The path of the file containing the table data.
     */
    __cell_virtual void importTable(const std::string& tableName, const std::string& filePath) = __cell_zero;

    /**
     * @brief Export a table to a file.
     *
     * This method exports the specified table to a file.
     *
     * @param tableName The name of the table to export.
     * @param filePath The path of the file to export the table data to.
     */
    __cell_virtual void exportTable(const std::string& tableName, const std::string& filePath) = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_MANAGEMENT_ABSTRACT_HPP
