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

#ifndef CELL_DATABASE_QUERY_BUILDER_ABSTRACT_HPP
#define CELL_DATABASE_QUERY_BUILDER_ABSTRACT_HPP

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
 * @brief The QueryBuilder class provides methods for building and validating SQL queries.
 */
class QueryBuilder {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(QueryBuilder)

    /**
     * @brief Escape a string for safe use in an SQL query.
     *
     * This method escapes special characters in the given string to ensure it can be safely used in an SQL query.
     *
     * @param str The string to escape.
     * @return The escaped string.
     */
    __cell_virtual std::string escapeString(const std::string& str)  = __cell_zero;

    /**
     * @brief Validate an SQL query.
     *
     * This method validates the syntax of the given SQL query.
     *
     * @param sql The SQL query to validate.
     * @return A boolean indicating whether the SQL query is valid.
     */
    __cell_virtual bool validateSqlQuery(const std::string& sql) = __cell_zero;

    /**
     * @brief Validate a vector of query parameters.
     *
     * This method validates the format and integrity of the given vector of query parameters.
     *
     * @param params The vector of query parameters to validate.
     * @return A boolean indicating whether the query parameters are valid.
     */
    __cell_virtual bool validateParams(const std::vector<std::string>& params) = __cell_zero;

};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_QUERY_BUILDER_ABSTRACT_HPP
