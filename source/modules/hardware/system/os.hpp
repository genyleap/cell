/*!
 * @file        os.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Operation system information.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_OS_HPP
#define CELL_OS_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

class __cell_export OsInfo
{
public:
    /**
     * @brief The ProductData class
     */
    struct ProductData final
    {
        Types::OptionalString   name         {};
        Types::OptionalString   codename     {};
        Types::OptionalString   version      {};
        Types::OptionalString   build        {};
        Types::OptionalString   releaseDate  {};
        Types::OptionalString   kernel       {};
        Types::OptionalString   kernelVer    {};
        Types::OptionalString   hostname     {};
        Types::OptionalString   username     {};
        Types::OptionalString   developer    {};
        Types::OptionalString   architecture {};
    };
    /**
     * @brief Constructs a OsInfo object.
     */
    OsInfo();

    /**
     * @brief Destroys the OsInfo object.
     */
    ~OsInfo();

    /**
     * @brief getName function will returns the name of the operating system.
     * @return as an optional string.
     */
    Types::OptionalString getName();

    /**
     * @brief getVersion function will returns the version of the operating system.
     * @return as an optional string.
     */
    Types::OptionalString getVersion();

    /**
     * @brief getBuildNumber function will returns the build number of the operating system.
     * @return as an optional string.
     */
    Types::OptionalString getBuildNumber();

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
     * @brief getDeveloper function will returns the developer of the os.
     * @return as an optional string.
     */
    Types::OptionalString getDeveloper();

    /**
     * @brief getReleaseDate function will returns the released date of the product.
     * @return as an optional string.
     */
    Types::OptionalString getReleaseDate();

    /**
     * @brief getArchitecture function will returns the architecture of the os.
     * @return as an optional string.
     */
    Types::OptionalString getArchitecture();

private:
    ProductData m_productData {};

};

CELL_NAMESPACE_END

#endif // CELL_OS_HPP
