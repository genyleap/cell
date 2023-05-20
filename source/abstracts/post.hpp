/*!
 * @file        post.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Post interface for pages.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_POST_ABSTRACT_HPP
#define CELL_POST_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core not found!"
#endif

#if __has_include("core/message.hpp")
#   include "core/message.hpp"
#else
#   error "Cell's message not found!"
#endif

#if __has_include("core/share.hpp")
#   include "core/share.hpp"
#else
#   error "Cell's share not found!"
#endif

#if __has_include("core/tags.hpp")
#   include "core/tags.hpp"
#else
#   error "Cell's tags not found!"
#endif


CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The PostStatus enum
 */
__cell_enum_class PostStatus : Types::u8
{
    Publish,        //!< Viewable by everyone.
    Future,         //!< Scheduled to be published in a future date.
    Draft,          //!< Incomplete post viewable by anyone with proper user role.
    Pending,        //!< Awaiting a user with the publish capability.
    Private,        //!< Viewable only to Cell users at Administrator level.
    Trash,          //!< Posts in the Trash are assigned the trash status.
    AutoDraft,      //!< Revisions that Cell saves automatically while you are editing.
    Inherit,        //!< Used with a child post (such as Attachments and Revisions) to determine the actual status from the parent post.
    Custom          //!< As custom status.
};

/*!
 * \brief The PostShare class
 */
struct PostData final
{
    ///!BASIC
    Types::OptionalNumeric id              {};    //!< Index of post.
    Types::OptionalNumeric priority        {};    //!< Index of post position.
    Types::OptionalString  title           {};    //!< Title (subject) of post.
    Types::OptionalString  url             {};    //!< Url for post.
    Tags            tags                   {};    //!< Tags list for post.
    Types::OptionalString  text            {};    //!< Text (main content) for post.
    Types::OptionalString  documentTitle   {};    //!< Document title (title of post).
    Types::OptionalString  metaDescr       {};    //!< Meta description (more details) for post.
    ///!MEDIA
    System::MediaType  cover               {};    //!< Image or video for post.
    System::IconType   icon                {};    //!< Icon for post.
    ///!DATETIME
    Types::OptionalString  createdDate     {};    //!< Created date time.
    Types::OptionalString  publishTime     {};    //!< Publishing time.
    Types::OptionalString  pinnedTime      {};    //!< Pinned time.
    Types::OptionalString  lastModified    {};    //!< Last Modified date-time.
    ///!EXTRA
    Types::OptionalBool    inclueInSitemap            {};  //!< If included in sitemap section.
    Types::OptionalBool    canBeModeratedFromFrontend {};  //!< Can be moderated from frontend?!
    Types::OptionalBool    accessByApi     {};  //!< Can be access from api output.
    Types::OptionalString  theme           {};  //!< Post theme.
    Types::OptionalString  link            {};  //!< Post link.
    PostStatus      postStatus      {};  //!< Post status.
    Share           shareAction     {};  //!< Share action.
    ShareData       shareData       {};  //!< Share data.
    Message         message         {};  //!< Messahe for post.
};

/*!
 * \brief The AbstractPost class
 */
class __cell_export AbstractPost
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractPost)

    /*!
     * \brief publish function will create and publish post by PostStatus state.
     * \param specifies data from the PostData.
     * \returns boolean.
     */
    __cell_no_discard_virtual Types::OptionalBool publish(const PostData& postData) __cell_const = __cell_zero;

    /*!
     * \brief remove function will delete a post by own id.
     * \param id is unique index of post.
     * \returns true, if the post is removed successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool remove(const Types::u32 id) __cell_const = __cell_zero;

    /*!
     * \brief update function will edit a post by own id.
     * \param id is unique index of post.
     * \param postData are the post's data.
     * \returns true, if the post is updated successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool update(const Types::u32 id, const PostData& postData) __cell_const = __cell_zero;

    /*!
     * \brief copy function will copy a post.
     * \param id is unique index of post.
     * \returns true, if the post is copied successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool copy(const u32 id) __cell_const = __cell_zero;

    /*!
     * \brief move function will move a post to sub post.
     * \param id is unique index of post.
     * \param toParentId is parent post id.
     * \returns true, if the post is moved successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool move(const Types::u32 id, const Types::u32 toParentId) __cell_const = __cell_zero;

    /*!
     * \brief lock function will lock and set a post as uneditable from users.
     * \param id is unique index of post.
     * \returns true, if the post is locked successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool lock(const Types::u32 id) __cell_const = __cell_zero;

    /*!
     * \brief hide function will hide a post from users.
     * \param id is unique index of post.
     * \returns true, if the post is hidden successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool hide(const Types::u32 id) __cell_const = __cell_zero;

    /*!
     * \brief status function will change the post status.
     * \param status is a parameter based on PostStatus.
     * \returns true, if the post status changed successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool status(const PostStatus status) __cell_const = __cell_zero;

    /*!
     * \brief addMessage function will add new message for the post.
     * \param message is a parameter based on MessageData.
     * \returns true, if the post message added successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool addMessage(const MessageData& messageData) __cell_const = __cell_zero;


private:
    CELL_DISABLE_COPY(AbstractPost)
    PostData* m_postData{};
};

CELL_NAMESPACE_END

#endif  // CELL_POST_ABSTRACT_HPP
