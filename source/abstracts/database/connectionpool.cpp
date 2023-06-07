#if __has_include("connectionpool.hpp")
#   include "connectionpool.hpp"
#else
#   error "Cell's connectionpool was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract ConnectionPool.
 */
ConnectionPool::ConnectionPool()
{
}

/*!
 * \brief Destroys the database.
 */
ConnectionPool::~ConnectionPool()
{
}

CELL_NAMESPACE_END
