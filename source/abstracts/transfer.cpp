#if __has_include("transfer.hpp")
#   include "transfer.hpp"
#else
#   error "Cell's transfer was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract transfer method.
 */
AbstractTransferMethod::AbstractTransferMethod()
{
}

/*!
 * \brief Destroys the transfer method.
 */
AbstractTransferMethod::~AbstractTransferMethod()
{
}

CELL_NAMESPACE_END
