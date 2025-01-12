/*!
 * @file        mysqlprivate.hpp
 * @brief       Database MySQL manager for the Cell Engine.
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

#ifndef CELL_MYSQL_PRIVATE_HPP
#define CELL_MYSQL_PRIVATE_HPP

#if defined(USE_MYSQL_MARIADB)

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

#if __has_include("mysqlconnectionpool.hpp")
#   include "mysqlconnectionpool.hpp"
#else
#   error "Cell's "mysqlconnectionpool.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Database)

/**
 * @brief Constants related to MySQL operations.
 *
 * This struct provides static string views representing various MySQL operations, keywords, and clauses.
 */
struct MYSQL_CONSTANTS final
{
    __cell_static_const_constexpr std::string_view DRIVER_NAME          {"MySQL"};                      //!<The name of the MySQL driver.
    __cell_static_const_constexpr std::string_view BEGIN                {"BEGIN"};                      //!<The BEGIN transaction keyword.
    __cell_static_const_constexpr std::string_view COMMIT               {"COMMIT"};                     //!<The COMMIT transaction keyword.
    __cell_static_const_constexpr std::string_view ROLLBACK             {"ROLLBACK"};                   //!<The ROLLBACK transaction keyword.
    __cell_static_const_constexpr std::string_view CALL                 {"CALL"};                       //!<The CALL procedure keyword.
    __cell_static_const_constexpr std::string_view SHOW_TABLES          {"SHOW TABLES"};                //!<The SHOW TABLES keyword.
    __cell_static_const_constexpr std::string_view SHOW_DATABASE        {"SHOW DATABASES"};             //!<The SHOW DATABASES keyword.
    __cell_static_const_constexpr std::string_view CREATE_TABLE         {"CREATE TABLE"};               //!<The CREATE TABLE keyword.
    __cell_static_const_constexpr std::string_view CREATE_DATABASE      {"CREATE DATABASE"};            //!<The CREATE DATABASE keyword.
    __cell_static_const_constexpr std::string_view DROP_TABLE           {"DROP TABLE"};                 //!<The DROP TABLE keyword.
    __cell_static_const_constexpr std::string_view DROP_DATABASE        {"DROP DATABASE"};              //!<The DROP DATABASE keyword.
    __cell_static_const_constexpr std::string_view ALTER_TABLE          {"ALTER TABLE"};                //!<The ALTER TABLE keyword.
    __cell_static_const_constexpr std::string_view SELECT_LAST_INSERT   {"SELECT LAST_INSERT_ID()"};    //!<The SELECT LAST_INSERT_ID() query.
    __cell_static_const_constexpr std::string_view INSERT_INTO          {"INSERT INTO"};                //!<The INSERT INTO keyword.
    __cell_static_const_constexpr std::string_view UPDATE               {"UPDATE"};                     //!<The UPDATE keyword.
    __cell_static_const_constexpr std::string_view SET                  {"SET"};                        //!<The SET keyword.
    __cell_static_const_constexpr std::string_view DELETE_FROM          {"DELETE FROM"};                //!<The DELETE FROM keyword.
    __cell_static_const_constexpr std::string_view SELECT               {"SELECT"};                     //!<The SELECT keyword.
    __cell_static_const_constexpr std::string_view LIMIT                {"LIMIT"};                      //!<The LIMIT keyword.
    __cell_static_const_constexpr std::string_view OFFSET               {"OFFSET"};                     //!<The OFFSET keyword.
    __cell_static_const_constexpr std::string_view CREATE               {"CREATE"};                     //!<The CREATE keyword.
    __cell_static_const_constexpr std::string_view WHERE                {"WHERE"};                      //!<The WHERE keyword.
    __cell_static_const_constexpr std::string_view DROP                 {"DROP"};                       //!<The DROP keyword.
    __cell_static_const_constexpr std::string_view GRANT                {"GRANT"};                      //!<The GRANT keyword.
    __cell_static_const_constexpr std::string_view REVOKE               {"REVOKE"};                     //!<The REVOKE keyword.
    __cell_static_const_constexpr std::string_view TRUNCATE             {"TRUNCATE"};                   //!<The TRUNCATE keyword.
};

/**
 * @brief Represents the data required for managing MySQL database connections.
 */
struct MySQLData final
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

#endif // CELL_MYSQL_PRIVATE_HPP

