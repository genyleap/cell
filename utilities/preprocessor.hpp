/*!
 *
 * Copyright (c) 2024 Kambiz Asadzadeh (compez.eth)
 * Copyright (c) 2024 Genyleap
 */

#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

/*!
 * namespace Preprocessor
 * This preprocessor helps you to detect CELL_COMPILER, platform, and CELL_ARCHITECTURE.
 */

namespace Preprocessor {

//! CELL_COMPILERS
#if defined(__clang__)
/* Clang/LLVM. ---------------------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "Clang/LLVM"
#undef CELL_COMPILER_CLANG_LLVM
#define CELL_COMPILER_CLANG_LLVM "Clang/LLVM"
#undef CELL_COMPILER_VER
#define CELL_COMPILER_VER __clang_version__
#elif (defined(__clang__) && !defined(__llvm__)) && !defined(__GNUC__)
#elif defined(__ICC) || defined(__INTEL_COMPILER)
/* Intel ICC/ICPC. ------------------------------------------ */
#undef CELL_COMPILER
#define CELL_COMPILER "Intel ICC/ICPC"
#undef CELL_COMPILER_INTEL
#define CELL_COMPILER_INTEL "Intel ICC/ICPC"
#define CELL_COMPILER_VER __INTEL_COMPILER_BUILD_DATE
#elif defined(__MINGW32__) && !defined(__amd64__) && !defined(__amd64) &&      \
    !defined(__ia64__)
/* __MINGW32__. ------------------------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "MinGW-w86 (x86) 32 Bit"
#undef CELL_COMPILER_MINGW
#define CELL_COMPILER_MINGW "MinGW-w86 (x86) 32 Bit"
#undef CELL_COMPILER_VER
#define CELL_COMPILER_VER __MINGW32_MAJOR_VERSION << "." << __MINGW32_MINOR_VERSION
#elif defined(__MINGW32__)
/* __MINGW64_32__. ------------------------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "MinGW-w64 (x86_64) 32-64 Bit"
#undef CELL_COMPILER_MINGW64_32
#define CELL_COMPILER_MINGW64_32 "MinGW-w64 (x86_64) 32-64 Bit"
#undef CELL_COMPILER_VER
#define CELL_COMPILER_VER __MINGW32_MAJOR_VERSION << "." << __MINGW32_MINOR_VERSION
#elif defined(__MINGW64__)
/* __MINGW64__. ------------------------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "MinGW-w64 (x64) 64 Bit"
#undef CELL_COMPILER_MINGW_64
#define CELL_COMPILER_MINGW_64 "MinGW-w64 (x64) 64 Bit"
#undef CELL_COMPILER_VER
#define CELL_COMPILER_VER __MINGW64_MAJOR_VERSION << "." << __MINGW64_MINOR_VERSION
#elif defined(__GNUC__) || defined(__GNUG__) && !defined(__clang__)
#define GCC_VERSION __GNUC__ << "." <<  __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__
/* GNU GCC/G++. --------------------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "GNU GCC/G++"
#undef CELL_COMPILER_GNU
#define CELL_COMPILER_GNU "GNU GCC/G++"
#undef CELL_COMPILER_GCC
#define CELL_COMPILER_GCC "GNU GCC/G++"
#undef CELL_COMPILER_VER
#define CELL_COMPILER_VER GCC_VERSION
#elif defined(__HP_cc) || defined(__HP_aCC)
/* Hewlett-Packard C/aC++. ---------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "Hewlett-Packard C/aC++"
#undef CELL_COMPILERHEWLETT
#define CELL_COMPILERHEWLETT "Hewlett-Packard C/aC++"
#define CELL_COMPILER_VER __HP_aCC
#elif defined(__IBMC__) || defined(__IBMCPP__)
/* IBM XL C/C++. -------------------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "IBM XL C/C++"
#undef CELL_COMPILER_IBM
#define CELL_COMPILER_IBM "IBM XL C/C++"
#define CELL_COMPILER_VER __xlC_ver__
#elif defined(_MSC_VER)
/* Microsoft Visual Studio. --------------------------------- */
#undef CELL_COMPILER
#define CELL_COMPILER "MSVC++ "
#undef CELL_COMPILER_MSVC
#define CELL_COMPILER_MSVC "MSVC++ "
#undef CELL_COMPILER_VER
#define CELL_COMPILER_VER _MSC_VER
#elif defined(__PGI)
/* Portland Group PGCC/PGCPP. ------------------------------- */
#undef CELL_COMPILER "PGCC/PGCPP"
#define CELL_COMPILER "PGCC/PGCPP"
#undef CELL_COMPILER_PGCC "PGCC/PGCPP"
#define CELL_COMPILER_PGCC "PGCC/PGCPP"
#define CELL_COMPILER_VER __VERSION__
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
/* Oracle Solaris Studio. ----------------------------------- */
#undef CELL_COMPILER "Oracle Solaris"
#define CELL_COMPILER "Oracle Solaris"
#undef CELL_COMPILER_ORACLE "Oracle Solaris"
#define CELL_COMPILER_ORACLE "Oracle Solaris"
#define CELL_COMPILER_VER __SUNPRO_CC
#endif

#if defined(_MSC_VER) && _MSC_VER == 1400
#undef MSVCPP
#define MSVCPP "MSVC++ 8.0"
#elif defined(_MSC_VER) && _MSC_VER == 1500
#undef MSVCPP
#define MSVCPP "MSVC++ 9.0"
#elif defined(_MSC_VER) && _MSC_VER == 1600
#undef MSVCPP
#define MSVCPP "MSVC++ 10.0"
#elif defined(_MSC_VER) && _MSC_VER == 1700
#undef MSVCPP
#define MSVCPP "MSVC++ 11.0"
#elif defined(_MSC_VER) && _MSC_VER == 1800
#undef MSVCPP
#define MSVCPP "MSVC++ 12.0"
#elif defined(_MSC_VER) && _MSC_VER == 1900
#undef MSVCPP
#define MSVCPP "MSVC++ 14.0"
#elif defined(_MSC_VER) && _MSC_VER == 1910
#undef MSVCPP
#define MSVCPP "MSVC++ 15.0"
#elif defined(_MSC_VER) && _MSC_VER == 1911
#undef MSVCPP
#define MSVCPP "MSVC++ 15.3"
#elif defined(_MSC_VER) && _MSC_VER == 1912
#undef MSVCPP
#define MSVCPP "MSVC++ 15.5"
#elif defined(_MSC_VER) && _MSC_VER == 1913
#undef MSVCPP
#define MSVCPP "MSVC++ 15.6"
#elif defined(_MSC_VER) && _MSC_VER == 1914
#undef MSVCPP
#define MSVCPP "MSVC++ 15.7"
#elif defined(_MSC_VER) && _MSC_VER == 1915
#undef MSVCPP
#define MSVCPP "MSVC++ 15.8"
#elif defined(_MSC_VER) && _MSC_VER == 1915
#undef MSVCPP
#define MSVCPP "MSVC++ 15.8"
#elif defined(_MSC_VER) && _MSC_VER == 1916
#undef MSVCPP
#define MSVCPP "MSVC++ 15.9"
#elif defined(_MSC_VER) && _MSC_VER == 1920
#undef MSVCPP
#define MSVCPP "MSVC++ RTW 16.0"
#elif defined(_MSC_VER) && _MSC_VER == 1921
#undef MSVCPP
#define MSVCPP "MSVC++ 16.1"
#elif defined(_MSC_VER) && _MSC_VER == 1922
#undef MSVCPP
#define MSVCPP "MSVC++ 16.2"
#elif defined(_MSC_VER) && _MSC_VER == 1923
#undef MSVCPP
#define MSVCPP "MSVC++ 16.3"
#elif defined(_MSC_VER) && _MSC_VER == 1924
#undef MSVCPP
#define MSVCPP "MSVC++ 16.4"
#elif defined(_MSC_VER) && _MSC_VER == 1925
#undef MSVCPP
#define MSVCPP "MSVC++ 16.5"
#elif defined(_MSC_VER) && _MSC_VER == 1926
#undef MSVCPP
#define MSVCPP "MSVC++ 16.6"
#elif defined(_MSC_VER) && _MSC_VER == 1927
#undef MSVCPP
#define MSVCPP "MSVC++ 16.7"
#elif defined(_MSC_VER) && _MSC_VER == 1928
#undef MSVCPP
#define MSVCPP "MSVC++ 16.8, 16.9"
#elif defined(_MSC_VER) && _MSC_VER == 1929
#undef MSVCPP
#define MSVCPP "MSVC++ 16.10"
#elif defined(_MSC_VER) && _MSC_VER == 1930
#undef MSVCPP
#elif defined(_MSC_VER) && _MSC_VER == 1931
#undef MSVCPP
#define MSVCPP "MSVC++ (17.1)"
#endif

//! LANGUAGE STANDARD
#if __cplusplus == 199711L && !defined(_MSC_VER)
/* C++98:  __cplusplus is 19971L.*/
#undef CPP_VERSION
#define CPP_VERSION "C++98"
#undef CPP_VALUE
#define CPP_VALUE "19971L"
#elif __cplusplus == 201103L
/* C++11:  __cplusplus is 201103L.*/
#undef CPP_VERSION
#define CPP_VERSION "C++11"
#undef CPP_VALUE
#define CPP_VALUE "201103L"
#elif __cplusplus == 201402L
/* C++14:  __cplusplus is 201402L.*/
#undef CPP_VERSION
#define CPP_VERSION "C++14"
#undef CPP_VALUE
#define CPP_VALUE "201402L"
#elif __cplusplus == 201702L || __cplusplus == 201703
/* C++17:  __cplusplus is c++1z.*/
#undef CPP_VERSION
#define CPP_VERSION "C++17"
#undef CPP_VALUE
#define CPP_VALUE "201703"
#elif __cplusplus == 201707 || __cplusplus == 202002L || __cplusplus == 201709
/* C++20:  __cplusplus is c++2a.*/
#undef CPP_VERSION
#define CPP_VERSION "C++20"
#undef CPP_VALUE
#define CPP_VALUE __cplusplus
#elif __cplusplus == 20120
/* C++23:  __cplusplus is c++2b.*/
#undef CPP_VERSION
#define CPP_VERSION "C++23"
#undef CPP_VALUE
#define CPP_VALUE __cplusplus
#elif __embedded_cplusplus
#undef CPP_VERSION
#define CPP_VERSION "Embedded C++"
#undef CPP_VALUE
#define CPP_VALUE "19971L"
#elif defined(__clang__)
#undef CPP_VERSION
#define CPP_VERSION __cplusplus
#undef CPP_VALUE
#define CPP_VALUE __cplusplus
#elif defined(__GNUC__)
#undef CPP_VERSION
#define CPP_VERSION __cplusplus
#undef CPP_VALUE
#define CPP_VALUE __cplusplus
#else
#undef CPP_VERSION
#define CPP_VERSION 0
#undef CPP_VALUE
#define CPP_VALUE "Unknown"
#endif

//! EXPORTS & EXTRA
#if defined(__WINNT) || defined(__WINNT__) || defined(WIN32) ||                \
    defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) ||               \
    defined(WIN64) || defined(_WIN64) || defined(__WIN64) ||                   \
    defined(__WIN64__)
