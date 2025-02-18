/*!
 * Gen3 License
 *
 * Copyright (c) 2024 Kambiz Asadzadeh (compez.eth)
 * Copyright (c) 2024 Genyleap
 */

#ifndef WIN32_PCH_HPP
#define WIN32_PCH_HPP

#if __has_include(<utilities/preprocessor.hpp>)
#   include <utilities/preprocessor.hpp>
#else
#   include <utilities/preprocessor.hpp>
#endif

#if defined(CELL_PLATFORM_WINDOWS) && !defined(CELL_PLATFORM_MOBILE)
//! Windows Apis.
#include <Windows.h>
#include <Iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")>
#endif

#endif // WIN32_PCH_HPP
