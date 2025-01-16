/*!
 * @file        menu.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Menu and item interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_MENU_ABSTRACT_HPP
#define CELL_MENU_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The MenuDisplayGroup enum
 * \details Defines groups for displaying menu items based on user roles.
 */
__cell_enum_class MenuDisplayGroup : Types::u8
{
    Default     = 0x1,  //!< 00000001 Display for all users.
    Guest       = 0x2,  //!< 00000010 Display for guest only.
    User        = 0x4,  //!< 00000100 Display for user only.
    Admin       = 0x8,  //!< 00001000 Display for admin only.
    Master      = 0x10, //!< 00010000 Display for master only.
    Customized  = 0x20  //!< 00100000 Display for customized group only.
};

/*!
 * \brief The UserRole enum
 * \details Defines user roles for role-based access control (RBAC).
 */
__cell_enum_class UserRole : Types::u8
{
    Guest       = 0x1,  //!< Unauthenticated users.
    User        = 0x2,  //!< Regular authenticated users.
    Editor      = 0x4,  //!< Users who can edit content.
    Admin       = 0x8,  //!< Administrators.
    Master      = 0x10  //!< Superusers with unrestricted access.
};

/*!
 * \brief The MenuItemType enum
 * \details Defines the type of a menu item (e.g., link, button, dropdown).
 */
__cell_enum_class MenuItemType : Types::u8
{
    Link        = 0x1,  //!< Standard link.
    Button      = 0x2,  //!< Button.
    Dropdown    = 0x3,  //!< Dropdown menu.
    Separator   = 0x4,  //!< Visual separator.
    Custom      = 0x5   //!< Custom type.
};

/*!
 * \brief The ItemStatus enum
 * \details Defines the status of a menu item.
 */
__cell_enum_class ItemStatus : Types::u8
{
    Disabled    = 0x0,  //!< Disabled.
    Hidden      = 0x1,  //!< Hidden.
    Active      = 0x2   //!< Active.
};

/*!
 * \brief The MenuItemData struct
 * \details Holds data for a menu item, including its ID, title, URL, and status.
 */
struct MenuItemData __cell_final
{
    Types::OptionalNumeric              id              {};   //!< Unique ID of the menu item.
    Types::OptionalNumeric              parentId        {};   //!< Parent ID of the menu item.
    Types::OptionalBool                 isParent        {};   //!< Whether the item is a parent.
    Types::OptionalString               title           {};   //!< Title of the menu item.
    Types::OptionalString               descr           {};   //!< Description of the menu item.
    Types::OptionalString               url             {};   //!< URL or URI of the menu item.
    Types::OptionalString               params          {};   //!< Additional parameters (e.g., rel="nofollow").
    Types::Optional<ItemStatus>         status          {};   //!< Status of the menu item.
    Types::OptionalNumeric              priority        {};   //!< Priority or position index.
    Types::OptionalString               language        {};   //!< Language code for localization (e.g., "en", "fa").
    Types::OptionalBool                 inSiteMap       {};   //!< Whether the item is included in the sitemap.
    Types::Optional<MenuDisplayGroup>   displayGroup    {};   //!< Display group for role-based access.
    Types::OptionalString               icon            {};   //!< Icon for the menu item (e.g., "fa-home").
    Types::Optional<MenuItemType>       type            {};   //!< Type of the menu item (e.g., link, button).
    Types::OptionalString               layout          {};   //!< Template (layout) for rendering the menu item (e.g., "horizontal", "vertical").
};

/*!
 * \brief The AbstractMenuItem class
 * \details Abstract base class for menu items. Provides an interface for managing menu item properties.
 */