//! Microsoft Windows
#define PROJECT_EXPORT __declspec(dllexport)
#define PROJECT_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//! Define for Unix base OS such as: Linux, macOS, FreeBSD, etc...
#define PROJECT_EXPORT __attribute__((visibility("default")))
#define PROJECT_IMPORT __attribute__((visibility("default")))
#define PROJECT_HIDDEN __attribute__((visibility("hidden")))
#else
//  do nothing and hope for the best?
#define PROJECT_EXPORT
#define PROJECT_IMPORT
#pragma warning Unknown dynamic link import / export semantics.
#endif

#define PROJECT_DATE __DATE__
#define PROJECT_TIME __TIME__
#define PROJECT_FUNCTION __FUNCTION__
#define PROJECT_LINE __LINE__
#define PROJECT_FILE __FILE__
#define PROJECT_COUNTER __COUNTER__

/* NOTICE:  __attribute__ is Linux syntax; __declspec is the Windows syntax.*/
/*The __declspec(noinline) attribute suppresses the inlining of a function at
the call points of the function.

__declspec(noinline) can also be applied to constant data, to prevent the
compiler from using the value for optimization purposes, without affecting its
placement in the object. This is a feature that can be used for patchable
constants, that is, data that is later patched to a different value. It is an
error to try to use such constants in a context where a constant value is
required. For example, an array dimension.
*/

#if defined(__WINNT) || defined(__WINNT__) || defined(WIN32) ||                \
    defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) ||               \
    defined(WIN64) || defined(_WIN64) || defined(__WIN64) ||                   \
    defined(__WIN64__)
