#ifdef __has_include
# if __has_include("bearertoken.hpp")
#   include "bearertoken.hpp"
#else
#   error "Cell's bearertoken not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Apis)

/*!
 * \brief Constructs an abstract bearer token.
 */
AbstractBearerToken::AbstractBearerToken()
{
}

/*!
 * \brief Destroys the bearer token.
 */
AbstractBearerToken::~AbstractBearerToken()
{
}

CELL_NAMESPACE_END
