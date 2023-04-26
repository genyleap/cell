#ifdef __has_include
# if __has_include("basic.hpp")
#   include "basic.hpp"
#else
#   error "Cell's basic not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Apis)

/*!
 * \brief Constructs an abstract basic api.
 */
AbstractBasicApi::AbstractBasicApi()
{
}

/*!
 * \brief Destroys the basic api.
 */
AbstractBasicApi::~AbstractBasicApi()
{
}

CELL_NAMESPACE_END