#define PROJECT_NOINLINE __declspec(noinline)
#define PROJECT_INLINE inline
#else
/// Define for Unix base OS such as: Linux, macOS, FreeBSD, etc...
#define PROJECT_NOINLINE __attribute__((noinline))
#define PROJECT_INLINE inline
#endif

//! CELL_ARCHITECTURE

/*
 * Classic Standard
 * 32-bit and 64-Bit systems
 * Developer:	Intel & AMD Holdings
 * CELL_PROCESSORs:	Intel & AMD Machine
 * (64-bit):	EM64T, IA-32e, Intel64, x64, x86-64
 * (32-bit):	IA-32, i386, x86, x86-32
 * CELL_PROCESSORs:	Athlon, Atom, Core, Core 2, Core i3/i5/i7, Opteron, Pentium,
 * Phenom, Sempron, Turion, etc.
 */

#if (defined(i386) || defined(__i386) || defined(__i386__) ||                  \
     defined(__IA32__) || defined(_M_IX86) || defined(_X86_)) &&               \
    !defined(__amd64)
//! x86 based systems (32-bit)
#undef X86_64BIT
#define X86_64BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Intel"
#undef INTEL
#define INTEL
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "x86 (32-Bit)"
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) ||          \
    defined(_M_AMD64) || defined(_M_X64) && !defined(X86_32bit)
//! x64 based systems (64-bit)
#undef X64_64BIT
#define X64_64BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Intel"
#undef INTEL
#define INTEL
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "x86_64 (64-Bit)"
#endif

/*
 * x86 and x86-64
 * (64-bit):	EM64T, IA-32e, Intel64, x64, x86-64
 * (32-bit):	IA-32, i386, x86, x86-32
 * Developers:	Intel only
 * CELL_PROCESSORs:	Athlon
 *
 */

#if defined(__i386__) && !defined(_M_AMD64)
/* x86 32-bit ----------------------------------------------- */
#undef INTEL_32BIT
#define INTEL_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Intel"
#undef INTEL
#define INTEL
#undef CELL_ARCHITECTURE_INTEL
#define CELL_ARCHITECTURE_INTEL "x86 (32-Bit)"
#elif defined(__x86_64__) && !defined(_M_AMD64)
/* x64 64-bit ----------------------------------------------- */
#undef INTEL_64BIT
#define INTEL_64BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Intel"
#undef INTEL
#define INTEL
#undef CELL_ARCHITECTURE_INTEL
#define CELL_ARCHITECTURE_INTEL "x86_64 (64-Bit)"
#endif

/*
 * x86 and x86-64
 * (32-bit):    i386, x86, x86-32
 * (64-bit):	AMD64, x64
 * Developers:	AMD only
 * CELL_PROCESSORs:	Athlon
 *
 */

#if defined(__i386__) && !defined(__x86_64__)
/* x86 32-bit ----------------------------------------------- */
#undef AMD_32BIT
#define AMD_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "AMD"
#undef AMD
#define AMD
#undef CELL_ARCHITECTURE
#undef CELL_ARCHITECTURE_AMD
#define CELL_ARCHITECTURE_AMD "x86 (32-Bit)"
#elif (defined(__amd64__) || defined(__amd64) || defined(_M_AMD64)) &&         \
    !defined(__x86_64__)
/* x64 64-bit ----------------------------------------------- */
#undef AMD_64BIT
#define AMD_64BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "AMD"
#undef AMD
#define AMD
#undef CELL_ARCHITECTURE_AMD
#define CELL_ARCHITECTURE_AMD "x86_64 (64-Bit)"
#endif

/*
 * Alpha AXP
 * (64-bit):	x64
 * (32-bit):	x86
 * Developers:	Digital Equipment Corporation
 * CELL_PROCESSORs:	Alpha
 *
 */

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
/* Alpha ----------------------------------------------- */
#undef ALPHA_32BIT
#define ALPHA_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Alpha"
#undef ALPHA
#define ALPHA
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Alpha (32-Bit)"
#endif

/*
 * ARM
 * 32-bit
 * Developer:	ARM Holdings
 * CELL_PROCESSORs:	Acorn RISC Machine
 */

#if defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||    \
    defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) ||        \
    defined(_M_ARMT) || defined(__arm)
/* ARM-x86 -------------------------------------------------- */
#undef ARM_32BIT
#define ARM_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Arm"
#undef ARM
#define ARM
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Arm (32-Bit)"
#endif

/*
 * ARM
 * 64-bit
 * Developer:	ARM Holdings
 * CELL_PROCESSORs:	Acorn RISC Machine
 */

#if defined(__aarch64__)
/* ARM-x64 -------------------------------------------------- */
#undef ARM_64BIT
#define ARM_64BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Arm64"
#undef ARM
#define ARM
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "ARM64/AArch64 (64-Bit)"
#endif

/*
 * PA-RISC
 * 32-bit
 * Developer:	Convex Computer Corporation
 * CELL_PROCESSORs:	PA-RISC
 */

#if defined(__convex__)
/* Blackfin -------------------------------------------------- */
#undef PA_RISC_32BIT
#define PA_RISC_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Convex PA-RISC"
#undef PA_RISC
#define PA_RISC
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "RISC (32-Bit)"
#endif

/*
 * Epiphany
 * 32-bit & 64-bit
 * Developer:	Adapteva
 * CELL_PROCESSORs:	Epiphany
 */

#if defined(__epiphany__)
/* Convex -------------------------------------------------- */
#undef EP_32BIT
#define EP_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Adapteva Epiphany"
#undef EPIPHANY
#define EPIPHANY
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Epiphany (32-Bit)"
#endif

/*
 * Motorola 68000
 * 32-bit
 * Developer:	Motorola
 * CELL_PROCESSORs:	Motorola 68000
 */

#if defined(__m68k__) || defined(M68000) || defined(__MC68K__)
/* Convex -------------------------------------------------- */
#undef MOTOROLA_32BIT
#define MOTOROLA_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Motorola 68000"
#undef MOTOROLA
#define MOTOROLA
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Motorola (32-Bit)"
#endif
/*
 * Notes:
 * "IA64" is the old name for the CELL_PROCESSOR CELL_ARCHITECTURE. Intel now prefers
 * "Itanium". There is no single Itanium CELL_PROCESSOR macro defined by all
 * CELL_COMPILERs on all OSes. An #if/#endif that checks multiple macros is required.
 * Microsoft's support for Itanium ended after Visual Studio 2010 and Windows
 * Server 2008. Clang/LLVM currently does not support Itanium CELL_PROCESSORs.
 */

