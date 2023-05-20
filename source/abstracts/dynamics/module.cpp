//! Cell's Abstract Dynamics.
#if __has_include("module.hpp")
#   include "module.hpp"
#else
#   error "Cell's module was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract module.
 */
AbstractModule::AbstractModule()
{
    __cell_safe_instance(m_moduleInfo, ModuleInfo);
}

/*!
 * \brief Destroys the module.
 */
AbstractModule::~AbstractModule()
{
    __cell_safe_delete(m_moduleInfo);
}


CELL_NAMESPACE_END
