/*!
 * Gen3 License
 *
 * Copyright (c) 2021 Kambiz Asadzadeh
 * Copyright (c) 2023 Genyleap
 */

#ifndef LINUX_PCH_HPP
#define LINUX_PCH_HPP

#if __has_include(<utilities/preprocessor.hpp>)
#   include <utilities/preprocessor.hpp>
#else
#   include <utilities/preprocessor.hpp>

#if defined(CELL_PLATFORM_LINUX)
//! Linux Apis.
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX
#endif

#endif

#endif // LINUX_PCH_HPP
