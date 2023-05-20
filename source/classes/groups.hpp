/*!
 * @file        groups.hpp
 * @brief       This file is part of the Cell System.
 * @details     Groups manager for accounts.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_GROUPS_HPP
#define CELL_GROUPS_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

//! Cell's Abstraction (Interfaces).
#if __has_include(<interface>)
#   include <interface>
#else
#   error "The abstractions of Cell was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The Groups class
 */
class __cell_export Groups : public Abstracts::Account::AbstractGroups
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Groups)

    /*!
     * \brief add function will add new group.
     * \param groupData is contains all data of permissions.
     * \returns boolean.
     */
    __cell_no_discard bool add(const Abstracts::Account::GroupData& groupData) __cell_const_noexcept_override;

    /*!
     * \brief edit function will updates group.
     * \param id is unique id for group.
     * \param groupData is all data for group.
     * \returns boolean.
     */
    __cell_no_discard bool edit(const Types::u32 id, const Abstracts::Account::GroupData& groupData) __cell_const_noexcept_override;

    /*!
     * \brief remove function will removes group by own id.
     * \param id is unique id for group.
     * \returns boolean.
     */
    __cell_no_discard bool remove(const Types::u32 id) __cell_const_noexcept_override;

    /*!
     * \brief get function will returns all data from group.
     * \param id is unique id for group.
     * \returns GroupData as own data.
     */
    __cell_no_discard Abstracts::Account::GroupData get(const Types::u32 id) __cell_const_noexcept_override;

private:
    CELL_DISABLE_COPY(Groups)
    Abstracts::Account::GroupData* m_groupData;
};

CELL_NAMESPACE_END

#endif  // CELL_GROUPS_HPP
