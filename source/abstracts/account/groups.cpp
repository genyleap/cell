//! Cell's Groups.
#if __has_include(<abstracts/groups>)
#   include <abstracts/groups>
#else
#   error "Cell's groups was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

/*!
 * \brief Constructs an abstract groups.
 */
AbstractGroups::AbstractGroups()
{
}

/*!
 * \brief Destroys the groups.
 */
AbstractGroups::~AbstractGroups()
{
}

CELL_NAMESPACE_END
