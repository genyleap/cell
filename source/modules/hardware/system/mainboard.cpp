#ifdef __has_include
# if __has_include("motherboard.hpp")
#   include "motherboard.hpp"
#else
#   error "Cell's "motherboard.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif


CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)


CELL_NAMESPACE_END
