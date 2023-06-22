#if __has_include("mainboard.hpp")
#   include "mainboard.hpp"
#else
#   error "Cell's "mainboard.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

MainboardInfo::MainboardInfo()
{

}

MainboardInfo::~MainboardInfo()
{

}

MainboardInfo::BoardInfo MainboardInfo::get() __cell_const_noexcept
{
    return MainboardInfo::BoardInfo();
}

CELL_NAMESPACE_END
