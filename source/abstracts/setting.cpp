#if __has_include("setting.hpp")
#   include "setting.hpp"
#else
#   error "Cell's setting was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract setting.
 */
AbstractSetting::AbstractSetting()
{
}

/*!
 * \brief Destroys the setting.
 */
AbstractSetting::~AbstractSetting()
{
}

CELL_NAMESPACE_END
