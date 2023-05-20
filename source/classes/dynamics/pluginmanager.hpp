/*!
 * @file        pluginmanager.hpp
 * @brief       This file is part of the Cell System.
 * @details     Plugin manager for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_MANAGER_HPP
#define CELL_PLUGIN_MANAGER_HPP

#if __has_include("plugin.hpp")
#   include "plugin.hpp"
#else
#   error "Cell's "plugin.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

// Define the prototype for a function that should exist in the lib
// that is used to create and return the plugin type in the lib.

PointerToObject(Plugin, fnCreatePlugin)

// Destroys the plugin type from the lib before the library is unloaded.
using fnDestroyPlugin = PointerToFunction;

class PluginManagerPimpl;

/*!
 * \brief The PluginManager class
 */
class __cell_export PluginManager
{
public:
    DeclareSingletonInstance(PluginManager)

  /*!
   * \brief load function loads the plugin and returns true if the plugin was loaded successfully; otherwise returns false.
   * \param plugin is plugin name.
   * \return plugin.
   */
  Plugin* load(const std::string& plugin);

  /*!
   * \brief unload function unloads the plugin and returns true if the plugin could be unloaded; otherwise returns false.
   * \param plugin
   */
  void unload(Plugin*& plugin);

  /*!
   * \brief isLoaded function returns true if the plugin is loaded; otherwise returns false.
   * \return bolean of status.
   */
  bool isLoaded() const;

private:
  CELL_DEFAULT_OCTORS(PluginManager)
  bool m_status = {false};
  Scope<PluginManagerPimpl> implementationPtr;
};

CELL_NAMESPACE_END

#endif // CELL_PLUGIN_MANAGER_HPP
