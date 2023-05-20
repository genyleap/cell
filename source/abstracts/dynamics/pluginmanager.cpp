#if __has_include("pluginmanager.hpp")
#   include "pluginmanager.hpp"
#else
#   error "Cell's pluginmanager not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract plugin manager.
 */
AbstractPluginManager::AbstractPluginManager()
{
    __cell_safe_instance(m_pluginManagerData, PluginManagerData);
}

/*!
 * \brief Destroys the plugin manager.
 */
AbstractPluginManager::~AbstractPluginManager()
{
    __cell_safe_delete(m_pluginManagerData);
}


CELL_NAMESPACE_END