/*
 * POWER
 * PowerPC
 * Developer:	IBM, Freescale
 * CELL_PROCESSORs:	PowerPC, POWER 1/2/3/4/5/6/7, G1, G2, G3, G4, G5, etc.
 */

/// Indicates that the target CELL_ARCHITECTURE is PowerPC®.
#if defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) ||  defined(__ppc__) || defined(_M_PPC) || defined(__PPC) || defined(__PPC__)
/* POWER ---------------------------------------------------- */
#undef POWER_PC_32BIT
#define POWER_PC_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Power PC"
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "PowerPC (32-Bit)"
#undef POWER_PC
#define POWER_PC
/// Indicates that the target CELL_ARCHITECTURE is PowerPC and that 64-bit
/// compilation mode is enabled.
#elif defined(__powerpc64__)
/* POWER 64-bit --------------------------------------------- */
#undef POWER_PC_64bit__
#define POWER_PC_64bit__
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Power PC"
#undef POWER_PC
#define POWER_PC
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "PowerPC (64-Bit)"
#endif

/*
 * Notes:
 * There is no single POWER CELL_PROCESSOR macro defined by all CELL_COMPILERs on all
 * OSes. An #if/#endif that checks multiple macros is required. GCC for AIX,
 * NetBSD, and OpenBSD defines the same macros for 32-bit and 64-bit POWER
 * CELL_PROCESSORs. For AIX, __64BIT__ is defined for 64-bit POWER. For OpenBSD,
 * _LP64 and __LP64__ are defined for 64-bit POWER. For NetBSD, GCC doesn't
 * provide a macro to check for 64-bit use. Apple's OSX support for POWER
 * CELL_PROCESSORs ended after OSX 10.5 Leopard in 2007. The open source Darwin
 * distribution, on which OSX is based, is still available for POWER CELL_PROCESSORs.
 */

/*
 * SPARC
 * Developer:	Oracle, Fujitsu, Sun
 * CELL_PROCESSORs:	UltraSPARC I/II/III/IV/T1/T2, SPARC T3/T4, etc.
 */

/*
 *  Notes:
 *  GCC defines CELL_PROCESSOR name macros depending upon the value of the -march
 * command-line option. These include__sparclite__, __sparclet__, __sparc_v8__,
 * __sparc_v9__, __supersparc__, __hypersparc__, and so forth. However, other
 * CELL_COMPILERs don't provide this level of detail and writing code that depends
 * upon these macros is probably a bad idea.
 */

#if defined(sparc) || defined(__sparc) || defined(__sparc__) ||                \
    defined(__sparc64__)
/* x86 32-bit ----------------------------------------------- */
#undef SPARC_32BIT
#define SPARC_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Sparc"
#undef SPARC
#define SPARC
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Sparc (32-Bit)"
#elif defined(__sparc64__)
/* x64 64-bit ----------------------------------------------- */
#undef SPARC_64bit__
#define SPARC_64bit__
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Sparc"
#undef SPARC
#define SPARC
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Sparc (64-Bit)"
#endif

/*
 * ARM
 * 32-bit
 * Developer:	ARM Holdings
 * CELL_PROCESSORs:	Acorn RISC Machine
 */

#if defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||    \
    defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) ||        \
    defined(_M_ARMT) || defined(__arm)
/* ARM-x86 -------------------------------------------------- */
#undef ARM_32BIT
#define ARM_32BIT
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Arm"
#undef ARM
#define ARM
#undef CELL_ARCHITECTURE
#define CELL_ARCHITECTURE "Arm (32-Bit)"
#endif

// Embedded CELL_ARCHITECTURE
#if defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||    \
    defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) ||        \
    defined(_M_ARMT) || defined(__arm)
#undef EMBEDDED
#define EMBEDDED
#undef CELL_PROCESSOR
#define CELL_PROCESSOR "Ebedded Unknown!"
#undef IS_EMBEDDED
#define IS_EMBEDDED 1
#endif

//! PLATFORM

/*
        Supported platforms:
     *      - Mac OSX, iPhone, Darwin
     *      - Orbis
     *      - OpenBSD
     *      - Generic BSD
     *      - Atari ST TOS
     *      - AmigaOS
     *      - Windows
     *      - Flashplayer (Crossbridge)
     *      - QNX
     *      - TI-Nspire
     *      - Emscripten
     *      - Linux
     *      - Solaris
     *      - Generic POSIX
     *      - Cygwin
     *      - Generic UNIX
     *      - Generic fallback
     *      - Playstation
     *      - Xbox
     *  Supported CELL_ARCHITECTUREs:
     *      - x86
     *      - x64
     *      - ARM 32-bit
     *      - ARM 64-bit
     *      - MIPS 32-bit
     *      - MIPS 64-bit
     *      - PowerPC 32-bit
     *      - PowerPC 64-bit
     *      - SPARC 32-bit
     *      - SPARC 64-bit
     *      - SuperH
     *      - Motorola 68k
     *      - Emscripten
     *      - Generic
     *
     *  Supported CELL_COMPILERs:
     *      - Clang
     *      - GCC
     *      - MSVC
     *      - Emscripten
     *      - TinyC
     *      - VBCC
     *      - Bruce's C CELL_COMPILER
     *      - Generic
     *
     */

/*
 * AIX
 * Developer:	IBM
 * Distributions:	AIX
 * CELL_PROCESSORs:	POWER
 */

#if defined(X86_32bit) && defined(_AIX) || defined(__TOS_AIX__) ||             \
    defined(__xlC__)
/* IBM AIX. ------------------------------------------------- */
#define CELL_PLATFORM_OS "AIX"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_AIX "AIX"
#define CELL_PLATFORM_TYPE "UNIX AIX"
#undef AIX
#define AIX
#elif defined(X64_64bit) && defined(_AIX) || defined(__TOS_AIX__) ||           \
    defined(__xlC__)
/* IBM AIX. ------------------------------------------------- */
#define CELL_PLATFORM_OS "AIX"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_AIX "AIX"
#undef AIX
#define AIX
#define CELL_PLATFORM_TYPE "UNIX AIX"
#endif

/*
 * HP-UX
 * Developer:	Hewlett-Packard
 * Distributions:	HP-UX
 * CELL_PROCESSORs:	Itanium
 */

