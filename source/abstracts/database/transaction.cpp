#if __has_include("transaction.hpp")
#   include "transaction.hpp"
#else
#   error "Cell's transaction was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract DatabaseTransaction.
 */
DatabaseTransaction::DatabaseTransaction()
{
}

/*!
 * \brief Destroys the DatabaseTransaction.
 */
DatabaseTransaction::~DatabaseTransaction()
{
}

CELL_NAMESPACE_END
