#ifdef __has_include
# if __has_include("module.hpp")
#   include "module.hpp"
#else
#   error "Cell's module not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

Module::Module()
{

}

Module::~Module()
{

}

CELL_NAMESPACE_END