#if defined(X86_32bit) && defined(hpux) || defined(__hpux) ||                  \
    defined(__hpux) || defined(__hpux)
/* Hewlett-Packard HP-UX. ----------------------------------- */
#define CELL_PLATFORM_OS "HP"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_HP "HP"
#define CELL_PLATFORM_TYPE "UNIX HP-UX"
#undef HPUX
#define HPUX
#elif defined(X64_64bit) && defined(X86_32bit) && defined(hpux) ||             \
    defined(__hpux) || defined(__hpux) || defined(__hpux)
/* Hewlett-Packard HP-UX. ----------------------------------- */
#define CELL_PLATFORM_OS "HP"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_HP "HP"
#define CELL_PLATFORM_TYPE "UNIX HP-UX"
#undef HPUX
#define HPUX
#endif

/*
 * Linux
 * Developer:	Open source
 * Distributions:	Centos, Debian, Fedora, OpenSUSE, RedHat, Ubuntu
 * CELL_PROCESSORs:	x86, x86-64, arm64, POWER, etc.
 */

#if defined(__linux__) && defined(linux) && !defined(ARM64_BIT) && !defined(X64_64bit)
/* Linux. --------------------------------------------------- */
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_LINUX "Linux"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_TYPE "Unix (Linux)"
#undef CELL_PLATFORM_IS_LINUX
#define CELL_PLATFORM_IS_LINUX
#elif defined(X64_64bit) && defined(__linux) && defined(__linux__) && defined(linux)
/* Linux. --------------------------------------------------- */
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_LINUX "Linux"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_TYPE "Unix (Linux)"
#undef CELL_PLATFORM_IS_LINUX
#define CELL_PLATFORM_IS_LINUX
/* Linux. --------------------------------------------------- */
#elif defined(ARM64_BIT) && defined(__linux) && defined(__linux__) && !defined(ANDROID)
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ARCH "arm64 (aarch64)"
#define CELL_PLATFORM_LINUX "Linux"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_TYPE "Unix (Linux)"
#undef CELL_PLATFORM_IS_LINUX
#define CELL_PLATFORM_IS_LINUX
#endif

/*
 * OSX, iOS, and Darwin
 * Developer:	Apple and open source
 * Distributions:	OSX, iOS, Darwin
 * CELL_PROCESSORs:	x86, x86-64, ARM
 */

#if defined(__APPLE__) && defined(__MACH__)
#define CELL_PLATFORM_DEVELOPER "Apple \u00AE"
// Detect for x86
/* Apple OSX and iOS (Darwin). ------------------------------ */
#include <TargetConditionals.h>
#if TARGET_OS_SIMULATOR == 1
/* iOS in Xcode simulator */
#define CELL_PLATFORM_OS "Apple iOS"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_IOS_SIMULATOR "iOS Simulator"
#define CELL_PLATFORM_TYPE "iOS-Emulator"
#undef CELL_PLATFORM_IS_IOS_EMULATOR
#define CELL_PLATFORM_IS_IOS_EMULATOR
#elif TARGET_OS_WATCH == 1
/* iOS on iWatch. */
#define CELL_PLATFORM_OS "Apple iOS"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_IWATCH "iOS (iWatch)"
#define CELL_PLATFORM_TYPE "iWatch"
#undef CELL_PLATFORM_IS_IWATCH
#define CELL_PLATFORM_IS_IWATCH
#elif TARGET_OS_TV == 1
/* Apple TV. */
#define CELL_PLATFORM_OS "Apple iOS"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_APPLE_TV "Apple (TV)"
#define CELL_PLATFORM_TYPE "Apple TV"
#undef CELL_PLATFORM_IS_IOS_APPLE_TV
#define CELL_PLATFORM_IS_IOS_APPLE_TV
#elif TARGET_OS_IPHONE == 1
/* iOS on iPhone, iPad, etc. */
#if defined(__arm__) && !defined(__arm64__)
#define CELL_PLATFORM_OS "Apple iOS"
#define CELL_PLATFORM_ARCH "arm (32-Bit)"
#define CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_IOS "iOS"
#define CELL_PLATFORM_DEVICE "Mobile"
#define CELL_PLATFORM_TYPE "iPhone, iPad"
#undef CELL_PLATFORM_IS_IOS
#define CELL_PLATFORM_IS_IOS
#elif !defined(__arm__) && defined(__arm64__)
#define CELL_PLATFORM_OS "Apple iOS"
#define CELL_PLATFORM_ARCH "arm64 (64-Bit)"
#define CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_IOS "iOS"
#define CELL_PLATFORM_DEVICE "Mobile"
#define CELL_PLATFORM_TYPE "iPhone, iPad"
#undef CELL_PLATFORM_IS_IOS
#define CELL_PLATFORM_IS_IOS
#endif
#elif TARGET_OS_MAC == 1
/* macOS */
#define CELL_PLATFORM_OS "macOS"
#define CELL_PLATFORM_ARCH CELL_ARCHITECTURE
#define CELL_PLATFORM_DESKTOP
#define CELL_PLATFORM_MAC "Unix(Darwin)-macOS (X11)"
#define CELL_PLATFORM_DEVICE "Unix(Darwin)-macOS (X11)"
#define CELL_PLATFORM_TYPE "Macintosh"
#undef CELL_PLATFORM_IS_MAC
#define CELL_PLATFORM_IS_MAC
#endif
#endif
#if defined(_APPLE) && defined(_LINUX) ||                                      \
    defined(__APPLE__) && defined(__LINUX__)
#error Conflicting operating system option selected, choose one.
#endif

/*
 * Solaris
 * Developer:	Oracle and open source
 * Distributions:	Oracle Solaris, Open Indiana
 * CELL_PROCESSORs:	x86, x86-64, SPARC
 */

#if defined(X86_32bit) && defined(__sun) && defined(__SVR4)
#define CELL_PLATFORM_DEVELOPER "Oracle Solaris \u00AE"
/* Solaris. ------------------------------------------------- */
#define CELL_PLATFORM_OS "Solaris"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_SOLARIS "Solaris"
#define CELL_PLATFORM_TYPE "SUN (Solaris)"
#elif defined(X64_64bit) && defined(__sun) && defined(__SVR4)
#define CELL_PLATFORM_DEVELOPER "Oracle Solaris \u00AE"
/* Solaris. ------------------------------------------------- */
#define CELL_PLATFORM_OS "Solaris"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_SOLARIS "Solaris"
#define CELL_PLATFORM_TYPE "SUN (Solaris)"
#endif

