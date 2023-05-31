#if __has_include("calendar.hpp")
#   include "calendar.hpp"
#else
#   error "Cell's calendar was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

CELL_DEFAULT_INTERFACE_OCTORS_IMPL(AbstractCalendar)

CELL_NAMESPACE_END
