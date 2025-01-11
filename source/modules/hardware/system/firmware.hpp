/*!
 * @file        firmware.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System firmware (bios/uefi) information.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_FIRMWARE_HPP
#define CELL_FIRMWARE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

/**
 * @class FirmwareInfo
 * @brief The FirmwareInfo class represents firmware information for a computer system.
 * It provides access to the firmware details such as brand, version, serial number, and date.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export FirmwareInfo final
{
public:
    /**
     * @brief Constructs a FirmwareInfo object.
     */
    FirmwareInfo();

    /**
     * @brief Destroys the FirmwareInfo object.
     */
    ~FirmwareInfo();

    /**
     * @enum FirmwareType
     * @brief Enumerates the types of firmware.
     */
    enum class FirmwareType
    {
        BIOS, UEFI
    };

    /**
     * @struct FirmwareStructure
     * @brief Represents the structure containing firmware details.
     */
    struct FirmwareStructure final
    {
        Types::OptionalString brand         {}; //!< Optional brand name of the firmware.
        Types::OptionalString version       {}; //!< Optional version number of the firmware.
        Types::OptionalString serialNumber  {}; //!< Optional serial number of the firmware.
        Types::OptionalString date          {}; //!< Optional date of the firmware.
    };
};


CELL_NAMESPACE_END

#endif // CELL_FIRMWARE_HPP
