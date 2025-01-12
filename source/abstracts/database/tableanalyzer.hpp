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

#ifndef CELL_DATABASE_TABLE_ANALYZER_ABSTRACT_HPP
#define CELL_DATABASE_TABLE_ANALYZER_ABSTRACT_HPP

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
 * @brief The TableDataAnalyzer class provides methods for analyzing table data.
 */
class TableDataAnalyzer {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(TableDataAnalyzer)

    /**
     * @brief Get the size of a table.
     *
     * This method returns the size (number of rows) of the specified table.
     *
     * @param tableName The name of the table to analyze.
     * @return The size of the table.
     */
    __cell_virtual int getTableSize(const std::string& tableName) = __cell_zero;

};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_TABLE_ANALYZER_ABSTRACT_HPP
