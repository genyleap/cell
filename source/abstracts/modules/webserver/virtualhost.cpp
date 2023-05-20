#if __has_include("virtualhost.hpp")
#   include "virtualhost.hpp"
#else
#   error "Cell's virtualhost was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs a VirtualHostConfig.
 */
VirtualHostConfig::VirtualHostConfig()
{
}

/*!
 * \brief Destroys the WebServer.
 */
VirtualHostConfig::~VirtualHostConfig()
{
}

CELL_NAMESPACE_END
