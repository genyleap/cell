#if __has_include("request.hpp")
#   include "request.hpp"
#else
#   error "Cell's request was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs a Request.
 */
Request::Request(const Types::OptionalString& method,
        const Types::OptionalString& uri,
        const Types::OptionalString& httpVersion,
        Types::Headers& headers,
        const Types::OptionalString& body)
{
}

/*!
 * \brief Destroys the Request.
 */
Request::~Request()
{
}

CELL_NAMESPACE_END
