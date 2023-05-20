#if __has_include("device.hpp")
#   include "device.hpp"
#else
#   error "Cell's device was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract device.
 */
AbstractDevice::AbstractDevice()
{
}

/*!
 * \brief Destroys the device.
 */
AbstractDevice::~AbstractDevice()
{
}

CELL_NAMESPACE_END
