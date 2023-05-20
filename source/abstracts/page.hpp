/*!
 * @file        page.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Page interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PAGE_ABSTRACT_HPP
#define CELL_PAGE_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/tags.hpp")
#   include "core/tags.hpp"
#else
#   error "Cell's "tags.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The PageType enum
 */
__cell_enum_class PageType : Types::u8
{
    Default     =   0x0,    //!< Page as default.
    Static      =   0x1,    //!< Page as static mode.
    Dynamic     =   0x2,    //!< Page as dynamic mode.
    Custom      =   0x3     //!< Page as custom design.
};

/*!
 * \brief The PageStatus enum
 */
__cell_enum_class PageStatus : Types::u8
{
    Locked          =   0x0,
    Important       =   0x1,
    Special         =   0x2,
    Hidden          =   0x3
};

__cell_enum_class PageThemeStyle : Types::u8
{
    Default         =   0x0,
    AsPage          =   0x1,
    BySystemDesign  =   0x2,
    ByCustomDesign  =   0x3
};

/*!
 * \brief The PageProperties class
 */
struct PageProperties __cell_final
{
    ///!BASIC
    Types::OptionalNumeric id              {};    //!< Index of page.
    Types::OptionalNumeric priority        {};    //!< Index of page position.
    Types::OptionalString  title           {};    //!< Title (subject) of page.
    Types::OptionalString  url             {};    //!< Url for page.
    Tags                   tags            {};    //!< Tags list for page.
    Types::OptionalString  text            {};    //!< Text (main content) for page.
    Types::OptionalString  documentTitle   {};    //!< Document title (title of page).
    Types::OptionalString  metaDescr       {};    //!< Meta description (more details) for page.
    ///!MEDIA
//    MediaType  cover    {};    //!< Image or video for page.
//    IconType   icon     {};    //!< Icon for page.
    ///!DATETIME
    Types::OptionalString  createdDate  {};    //!< Created date time.
    Types::OptionalString  publishTime  {};    //!< Publishing time.
    Types::OptionalString  pinnedTime   {};    //!< Pinned time.
    Types::OptionalString  lastModified {};    //!< Last Modified date-time.
    ///!EXTRA
    Types::OptionalBool    inclueInSitemap            {};  //!< If included in sitemap section.
    Types::OptionalBool    canBeModeratedFromFrontend {};  //!< Can be moderated from frontend?!
    Types::OptionalBool    accessByApi {};  //!< Can be access from api output.
    Types::OptionalString  theme       {};  //!< Page theme.
};

/*!
 * \brief The AbstractPage class
 */
class __cell_export AbstractPage
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractPage)

    /*!
     * \brief id will gets index number of page.
     * \returns as numeric.
     */
    __cell_no_discard_virtual Types::OptionalString id() __cell_const = __cell_zero;

    /*!
     * \brief priority will gets position number of page.
     * \returns as numeric.
     */
    __cell_no_discard_virtual Types::OptionalString priority() __cell_const = __cell_zero;

    /*!
     * \brief title will gets title of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString title() __cell_const = __cell_zero;

    /*!
     * \brief url will gets url of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString url() __cell_const = __cell_zero;

    /*!
     * \brief tags will gets inserted tags for page.
     * \returns as Tags class.
     */
    __cell_no_discard_virtual Tags tags() __cell_const = __cell_zero;

    /*!
     * \brief text will gets content of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString text() __cell_const = __cell_zero;

    /*!
     * \brief documentTitle will gets document title of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString documentTitle() __cell_const = __cell_zero;

    /*!
     * \brief metaDescr will gets meta description of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString metaDescr() __cell_const = __cell_zero;

    /*!
     * \brief icon will gets icon of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString icon() __cell_const = __cell_zero;

    /*!
     * \brief publishTime will gets publish time of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString publishTime() __cell_const = __cell_zero;

    /*!
     * \brief pinnedTime will gets pinned time of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString pinnedTime() __cell_const = __cell_zero;

    /*!
     * \brief lastModified will gets last modified date and time of page.
     * \returns as string.
     */
    __cell_no_discard_virtual Types::OptionalString lastModified() __cell_const = __cell_zero;

    /*!
     * \brief inclueInSitemap will gets included status in map.
     * \returns as boolean.
     */
    __cell_no_discard_virtual Types::OptionalBool inclueInSitemap() __cell_const = __cell_zero;

    /*!
     * \brief canBeModeratedFromFrontend will gets moderated to frontend.
     * \returns as boolean.
     */
    __cell_no_discard_virtual Types::OptionalBool canBeModeratedFromFrontend() __cell_const = __cell_zero;

    /*!
     * \brief accessByApi will generates output as api strcuture.
     * \returns as boolean.
     */
    __cell_no_discard_virtual Types::OptionalBool accessByApi() __cell_const = __cell_zero;

    /*!
     * \brief create function will add a new page.
     * \param properties are the page information.
     * \returns true, if the page is created successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool create(const PageProperties& properties) __cell_const = __cell_zero;

    /*!
     * \brief remove function will delete a page by own id.
     * \param id is unique index of page.
     * \returns true, if the page is removed successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool remove(const Types::u32 id) __cell_const = __cell_zero;

    /*!
     * \brief update function will edit a page by own id.
     * \param id is unique index of page.
     * \param properties are the page's data.
     * \returns true, if the page is updated successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool update(const Types::u32 id, const PageProperties& properties) __cell_const = __cell_zero;

    /*!
     * \brief move function will move a page to sub page.
     * \param id is unique index of page.
     * \param toParentId is parent page id.
     * \returns true, if the page is moved successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool move(const Types::u32 id, const Types::u32 toParentId) __cell_const = __cell_zero;

    /*!
     * \brief lock function will lock and set a page as uneditable from users.
     * \param id is unique index of page.
     * \returns true, if the page is locked successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool lock(const Types::u32 id) __cell_const = __cell_zero;

    /*!
     * \brief hide function will hide a page from users.
     * \param id is unique index of page.
     * \returns true, if the page is hidden successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool hide(const Types::u32 id) __cell_const = __cell_zero;

    /*!
     * \brief status function will change the page status.
     * \param status is a parameter based on PageStatus.
     * \returns true, if the page status changed successfully.
     */
    __cell_no_discard_virtual Types::OptionalBool status(const PageStatus status) __cell_const = __cell_zero;

    /*!
     * \brief theme function will gets theme for page.
     * \param theme parameter as PageThemeStyle.
     * \returns output of theme.
     */
    __cell_no_discard_virtual Types::OptionalString theme(const PageThemeStyle theme) __cell_const = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractPage)
};

CELL_NAMESPACE_END

#endif  // CELL_PAGE_ABSTRACT_HPP
