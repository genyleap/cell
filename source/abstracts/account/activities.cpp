//! Cell's Activities.
#if __has_include(<abstracts/activities>)
#   include <abstracts/activities>
#else
#   error "Cell's activities was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

/*!
 * \brief Constructs an abstract activities.
 */
AbstractActivities::AbstractActivities()
{
}

/*!
 * \brief Destroys the abstract activities.
 */
AbstractActivities::~AbstractActivities()
{
}

CELL_NAMESPACE_END
