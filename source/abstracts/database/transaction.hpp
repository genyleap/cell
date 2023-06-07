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


#ifndef CELL_DATABASE_TRANSACTION_ABSTRACT_HPP
#define CELL_DATABASE_TRANSACTION_ABSTRACT_HPP

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
 * @brief Database transaction interface.
 *
 * The DatabaseTransaction class provides an interface for managing database transactions.
 * It allows starting, committing, and rolling back transactions.
 */
class DatabaseTransaction {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(DatabaseTransaction)

    /**
     * @brief Begin a database transaction.
     *
     * This method starts a new database transaction.
     *
     * @return True if the transaction was successfully started, false otherwise.
     */
    __cell_virtual bool beginTransaction() = __cell_zero;

    /**
     * @brief Commit the current database transaction.
     *
     * This method commits the changes made during the current database transaction.
     *
     * @return True if the transaction was successfully committed, false otherwise.
     */
    __cell_virtual bool commitTransaction() = __cell_zero;

    /**
     * @brief Rollback the current database transaction.
     *
     * This method rolls back the changes made during the current database transaction.
     *
     * @return True if the transaction was successfully rolled back, false otherwise.
     */
    __cell_virtual bool rollbackTransaction() = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_DATABASE_ABSTRACT_HPP
