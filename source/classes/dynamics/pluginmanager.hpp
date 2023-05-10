#ifndef CELL_PLUGIN_MANAGER_HPP
#define CELL_PLUGIN_MANAGER_HPP

#ifdef __has_include
# if __has_include("plugin.hpp")
#   include "plugin.hpp"
#else
#   error "Cell's "plugin.hpp" was not found!"
# endif
#endif

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

#endif // CELL_PLUGIN_MANAGER_HPP
