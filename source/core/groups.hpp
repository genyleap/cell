/*!
 * @file        groups.hpp
 * @brief       This file is part of the Cell Engine.
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

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell)

__cell_enum_class SpecialType : u8
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
    u32                 id              {};     //!< Id for group.
    OptionalString      title           {};     //!< Title for group.
    OptionalString      description     {};     //!< Description for group.
    u32                 parentId        {};     //!< Parent's id.
    OptionalBool        protection      {};     //!< Group's protection mode.
    OptionalString      icon            {};     //!< Icon for group.
    u32                 stars           {};     //!< Total of stars.
    OptionalString      stylePrefix     {};     //!< Custom style for prefix.
    OptionalString      styleSuffix     {};     //!< Custom style for suffix.
    OptionalString      doHtml          {};     //!< Can insert html tag inside posts.
    OptionalString      service         {};     //!< Service for group.
    OptionalString      module          {};     //!< Module for group.
    OptionalString      plugin          {};     //!< Plugin for group.
    OptionalBool        root            {};     //!< Group can be access as root permission.
    OptionalBool        master          {};     //!< Group can be access as master permission.
    OptionalNumeric     maxUpload       {};     //!< Maximum upload size.
    OptionalNumeric     maxDownload     {};     //!< Maximum download size.
    OptionalNumeric     maxPayment      {};     //!< Maximum payment count.
    OptionalBool        captcha         {};     //!< Enable captcha for group or not.
    OptionalBool        moderate        {};     //!< Group can access to site as moderator.
    OptionalString      platforms       {};     //!< Usable platforms.
    OptionalBool        hasSign         {};     //!< Group can has sign under the posts.
    u32                 report          {};     //!< Total of reports.
    u32                 rate            {};     //!< Total of rates.
    OptionalBool        createOwnUser   {};     //!< Can create own user [sub user].
    OptionalBool        createOwnPost   {};     //!< Can create own post.
    OptionalBool        editOwnPost     {};     //!< Can edit own posts.
    OptionalBool        editAllPost     {};     //!< Can edit all posts.
    OptionalBool        hideOwnPost     {};     //!< Can hide own posts.
    OptionalBool        hideAllPost     {};     //!< Can hide all posts.
    OptionalBool        removeOwnPost   {};     //!< Can remove own posts.
    OptionalBool        removeAllPost   {};     //!< Can remove all posts.
    OptionalBool        changeOwnPost   {};     //!< Can change own posts.
    OptionalBool        canPromote      {};     //!< Can promote own posts.
    OptionalBool        canCoverChange  {};     //!< Can change own cover.
    OptionalBool        canAvatarChange {};     //!< Can change own avatar.
    OptionalBool        editProfile     {};     //!< Can edit profile details.
    OptionalBool        useAnimation    {};     //!< Can use animation file like gif or lotties.
    OptionalNumeric     maxCoverSize    {};     //!< Maximum cover size.
    OptionalNumeric     maxAvatarSize   {};     //!< Maximum avatar size.
    OptionalBool        banned          {};     //!< Banned mode.
    OptionalNumeric     floodLimit      {};     //!< Flood limitation.
    OptionalNumeric     searchLimit     {};     //!< Search limitation.
    OptionalBool        accessClosed    {};     //!< Can access to closed site.
    SpecialType         special         {};     //!< Is special group.
    OptionalBool        apiAccess       {};     //!< Can access to api as developer.
};

/*!
 * \brief The Groups class
 */
class __cell_export Groups
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Groups)

    /*!
     * \brief add function will add new group.
     * \param groupData is contains all data of permissions.
     * \returns boolean.
     */
    __cell_no_discard bool add(const GroupData& groupData) __cell_noexcept;

    /*!
     * \brief edit function will update group.
     * \param id is unique id for group.
     * \param groupData is all data for group.
     * \returns boolean.
     */
    __cell_no_discard bool edit(const u32 id, const GroupData& groupData) __cell_noexcept;

    /*!
     * \brief remove function will remove group by own id.
     * \param id is unique id for group.
     * \returns boolean.
     */
    __cell_no_discard bool remove(const u32 id) __cell_noexcept;

    /*!
     * \brief get function will returns all data from group.
     * \param id is unique id for group.
     * \returns GroupData as own data.
     */
    __cell_no_discard GroupData get(const u32 id) __cell_noexcept;

private:
    CELL_DISABLE_COPY(Groups)
    GroupData* m_groupData;
};

CELL_NAMESPACE_END

#endif  // CELL_GROUPS_HPP
