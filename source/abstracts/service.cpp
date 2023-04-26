#ifdef __has_include
# if __has_include("service.hpp")
#   include "service.hpp"
#else
#   error "Cell's service was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract activity.
 */
AbstractActivity::AbstractActivity()
{
}

/*!
 * \brief Destroys the activity.
 */
AbstractActivity::~AbstractActivity()
{
}

/*!
 * \brief Constructs an abstract service.
 */
AbstractService::AbstractService()
{
}

/*!
 * \brief Destroys the service.
 */
AbstractService::~AbstractService()
{
}

CELL_NAMESPACE_END
