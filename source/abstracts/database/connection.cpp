#if __has_include("connection.hpp")
#   include "connection.hpp"
#else
#   error "Cell's connection was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract database.
 */
DatabaseConnection::DatabaseConnection()
{
}

/*!
 * \brief Destroys the database.
 */
DatabaseConnection::~DatabaseConnection()
{
}

CELL_NAMESPACE_END
