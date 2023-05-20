#if __has_include("base.hpp")
#   include "base.hpp"
#else
#   error "Cell's base was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract base class.
 */
AbstractBaseClass::AbstractBaseClass()
{
}

/*!
 * \brief Destroys the base class.
 */
AbstractBaseClass::~AbstractBaseClass()
{
}


CELL_NAMESPACE_END
