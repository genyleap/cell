#if __has_include("datamanipulator.hpp")
#   include "datamanipulator.hpp"
#else
#   error "Cell's datamanipulator was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract DataManipulator.
 */
DataManipulator::DataManipulator()
{
}

/*!
 * \brief Destroys the DataManipulator.
 */
DataManipulator::~DataManipulator()
{
}

CELL_NAMESPACE_END