/*
 * Android
 * Developer:	Google
 * Distributions:	Android
 * CELL_PROCESSORs:	x86, x86-64, ARM
 */

#if !defined(__aarch64__) && defined(__ANDROID__) && defined(__ARM_ARCH) || defined(__ARM_ARCH_7A__)
#define CELL_PLATFORM_DEVELOPER "Google \u00AE"
/* Android. ------------------------------------------------- */
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ANDROID "Linux (Android)"
#undef CELL_PLATFORM_DEVICE
#define CELL_PLATFORM_DEVICE "Mobile"
#undef CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_MOBILE
#undef CELL_PLATFORM_ARCH
#define CELL_PLATFORM_ARCH "armv7a (32-Bit)"
#undef CELL_PLATFORM_TYPE
#define CELL_PLATFORM_TYPE "Android"
#undef CELL_PLATFORM_IS_ANDROID
#define CELL_PLATFORM_IS_ANDROID
#elif defined(__aarch64__) && defined(__ANDROID__)
/* Android. ------------------------------------------------- */
#define CELL_PLATFORM_DEVELOPER "Google \u00AE"
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ANDROID "Linux (Android)"
#undef CELL_PLATFORM_DEVICE
#define CELL_PLATFORM_DEVICE "Mobile"
#undef CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_MOBILE
#undef CELL_PLATFORM_ARCH
#define CELL_PLATFORM_ARCH "arm64-v8a (64-Bit)"
#undef CELL_PLATFORM_TYPE
#define CELL_PLATFORM_TYPE "Android"
#undef CELL_PLATFORM_IS_ANDROID
#define CELL_PLATFORM_IS_ANDROID
#elif defined(X86_64BIT) && !defined(__aarch64__) && !defined(__ARM_ARCH) && defined(__ANDROID__)
#define CELL_PLATFORM_DEVELOPER "Google \u00AE"
/* Android. ------------------------------------------------- */
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ANDROID "Linux (Android)"
#undef CELL_PLATFORM_DEVICE
#define CELL_PLATFORM_DEVICE "Mobile"
#undef CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_MOBILE
#undef CELL_PLATFORM_ARCH
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#undef CELL_PLATFORM_TYPE
#define CELL_PLATFORM_TYPE "Android"
#undef CELL_PLATFORM_IS_ANDROID
#define CELL_PLATFORM_IS_ANDROID
#elif defined(X64_64BIT) && !defined(__aarch64__) && !defined(__ARM_ARCH) && defined(__ANDROID__)
#define CELL_PLATFORM_DEVELOPER "Google \u00AE"
/* Android. ------------------------------------------------- */
#define CELL_PLATFORM_OS "Linux"
#define CELL_PLATFORM_ANDROID "Linux (Android)"
#undef CELL_PLATFORM_DEVICE
#define CELL_PLATFORM_DEVICE "Mobile"
#undef CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_MOBILE
#undef CELL_PLATFORM_ARCH
#define CELL_PLATFORM_ARCH "x86_64 (64-Bit)"
#undef CELL_PLATFORM_TYPE
#define CELL_PLATFORM_TYPE "Android"
#undef CELL_PLATFORM_IS_ANDROID
#define CELL_PLATFORM_IS_ANDROID
#endif

/*
 * Windows with Cygwin (POSIX)
 * Developer:	Open source
 * Distributions:	Cygwin
 * CELL_PROCESSORs:	x86
 */

#if defined(X86_32bit) && defined(__CYGWIN__) && !defined(_WIN32)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Cygwin POSIX under Microsoft Windows. -------------------- */
#define CELL_PLATFORM_OS "Microsoft Windows"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_POSIX_WINDOWS "POSIX under Microsoft Windows"
#define CELL_PLATFORM_TYPE "POSIX under Microsoft Windows"
#elif defined(X64_64bit) && defined(__CYGWIN__) && !defined(_WIN32)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Cygwin POSIX under Microsoft Windows. -------------------- */
#define CELL_PLATFORM_OS "Microsoft Windows"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_POSIX_WINDOWS "POSIX under Microsoft Windows"
#define CELL_PLATFORM_TYPE "POSIX under Microsoft Windows"
#undef CELL_PLATFORM_IS_WINDOWS
#define CELL_PLATFORM_IS_WINDOWS
#endif

/* FreeBSD */
#if defined(X86_32bit) && defined(__FreeBSD__) || defined(__FreeBSD)
#define CELL_PLATFORM_DEVELOPER "The FreeBSD Project \u00AE"
#define CELL_P_FREEBSD
#define CELL_PLATFORM_OS "FreeBSD"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_FREEBSD "Linux (FreeBSD)"
#define CELL_PLATFORM_TYPE "FreeBSD"
#elif defined(X64_64bit) && defined(__FreeBSD__) || defined(__FreeBSD)
#define CELL_PLATFORM_DEVELOPER "The FreeBSD Project \u00AE"
#define CELL_P_FREEBSD
#define CELL_PLATFORM_OS "FreeBSD"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_FREEBSD "Linux (FreeBSD)"
#undef CELL_PLATFORM_IS_FREEBSD
#define CELL_PLATFORM_IS_FREEBSD
#endif

/*
 * FreeBSD, ORBIS
 * Developer:	Sony
 * Distributions:	Orbis OS based on FreeBSD
 * CELL_PROCESSORs:	x86, x86-64
 */

/* Orbis (PS4) variant */
#if defined(X86_32bit) && defined(CELL_P_FREEBSD) && defined(__ORBIS__)
#define CELL_PLATFORM_DEVELOPER "Sony \u00AE"
#define CELL_PLATFORM_OS "Orbis"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_ORBIS "Linux (Orbis)"
#define CELL_PLATFORM_PLAYSTATION "Playstation"
#define CELL_PLATFORM_TYPE "Playstation"
#elif defined(X64_64bit) && defined(CELL_P_FREEBSD) && defined(__ORBIS__)
#define CELL_PLATFORM_DEVELOPER "Sony \u00AE"
#define CELL_PLATFORM_OS "Orbis"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_ORBIS "Linux (Orbis)"
#define CELL_PLATFORM_TYPE "Playstation"
#undef CELL_PLATFORM_IS_PLAYSTATION
#define CELL_PLATFORM_IS_PLAYSTATION
#endif

