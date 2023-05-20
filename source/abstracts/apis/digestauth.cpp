#if __has_include("digestauth.hpp")
#   include "digestauth.hpp"
#else
#   error "Cell's digestauth not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Apis)

/*!
 * \brief Constructs an abstract digest auth.
 */
AbstractDigestAuth::AbstractDigestAuth()
{
}

/*!
 * \brief Destroys the digets auth.
 */
AbstractDigestAuth::~AbstractDigestAuth()
{
}

CELL_NAMESPACE_END
