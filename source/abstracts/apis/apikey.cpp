#ifdef __has_include
# if __has_include("apikey.hpp")
#   include "apikey.hpp"
#else
#   error "Cell's apikey not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Apis)

/*!
 * \brief Constructs an abstract api key.
 */
AbstractApiKey::AbstractApiKey()
{
}

/*!
 * \brief Destroys the api key.
 */
AbstractApiKey::~AbstractApiKey()
{
}

CELL_NAMESPACE_END
