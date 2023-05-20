#if __has_include("api.hpp")
#   include "api.hpp"
#else
#   error "Cell's api was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract api.
 */
AbstractApi::AbstractApi()
{
}

/*!
 * \brief Destroys the api.
 */
AbstractApi::~AbstractApi()
{
}

CELL_NAMESPACE_END
