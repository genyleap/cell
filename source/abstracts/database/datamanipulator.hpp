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

#ifndef CELL_DATABASE_DATA_MANIPULATOR_ABSTRACT_HPP
#define CELL_DATABASE_DATA_MANIPULATOR_ABSTRACT_HPP

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
 * @brief The abstract base class for data manipulation operations.
 */
class DataManipulator {
public:
    /**
     * @brief Default constructor and destructor.
     */
    CELL_DEFAULT_INTERFACE_OCTORS(DataManipulator)

    /**
     * @brief Perform a bulk insert operation.
     *
     * @param tableName Name of the table to insert data into.
     * @param data Vector of vectors representing the data to be inserted.
     * @return bool True if the bulk insert operation was successful, false otherwise.
     */
    __cell_virtual bool bulkInsert(const std::string& tableName, const std::vector<std::vector<std::string>>& data) = __cell_zero;

    /**
     * @brief Perform a bulk update operation.
     *
     * @param tableName Name of the table to update.
     * @param data Vector of vectors representing the data to be updated.
     * @param condition The condition to apply for updating the data.
     * @return bool True if the bulk update operation was successful, false otherwise.
     */
    __cell_virtual bool bulkUpdate(const std::string& tableName, const std::vector<std::vector<std::string>>& data, const std::string& condition) = __cell_zero;

    /**
     * @brief Perform a bulk delete operation.
     *
     * @param tableName Name of the table to delete from.
     * @param condition The condition to apply for deleting the data.
     * @return bool True if the bulk delete operation was successful, false otherwise.
     */
    __cell_virtual bool bulkDelete(const std::string& tableName, const std::string& condition) = __cell_zero;

    /**
     * @brief Migrate data from a source table to a destination table.
     *
     * @param sourceTableName Name of the source table.
     * @param destinationTableName Name of the destination table.
     * @return bool True if the data migration was successful, false otherwise.
     */
    __cell_virtual bool migrateData(const std::string& sourceTableName, const std::string& destinationTableName) = __cell_zero;

    /**
     * @brief Query data from a table with pagination.
     *
     * @param sql The SQL query string.
     * @param pageNumber The page number of the result set to retrieve.
     * @param pageSize The number of records per page.
     * @return std::vector<std::vector<std::string>> The queried data with pagination.
     */
    __cell_virtual std::vector<std::vector<std::string>> queryWithPagination(const std::string& sql, int pageNumber, int pageSize) = __cell_zero;

    /**
     * @brief Get the row count of a table.
     *
     * @param tableName Name of the table.
     * @return int The number of rows in the table.
     */
    __cell_virtual int getRowCount(const std::string& tableName)  = __cell_zero;

    /**
     * @brief Get the maximum value of a column in a table.
     *
     * @param tableName Name of the table.
     * @param columnName Name of the column.
     * @return std::string The maximum value of the column.
     */
    __cell_virtual std::string getMaxValue(const std::string& tableName, const std::string& columnName)  = __cell_zero;

    /**
     * @brief Get the minimum value of a column in a table.
     *
     * @param tableName Name of the table.
     * @param columnName Name of the column.
     * @return std::string The minimum value of the column.
     */
    __cell_virtual std::string getMinValue(const std::string& tableName, const std::string& columnName)  = __cell_zero;

    /**
     * @brief Get the average value of a column in a table.
     *
     * @param tableName Name of the table.
     * @param columnName Name of the column.
     * @return double The average value of the column.
     */
    __cell_virtual double getAverageValue(const std::string& tableName, const std::string& columnName)  = __cell_zero;

    /**
     * @brief Get the sum value of a column in a table.
     *
     * @param tableName Name of the table.
     * @param columnName Name of the column.
     * @return double The sum value of the column.
     */
    __cell_virtual double getSumValue(const std::string& tableName, const std::string& columnName)  = __cell_zero;

    /**
     * @brief Get the distinct values of a column in a table.
     *
     * @param tableName Name of the table.
     * @param columnName Name of the column.
     * @return std::vector<std::string> The distinct values of the column.
     */
    __cell_virtual std::vector<std::string> getDistinctValues(const std::string& tableName, const std::string& columnName)  = __cell_zero;
};


CELL_NAMESPACE_END

#endif  // CELL_DATABASE_DATA_MANIPULATOR_ABSTRACT_HPP
