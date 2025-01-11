/*!
 * @file        activities.hpp
 * @brief       This file is part of the Cell System.
 * @details     User activities interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_USER_ACTIVITIES_ABSTRACT_HPP
#define CELL_USER_ACTIVITIES_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

enum class ActivityAction : Types::u8
{
    SignUp,
    SignIn,
    Update,
    Rules,
    Download,
    Upload,
    Create,
    Remove,
    Rename,
    Change,
    Buy,
    Sell,
    Forward,
    Reply,
    View,
    Move,
    Custom
};

struct ActivityData final
{
    Types::OptionalString datetime         {};
    Types::OptionalString ipAddress        {};
    Types::Optional<ActivityAction> action {};
};

/*!
 * \brief The AbstractActivities class
 */
class __cell_export AbstractActivities
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractActivities)

    /*!
     * \brief function get will gets user activities.
     * \param memberId is unique id for user.
     * \returns as Activity data.
     */
    __cell_no_discard_virtual ActivityData get(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief set function will sets user activities.
     * \param activity is data based on Activity struct members.
     */
    __cell_virtual void set(const ActivityData& activity) __cell_const_noexcept = __cell_zero;

private:
    ActivityData m_activity;
};

CELL_NAMESPACE_END

#endif // CELL_USER_ACTIVITIES_ABSTRACT_HPP
