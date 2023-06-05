#if __has_include("message.hpp")
#   include "message.hpp"
#else
#   error "Cell's message was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract Message.
 */
AbstractMessage::AbstractMessage()
{
}

/*!
 * \brief Destroys the Message.
 */
AbstractMessage::~AbstractMessage()
{
}

CELL_NAMESPACE_END
