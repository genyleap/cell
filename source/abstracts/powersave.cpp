#if __has_include("powersave.hpp")
#   include "powersave.hpp"
#else
#   error "Cell's powersave was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract powersave.
 */
AbstractPowerSave::AbstractPowerSave()
{
}

/*!
 * \brief Destroys the powersave.
 */
AbstractPowerSave::~AbstractPowerSave()
{
}

CELL_NAMESPACE_END
