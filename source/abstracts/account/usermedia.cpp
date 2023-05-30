//! Cell's Usermedia.
#if __has_include(<abstracts/usermedia>)
#   include <abstracts/usermedia>
#else
#   error "Cell's usermedia was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

/*!
 * \brief Constructs an abstract avatar.
 */
AbstractAvatar::AbstractAvatar()
{
}

/*!
 * \brief Destroys the abstract avatar.
 */
AbstractAvatar::~AbstractAvatar()
{
}

/*!
 * \brief Constructs an abstract image.
 */
AbstractImage::AbstractImage()
{
}

/*!
 * \brief Destroys the abstract image.
 */
AbstractImage::~AbstractImage()
{
}

/*!
 * \brief Constructs an abstract cover.
 */
AbstractCover::AbstractCover()
{
}

/*!
 * \brief Destroys the abstract cover.
 */
AbstractCover::~AbstractCover()
{
}

/*!
 * \brief Constructs an abstract story.
 */
AbstractStory::AbstractStory()
{
}

/*!
 * \brief Destroys the abstract story.
 */
AbstractStory::~AbstractStory()
{
}

CELL_NAMESPACE_END
