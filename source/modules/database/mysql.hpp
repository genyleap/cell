/*!
 * @file        mysql.hpp
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

#ifndef CELL_MYSQL_HPP
#define CELL_MYSQL_HPP

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

#if __has_include("mysqlprivate.hpp")
#   include "mysqlprivate.hpp"
#else
#   error "Cell's "mysqlprivate.hpp" was not found!"
#endif

#if __has_include("mysqlconnectionpool.hpp")
#   include "mysqlconnectionpool.hpp"
#else
#   error "Cell's "mysqlconnectionpool.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Database)

/**
 * @class MySQLDatabaseConnection
 * @brief Represents a connection to a MySQL database.
 *
 * This class inherits from multiple abstract classes/interfaces including
 * Abstracts::DatabaseConnection, Abstracts::DatabaseMaintenance,
 * Abstracts::DatabaseTransaction, Abstracts::DataManipulator,
 * Abstracts::QueryBuilder, Abstracts::QueryExecutor,
 * Abstracts::TableDataAnalyzer, Abstracts::TableManager, and
 * Abstracts::DatabaseManagement.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export MySQLDatabaseConnection : public
                                              Abstracts::DatabaseConnection,
                                              Abstracts::DatabaseMaintenance,
                                              Abstracts::DatabaseTransaction,
                                              Abstracts::DataManipulator,
                                              Abstracts::QueryBuilder,
                                              Abstracts::QueryExecutor,
                                              Abstracts::TableDataAnalyzer,
                                              Abstracts::TableManager,
                                              Abstracts::DatabaseManagement
{
public:
    /**
     * @brief Constructs a MySQLDatabaseConnection object.
     *
     * @param connectionPool The connection pool for managing MySQL connections.
     */
    MySQLDatabaseConnection(MySqlConnectionPool& connectionPool);

    /**
     * @brief Destroys the MySQLDatabaseConnection object.
     */
    ~MySQLDatabaseConnection();

    /**
     * @brief Retrieves the underlying connection object.
     *
     * @return A void pointer to the underlying connection object.
     */
    void* get() __cell_override;

    /**
     * @brief Connects to the MySQL database.
     *
     * @return True if the connection is successful, false otherwise.
     */
    bool connect() __cell_override;

    /**
     * @brief Disconnects from the MySQL database.
     *
     * @return True if disconnection is successful, false otherwise.
     */
    bool disconnect() __cell_override;

    /**
     * @brief Checks if the database connection is active.
     *
     * @return True if the connection is active, false otherwise.
     */
    bool isConnected() __cell_override;

    /**
     * @brief Checks if the database connection is alive.
     *
     * @return True if the connection is alive, false otherwise.
     */
    bool isConnectionAlive() __cell_override;

    /**
     * @brief Retrieves statistics about the database connection.
     *
     * @return A map containing the connection statistics.
     */
    std::map<std::string, std::string> getConnectionStatistics() __cell_override;

    /**
     * @brief Retrieves the count of active connections.
     *
     * @return The number of active connections.
     */
    int getActiveConnectionsCount() __cell_override;

    /**
     * @brief Retrieves the maximum allowed connections count.
     *
     * @return The maximum connections count.
     */
    int getMaxConnectionsCount() __cell_override;

    /**
     * @brief Retrieves the health status of the database connection.
     *
     * @return The health status of the connection as a string.
     */
    std::string getConnectionHealthStatus() __cell_override;

    /**
     * @brief Retrieves the version of the connected database server.
     *
     * @return The version of the database server as a string.
     */
    std::string getDatabaseServerVersion() __cell_override;

    /**
     * @brief Retrieves the uptime of the database connection.
     *
     * @return The uptime of the connection in seconds.
     */
    std::chrono::seconds getConnectionUptime() __cell_override;

    /**
     * @brief Retrieves the activity log of the database connection.
     *
     * @return A vector of strings representing the activity log.
     */
    std::vector<std::string> getConnectionActivityLog() __cell_override;

    /**
     * @brief Asynchronously connects to the MySQL database.
     *
     * @return A future object that can be used to obtain the result of the connection.
     */
    std::future<bool> connectAsync() __cell_override;

    /**
     * @brief Asynchronously disconnects from the MySQL database.
     *
     * @return A future object that can be used to obtain the result of the disconnection.
     */
    std::future<bool> disconnectAsync() __cell_override;

    /**
     * @brief Checks if the specified query is cached.
     *
     * @param sql The SQL query to check.
     * @return True if the query is cached, false otherwise.
     */
    bool isQueryCached(const std::string& sql) __cell_override;

    /**
     * @brief Optimizes the indexes of the database.
     *
     * @return True if the index optimization is successful, false otherwise.
     */
    bool optimizeIndexes();

    /**
     * @brief Begins a transaction.
     *
     * @return True if the transaction is successfully started, false otherwise.
     */
    bool beginTransaction() __cell_override;

    /**
     * @brief Commits the current transaction.
     *
     * @return True if the transaction is successfully committed, false otherwise.
     */
    bool commitTransaction() __cell_override;

    /**
     * @brief Rolls back the current transaction.
     *
     * @return True if the transaction is successfully rolled back, false otherwise.
     */
    bool rollbackTransaction() __cell_override;

    /**
     * @brief Executes an SQL query synchronously.
     *
     * @param sql The SQL query to execute.
     * @return True if the execution is successful, false otherwise.
     */
    bool executeSync(const std::string& sql) __cell_override;

    /**
     * @brief Executes an SQL query asynchronously.
     *
     * @param sql The SQL query to execute.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executeAsync(const std::string& sql) __cell_override;

    /**
     * @brief Executes a prepared statement synchronously.
     *
     * @param sql The SQL query with placeholders.
     * @param params The parameters to be bound to the prepared statement.
     * @return True if the execution is successful, false otherwise.
     */
    bool executePreparedStatementSync(const std::string& sql, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes a prepared statement asynchronously.
     *
     * @param sql The SQL query with placeholders.
     * @param params The parameters to be bound to the prepared statement.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executePreparedStatementAsync(const std::string& sql, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes a batch of SQL queries synchronously.
     *
     * @param sqlBatch A vector of SQL queries to execute as a batch.
     * @return True if the execution is successful for all queries, false otherwise.
     */
    bool executeBatchSync(const std::vector<std::string>& sqlBatch) __cell_override;

    /**
     * @brief Executes a batch of SQL queries asynchronously.
     *
     * @param sqlBatch A vector of SQL queries to execute as a batch.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executeBatchAsync(const std::vector<std::string>& sqlBatch) __cell_override;

    /**
     * @brief Executes a stored procedure synchronously.
     *
     * @param procedure The name of the stored procedure to execute.
     * @return True if the execution of the stored procedure is successful, false otherwise.
     */
    bool executeProcedureSync(const std::string& procedure) __cell_override;

    /**
     * @brief Executes a stored procedure asynchronously.
     *
     * @param procedure The name of the stored procedure to execute.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executeProcedureAsync(const std::string& procedure) __cell_override;

    /**
     * @brief Executes an SQL query synchronously and returns the result as a 2D vector of strings.
     *
     * @param sql The SQL query to execute.
     * @return A 2D vector of strings representing the result of the query.
     */
    std::vector<std::vector<std::string>> querySync(const std::string& sql) __cell_override;

    /**
     * @brief Executes an SQL query asynchronously and returns the result as a future object.
     *
     * @param sql The SQL query to execute.
     * @return A future object that can be used to obtain the result of the query.
     */
    std::future<std::vector<std::vector<std::string>>> queryAsync(const std::string& sql) __cell_override;

    /**
     * @brief Executes an SQL query with parameters synchronously and returns the result as a 2D vector of strings.
     *
     * @param sql The SQL query with placeholders.
     * @param params The parameters to be bound to the query.
     * @return A 2D vector of strings representing the result of the query.
     */
    std::vector<std::vector<std::string>> queryWithParamsSync(const std::string& sql, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes an SQL query with parameters asynchronously and returns the result as a future object.
     *
     * @param sql The SQL query with placeholders.
     * @param params The parameters to be bound to the query.
     * @return A future object that can be used to obtain the result of the query.
     */
    std::future<std::vector<std::vector<std::string>>> queryWithParamsAsync(const std::string& sql, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes an SQL query with parameters synchronously.
     *
     * @param sql The SQL query with placeholders.
     * @param params The parameters to be bound to the query.
     * @return True if the execution is successful, false otherwise.
     */
    bool executeWithParamsSync(const std::string& sql, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes an SQL query with parameters asynchronously.
     *
     * @param sql The SQL query with placeholders.
     * @param params The parameters to be bound to the query.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executeWithParamsAsync(const std::string& sql, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes a batch of SQL queries with parameters synchronously.
     *
     * @param sql The SQL query with placeholders.
     * @param paramsBatch A vector of parameter vectors to be bound to the query.
     * @return True if the execution is successful for all queries, false otherwise.
     */
    bool executeBatchWithParamsSync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch) __cell_override;

    /**
     * @brief Executes a batch of SQL queries with parameters asynchronously.
     *
     * @param sql The SQL query with placeholders.
     * @param paramsBatch A vector of parameter vectors to be bound to the query.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executeBatchWithParamsAsync(const std::string& sql, const std::vector<std::vector<std::string>>& paramsBatch) __cell_override;

    /**
     * @brief Executes a stored procedure with parameters synchronously.
     *
     * @param procedure The name of the stored procedure to execute.
     * @param params The parameters to be bound to the stored procedure.
     * @return True if the execution of the stored procedure is successful, false otherwise.
     */
    bool executeProcedureWithParamsSync(const std::string& procedure, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Executes a stored procedure with parameters asynchronously.
     *
     * @param procedure The name of the stored procedure to execute.
     * @param params The parameters to be bound to the stored procedure.
     * @return A future object that can be used to obtain the result of the execution.
     */
    std::future<bool> executeProcedureWithParamsAsync(const std::string& procedure, const std::vector<std::string>& params) __cell_override;

    /**
     * @brief Sanitizes an input string to prevent SQL injection attacks.
     *
     * @param input The input string to sanitize.
     * @return The sanitized input string.
     */
    std::string sanitizeInput(const std::string& input);

    /**
     * @brief Escapes special characters in a string to be used in SQL queries, synchronously.
     *
     * @param str The string to escape.
     * @return The escaped string.
     */
    std::string escapeString(const std::string& str) __cell_override;

    /**
     * @brief Sets the connection timeout in seconds.
     *
     * @param timeoutSeconds The connection timeout value in seconds.
     */
    void setConnectionTimeout(int timeoutSeconds) __cell_override;

    /**
     * @brief Retrieves the names of all tables in the database.
     *
     * @return A vector of table names.
     */
    std::vector<std::string> getTableNames() __cell_override;

    /**
     * @brief Retrieves the column names of a specific table in the database.
     *
     * @param tableName The name of the table.
     * @return A vector of column names.
     */
    std::vector<std::string> getTableColumns(const std::string& tableName) __cell_override;

    /**
     * @brief Retrieves the column types of a specific table in the database.
     *
     * @param tableName The name of the table.
     * @return A vector of column types.
     */
    std::vector<std::string> getTableColumnTypes(const std::string& tableName) __cell_override;

    /**
     * @brief Retrieves the primary key of a specific table in the database.
     *
     * @param tableName The name of the table.
     * @return The primary key of the table.
     */
    std::string getTablePrimaryKey(const std::string& tableName) __cell_override;

    /**
     * @brief Retrieves the foreign key details of a specific table in the database.
     *
     * @param tableName The name of the table.
     * @param foreignKey The name of the foreign key.
     * @return A pair of strings representing the referenced table and column of the foreign key.
     */
    std::pair<std::string, std::string> getTableForeignKey(const std::string& tableName, const std::string& foreignKey) __cell_override;


    /**
     * @brief Creates a new table in the database with the specified table name and columns.
     *
     * @param tableName The name of the table to create.
     * @param columns A vector of column definitions for the table.
     * @return True if the table creation is successful, false otherwise.
     */
    bool createTable(const std::string& tableName, const std::vector<std::string>& columns) __cell_override;

    /**
     * @brief Drops an existing table from the database.
     *
     * @param tableName The name of the table to drop.
     * @return True if the table is successfully dropped, false otherwise.
     */
    bool dropTable(const std::string& tableName) __cell_override;

    /**
     * @brief Adds a new column to an existing table in the database.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column to add.
     * @param columnType The data type of the column.
     * @return True if the column is successfully added, false otherwise.
     */
    bool addColumn(const std::string& tableName, const std::string& columnName, const std::string& columnType) __cell_override;

    /**
     * @brief Modifies the data type of an existing column in a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column to modify.
     * @param newColumnType The new data type for the column.
     * @return True if the column modification is successful, false otherwise.
     */
    bool modifyColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnType) __cell_override;

    /**
     * @brief Renames an existing column in a table.
     *
     * @param tableName The name of the table.
     * @param columnName The current name of the column to rename.
     * @param newColumnName The new name for the column.
     * @return True if the column is successfully renamed, false otherwise.
     */
    bool renameColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnName) __cell_override;

    /**
     * @brief Deletes an existing column from a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column to delete.
     * @return True if the column is successfully deleted, false otherwise.
     */
    bool deleteColumn(const std::string& tableName, const std::string& columnName) __cell_override;

    /**
     * @brief Retrieves the last inserted ID in the database.
     *
     * @return The last inserted ID.
     */
    Types::uint getLastInsertID() __cell_override;

    /**
     * @brief Retrieves the existing indexes of a table in the database.
     *
     * @param tableName The name of the table.
     * @return A vector of strings representing the existing indexes of the table.
     */
    std::vector<std::string> getExistingIndexes(const std::string& tableName) __cell_override;

    /**
     * @brief Checks if an index exists in a table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @return True if the index exists, false otherwise.
     */
    bool indexExists(const std::string& tableName, const std::string& indexName) __cell_override;

    /**
     * @brief Creates an index on a table with the specified index name and columns.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index to create.
     * @param columns A vector of column names to include in the index.
     * @return True if the index creation is successful, false otherwise.
     */
    bool createIndex(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns) __cell_override;

    /**
     * @brief Drops an index from a table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index to drop.
     * @return True if the index is successfully dropped, false otherwise.
     */
    bool dropIndex(const std::string& tableName, const std::string& indexName) __cell_override;

    /**
     * @brief Generates the SQL statement to create an index on a table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @param columns A vector of column names to include in the index.
     * @return The SQL statement to create the index.
     */
    std::string generateCreateIndexSQL(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns) __cell_override;

    /**
     * @brief Generates the SQL statement to drop an index from a table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @return The SQL statement to drop the index.
     */
    std::string generateDropIndexSQL(const std::string& tableName, const std::string& indexName) __cell_override;

    /**
     * @brief Performs a bulk insert of data into a table.
     *
     * @param tableName The name of the table.
     * @param data A vector of vectors representing the data rows to insert.
     * @return True if the bulk insert is successful, false otherwise.
     */
    bool bulkInsert(const std::string& tableName, const std::vector<std::vector<std::string>>& data) __cell_override;

    /**
     * @brief Performs a bulk update of data in a table based on a condition.
     *
     * @param tableName The name of the table.
     * @param data A vector of vectors representing the data rows to update.
     * @param condition The condition for updating the data.
     * @return True if the bulk update is successful, false otherwise.
     */
    bool bulkUpdate(const std::string& tableName, const std::vector<std::vector<std::string>>& data, const std::string& condition) __cell_override;

    /**
     * @brief Performs a bulk delete of data from a table based on a condition.
     *
     * @param tableName The name of the table.
     * @param condition The condition for deleting the data.
     * @return True if the bulk delete is successful, false otherwise.
     */
    bool bulkDelete(const std::string& tableName, const std::string& condition) __cell_override;

    /**
     * @brief Migrates data from a source table to a destination table.
     *
     * @param sourceTableName The name of the source table.
     * @param destinationTableName The name of the destination table.
     * @return True if the data migration is successful, false otherwise.
     */
    bool migrateData(const std::string& sourceTableName, const std::string& destinationTableName) __cell_override;


    /**
     * @brief Executes a query with pagination, returning a subset of results based on the specified page number and page size.
     *
     * @param sql The SQL query to execute.
     * @param pageNumber The page number of the results to retrieve.
     * @param pageSize The maximum number of results per page.
     * @return A vector of vectors representing the paginated query results.
     */
    std::vector<std::vector<std::string>> queryWithPagination(const std::string& sql, int pageNumber, int pageSize) __cell_override;

    /**
     * @brief Retrieves the number of rows in a table.
     *
     * @param tableName The name of the table.
     * @return The total number of rows in the table.
     */
    int getRowCount(const std::string& tableName) __cell_override;

    /**
     * @brief Retrieves the maximum value of a column in a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column.
     * @return The maximum value of the column.
     */
    std::string getMaxValue(const std::string& tableName, const std::string& columnName) __cell_override;

    /**
     * @brief Retrieves the minimum value of a column in a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column.
     * @return The minimum value of the column.
     */
    std::string getMinValue(const std::string& tableName, const std::string& columnName) __cell_override;

    /**
     * @brief Retrieves the average value of a column in a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column.
     * @return The average value of the column.
     */
    double getAverageValue(const std::string& tableName, const std::string& columnName) __cell_override;

    /**
     * @brief Retrieves the sum of values in a column of a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column.
     * @return The sum of values in the column.
     */
    double getSumValue(const std::string& tableName, const std::string& columnName) __cell_override;

    /**
     * @brief Retrieves the distinct values of a column in a table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column.
     * @return A vector of strings representing the distinct values of the column.
     */
    std::vector<std::string> getDistinctValues(const std::string& tableName, const std::string& columnName) __cell_override;

    /**
     * @brief Executes a script by reading and executing SQL statements from a file.
     *
     * @param filename The name of the file containing the SQL script.
     * @return True if the script execution is successful, false otherwise.
     */
    bool executeScriptFromFile(const std::string& filename) __cell_override;

    /**
     * @brief Creates a backup of the database to a file.
     *
     * @param backupFilename The name of the backup file.
     * @return True if the database backup is successful, false otherwise.
     */
    bool backupDatabase(const std::string& backupFilename) __cell_override;

    /**
     * @brief Restores a database from a backup file.
     *
     * @param backupFilename The name of the backup file to restore from.
     * @return True if the database restore is successful, false otherwise.
     */
    bool restoreDatabase(const std::string& backupFilename) __cell_override;

    /**
     * @brief Retrieves the list of databases available in the server.
     *
     * @return A vector of strings representing the names of the databases.
     */
    std::vector<std::string> getDatabaseList() __cell_override;

    /**
     * @brief Creates a new database with the specified name.
     *
     * @param databaseName The name of the database to create.
     * @return True if the database creation is successful, false otherwise.
     */
    bool createDatabase(const std::string& databaseName) __cell_override;

    /**
     * @brief Drops an existing database with the specified name.
     *
     * @param databaseName The name of the database to drop.
     * @return True if the database drop is successful, false otherwise.
     */
    bool dropDatabase(const std::string& databaseName) __cell_override;

    /**
     * @brief Grants specified privileges to a user for a given database.
     *
     * @param username The name of the user.
     * @param databaseName The name of the database.
     * @param privileges A vector of strings representing the privileges to grant.
     * @return True if the privilege granting is successful, false otherwise.
     */
    bool grantPrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges) __cell_override;

    /**
     * @brief Revokes specified privileges from a user for a given database.
     *
     * @param username The name of the user.
     * @param databaseName The name of the database.
     * @param privileges A vector of strings representing the privileges to revoke.
     * @return True if the privilege revocation is successful, false otherwise.
     */
    bool revokePrivileges(const std::string& username, const std::string& databaseName, const std::vector<std::string>& privileges) __cell_override;

    /**
     * @brief Retrieves the size of a table in the database.
     *
     * @param tableName The name of the table.
     * @return The size of the table in bytes.
     */
    int getTableSize(const std::string& tableName) __cell_override;

    /**
     * @brief Executes a non-query SQL statement.
     *
     * @param sql The SQL statement to execute.
     */
    void executeNonQuery(const std::string& sql) __cell_override;

    /**
     * @brief Imports data into a table from a file.
     *
     * @param tableName The name of the table.
     * @param filePath The path to the file containing the data to import.
     */
    void importTable(const std::string& tableName, const std::string& filePath) __cell_override;

    /**
     * @brief Exports data from a table to a file.
     *
     * @param tableName The name of the table.
     * @param filePath The path to the file where the data will be exported.
     */
    void exportTable(const std::string& tableName, const std::string& filePath) __cell_override;

    /**
     * @brief Retrieves the last error message generated by the database connection.
     *
     * @return A string representing the last error message.
     */
    std::string getLastError() __cell_override;


private:
    /**
     * @brief Validates the syntax of an SQL query.
     *
     * @param sql The SQL query to validate.
     * @return True if the query syntax is valid, false otherwise.
     */
    bool validateSqlQuery(const std::string& sql) __cell_override;

    /**
     * @brief Validates the parameters passed to a query.
     *
     * @param params The vector of strings representing the query parameters.
     * @return True if the parameters are valid, false otherwise.
     */
    bool validateParams(const std::vector<std::string>& params) __cell_override;


private:
    System::EngineController engineController;
    MySQLData            m_mysqlData;
    MySqlPtr             connection;        //!< Pointer to the MySQL connection object.
    MYSQL_RES*           m_result;          //!< Pointer to the MySQL result set.
    MySqlConnectionPool& connectionPool;    //!< Reference to the MySQL connection pool.
};

CELL_NAMESPACE_END

#endif
#endif // CELL_MYSQL_HPP
