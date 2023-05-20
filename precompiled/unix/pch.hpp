/*!
 * Gen3 License
 *
 * Copyright (c) 2021 Kambiz Asadzadeh
 * Copyright (c) 2023 Genyleap
 */

#ifndef UNIX_PCH_HPP
#define UNIX_PCH_HPP
#if __has_include(<utilities/preprocessor.hpp>)
#   include <utilities/preprocessor.hpp>
#else
#   include <utilities/preprocessor.hpp>
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Welaborated-enum-base"
#if defined(PLATFORM_MAC) && !defined(PLATFORM_MOBILE)
//!Apple macOS Apis.
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <mach-o/dyld.h>
#include <IOKit/IOKitLib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <ImageIO/ImageIO.h>
#elif defined(PLATFORM_MAC) && defined(PLATFORM_MOBILE)
//! Apple iOS Apis.
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <mach-o/dyld.h>
#include <IOKit/IOKitLib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <ImageIO/ImageIO.h>
#elif defined(PLATFORM_LINUX)
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX
#elif defined(PLATFORM_FREEBSD)
//! FreeBSD Apis.
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#endif

#pragma clang diagnostic pop

#endif // UNIX_PCH_HPP