class __cell_export AbstractMenuItem
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractMenuItem)

    /*!
     * \brief id is the unique ID of the menu item.
     * \returns The ID as an optional numeric value.
     */
    __cell_virtual Types::OptionalNumeric id() __cell_const = __cell_zero;

    /*!
     * \brief parentId is the parent ID of the menu item.
     * \returns The parent ID as an optional numeric value.
     */
    __cell_virtual Types::OptionalNumeric parentId() __cell_const = __cell_zero;

    /*!
     * \brief isParent indicates whether the item is a parent.
     * \returns True if the item is a parent, false otherwise.
     */
    __cell_virtual Types::OptionalBool isParent() __cell_const = __cell_zero;

    /*!
     * \brief title is the title of the menu item.
     * \returns The title as an optional string.
     */
    __cell_virtual Types::OptionalString title() __cell_const = __cell_zero;

    /*!
     * \brief descr is the description of the menu item.
     * \returns The description as an optional string.
     */
    __cell_virtual Types::OptionalString descr() __cell_const = __cell_zero;

    /*!
     * \brief url is the URL or URI of the menu item.
     * \returns The URL as an optional string.
     */
    __cell_virtual Types::OptionalString url() __cell_const = __cell_zero;

    /*!
     * \brief params are additional parameters for the menu item.
     * \returns The parameters as an optional string.
     */
    __cell_virtual Types::OptionalString params() __cell_const = __cell_zero;

    /*!
     * \brief status is the status of the menu item.
     * \returns The status as an optional ItemStatus value.
     */
    __cell_virtual Types::Optional<ItemStatus> status() __cell_const = __cell_zero;

    /*!
     * \brief priority is the priority or position index of the menu item.
     * \returns The priority as an optional numeric value.
     */
    __cell_virtual Types::OptionalNumeric priority() __cell_const = __cell_zero;

    /*!
     * \brief inSiteMap indicates whether the item is included in the sitemap.
     * \returns True if the item is in the sitemap, false otherwise.
     */
    __cell_virtual Types::OptionalBool inSiteMap() __cell_const = __cell_zero;

    /*!
     * \brief language is the language code for localization.
     * \details This method returns the language code associated with the menu item (e.g., "en", "fr").
     * \returns The language code as an optional string.
     */
    __cell_virtual Types::OptionalString language() __cell_const = __cell_zero;

    /*!
     * \brief displayGroup is the display group for role-based access.
     * \details This method returns the display group associated with the menu item, which determines
     *          which user roles can see the item.
     * \returns The display group as an optional MenuDisplayGroup value.
     */
    __cell_virtual Types::Optional<MenuDisplayGroup> displayGroup() __cell_const = __cell_zero;

    /*!
     * \brief icon is the icon associated with the menu item.
     * \details This method returns the icon code or identifier (e.g., "fa-home" for FontAwesome).
     * \returns The icon as an optional string.
     */
    __cell_virtual Types::OptionalString icon() __cell_const = __cell_zero;

    /*!
     * \brief type is the type of the menu item.
     * \details This method returns the type of the menu item (e.g., link, button, dropdown).
     * \returns The type as an optional MenuItemType value.
     */
    __cell_virtual Types::Optional<MenuItemType> type() __cell_const = __cell_zero;

    /*!
     * \brief layout is the layout for rendering the menu item.
     * \details This method returns the layout or template used to render the menu item
     *          (e.g., "horizontal", "vertical").
     * \returns The layout as an optional string.
     */
    __cell_virtual Types::OptionalString layout() __cell_const = __cell_zero;

    /*!
     * \brief getMenuById retrieves a menu item by its ID.
     * \param id The ID of the menu item to retrieve.
     * \returns The menu item data as a MenuItemData object.
     */
    __cell_virtual MenuItemData getMenuById(const Types::OptionalNumeric id) __cell_const = __cell_zero;

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
     * \brief getChildren retrieves all child items of a given parent item.
     * \param parentId The ID of the parent item.
     * \returns A vector of child menu items.
     */
    __cell_virtual std::vector<MenuItemData> getChildren(const Types::OptionalNumeric parentId) __cell_const = __cell_zero;

    /*!
     * \brief getMenuTree retrieves the entire menu hierarchy.
     * \details This method constructs and returns a tree structure of menu items,
     *          where each item includes its children recursively.
     * \returns A vector of menu items representing the menu tree.
     */
    __cell_virtual std::vector<MenuItemData> getMenuTree() __cell_const = __cell_zero;

    /*!
     * \brief isAccessible checks if a menu item is accessible for a specific user role.
     * \details This method verifies whether the menu item with the given ID is accessible
     *          to the user based on their role and the item's display group.
     * \param itemId The ID of the menu item to check.
     * \param role The user role to validate against.
     * \returns True if the item is accessible, false otherwise.
     */
    __cell_virtual bool isAccessible(const Types::OptionalNumeric itemId, const UserRole& role) __cell_const = __cell_zero;

    /*!
     * \brief generateBreadcrumbs generates breadcrumbs for a given menu item.
     * \details This method constructs a breadcrumb trail from the root to the specified menu item.
     * \param itemId The ID of the menu item to generate breadcrumbs for.
     * \returns A vector of menu items representing the breadcrumb trail.
     */
    __cell_virtual std::vector<MenuItemData> generateBreadcrumbs(const Types::OptionalNumeric itemId) __cell_const = __cell_zero;

    /*!
     * \brief moveItem moves a menu item to a new position.
     * \details This method reorders menu items by moving the specified item to a new position.
     * \param itemId The ID of the menu item to move.
     * \param newPosition The new position index.
     * \returns True if the item was successfully moved, false otherwise.
     */
    __cell_virtual bool moveItem(const Types::OptionalNumeric itemId, const Types::OptionalNumeric newPosition) = __cell_zero;

    /*!
     * \brief onBeforeRender registers a callback to be executed before rendering the menu.
     * \param callback The callback function.
     */
    __cell_virtual void onBeforeRender(std::function<void()> callback) = __cell_zero;

    /*!
     * \brief onAfterRender registers a callback to be executed after rendering the menu.
     * \param callback The callback function.
     */
    __cell_virtual void onAfterRender(std::function<void()> callback) = __cell_zero;

    /*!
     * \brief setTitle inserts data for the option's title.
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

    /*!
     * \brief setLanguage sets the language code for localization.
     * \details This method sets the language code associated with the menu item (e.g., "en", "fr").
     * \param lang The language code to set.
     */
    __cell_virtual void setLanguage(const Types::OptionalString& lang) = __cell_zero;

    /*!
     * \brief setDisplayGroup sets the display group for role-based access.
     * \details This method sets the display group associated with the menu item, which determines
     *          which user roles can see the item.
     * \param group The display group to set.
     */
    __cell_virtual void setDisplayGroup(const Types::Optional<MenuDisplayGroup> group) = __cell_zero;

    /*!
     * \brief setIcon sets the icon associated with the menu item.
     * \details This method sets the icon code or identifier (e.g., "fa-home" for FontAwesome).
     * \param icon The icon code or identifier to set.
     */
    __cell_virtual void setIcon(const Types::OptionalString& icon) = __cell_zero;

    /*!
     * \brief setType sets the type of the menu item.
     * \details This method sets the type of the menu item (e.g., link, button, dropdown).
     * \param type The type to set.
     */
    __cell_virtual void setType(const Types::Optional<MenuItemType> type) = __cell_zero;

    /*!
     * \brief setLayout sets the layout for rendering the menu item.
     * \details This method sets the layout or template used to render the menu item
     *          (e.g., "horizontal", "vertical").
     * \param layout The layout to set.
     */
    __cell_virtual void setLayout(const Types::OptionalString& layout) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractMenuItem)
};

