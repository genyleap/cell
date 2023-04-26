#ifdef __has_include
# if __has_include("menu.hpp")
#   include "menu.hpp"
#else
#   error "Cell's menu was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract menu item.
 */
AbstractMenuItem::AbstractMenuItem()
{
}

/*!
 * \brief Destroys the menu item.
 */
AbstractMenuItem::~AbstractMenuItem()
{
}

/*!
 * \brief Constructs an abstract menu.
 */
AbstractMenu::AbstractMenu()
{
}

/*!
 * \brief Destroys the menu.
 */
AbstractMenu::~AbstractMenu()
{
}

CELL_NAMESPACE_END
