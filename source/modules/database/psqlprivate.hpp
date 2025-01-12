/*!
 * @file        psqlprivate.hpp
 * @brief       Database PostgreSQL manager for the Cell Engine.
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

#ifndef CELL_PSQL_PRIVATE_HPP
#define CELL_PSQL_PRIVATE_HPP

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

#if __has_include("psqlconnectionpool.hpp")
#   include "psqlconnectionpool.hpp"
#else
#   error "Cell's "psqlconnectionpool.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Database)

struct POSTGRESQL_CONSTANTS final
{
    __cell_static_const_constexpr std::string_view DRIVER_NAME          {"PSQL"};
    __cell_static_const_constexpr std::string_view BEGIN                {"BEGIN"};
    __cell_static_const_constexpr std::string_view COMMIT               {"COMMIT"};
    __cell_static_const_constexpr std::string_view ROLLBACK             {"ROLLBACK"};
    __cell_static_const_constexpr std::string_view CALL                 {"CALL"};
    __cell_static_const_constexpr std::string_view SHOW_TABLES          {"SHOW TABLES"};
    __cell_static_const_constexpr std::string_view CREATE_TABLE         {"CREATE TABLE"};
    __cell_static_const_constexpr std::string_view DROP_TABLE           {"DROP TABLE"};
    __cell_static_const_constexpr std::string_view ALTER_TABLE          {"ALTER TABLE"};
    __cell_static_const_constexpr std::string_view SELECT_LAST_INSERT   {"SELECT LAST_INSERT_ID()"};
    __cell_static_const_constexpr std::string_view INSERT_INTO          {"INSERT INTO"};
    __cell_static_const_constexpr std::string_view UPDATE               {"UPDATE"};
    __cell_static_const_constexpr std::string_view SET                  {"SET"};
    __cell_static_const_constexpr std::string_view DELETE_FROM          {"DELETE FROM"};
    __cell_static_const_constexpr std::string_view SELECT               {"SELECT"};
    __cell_static_const_constexpr std::string_view LIMIT                {"LIMIT"};
    __cell_static_const_constexpr std::string_view OFFSET               {"OFFSET"};

    __cell_static_const_constexpr std::string_view CREATE               {"CREATE"};
    __cell_static_const_constexpr std::string_view DROP                 {"DROP"};
    __cell_static_const_constexpr std::string_view GRANT                {"GRANT"};
    __cell_static_const_constexpr std::string_view REVOKE               {"REVOKE"};
    __cell_static_const_constexpr std::string_view TRUNCATE             {"TRUNCATE"};
};

/**
 * @brief Represents the data required for managing MySQL database connections.
 */
struct PostgreSqlData final
{
    std::string          lastError;         //!< Last error message encountered.

    int connectionTimeout;                  //!< Connection timeout duration in seconds.

    Types::OptionalString host      {};     //!< Optional host name or IP address of the database server.
    Types::uint           port      {};     //!< Port number on which the database server is running.
    Types::OptionalString user      {};     //!< Optional username for authenticating the database connection.
    Types::OptionalString password  {};     //!< Optional password for the database user.
    Types::OptionalString database  {};     //!< Optional name of the database to connect to.

    Types::QueryCache    queryCache {};     //!< Cache for storing query results.
    Types::Mutex         cacheMutex {};     //!< Mutex for synchronizing access to the query cache.
};

CELL_NAMESPACE_END

#endif

#endif // CELL_PSQL_PRIVATE_HPP