/* OpenBSD */
#if defined(X86_32bit) && defined(__OpenBSD__) || defined(__OpenBSD)
#define CELL_PLATFORM_DEVELOPER "Theo de Raadt \u00AE"
#define CELL_PLATFORM_OS "Unix-like (BSD)"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_OPENBSD "OpenBSD"
#define CELL_PLATFORM_TYPE "OpenBSD"
#elif defined(X64_64bit) && defined(__OpenBSD__) || defined(__OpenBSD)
#define CELL_PLATFORM_DEVELOPER "Theo de Raadt \u00AE"
#define CELL_PLATFORM_OS "Unix-like (BSD)"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_OPENBSD "OpenBSD"
#define CELL_PLATFORM_TYPE "OpenBSD"
#undef CELL_PLATFORM_IS_OPENBSD
#define CELL_PLATFORM_IS_OPENBSD
#endif

#if defined(_XBOX_ONE) && defined(_TITLE)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
#define CELL_PLATFORM_OS "Windows 10.x"
#define CELL_PLATFORM_ARCH "AMD64 (x86-64)"
#define CELL_PLATFORM_XBOX "Windows 10 (Xbox)"
#define CELL_PLATFORM_TYPE "Xbox"
#undef CELL_PLATFORM_IS_XBOX
#define CELL_PLATFORM_IS_XBOX
#endif

/* NetBSD */
#if defined(X86_32bit) && defined(__NetBSD__) || defined(__NetBSD)
#define CELL_PLATFORM_DEVELOPER "The NetBSD Foundation \u00AE"
#define CELL_PLATFORM_OS "Unix (NetBSD)"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_BLACKBERRY "NetBSD"
#define CELL_PLATFORM_TYPE "NetBSD"
#elif defined(X64_64bit) && defined(__NetBSD__) || defined(__NetBSD)
#define CELL_PLATFORM_DEVELOPER "The NetBSD Foundation \u00AE"
#define CELL_PLATFORM_OS "Unix (NetBSD)"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_BLACKBERRY "NetBSD"
#define CELL_PLATFORM_TYPE "NetBSD"
#undef CELL_PLATFORM_IS_NETBSD
#define CELL_PLATFORM_IS_NETBSD
#endif

/* QNX (Blackberry) variant */
#if defined(X86_32bit) && defined(__QNXNTO__) || defined(__QNX__)
#define CELL_PLATFORM_DEVELOPER "QNX Software System \u00AE"
#define CELL_PLATFORM_OS "Unix (RTOS)"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_BLACKBERRY "QNX"
#define CELL_PLATFORM_TYPE "Blackberry"
#elif defined(X64_64bit) && defined(__QNXNTO__) || defined(__QNX__)
#define CELL_PLATFORM_DEVELOPER "QNX Software System \u00AE"
#define CELL_PLATFORM_OS "Unix (RTOS)"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_BLACKBERRY "QNX"
#define CELL_PLATFORM_TYPE "Blackberry"
#undef CELL_PLATFORM_IS_BLACKBERRY
#define CELL_PLATFORM_IS_BLACKBERRY
#endif

/* VMS */
#if defined(X86_32bit) && defined(VMS) || defined(__VMS)
#define CELL_PLATFORM_DEVELOPER "OpenVMS \u00AE"
#define CELL_PLATFORM_OS "OpenVMS"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_VMS "DEC (OpenVMS)"
#define CELL_PLATFORM_TYPE "DEC"
#elif defined(X64_64bit) && defined(VMS) || defined(__VMS)
#define CELL_PLATFORM_DEVELOPER "OpenVMS \u00AE"
#define CELL_PLATFORM_OS "OpenVMS"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_VMS "DEC (OpenVMS)"
#define CELL_PLATFORM_TYPE "DEC"
#undef CELL_PLATFORM_IS_OPENVMS
#define CELL_PLATFORM_IS_OPENVMS
#endif

/* VXWORKS variant */
#if defined(X86_32bit) && defined(VXWORKS)
#define CELL_PLATFORM_DEVELOPER "Wind River Systems, Siemens EDA \u00AE"
#define CELL_PLATFORM_OS "RTOS"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_VXWORKS "Monolithic"
#define CELL_PLATFORM_TYPE "VXWORKS"
#elif defined(X64_64bit) && defined(VXWORKS)
#define CELL_PLATFORM_DEVELOPER "Wind River Systems, Siemens EDA \u00AE"
#define CELL_PLATFORM_OS "RTOS"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_VXWORKS "Monolithic"
#define CELL_PLATFORM_TYPE "VXWORKS"
#undef CELL_PLATFORM_IS_VXWORKS
#define CELL_PLATFORM_IS_VXWORKS
#endif

/* Motorola 68K.  Not defined by VBCC, so user must define one of these
 * manually when using VBCC.
 */
#if defined(X86_32bit) && defined(__m68k__) || defined(M68000) || defined(__MC68K__)
#define CELL_PLATFORM_OS "68K"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_MOTOROLA "Motorola (68K)"
#define CELL_PLATFORM_TYPE "Motorola 68K"
#elif defined(X64_64bit) && defined(__m68k__) || defined(M68000) || defined(__MC68K__)
#define CELL_PLATFORM_OS "68K"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_MOTOROLA "Motorola (68K)"
#define CELL_PLATFORM_TYPE "Motorola 68K"
#endif

/* Ultrix */
#if defined(X86_32bit) && defined(ultrix) || defined(__ultrix) ||  defined(__ultrix__)
#define CELL_PLATFORM_OS "Ultrix Os"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_ULTRIX "Ultrix"
#define CELL_PLATFORM_TYPE "Ultrix"
#elif defined(X86_32bit) && defined(unix) && defined(vax)
#define CELL_PLATFORM_OS "Ultrix Os"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_ULTRIX "Ultrix"
#define CELL_PLATFORM_TYPE "Ultrix"
#elif defined(X64_64bit) && defined(ultrix) || defined(__ultrix) || defined(__ultrix__)
#define CELL_PLATFORM_OS "Ultrix Os"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_ULTRIX "Ultrix"
#define CELL_PLATFORM_TYPE "Ultrix"
#elif defined(X64_64bit) && defined(unix) && defined(vax)
#define CELL_PLATFORM_OS "Ultrix Os"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_ULTRIX "Ultrix"
#define CELL_PLATFORM_TYPE "Ultrix"
#undef CELL_PLATFORM_IS_ULTRIX
#define CELL_PLATFORM_IS_ULTRIX
#endif

