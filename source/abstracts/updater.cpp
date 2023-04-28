#ifdef __has_include
# if __has_include("updater.hpp")
#   include "updater.hpp"
#else
#   error "Cell's updater was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract updater.
 */
AbstractUpdater::AbstractUpdater()
{
}

/*!
 * \brief Destroys the updater.
 */
AbstractUpdater::~AbstractUpdater()
{
}

CELL_NAMESPACE_END
