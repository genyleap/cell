#ifdef __has_include
# if __has_include("page.hpp")
#   include "page.hpp"
#else
#   error "Cell's page was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract page class.
 */
AbstractPage::AbstractPage()
{
}

/*!
 * \brief Destroys the page class.
 */
AbstractPage::~AbstractPage()
{
}


CELL_NAMESPACE_END
