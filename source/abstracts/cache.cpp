#if __has_include("cache.hpp")
#   include "cache.hpp"
#else
#   error "Cell's cache was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract cache.
 */
AbstractCache::AbstractCache()
{
}

/*!
 * \brief Destroys the cache.
 */
AbstractCache::~AbstractCache()
{
}

CELL_NAMESPACE_END
