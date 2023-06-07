#if __has_include("maintenance.hpp")
#   include "maintenance.hpp"
#else
#   error "Cell's maintenance was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract DatabaseMaintenance.
 */
DatabaseMaintenance::DatabaseMaintenance()
{
}

/*!
 * \brief Destroys the DatabaseMaintenance.
 */
DatabaseMaintenance::~DatabaseMaintenance()
{
}

CELL_NAMESPACE_END
