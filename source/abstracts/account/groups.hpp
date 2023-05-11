/*!
 * @file        groups.hpp
 * @brief       This file is part of the Cell System.
 * @details     Groups manager interface for accounts.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_GROUPS_ABSTRACT_HPP
#define CELL_GROUPS_ABSTRACT_HPP

//! Cell's Common.
#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

__cell_enum_class SpecialType : Types::u8
{
    AsDefaultUsers      =   0x1,    //!< As a Simple user [Limited].
    AsDevelopers        =   0x2,    //!< As a Developer/Programmer.
    AsDesigners         =   0x3,    //!< As a Designer.
    AsManagers          =   0x4,    //!< As a Manager.
    AsRobots            =   0x5,    //!< As a Robot.
    AsFullAccess        =   0x6     //!< As a master with all privileges.
};

/*!
 * \brief The GroupData class
 */
struct GroupData __cell_final
{
    Types::u32                 id              {};     //!< Id for group.
    Types::OptionalString      title           {};     //!< Title for group.
    Types::OptionalString      description     {};     //!< Description for group.
    Types::u32                 parentId        {};     //!< Parent's id.
    Types::OptionalBool        protection      {};     //!< Group's protection mode.
    Types::OptionalString      icon            {};     //!< Icon for group.
    Types::u32                 stars           {};     //!< Total of stars.
    Types::OptionalString      stylePrefix     {};     //!< Custom style for prefix.
    Types::OptionalString      styleSuffix     {};     //!< Custom style for suffix.
    Types::OptionalString      doHtml          {};     //!< Can insert html tag inside posts.
    Types::OptionalString      service         {};     //!< Service for group.
    Types::OptionalString      module          {};     //!< Module for group.
    Types::OptionalString      plugin          {};     //!< Plugin for group.
    Types::OptionalBool        root            {};     //!< Group can be access as root permission.
    Types::OptionalBool        master          {};     //!< Group can be access as master permission.
    Types::OptionalNumeric     maxUpload       {};     //!< Maximum upload size.
    Types::OptionalNumeric     maxDownload     {};     //!< Maximum download size.
    Types::OptionalNumeric     maxPayment      {};     //!< Maximum payment count.
    Types::OptionalBool        captcha         {};     //!< Enable captcha for group or not.
    Types::OptionalBool        moderate        {};     //!< Group can access to site as moderator.
    Types::OptionalString      platforms       {};     //!< Usable platforms.
    Types::OptionalBool        hasSign         {};     //!< Group can has sign under the posts.
    Types::u32                 report          {};     //!< Total of reports.
    Types::u32                 rate            {};     //!< Total of rates.
    Types::OptionalBool        createOwnUser   {};     //!< Can create own user [sub user].
    Types::OptionalBool        createOwnPost   {};     //!< Can create own post.
    Types::OptionalBool        editOwnPost     {};     //!< Can edit own posts.
    Types::OptionalBool        editAllPost     {};     //!< Can edit all posts.
    Types::OptionalBool        hideOwnPost     {};     //!< Can hide own posts.
    Types::OptionalBool        hideAllPost     {};     //!< Can hide all posts.
    Types::OptionalBool        removeOwnPost   {};     //!< Can remove own posts.
    Types::OptionalBool        removeAllPost   {};     //!< Can remove all posts.
    Types::OptionalBool        changeOwnPost   {};     //!< Can change own posts.
    Types::OptionalBool        canPromote      {};     //!< Can promote own posts.
    Types::OptionalBool        canCoverChange  {};     //!< Can change own cover.
    Types::OptionalBool        canAvatarChange {};     //!< Can change own avatar.
    Types::OptionalBool        editProfile     {};     //!< Can edit profile details.
    Types::OptionalBool        useAnimation    {};     //!< Can use animation file like gif or lotties.
    Types::OptionalNumeric     maxCoverSize    {};     //!< Maximum cover size.
    Types::OptionalNumeric     maxAvatarSize   {};     //!< Maximum avatar size.
    Types::OptionalBool        banned          {};     //!< Banned mode.
    Types::OptionalNumeric     floodLimit      {};     //!< Flood limitation.
    Types::OptionalNumeric     searchLimit     {};     //!< Search limitation.
    Types::OptionalBool        accessClosed    {};     //!< Can access to closed site.
    Types::OptionalBool        apiAccess       {};     //!< Can access to api as developer.
    SpecialType                special         {};     //!< Is special group.
};

/*!
 * \brief The AbstractGroups class
 */
class __cell_export AbstractGroups
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractGroups)

    /*!
     * \brief add function will inserts new group.
     * \param groupData is contains all data of permissions.
     * \returns boolean.
     */
    __cell_no_discard_virtual bool add(const GroupData& groupData) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief edit function will updates group.
     * \param id is unique id for group.
     * \param groupData is all data for group.
     * \returns boolean.
     */
    __cell_no_discard_virtual bool edit(const Types::u32 id, const GroupData& groupData) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief remove function will removes group by own id.
     * \param id is unique id for group.
     * \returns boolean.
     */
    __cell_no_discard_virtual bool remove(const Types::u32 id) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will returns all data from group.
     * \param id is unique id for group.
     * \returns GroupData as own data.
     */
    __cell_no_discard_virtual GroupData get(const Types::u32 id) __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractGroups)
    GroupData* m_groupData;
};

CELL_NAMESPACE_END

#endif  // CELL_GROUPS_ABSTRACT_HPP
