#if __has_include("querybuilder.hpp")
#   include "querybuilder.hpp"
#else
#   error "Cell's querybuilder was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract QueryBuilder.
 */
QueryBuilder::QueryBuilder()
{
}

/*!
 * \brief Destroys the QueryBuilder.
 */
QueryBuilder::~QueryBuilder()
{
}

CELL_NAMESPACE_END