/*!
 * \brief The AbstractMenu class
 * \details Abstract base class for managing a collection of menu items.
 */
class __cell_export AbstractMenu
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractMenu)

    /*!
     * \brief insert creates a new menu item.
     * \param menuItemData The data for the new menu item.
     * \returns True if the item was successfully created.
     */
    __cell_virtual Types::OptionalBool insert(const MenuItemData& menuItemData) = __cell_zero;

    /*!
     * \brief edit updates an existing menu item.
     * \param id The ID of the menu item to update.
     * \param menuItemData The new data for the menu item.
     * \returns True if the item was successfully updated.
     */
    __cell_virtual Types::OptionalBool edit(const int id, const MenuItemData& menuItemData) = __cell_zero;

    /*!
     * \brief removeItem deletes a menu item.
     * \param id The ID of the menu item to delete.
     * \returns True if the item was successfully deleted.
     */
    __cell_virtual Types::OptionalBool removeItem(const int id) = __cell_zero;

    /*!
     * \brief changePos changes the position of a menu item.
     * \param id The ID of the menu item to move.
     * \param posId The new position index.
     * \returns True if the item was successfully moved.
     */
    __cell_virtual Types::OptionalBool changePos(const int id, const int posId) = __cell_zero;

    /*!
     * \brief items retrieves all menu items.
     * \returns A vector of all menu items.
     */
    __cell_virtual std::vector<Types::OptionalString> items() __cell_const = __cell_zero;

    /*!
     * \brief itemsByStatus retrieves menu items filtered by status.
     * \param status The status to filter by.
     * \returns A vector of menu items matching the status.
     */
    __cell_virtual std::vector<Types::OptionalString> itemsByStatus(const ItemStatus& status) __cell_const = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractMenu)
};

CELL_NAMESPACE_END

#endif  // CELL_MENU_ABSTRACT_HPP
