/*!
 * @file        usermedia.hpp
 * @brief       This file is part of the Cell System.
 * @details     User media interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_USER_MEDIA_ABSTRACT_HPP
#define CELL_USER_MEDIA_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

enum class AvatarViewStatus : Types::u8
{
    NoAvatar, ForEveryone, SpecificGroups, SelectedUsers
};

enum class ImageViewStatus : Types::u8
{
    NoAvatar, ForEveryone, SpecificGroups, SelectedUsers
};

enum class CoverViewStatus : Types::u8
{
    NoAvatar, ForEveryone, SpecificGroups, SelectedUsers
};

enum class StoryViewStatus : Types::u8
{
    NoAvatar, ForEveryone, SpecificGroups, SelectedUsers
};

/*!
 * \brief The AbstractAvatar class
 */
class __cell_export AbstractAvatar
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractAvatar)

    /*!
     * \brief function get will gets profile picture address by own memberId.
     * \param memberId is unique id for user.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString get(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief function add will inserts avatar image by memberId and image address or link.
     * \param memberId is unique id for user.
     * \param url is a link for image.
     * \returns as string.
     */
    __cell_no_discard_virtual bool add(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will changes and updates profile picture by memberId and a new image address or link.
     * \param memberId is unique id for user.
     * \param url is a link for image.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool update(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief remove function will removes profile picture by memberId.
     * \param memberId is unique id for user.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool remove(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief viewStatus function will checks the status of view for user's avatar.
     * \param viewStatus as AvatarViewStatus enum.
     * \returns as one of AvatarViewStatus's items.
     */
    __cell_no_discard_virtual AvatarViewStatus viewStatus(const AvatarViewStatus viewStatus) __cell_const_noexcept = __cell_zero;


private:
    AvatarViewStatus m_avatarViewStatus;
};

/*!
 * \brief The AbstractImage class
 */
class __cell_export AbstractImage
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractImage)

    /*!
     * \brief get function will gets profile image address by own memberId.
     * \param memberId is unique id for user.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString get(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will inserts profile picture by memberId and image address or link.
     * \param memberId is unique id for user.
     * \param url is a link for image.
     * \returns as string.
     */
    __cell_no_discard_virtual bool add(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will changes and updates profile image by memberId and a new image address or link.
     * \param memberId is unique id for user.
     * \param url is a link for image.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool update(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief remove function will removes profile image by memberId.
     * \param memberId is unique id for user.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool remove(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief viewStatus function will checks the status of view for user's image.
     * \param viewStatus as ImageViewStatus enum.
     * \returns as one of ImageViewStatus's items.
     */
    __cell_no_discard_virtual ImageViewStatus viewStatus(const ImageViewStatus viewStatus) __cell_const_noexcept = __cell_zero;


private:
    ImageViewStatus m_imageViewStatus;
};

/*!
 * \brief The AbstractCover class
 */
class __cell_export AbstractCover
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractCover)

    /*!
     * \brief get function will gets profile cover address by own memberId.
     * \param memberId is unique id for user.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString get(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will inserts profile cover by memberId and cover address or link.
     * \param memberId is unique id for user.
     * \param url is a link for cover.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool add(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will changes and updates profile cover by memberId and a new cover address or link.
     * \param memberId is unique id for user.
     * \param url is a link for cover.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool update(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief remove function will removes profile cover by memberId.
     * \param memberId is unique id for user.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool remove(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief viewStatus function will checks the status of view for user's cover.
     * \param viewStatus as ImageViewStatus enum.
     * \returns as one of ImageViewStatus's items.
     */
    __cell_no_discard_virtual CoverViewStatus viewStatus(const CoverViewStatus viewStatus) __cell_const_noexcept = __cell_zero;


private:
    CoverViewStatus m_coverViewStatus;
};

/*!
 * \brief The AbstractStory class
 */
class __cell_export AbstractStory
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractStory)

    /*!
     * \brief get function will gets profile story address by own memberId.
     * \param memberId is unique id for user.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString get(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will inserts profile story by memberId and story address or link.
     * \param memberId is unique id for user.
     * \param url is a link for cover.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool add(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will changes and updates profile story by memberId and a new story address or link.
     * \param memberId is unique id for user.
     * \param url is a link for story.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool update(const Types::OptionalNumeric memberId, const std::string& url) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief remove function will removes profile story by memberId.
     * \param memberId is unique id for user.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool remove(const Types::OptionalNumeric memberId) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief viewStatus function will checks the status of view for user's story.
     * \param viewStatus as StoryViewStatus enum.
     * \returns as one of StoryViewStatus's items.
     */
    __cell_no_discard_virtual StoryViewStatus viewStatus(const StoryViewStatus viewStatus) __cell_const_noexcept = __cell_zero;


private:
    StoryViewStatus m_storyViewStatus;
};

CELL_NAMESPACE_END

#endif // CELL_USER_MEDIA_ABSTRACT_HPP
