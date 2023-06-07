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

#ifndef CELL_DATABASE_QUERY_ABSTRACT_HPP
#define CELL_DATABASE_QUERY_ABSTRACT_HPP

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
 * @brief The abstract base class for executing database queries and statements.
 */
class QueryExecutor {
public:
    /**
     * @brief Default constructor and destructor.
     */
    CELL_DEFAULT_INTERFACE_OCTORS(QueryExecutor)

    /**
     * @brief Asynchronously execute a SQL statement.
     *
     * This method asynchronously executes the specified SQL statement.
     *
     * @param sql The SQL statement to execute.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executeAsync(const std::string& sql) = __cell_zero;

    /**
     * @brief Asynchronously execute a prepared SQL statement with parameters.
     *
     * This method asynchronously executes the specified prepared SQL statement with the given parameters.
     *
     * @param sql The prepared SQL statement to execute.
     * @param params The vector of parameters to be used in the prepared statement.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executePreparedStatementAsync(const std::string& sql, const std::vector<std::string>& params) = __cell_zero;

    /**
     * @brief Asynchronously execute a batch of SQL statements.
     *
     * This method asynchronously executes a batch of SQL statements.
     *
     * @param sqlBatch The vector of SQL statements to execute as a batch.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executeBatchAsync(const std::vector<std::string>& sqlBatch) = __cell_zero;

    /**
     * @brief Asynchronously execute a stored procedure.
     *
     * This method asynchronously executes the specified stored procedure.
     *
     * @param procedure The name of the stored procedure to execute.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executeProcedureAsync(const std::string& procedure) = __cell_zero;

    /**
     * @brief Asynchronously execute a SQL query and retrieve the result.
     *
     * This method asynchronously executes the specified SQL query and returns the result as a vector of rows, where each row is represented as a vector of strings.
     *
     * @param sql The SQL query to execute.
     * @return A future that holds the vector of rows representing the result of the query.
     */
    __cell_virtual std::future<std::vector<std::vector<std::string>>> queryAsync(const std::string& sql) = __cell_zero;

    /**
     * @brief Asynchronously execute a SQL query with parameters and retrieve the result.
     *
     * This method asynchronously executes the specified SQL query with the given parameters and returns the result as a vector of rows, where each row is represented as a vector of strings.
     *
     * @param sql The SQL query to execute.
     * @param params The vector of parameters to be used in the query.
     * @return A future that holds the vector of rows representing the result of the query.
     */
    __cell_virtual std::future<std::vector<std::vector<std::string>>> queryWithParamsAsync(const std::string& sql, const std::vector<std::string>& params) = __cell_zero;

    /**
     * @brief Asynchronously execute a SQL statement with parameters.
     *
     * This method asynchronously executes the specified SQL statement with the given parameters.
     *
     * @param sql The SQL statement to execute.
     * @param params The vector of parameters to be used in the statement.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executeWithParamsAsync(const std::string& sql, const std::vector<std::string>& params) = __cell_zero;

    /**
     * @brief Asynchronously execute a batch of SQL statements with parameters.
     *
     * This method asynchronously executes a batch of SQL statements with the given parameters.
     *
     * @param sql The SQL statement to execute.
     * @param paramsBatch The vector of parameter batches, where each batch is a vector of parameters.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executeBatchWithParamsAsync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch) = __cell_zero;

    /**
     * @brief Asynchronously execute a stored procedure with parameters.
     *
     * This method asynchronously executes the specified stored procedure with the given parameters.
     *
     * @param procedure The name of the stored procedure to execute.
     * @param params The vector of parameters to be used in the stored procedure.
     * @return A future that holds the boolean result indicating the success of the execution.
     */
    __cell_virtual std::future<bool> executeProcedureWithParamsAsync(const std::string& procedure, const std::vector<std::string>& params) = __cell_zero;

    /**
     * @brief Execute a SQL statement.
     *
     * This method executes the specified SQL statement synchronously.
     *
     * @param sql The SQL statement to execute.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool execute(const std::string& sql)  = __cell_zero;

    /**
     * @brief Execute a SQL statement that does not return a result.
     *
     * This method executes the specified SQL statement that does not return a result.
     *
     * @param sql The SQL statement to execute.
     */
    __cell_virtual void executeNonQuery(const std::string& sql) = __cell_zero;

    /**
     * @brief Execute a prepared SQL statement with parameters.
     *
     * This method executes the specified prepared SQL statement with the given parameters synchronously.
     *
     * @param sql The prepared SQL statement to execute.
     * @param params The vector of parameters to be used in the prepared statement.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool executePreparedStatement(const std::string& sql, const std::vector<std::string>& params) = __cell_zero;

    /**
     * @brief Execute a batch of SQL statements.
     *
     * This method executes a batch of SQL statements synchronously.
     *
     * @param sqlBatch The vector of SQL statements to execute as a batch.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool executeBatch(const std::vector<std::string>& sqlBatch)  = __cell_zero;

    /**
     * @brief Execute a stored procedure.
     *
     * This method executes the specified stored procedure synchronously.
     *
     * @param procedure The name of the stored procedure to execute.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool executeProcedure(const std::string& procedure)  = __cell_zero;

    /**
     * @brief Execute a SQL query and retrieve the result.
     *
     * This method executes the specified SQL query synchronously and returns the result as a vector of rows, where each row is represented as a vector of strings.
     *
     * @param sql The SQL query to execute.
     * @return The vector of rows representing the result of the query.
     */
    __cell_virtual std::vector<std::vector<std::string>> query(const std::string& sql)  = __cell_zero;

    /**
     * @brief Execute a SQL query with parameters and retrieve the result.
     *
     * This method executes the specified SQL query with the given parameters synchronously and returns the result as a vector of rows, where each row is represented as a vector of strings.
     *
     * @param sql The SQL query to execute.
     * @param params The vector of parameters to be used in the query.
     * @return The vector of rows representing the result of the query.
     */
    __cell_virtual std::vector<std::vector<std::string>> queryWithParams(const std::string& sql, const std::vector<std::string>& params)  = __cell_zero;

    /**
     * @brief Execute a SQL statement with parameters.
     *
     * This method executes the specified SQL statement with the given parameters synchronously.
     *
     * @param sql The SQL statement to execute.
     * @param params The vector of parameters to be used in the statement.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool executeWithParams(const std::string& sql, const std::vector<std::string>& params)  = __cell_zero;

    /**
     * @brief Execute a batch of SQL statements with parameters.
     *
     * This method executes a batch of SQL statements with the given parameters synchronously.
     *
     * @param sql The SQL statement to execute.
     * @param paramsBatch The vector of parameter batches, where each batch is a vector of parameters.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool executeBatchWithParams(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch)  = __cell_zero;

    /**
     * @brief Execute a stored procedure with parameters.
     *
     * This method executes the specified stored procedure with the given parameters synchronously.
     *
     * @param procedure The name of the stored procedure to execute.
     * @param params The vector of parameters to be used in the stored procedure.
     * @return The boolean result indicating the success of the execution.
     */
    __cell_virtual bool executeProcedureWithParams(const std::string& procedure, const std::vector<std::string>& params)  = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_QUERY_ABSTRACT_HPP
