#if __has_include("tablemanager.hpp")
#   include "tablemanager.hpp"
#else
#   error "Cell's tablemanager was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract TableManager.
 */
TableManager::TableManager()
{
}

/*!
 * \brief Destroys the TableManager.
 */
TableManager::~TableManager()
{
}

CELL_NAMESPACE_END
