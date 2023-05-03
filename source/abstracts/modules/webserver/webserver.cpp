#ifdef __has_include
# if __has_include("webserver.hpp")
#   include "webserver.hpp"
#else
#   error "Cell's webserver was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs a WebServer.
 */
AbstractWebServer::AbstractWebServer()
{
}

/*!
 * \brief Destroys the WebServer.
 */
AbstractWebServer::~AbstractWebServer()
{
}

CELL_NAMESPACE_END
