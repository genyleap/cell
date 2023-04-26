#ifdef __has_include
# if __has_include("post.hpp")
#   include "post.hpp"
#else
#   error "Cell's post was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract page class.
 */
AbstractPost::AbstractPost()
{
    __cell_safe_instance(m_postData, PostData);
}

/*!
 * \brief Destroys the page class.
 */
AbstractPost::~AbstractPost()
{
    __cell_safe_delete(m_postData);
}


CELL_NAMESPACE_END
