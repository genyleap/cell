/*!
 * @file        pluginmanager.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Plugin manager interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_MANAGER_ABSTRACT_HPP
#define CELL_PLUGIN_MANAGER_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("plugin.hpp")
#   include "plugin.hpp"
#else
#   error "Cell's "plugin.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("plugininterface.hpp")
#   include "plugininterface.hpp"
#else
#   error "Cell's "plugininterface.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

// Define the prototype for a function that should exist in the lib
// that is used to create and return the plugin type in the lib.

CELL_POINTER_TO_AN_OBJECT(AbstractPlugin, fnCreatePlugin)

// Destroys the plugin type from the lib before the library is unloaded.
using fnDestroyPlugin = CELL_POINTER_TO_A_FUNCTION;

using PluginMap  =  std::map<std::string, AbstractPlugin*>;

using LibraryMap =  std::map<std::string, void*>;

/*!
 * \brief The PluginManagerData class
 */
class PluginManagerData final
{
public:
    PluginMap   plugins {};
    LibraryMap  libs    {};
};

/*!
 * \brief The AbstractPluginManager class
 */
class __cell_export AbstractPluginManager
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractPluginManager)

    /*!
     * \brief load function loads the plugin and returns true if the plugin was loaded successfully; otherwise returns false.
     * \param plugin is plugin name.
     * \returns plugin.
     */
    __cell_no_discard_virtual AbstractPlugin* load(const std::string& plugin) = __cell_zero;

    /*!
     * \brief unload function unloads the plugin and returns true if the plugin could be unloaded; otherwise returns false.
     * \param plugin
     */
    __cell_virtual void unload(AbstractPlugin*& plugin) = __cell_zero;

    /*!
     * \brief isLoaded function returns true if the plugin is loaded; otherwise returns false.
     * \return bolean of status.
     */
    __cell_no_discard_virtual bool isLoaded() = __cell_zero;

private:
    PluginManagerData* m_pluginManagerData;
    bool m_status = {false};
};

CELL_NAMESPACE_END

#endif  // CELL_PLUGIN_MANAGER_ABSTRACT_HPP
