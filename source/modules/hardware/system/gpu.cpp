#ifdef _WIN32
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
//!libs
#pragma comment(lib, "Ws2_32.lib")
#elif __APPLE__
#include <unistd.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#else
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#endif

#if __has_include("gpu.hpp")
#   include "gpu.hpp"
#else
#   error "Cell's "gpu.hpp" was not found!"
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

GraphicInformation::GraphicInformation()
{
}

GraphicInformation::~GraphicInformation()
{
}

std::vector<GpuInfo> GraphicInformation::get()
{
#if defined(PLATFORM_WINDOWS)
//! Todo...
#elif defined(PLATFORM_MAC)
//! Todo...
#elif defined(PLATFORM_LINUX)
//! Todo...
#endif
    return std::vector<GpuInfo>();
}

CELL_NAMESPACE_END
