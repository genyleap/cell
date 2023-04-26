#ifdef __has_include
# if __has_include("moduleinterface.hpp")
#   include "moduleinterface.hpp"
#else
#   error "Cell's moduleinterface not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract module interface.
 */
AbstractModuleInterface::AbstractModuleInterface()
{
    __cell_safe_instance(m_moduleInterfaceData, ModuleInterfaceData);
}

/*!
 * \brief Destroys the module interface.
 */
AbstractModuleInterface::~AbstractModuleInterface()
{
    __cell_safe_delete(m_moduleInterfaceData);
}


CELL_NAMESPACE_END
