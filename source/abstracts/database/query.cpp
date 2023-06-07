#if __has_include("query.hpp")
#   include "query.hpp"
#else
#   error "Cell's query was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract QueryExecutor.
 */
QueryExecutor::QueryExecutor()
{
}

/*!
 * \brief Destroys the QueryExecutor.
 */
QueryExecutor::~QueryExecutor()
{
}

CELL_NAMESPACE_END
