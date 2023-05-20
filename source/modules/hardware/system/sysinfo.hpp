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

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("mainboard.hpp")
#   include "mainboard.hpp"
#else
#   error "Cell's "mainboard.hpp" was not found!"
#endif

#if __has_include("firmware.hpp")
#   include "firmware.hpp"
#else
#   error "Cell's "firmware.hpp" was not found!"
#endif

#if __has_include("cpu.hpp")
#   include "cpu.hpp"
#else
#   error "Cell's "cpu.hpp" was not found!"
#endif

#if __has_include("memory.hpp")
#   include "memory.hpp"
#else
#   error "Cell's "memory.hpp" was not found!"
#endif

#if __has_include("gpu.hpp")
#   include "gpu.hpp"
#else
#   error "Cell's "gpu.hpp" was not found!"
#endif

#if __has_include("os.hpp")
#   include "os.hpp"
#else
#   error "Cell's "os.hpp" was not found!"
#endif

#if __has_include("product.hpp")
#   include "product.hpp"
#else
#   error "Cell's "product.hpp" was not found!"
#endif


CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

/**
 * @brief The InformationData class
 */
struct InformationData final
{
    /* Hardware Data */
    FirmwareInfo    firmware        {};
    MainboardInfo   mainBoard       {};
    CpuInfo         processor       {};
    GpuInfo         videoGraphic    {};
    MemoryInfo      mainMemory      {};

    /* Software Data */
    ProductInfo     productInfo     {};
    OsInfo          osInfo          {};

    /* Extra Data */
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
     * @brief The MainboardInfo() method returns a MainboardInfo object that contains information about the Motherboard.
     * @return as MainboardInfo object.
     */
    MainboardInfo getMainboardInfo();

    /**
     * @brief The FirmwareInfo() method returns a FirmwareInfo object that contains information about the Firmware [BIOS/UEFI].
     * @return as FirmwareInfo object.
     */
    FirmwareInfo getFirmwareInfo();

    /**
     * @brief The getCpuInfo() method returns a CpuInfo object that contains information about the CPU, such as the name and number of cores.
     * @return as CpuInfo object.
     */
    CpuInfo getCpuInfo();

    /**
     * @brief The getMemoryInfo() method returns a MemoryInfo object that contains information about the memory, such as the total, used, and free memory.
     * @return as MemoryInfo object.
     */
    MemoryInfo  getMemoryInfo();

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
