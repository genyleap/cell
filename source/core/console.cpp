#if __has_include("console.hpp")
#   include "console.hpp"
#else
#   error "Cell's "console.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Console)

Output::Output() {}

Output::~Output() {}

CELL_NAMESPACE_END
