/*!
 * @file        menu.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Menu and item interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MENU_ABSTRACT_HPP
#define CELL_MENU_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The MenuDisplayGroup enum
 * \details Display items by grouping.
 */
__cell_enum_class MenuDisplayGroup : Types::u8
{
    Default     =   0x1,  ///< Display for all users.
    Guest       =   0x2,  ///< Display for guest only.
    User        =   0x3,  ///< Display for user only.
    Admin       =   0x4,  ///< Display for admin only.
    Master      =   0x5,  ///< Display for master only.
    Customized  =   0x6   ///< Display for customized group only.
};

__cell_enum_class ItemStatus : Types::u8
{
    Disabled    =   0x0,  ///< Disabled.
    Hidden      =   0x1,  ///< Hidden.
    Active      =   0x2   ///< Active.
};

/*!
 * \brief The SettingData class
 */
struct MenuItemData __cell_final
{
    Types::OptionalNumeric         id         {};   ///< Id of menu item.
    Types::OptionalNumeric         parentId   {};   ///< Parent id of menu item.
    Types::OptionalBool            isParent   {};   ///< Parent mode of menu item.
    Types::OptionalString          title      {};   ///< Title of menu item.
    Types::OptionalString          descr      {};   ///< Description of menu item.
    Types::OptionalString          url        {};   ///< Url of menu item.
    Types::OptionalString          params     {};   ///< Params of menu item.
    Types::Optional<ItemStatus>    status     {};   ///< Status value of menu item.
    Types::OptionalNumeric         priority   {};   ///< Group index value of menu item.
    Types::OptionalBool            inSiteMap  {};   ///< InMap status for menu item.
};

class __cell_export AbstractMenuItem
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractMenuItem)

    /*!
     * \brief id is unique id of menu item.
     * \returns integer.
     */
    __cell_virtual Types::OptionalNumeric id() __cell_const = __cell_zero;

    /*!
     * \brief parentId is parent's id of menu item.
     * \returns integer.
     */
    __cell_virtual Types::OptionalNumeric parentId() __cell_const = __cell_zero;

    /*!
     * \brief isParent will gets item parent situation.
     * \returns true if item has parent id.
     */
    __cell_virtual Types::OptionalBool isParent() __cell_const = __cell_zero;

    /*!
     * \brief title is subject of setting option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString title() __cell_const = __cell_zero;

    /*!
     * \brief descr is description of setting option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString descr() __cell_const = __cell_zero;

    /*!
     * \brief url/uri is link or uri of menu item.
     * \returns string of url.
     */
    __cell_virtual Types::OptionalString url() __cell_const = __cell_zero;

    /*!
     * \brief parameter of rel options like [rel="nofollow"].
     * \returns string.
     */
    __cell_virtual Types::OptionalString params() __cell_const = __cell_zero;

    /*!
     * \brief status will gets status value from option.
     * \returns one of the Status.
     */
    __cell_virtual Types::Optional<ItemStatus> status() __cell_const = __cell_zero;

    /*!
     * \brief priority will gets priority(position index) of menu item.
     * \returns as integer.
     */
    __cell_virtual Types::OptionalNumeric priority() __cell_const = __cell_zero;

    /*!
     * \brief inSiteMap will gets sitemap status for an item.
     * \returns as boolean.
     */
    __cell_virtual Types::OptionalBool inSiteMap() __cell_const = __cell_zero;

    /*!
     * \brief Getting menu item by id from list.
     * \returns MenuItemData of items.
     */
    __cell_virtual MenuItemData getMenuById() __cell_const = __cell_zero;

    /*!
     * \brief setId inserts id for an item.
     * \param id is a number type for inserting values into the function.
     */
    __cell_virtual void setId(const Types::OptionalNumeric id) = __cell_zero;

    /*!
     * \brief setParentId inserts parent's id for an item.
     * \param pid is a number type for inserting values into the function.
     */
    __cell_virtual void setParentId(const Types::OptionalNumeric pid) = __cell_zero;

    /*!
     * \brief setIsParent inserts parent's situation for an item.
     * \param isp is a number type for inserting values into the function.
     */
    __cell_virtual void setIsParent(const Types::OptionalBool isp) = __cell_zero;

    /*!
     * \brief SetTitle inserts data for the option's title.
     * \param title is a string type for inserting values into the function.
     */
    __cell_virtual void setTitle(const Types::OptionalString& title) = __cell_zero;

    /*!
     * \brief setDescr inserts data for the option's description.
     * \param descr is a string type for inserting values into the function.
     */
    __cell_virtual void setDescr(const Types::OptionalString& descr) = __cell_zero;

    /*!
     * \brief setUrl inserts link for the item's href.
     * \param url is a string type for inserting values into the function.
     */
    __cell_virtual void setUrl(const Types::OptionalString& url) = __cell_zero;

    /*!
     * \brief setParams inserts data for the option's default value.
     * \param param is a string type for inserting values into the function.
     */
    __cell_virtual void setParams(const Types::OptionalString& param) = __cell_zero;

    /*!
     * \brief setStatus will change option's status.
     * \param status is a Status type for change the option status.
     */
    __cell_virtual void setStatus(const Types::Optional<ItemStatus> status) = __cell_zero;

    /*!
     * \brief setPriority will sets a position as integer for item.
     * \param pos is number of item's position.
     */
    __cell_virtual void setPriority(const Types::OptionalNumeric pos) = __cell_zero;

    /*!
     * \brief setInSiteMap will sets item into sitemap service.
     * \param map is status of item's in sitemap.
     */
    __cell_virtual void setInSiteMap(const Types::OptionalBool map) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractMenuItem)
};

class __cell_export AbstractMenu
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractMenu)

    /*!
     * \brief insert will create a new item for menu.
     * \param menuItemData parameter is item's data as MenuItemData.
     * \returns true if the object[item] was successfully created.
     */
    __cell_virtual Types::OptionalBool insert(const MenuItemData& menuItemData) = __cell_zero;

    /*!
     * \brief edit will replace current item data with new.
     * \param id parameter is item's unique id for find it.
     * \param menuItemData parameter is item's data as MenuItemData.
     * \returns true if the object[item] was successfully edited.
     */
    __cell_virtual Types::OptionalBool edit(const int id, const MenuItemData& menuItemData) = __cell_zero;

    /*!
     * \brief removeItem will removes an item from menu list.
     * \param id parameter is required to specify the item uid.
     * \returns true if the object[item] was successfully removed.
     */
    __cell_virtual Types::OptionalBool removeItem(const int id) = __cell_zero;

    /*!
     * \brief changePos will change or move item's position between items.
     * \param id parameter is item's unique id.
     * \param posId parameter is position number for move.
     * \returns true if the object[item] was successfully moved.
     */
    __cell_virtual Types::OptionalBool changePos(const int id, const int posId) = __cell_zero;

    /*!
     * \brief items will gets all item as string;
     * \returns list of items.
     */
    __cell_virtual std::vector<Types::OptionalString> items() __cell_const = __cell_zero;

    /*!
     * \brief itemsByStatus will gets all item as string;
     * \param status parameter is required for check status of item.
     * \returns list of items based on their status.
     */
    __cell_virtual std::vector<Types::OptionalString> itemsByStatus(const ItemStatus& status) __cell_const = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractMenu)
};

CELL_NAMESPACE_END

#endif  // CELL_MENU_ABSTRACT_HPP
