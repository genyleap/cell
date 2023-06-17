#if __has_include("installer.hpp")
#   include "installer.hpp"
#else
#   error "Cell's installer was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract menu item.
 */
AbstractInstaller::AbstractInstaller()
{
}

/*!
 * \brief Destroys the menu item.
 */
AbstractInstaller::~AbstractInstaller()
{
}


CELL_NAMESPACE_END
