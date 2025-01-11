/*!
 * @file        usermanager.hpp
 * @brief       This file is part of the Cell System.
 * @details     User manager interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_USER_MANAGER_ABSTRACT_HPP
#define CELL_USER_MANAGER_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Core (Core Only).
#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's requirements was not found!"
#endif

//! Cell's Abstraction (Interface).
#if __has_include(<abstracts/account>)
#   include <abstracts/account>
#else
#   error "The account abstraction of Cell was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

using ArrayIds = std::vector<Types::OptionalNumeric>; //!< Array as int for user id.

/*!
 * \brief The UserData class
 */
struct UserData __cell_final
{
    UserBasicData basic {}; //!< Basic Data (Default & Required)
};

struct DataTransfer final
{
//    System::DataGetway dataGetway {};   //!< Getway model.
    UserData* userDataPtr {};   //!< A pointer to UserData;
};

/*!
 * \brief The AbstractUserManager class
 */
class __cell_export AbstractUserManager
{
public:
    AbstractUserManager();
    AbstractUserManager(const UserData& userData);
    __cell_virtual ~AbstractUserManager();

    /*!
     * \brief memberId function will retrieves user id (memberId).
     * \param array username is a user unique name.
     * \returns as numeric id.
     */
    __cell_no_discard_virtual Types::OptionalNumeric memberId(const std::vector<std::string>& username) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief The get function returns all the data related to the user based on the memberId.
     * \param int|array ID of the user to be creates.
     * \returns as UserData.
     */

    __cell_no_discard_virtual UserData get(const ArrayIds& ids) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief Create a user in the system.
     * \param array user userData. The keys must match the names of the fields in the database.
     * \returns true, if the user registration process is successful.
     */
    __cell_no_discard_virtual bool create(const std::vector<UserData>& userData) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief Update the user in the system.
     * \param int|array ID of the user to be updated.
     * \param array userData to update. The keys must match the usernames of the fields in the database.
     * \returns true, if the user information is successfully updated.
     */
    __cell_no_discard_virtual bool update(const ArrayIds& ids, const std::vector<UserData>& userData) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief Removing a user from the system.
     * \param int|array ID of the user to be deleted.
     * \returns true, if the target user is deleted successfully.
     */
    __cell_no_discard_virtual bool remove(const ArrayIds& ids) __cell_const_noexcept = __cell_zero;


private:
    DataTransfer *dataTransferPtr{}; //! A pointer to DataTransfer.
};

CELL_NAMESPACE_END

#endif // CELL_USER_MANAGER_ABSTRACT_HPP
