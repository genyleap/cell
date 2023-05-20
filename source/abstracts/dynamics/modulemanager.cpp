//! Cell's Abstract Dynamics.
#if __has_include("modulemanager.hpp")
#   include "modulemanager.hpp"
#else
#   error "Cell's modulemanager was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract module manager.
 */
AbstractModuleManager::AbstractModuleManager()
{
    __cell_safe_instance(m_moduleManagerData, ModuleManagerData);
}

/*!
 * \brief Destroys the module manager.
 */
AbstractModuleManager::~AbstractModuleManager()
{
    __cell_safe_delete(m_moduleManagerData);
}

CELL_NAMESPACE_END
