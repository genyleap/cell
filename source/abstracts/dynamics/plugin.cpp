#ifdef __has_include
# if __has_include("plugin.hpp")
#   include "plugin.hpp"
#else
#   error "Cell's plugin not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract plugin.
 */
AbstractPlugin::AbstractPlugin()
{
    __cell_safe_instance(m_pluginInfo, PluginInfo);
}

/*!
 * \brief Destroys the plugin.
 */
AbstractPlugin::~AbstractPlugin()
{
    __cell_safe_delete(m_pluginInfo);
}


CELL_NAMESPACE_END
