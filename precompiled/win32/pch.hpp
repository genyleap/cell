/*!
 * Gen3 License
 *
 * Copyright (c) 2021 Kambiz Asadzadeh
 * Copyright (c) 2023 Genyleap
 */

#ifndef WIN32_PCH_HPP
#define WIN32_PCH_HPP
#if __has_include(<utilities/preprocessor.hpp>)
#   include <utilities/preprocessor.hpp>
#else
#   include <utilities/preprocessor.hpp>
#endif

#if defined(PLATFORM_WINDOWS) && !defined(PLATFORM_MOBILE)
//! Windows Apis.
#include <Windows.h>
#include <Iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")>
#endif

#endif // WIN32_PCH_HPP
