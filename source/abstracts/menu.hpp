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
    Action      = 0x5,  //!< Action type (e.g., run a shell command or function).
    Custom      = 0x6   //!< Custom type.
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
    Types::OptionalNumeric              id               {};   //!< Unique ID of the menu item.
    Types::OptionalNumeric              parentId         {};   //!< Parent ID of the menu item.
    Types::OptionalBool                 isParent         {};   //!< Whether the item is a parent.
    Types::OptionalString               title            {};   //!< Title of the menu item.
    Types::OptionalString               descr            {};   //!< Description of the menu item.
    Types::OptionalString               url              {};   //!< URL or URI of the menu item.
    Types::OptionalString               params           {};   //!< Additional parameters (e.g., rel="nofollow").
    Types::Optional<ItemStatus>         status           {};   //!< Status of the menu item.
    Types::OptionalNumeric              priority         {};   //!< Priority or position index.
    Types::OptionalString               language         {};   //!< Language code for localization (e.g., "en", "fa").

    Types::OptionalBool                 inSiteMap        {};   //!< Whether the item is included in the sitemap.
    Types::Optional<MenuDisplayGroup>   displayGroup     {};   //!< Display group for role-based access.

    Types::OptionalString               icon             {};   //!< Icon for the menu item (e.g., "fa-home").
    Types::Optional<MenuItemType>       type             {};   //!< Type of the menu item (e.g., link, button).
    Types::OptionalString               layout           {};   //!< Template (layout) for rendering the menu item (e.g., "horizontal", "vertical").
    Types::OptionalString               expiryDate       {};   //!< Expiry date of the menu item (e.g., "2025-12-31").

    Types::OptionalString               visibleStartTime {};   //!< Start time when the menu item is visible (e.g., "09:00").
    Types::OptionalString               visibleEndTime   {};   //!< End time when the menu item is visible (e.g., "17:00").

    std::map<Types::OptionalString, Types::OptionalBool>    permissions          {};   //!< Permissions for the menu item (e.g., "view": true, "edit": false).
    std::map<Types::OptionalString, Types::OptionalString>  customAttributes     {};   //!< Custom attributes for the menu item.
    std::vector<Types::OptionalNumeric>                     dependencies         {};   //!< List of menu item IDs that this item depends on.
    std::map<Types::OptionalString, std::shared_ptr<void>>  externalDependencies {};   //!< External dependencies.

    Types::OptionalNumeric                                  accessCount          {};   //!< Number of times the menu item has been accessed.
    Types::OptionalString                                   visibilityCondition  {};   //!< Condition for visibility (e.g., "device == 'mobile'").
    std::map<Types::OptionalString, std::function<void()>>  eventHooks           {};   //!< Event hooks (e.g., "onClick": []() { ... }).
    std::vector<Types::OptionalString>                      tags                 {};   //!< Tags for the menu item (e.g., "admin", "settings").

    Types::OptionalNumeric                                  rateLimit            {};   //!< Rate limit (e.g., 10 accesses per minute).
    std::map<Types::OptionalString, Types::OptionalString>  geolocationRules     {};   //!< Geolocation rules (e.g., "country == 'US'").
    std::vector<Types::OptionalString>                      webhooks             {};   //!< Webhooks to trigger (e.g., "https://example.com/webhook").
    Types::OptionalString                                   templates            {};   //!< Template for dynamic content (e.g., "Hello, {{user}}!").
    Types::OptionalString                                   apiEndpoint          {};   //!< API endpoint to fetch data from.
    std::map<Types::OptionalString, Types::OptionalString>  state                {};   //!< State of the menu item (e.g., "open": "true").
    std::vector<Types::OptionalString>                      collaborators        {};   //!< List of collaborators (e.g., user IDs).
    Types::OptionalString                                   aiModel              {};   //!< AI model for recommendations (e.g., "recommendation_model").

    Types::OptionalString                                   version              {};   //!< Version of the menu item (e.g., "1.0", "2.0").
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

    /*!
     * \brief setAction sets a shell command or function to be executed when the menu item is clicked.
     * \param action The shell command or function to execute.
     */
    __cell_virtual void setAction(const Types::OptionalString& action) = __cell_zero;

    /*!
     * \brief executeAction executes the shell command or function associated with the menu item.
     * \returns True if the action was successfully executed.
     */
    __cell_virtual Types::OptionalBool executeAction() = __cell_zero;

    /*!
     * \brief setExpiryDate sets the expiry date for the menu item.
     * \param date The expiry date as a string (e.g., "2023-12-31").
     */
    __cell_virtual void setExpiryDate(const Types::OptionalString& date) = __cell_zero;

    /*!
     * \brief isExpired checks if the menu item has expired.
     * \returns True if the menu item has expired, false otherwise.
     */
    __cell_virtual Types::OptionalBool isExpired() __cell_const = __cell_zero;

    /*!
     * \brief setVisibilityTime sets the visibility time range for the menu item.
     * \param startTime The start time as a string (e.g., "09:00").
     * \param endTime The end time as a string (e.g., "17:00").
     */
    __cell_virtual void setVisibilityTime(const Types::OptionalString& startTime, const Types::OptionalString& endTime) = __cell_zero;

    /*!
     * \brief isVisible checks if the menu item is currently visible based on the time.
     * \returns True if the menu item is visible, false otherwise.
     */
    __cell_virtual Types::OptionalBool isVisible() __cell_const = __cell_zero;

    /*!
     * \brief logAction logs an action performed on the menu item.
     * \param action The action to log (e.g., "clicked", "executed").
     * \param userRole The role of the user performing the action.
     */
    __cell_virtual void logAction(const Types::OptionalString& action, const UserRole& userRole) = __cell_zero;

    /*!
     * \brief getActionLogs retrieves the logs for the menu item.
     * \returns A vector of log entries.
     */
    __cell_virtual std::vector<Types::OptionalString> getActionLogs() __cell_const = __cell_zero;

    /*!
     * \brief setCustomAttribute sets a custom attribute for the menu item.
     * \param key The key of the attribute.
     * \param value The value of the attribute.
     */
    __cell_virtual void setCustomAttribute(const Types::OptionalString& key, const Types::OptionalString& value) = __cell_zero;

    /*!
     * \brief getCustomAttribute retrieves a custom attribute by key.
     * \param key The key of the attribute.
     * \returns The value of the attribute as an optional string.
     */
    __cell_virtual Types::OptionalString getCustomAttribute(const Types::OptionalString& key) __cell_const = __cell_zero;

    /*!
     * \brief removeCustomAttribute removes a custom attribute by key.
     * \param key The key of the attribute to remove.
     * \returns True if the attribute was successfully removed.
     */
    __cell_virtual Types::OptionalBool removeCustomAttribute(const Types::OptionalString& key) = __cell_zero;

    /*!
     * \brief addDependency adds a dependency to the menu item.
     * \param itemId The ID of the menu item to depend on.
     */
    __cell_virtual void addDependency(const Types::OptionalNumeric itemId) = __cell_zero;

    /*!
     * \brief removeDependency removes a dependency from the menu item.
     * \param itemId The ID of the menu item to remove as a dependency.
     * \returns True if the dependency was successfully removed.
     */
    __cell_virtual Types::OptionalBool removeDependency(const Types::OptionalNumeric itemId) = __cell_zero;

    /*!
     * \brief checkDependencies checks if all dependencies are met.
     * \returns True if all dependencies are met, false otherwise.
     */
    __cell_virtual Types::OptionalBool checkDependencies() __cell_const = __cell_zero;

    /*!
     * \brief cacheMenu caches the entire menu for faster retrieval.
     * \returns True if the menu was successfully cached.
     */
    __cell_virtual Types::OptionalBool cacheMenu() = __cell_zero;

    /*!
     * \brief getCachedMenu retrieves the cached menu.
     * \returns A vector of menu items from the cache.
     */
    __cell_virtual std::vector<MenuItemData> getCachedMenu() __cell_const = __cell_zero;

    /*!
     * \brief clearCache clears the menu cache.
     * \returns True if the cache was successfully cleared.
     */
    __cell_virtual Types::OptionalBool clearCache() = __cell_zero;

    /*!
     * \brief incrementAccessCount increments the access count for the menu item.
     */
    __cell_virtual void incrementAccessCount() = __cell_zero;

    /*!
     * \brief getAccessCount retrieves the access count for the menu item.
     * \returns The access count as an optional numeric value.
     */
    __cell_virtual Types::OptionalNumeric getAccessCount() __cell_const = __cell_zero;

    /*!
     * \brief setPermission sets a permission for the menu item.
     * \param permission The permission name (e.g., "view", "edit").
     * \param value The value of the permission (true or false).
     */
    __cell_virtual void setPermission(const Types::OptionalString& permission, const Types::OptionalBool value) = __cell_zero;

    /*!
     * \brief hasPermission checks if a specific permission is granted.
     * \param permission The permission name (e.g., "view", "edit").
     * \returns True if the permission is granted, false otherwise.
     */
    __cell_virtual Types::OptionalBool hasPermission(const Types::OptionalString& permission) __cell_const = __cell_zero;

    /*!
     * \brief setVisibilityCondition sets a condition for the menu item's visibility.
     * \param condition The condition as a string (e.g., "device == 'mobile'").
     */
    __cell_virtual void setVisibilityCondition(const Types::OptionalString& condition) = __cell_zero;

    /*!
     * \brief evaluateVisibility evaluates the visibility condition.
     * \param context A map of contextual data (e.g., device type, user location).
     * \returns True if the condition is met, false otherwise.
     */
    __cell_virtual Types::OptionalBool evaluateVisibility(const std::map<Types::OptionalString, Types::OptionalString>& context) __cell_const = __cell_zero;

    /*!
     * \brief addEventHook adds an event hook to the menu item.
     * \param eventName The name of the event (e.g., "onClick", "onHover").
     * \param callback The callback function to execute.
     */
    __cell_virtual void addEventHook(const Types::OptionalString& eventName, std::function<void()> callback) = __cell_zero;

    /*!
     * \brief triggerEvent triggers an event hook.
     * \param eventName The name of the event to trigger.
     * \returns True if the event was triggered successfully.
     */
    __cell_virtual Types::OptionalBool triggerEvent(const Types::OptionalString& eventName) = __cell_zero;

    /*!
     * \brief setVersion sets the version of the menu item.
     * \param version The version as a string (e.g., "1.0").
     */
    __cell_virtual void setVersion(const Types::OptionalString& version) = __cell_zero;

    /*!
     * \brief getVersion retrieves the version of the menu item.
     * \returns The version as an optional string.
     */
    __cell_virtual Types::OptionalString getVersion() __cell_const = __cell_zero;

    /*!
     * \brief searchItems searches for menu items by keyword.
     * \param keyword The keyword to search for.
     * \returns A vector of matching menu items.
     */
    __cell_virtual std::vector<MenuItemData> searchItems(const Types::OptionalString& keyword) __cell_const = __cell_zero;

    /*!
     * \brief filterItemsByTag filters menu items by tag.
     * \param tag The tag to filter by.
     * \returns A vector of matching menu items.
     */
    __cell_virtual std::vector<MenuItemData> filterItemsByTag(const Types::OptionalString& tag) __cell_const = __cell_zero;

    /*!
     * \brief injectDependency injects an external dependency into the menu item.
     * \param key The key for the dependency.
     * \param dependency The dependency to inject.
     */
    __cell_virtual void injectDependency(const Types::OptionalString& key, std::shared_ptr<void> dependency) = __cell_zero;

    /*!
     * \brief getDependency retrieves an injected dependency by key.
     * \param key The key for the dependency.
     * \returns The dependency as a shared pointer.
     */
    __cell_virtual std::shared_ptr<void> getDependency(const Types::OptionalString& key) __cell_const = __cell_zero;

    /*!
     * \brief setRateLimit sets a rate limit for the menu item.
     * \param limit The rate limit (e.g., 10).
     * \param interval The time interval (e.g., "minute").
     */
    __cell_virtual void setRateLimit(const Types::OptionalNumeric limit, const Types::OptionalString& interval) = __cell_zero;

    /*!
     * \brief checkRateLimit checks if the rate limit has been exceeded.
     * \returns True if the rate limit has not been exceeded, false otherwise.
     */
    __cell_virtual Types::OptionalBool checkRateLimit() __cell_const = __cell_zero;

    /*!
     * \brief addGeolocationRule adds a geolocation rule for the menu item.
     * \param rule The rule as a string (e.g., "country == 'US'").
     */
    __cell_virtual void addGeolocationRule(const Types::OptionalString& rule) = __cell_zero;

    /*!
     * \brief evaluateGeolocation evaluates geolocation rules for a user.
     * \param location A map of location data (e.g., "country": "US").
     * \returns True if the rules are satisfied, false otherwise.
     */
    __cell_virtual Types::OptionalBool evaluateGeolocation(const std::map<Types::OptionalString, Types::OptionalString>& location) __cell_const = __cell_zero;

    /*!
     * \brief addWebhook adds a webhook to the menu item.
     * \param url The URL of the webhook.
     */
    __cell_virtual void addWebhook(const Types::OptionalString& url) = __cell_zero;

    /*!
     * \brief triggerWebhooks triggers all webhooks associated with the menu item.
     * \returns True if all webhooks were triggered successfully.
     */
    __cell_virtual Types::OptionalBool triggerWebhooks() = __cell_zero;

    /*!
     * \brief setTemplate sets a template for the menu item.
     * \param template The template as a string (e.g., "Hello, {{user}}!").
     */
    __cell_virtual void setTemplate(const Types::OptionalString& templates) = __cell_zero;

    /*!
     * \brief renderTemplate renders the template with provided data.
     * \param data A map of data to inject into the template.
     * \returns The rendered content as a string.
     */
    __cell_virtual Types::OptionalString renderTemplate(const std::map<Types::OptionalString, Types::OptionalString>& data) __cell_const = __cell_zero;

    /*!
     * \brief setApiEndpoint sets an API endpoint for the menu item.
     * \param endpoint The API endpoint (e.g., "https://api.example.com/data").
     */
    __cell_virtual void setApiEndpoint(const Types::OptionalString& endpoint) = __cell_zero;

    /*!
     * \brief fetchApiData fetches data from the API endpoint.
     * \returns The fetched data as a string.
     */
    __cell_virtual Types::OptionalString fetchApiData() __cell_const = __cell_zero;

    /*!
     * \brief setState sets a state value for the menu item.
     * \param key The state key (e.g., "open").
     * \param value The state value (e.g., "true").
     */
    __cell_virtual void setState(const Types::OptionalString& key, const Types::OptionalString& value) = __cell_zero;

    /*!
     * \brief getState retrieves a state value by key.
     * \param key The state key (e.g., "open").
     * \returns The state value as an optional string.
     */
    __cell_virtual Types::OptionalString getState(const Types::OptionalString& key) __cell_const = __cell_zero;

    /*!
     * \brief addCollaborator adds a collaborator to the menu item.
     * \param userId The ID of the collaborator.
     */
    __cell_virtual void addCollaborator(const Types::OptionalString& userId) = __cell_zero;

    /*!
     * \brief removeCollaborator removes a collaborator from the menu item.
     * \param userId The ID of the collaborator.
     * \returns True if the collaborator was successfully removed.
     */
    __cell_virtual Types::OptionalBool removeCollaborator(const Types::OptionalString& userId) = __cell_zero;

    /*!
     * \brief setAiModel sets an AI model for the menu item.
     * \param model The AI model identifier.
     */
    __cell_virtual void setAiModel(const Types::OptionalString& model) = __cell_zero;

    /*!
     * \brief generateRecommendations generates recommendations using the AI model.
     * \returns A vector of recommended menu items.
     */
    __cell_virtual std::vector<MenuItemData> generateRecommendations() __cell_const = __cell_zero;

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

    /*!
     * \brief generateDynamicItems generates menu items dynamically based on a condition.
     * \param condition A function that returns true if the condition is met.
     * \param generator A function that generates menu items.
     * \returns A vector of dynamically generated menu items.
     */
    __cell_virtual std::vector<MenuItemData> generateDynamicItems(std::function<bool()> condition, std::function<std::vector<MenuItemData>()> generator) = __cell_zero;

    /*!
     * \brief undo reverts the last change made to the menu.
     * \returns True if the undo operation was successful.
     */
    __cell_virtual Types::OptionalBool undo() = __cell_zero;

    /*!
     * \brief redo reapplies the last undone change.
     * \returns True if the redo operation was successful.
     */
    __cell_virtual Types::OptionalBool redo() = __cell_zero;

    /*!
     * \brief getHistory retrieves the change history.
     * \returns A vector of change descriptions.
     */
    __cell_virtual std::vector<Types::OptionalString> getHistory() __cell_const = __cell_zero;

    /*!
     * \brief exportMenu exports the menu to a file.
     * \param filePath The path to the export file.
     * \returns True if the export was successful.
     */
    __cell_virtual Types::OptionalBool exportMenu(const Types::OptionalString& filePath) __cell_const = __cell_zero;

    /*!
     * \brief importMenu imports the menu from a file.
     * \param filePath The path to the import file.
     * \returns True if the import was successful.
     */
    __cell_virtual Types::OptionalBool importMenu(const Types::OptionalString& filePath) = __cell_zero;

    /*!
     * \brief generateAnalyticsReport generates a report of menu item usage.
     * \returns A map of analytics data (e.g., "mostAccessedItem", "totalAccesses").
     */
    __cell_virtual std::map<Types::OptionalString, Types::OptionalNumeric> generateAnalyticsReport() __cell_const = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractMenu)
};

CELL_NAMESPACE_END

#endif  // CELL_MENU_ABSTRACT_HPP
