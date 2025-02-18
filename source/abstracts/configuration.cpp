#if __has_include("configuration.hpp")
#   include "configuration.hpp"
#else
#   error "Cell's configuration was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract configuration.
 */
AbstractConfiguration::AbstractConfiguration()
{
}

/*!
 * \brief Destroys the configuration.
 */
AbstractConfiguration::~AbstractConfiguration()
{
}

CELL_NAMESPACE_END
