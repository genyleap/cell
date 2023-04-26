#include "plugininterface.hpp"

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract plugin interface.
 */
AbstractPluginInterface::AbstractPluginInterface()
{
    __cell_safe_instance(m_pluginInterfaceData, PluginInterfaceData);
}

/*!
 * \brief Destroys the plugin interface.
 */
AbstractPluginInterface::~AbstractPluginInterface()
{
    __cell_safe_delete(m_pluginInterfaceData);
}


CELL_NAMESPACE_END