/* Embedded */
#if defined(IS_EMBEDDED)
#define CELL_PLATFORM_EMBEDDED "Embedded"
#define CELL_PLATFORM_RPI "Embedded"
#endif

/* Microsoft DOS */
#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
#define CELL_PLATFORM_OS "Dos"
#define CELL_PLATFORM_DOS "Microsoft-DOS"
#define CELL_PLATFORM_ARCH "16-Bit"
#define CELL_PLATFORM_TYPE "MS-Dos"
#undef CELL_PLATFORM_IS_MSDOS
#define CELL_PLATFORM_IS_MSDOS
#endif

/*
 * Windows, Cygwin (non-POSIX), and MinGW
 * Developer:	Microsoft
 * Distributions:	Windows XP, Vista, 7, 8
 * CELL_PROCESSORs:	x86, x86-64
 */


#if defined(_WIN32) && !defined(_WIN64) && !defined (WINAPI_FAMILY_PHONE_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Microsoft Windows (32-bit). ------------------------------ */
#define CELL_PLATFORM_OS "Windows"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_WINDOWS_X86 "Microsoft Windows (32-Bit)"
#define CELL_PLATFORM_WINDOWS "Microsoft Windows (32-Bit)"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_DESKTOP
#define CELL_PLATFORM_TYPE "PC"
#undef CELL_PLATFORM_IS_PC
#define CELL_PLATFORM_IS_PC
#elif defined(_WIN64) && defined(_WIN32) && !defined(_M_ARM64) && !defined (WINAPI_FAMILY_PHONE_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Microsoft Windows (64-bit). ------------------------------ */
#define CELL_PLATFORM_OS "Windows"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_WINDOWS_X64 "Microsoft Windows (64-Bit)"
#define CELL_PLATFORM_WINDOWS "Microsoft Windows (64-Bit)"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_DESKTOP
#define CELL_PLATFORM_TYPE "PC"
#undef CELL_PLATFORM_IS_PC
#define CELL_PLATFORM_IS_PC
#elif defined(_M_ARM64) && defined(_WIN32) && !defined (WINAPI_FAMILY_PHONE_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Microsoft Windows (64-bit). ------------------------------ */
#define CELL_PLATFORM_OS "Windows"
#define CELL_PLATFORM_ARCH "Arm64 (64-Bit)"
#define CELL_PLATFORM_WINDOWS_ARM64 "Microsoft Windows (64-Bit)"
#define CELL_PLATFORM_WINDOWS "Microsoft Windows (64-Bit)"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_DESKTOP
#define CELL_PLATFORM_TYPE "PC"
#undef CELL_PLATFORM_IS_PC
#define CELL_PLATFORM_IS_PC
/* Microsoft Phone ------------------------------ */
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Microsoft Windows Store or Universal Windows Platform - (32-bit).
 * ------------------------------ */
#define CELL_PLATFORM_OS "Windows"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_WINDOWS_X86 "Microsoft Windows (32-Bit)"
#define CELL_PLATFORM_WINDOWS_UWP "Microsoft Windows UWP (32-Bit)"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_DESKTOP
#define CELL_PLATFORM_TYPE "PC"
#undef CELL_PLATFORM_IS_PC
#define CELL_PLATFORM_IS_PC
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP) &&        \
    defined(_WIN64) && !defined(_WIN32) && !defined(_WIN32_WINNT)
/* Microsoft Windows (64-bit). ------------------------------ */
#define CELL_PLATFORM_OS "Windows "
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_WINDOWS_X64 "Microsoft Windows x64"
#define CELL_PLATFORM_WINDOWS_UWP "Microsoft Windows UWP"
#define CELL_PLATFORM_DEVICE "Desktop"
#define CELL_PLATFORM_DESKTOP
#define CELL_PLATFORM_WINDOWS "Microsoft Windows"
#define CELL_PLATFORM_TYPE "PC"
#undef CELL_PLATFORM_IS_PC
#define CELL_PLATFORM_IS_PC
/* Microsoft Phone ------------------------------ */
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Microsoft Windows (Phone). ------------------------------ */
#define CELL_PLATFORM_OS "WindowsRT"
#define CELL_PLATFORM_ARCH "x86 (32-Bit)"
#define CELL_PLATFORM_WINDOWS_PHONE "Windows Phone"
#define CELL_PLATFORM_DEVICE "Mobile"
#define CELL_PLATFORM_MOBILE
#define CELL_PLATFORM_TYPE "Mobile (Windows Phone)"
#elif defined(_WIN64) && defined(WINAPI_FAMILY_PHONE_APP)
#define CELL_PLATFORM_DEVELOPER "Microsoft \u00AE"
/* Microsoft Windows (Phone). ------------------------------ */
#define CELL_PLATFORM_OS "WindowsRT"
#define CELL_PLATFORM_ARCH "x64 (64-Bit)"
#define CELL_PLATFORM_DEVICE "Mobile"
#define CELL_PLATFORM_WINDOWS_PHONE "Windows Phone"
#define CELL_PLATFORM_TYPE "Mobile (Windows Phone)"
#undef CELL_PLATFORM_IS_WINDOWS_PHONE
#define CELL_PLATFORM_IS_WINDOWS_PHPNE
#endif

//! Language Standard Macro
#ifdef _MSC_VER
    #if _MSC_VER < 1920
        #if __cplusplus == 199711L
        #define CXX_STANDARD_98 199711L
        #elif __cplusplus == 201103L || __cplusplus == 201100
        #define CXX_STANDARD_11 201100
        #elif __cplusplus == 201402L
        #define CXX_STANDARD_14
        #elif __cplusplus == 201703L || __cplusplus == 201704L
        #define CXX_STANDARD_17 201703L
        #elif __cplusplus == 202002L
        #define CXX_STANDARD_20 202002L
        #endif
    #else
        #define CXX_STANDARD_20 202002L
    #endif
#else
    #if __cplusplus == 199711L
    #define CXX_STANDARD_98 199711L
    #elif __cplusplus == 201103L || __cplusplus == 201100
    #define CXX_STANDARD_11 201100
    #elif __cplusplus == 201402L
    #define CXX_STANDARD_14 201402L
    #elif __cplusplus == 201703L || __cplusplus == 201704L
    #define CXX_STANDARD_17 201703L
    #elif __cplusplus == 202002L
    #define CXX_STANDARD_20 202002L
    #endif
#endif

} // namespace Preprocessor

#endif // PREPROCESSORS_HPP
