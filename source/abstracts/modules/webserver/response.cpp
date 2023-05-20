#if __has_include("response.hpp")
#   include "response.hpp"
#else
#   error "Cell's response was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs a Response.
 */
Response::Response(int status_code,
                   const Types::OptionalString& content,
                   const Types::OptionalString& contentType)
{
}

/*!
 * \brief Destroys the Response.
 */
Response::~Response()
{
}

CELL_NAMESPACE_END
