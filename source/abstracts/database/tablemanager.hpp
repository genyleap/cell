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


#ifndef CELL_DATABASE_TABLE_MANAGER_ABSTRACT_HPP
#define CELL_DATABASE_TABLE_MANAGER_ABSTRACT_HPP

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
 * @brief The TableManager class provides methods for managing database tables.
 */
class TableManager {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(TableManager)

    /**
     * @brief Get the names of all tables in the database.
     *
     * This method returns a vector containing the names of all tables in the database.
     *
     * @return A vector of table names.
     */
    __cell_virtual std::vector<std::string> getTableNames() = __cell_zero;

    /**
     * @brief Get the columns of a specific table.
     *
     * This method returns a vector containing the column names of the specified table.
     *
     * @param tableName The name of the table.
     * @return A vector of column names.
     */
    __cell_virtual std::vector<std::string> getTableColumns(const std::string& tableName) = __cell_zero;

    /**
     * @brief Get the column types of a specific table.
     *
     * This method returns a vector containing the column types of the specified table.
     *
     * @param tableName The name of the table.
     * @return A vector of column types.
     */
    __cell_virtual std::vector<std::string> getTableColumnTypes(const std::string& tableName) = __cell_zero;

    /**
     * @brief Get the primary key of a specific table.
     *
     * This method returns the primary key of the specified table as a string.
     *
     * @param tableName The name of the table.
     * @return The primary key.
     */
    __cell_virtual std::string getTablePrimaryKey(const std::string& tableName) = __cell_zero;

    /**
     * @brief Get the foreign key of a specific table.
     *
     * This method returns the foreign key of the specified table as a pair of strings, where the first element is the
     * referenced table name and the second element is the referenced foreign key column name.
     *
     * @param tableName The name of the table.
     * @param foreignKey The foreign key column name.
     * @return A pair containing the referenced table name and foreign key column name.
     */
    __cell_virtual std::pair<std::string, std::string> getTableForeignKey(const std::string& tableName, const std::string& foreignKey) = __cell_zero;

    /**
     * @brief Create a new table.
     *
     * This method creates a new table with the specified name and columns.
     *
     * @param tableName The name of the table.
     * @param columns The column names.
     * @return True if the table was created successfully, false otherwise.
     */
    __cell_virtual bool createTable(const std::string& tableName, const std::vector<std::string>& columns) = __cell_zero;

    /**
     * @brief Drop an existing table.
     *
     * This method drops the specified table from the database.
     *
     * @param tableName The name of the table to drop.
     * @return True if the table was dropped successfully, false otherwise.
     */
    __cell_virtual bool dropTable(const std::string& tableName) = __cell_zero;

    /**
     * @brief Add a new column to an existing table.
     *
     * This method adds a new column to the specified table with the given name and type.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the new column.
     * @param columnType The type of the new column.
     * @return True if the column was added successfully, false otherwise.
     */
    __cell_virtual bool addColumn(const std::string& tableName, const std::string& columnName, const std::string& columnType) = __cell_zero;

    /**
     * @brief Modify the type of an existing column in a table.
     *
     * This method modifies the type of an existing column in the specified table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column to modify.
     * @param newColumnType The new type of the column.
     * @return True if the column was modified successfully, false otherwise.
     */
    __cell_virtual bool modifyColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnType) = __cell_zero;

    /**
     * @brief Rename an existing column in a table.
     *
     * This method renames an existing column in the specified table.
     *
     * @param tableName The name of the table.
     * @param columnName The current name of the column.
     * @param newColumnName The new name of the column.
     * @return True if the column was renamed successfully, false otherwise.
     */
    __cell_virtual bool renameColumn(const std::string& tableName, const std::string& columnName, const std::string& newColumnName) = __cell_zero;

    /**
     * @brief Get the names of existing indexes on a table.
     *
     * This method returns a vector containing the names of all indexes on the specified table.
     *
     * @param tableName The name of the table.
     * @return A vector of index names.
     */
    __cell_virtual std::vector<std::string> getExistingIndexes(const std::string& tableName) = __cell_zero;

    /**
     * @brief Check if an index exists on a table.
     *
     * This method checks if the specified index exists on the specified table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @return True if the index exists, false otherwise.
     */
    __cell_virtual bool indexExists(const std::string& tableName, const std::string& indexName) = __cell_zero;

    /**
     * @brief Delete a column from a table.
     *
     * This method deletes the specified column from the specified table.
     *
     * @param tableName The name of the table.
     * @param columnName The name of the column to delete.
     * @return True if the column was deleted successfully, false otherwise.
     */
    __cell_virtual bool deleteColumn(const std::string& tableName, const std::string& columnName) = __cell_zero;

    /**
     * @brief Create an index on a table.
     *
     * This method creates an index with the specified name on the specified table and columns.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @param columns The column names for the index.
     * @return True if the index was created successfully, false otherwise.
     */
    __cell_virtual bool createIndex(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns) = __cell_zero;

    /**
     * @brief Generate the SQL statement for creating an index.
     *
     * This method generates the SQL statement for creating an index with the specified name on the specified table and columns.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @param columns The column names for the index.
     * @return The SQL statement for creating the index.
     */
    __cell_virtual std::string generateCreateIndexSQL(const std::string& tableName, const std::string& indexName, const std::vector<std::string>& columns) = __cell_zero;

    /**
     * @brief Generate the SQL statement for dropping an index.
     *
     * This method generates the SQL statement for dropping the index with the specified name from the specified table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index.
     * @return The SQL statement for dropping the index.
     */
    __cell_virtual std::string generateDropIndexSQL(const std::string& tableName, const std::string& indexName) = __cell_zero;

    /**
     * @brief Drop an existing index from a table.
     *
     * This method drops the specified index from the specified table.
     *
     * @param tableName The name of the table.
     * @param indexName The name of the index to drop.
     * @return True if the index was dropped successfully, false otherwise.
     */
    __cell_virtual bool dropIndex(const std::string& tableName, const std::string& indexName) = __cell_zero;

    /**
     * @brief Retrieves the last inserted ID from the specified database connection.
     *
     * This function returns the last auto-generated ID that was inserted into the database using the specified connection.
     *
     * @return The last inserted ID as an unsigned integer.
     */
    __cell_virtual Types::uint getLastInsertID() = __cell_zero;

    /**
     * @brief Get the last error message.
     *
     * This method returns the last error message generated by the TableManager.
     *
     * @return The last error message.
     */
    __cell_virtual std::string getLastError() = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_TABLE_MANAGER_ABSTRACT_HPP
