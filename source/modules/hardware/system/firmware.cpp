#if __has_include("firmware.hpp")
#   include "firmware.hpp"
#else
#   error "Cell's "firmware.hpp" was not found!"
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
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

FirmwareInfo::FirmwareInfo()
{
}

FirmwareInfo::~FirmwareInfo()
{
}

CELL_NAMESPACE_END
