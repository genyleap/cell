#if __has_include("management.hpp")
#   include "management.hpp"
#else
#   error "Cell's management was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract DatabaseManagement.
 */
DatabaseManagement::DatabaseManagement()
{
}

/*!
 * \brief Destroys the DatabaseManagement.
 */
DatabaseManagement::~DatabaseManagement()
{
}

CELL_NAMESPACE_END
