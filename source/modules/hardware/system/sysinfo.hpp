/*!
 * @file        sysinfo.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System information manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SYSINFO_HPP
#define CELL_SYSINFO_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif
CELL_NAMESPACE_BEGIN(Cell::Modules::Hardware)

/**
 * @brief The MemoryInfo class
 */
struct MemoryInfo final
{
    Types::llong totalMemory    {}; ///<! Total physical memory size.
    Types::llong usedMemory     {}; ///<! Total physical used memory Size.
    Types::llong freeMemory     {}; ///<! Total physical free memory Size.
};

/**
 * @brief The CpuInfo class
 */
struct CpuInfo final
{
    std::string brandString     {}; ///<! Processor brand as string [Intel, AMD, Apple and etc].
    Types::uint count           {}; ///<! Total physical processor core.
};

struct ProductInfo final
{
    Types::OptionalString productName;
    Types::OptionalString productVersion;
    Types::OptionalString productBuildVersion;
};

/**
 * @brief The InformationData class
 */
struct InformationData final
{
    std::string osName;
    std::string hostName;
    std::string userName;
    std::string kernelName;
    std::string kernelVersion;
    Types::uint numProcessors;

    CpuInfo     processorInfo;
    MemoryInfo  memoryInfo;
    ProductInfo productInfo;
};

class __cell_export SystemInformation
{
public:
    SystemInformation();
    ~SystemInformation();

    /**
     * @brief getOsName function will returns the name of the operating system.
     * @return as an optional string.
     */
    Types::OptionalString getOsName();

    /**
     * @brief getHostName function will returns the hostname of the system.
     * @return as an optional string.
     */
    Types::OptionalString getHostName();

    /**
     * @brief getKernelName function will returns the name of the kernel.
     * @return as an optional string.
     */
    Types::OptionalString getKernelName();

    /**
     * @brief getKernelVersion function will returns the version of the kernel.
     * @return as an optional string.
     */
    Types::OptionalString getKernelVersion();

    /**
     * @brief getUserName function will returns the name of the user.
     * @return as an optional string.
     */
    Types::OptionalString getUserName();

    /**
     * @brief The getCpuInfo() method returns a CpuInfo object that contains information about the CPU, such as the name and number of cores.
     * @return as CpuInfo object.
     */
    CpuInfo               getCpuInfo();

    /**
     * @brief The getMemoryInfo() method returns a MemoryInfo object that contains information about the memory, such as the total, used, and free memory.
     * @return as MemoryInfo object.
     */
    MemoryInfo            getMemoryInfo();

    /**
     * @brief getProductInfo function will gets product data such as name, version and build number.
     * @return as ProductInfo object.
     */
    ProductInfo getProductInfo();

private:
    InformationData informationData {};
};

CELL_NAMESPACE_END

#endif // CELL_SYSINFO_HPP
