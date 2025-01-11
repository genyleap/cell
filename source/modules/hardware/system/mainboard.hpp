/*!
 * @file        mainboard.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System Main Board (Motehrboard) information.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MAINBOARD_HPP
#define CELL_MAINBOARD_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

/**
 * @class MainboardInfo
 * @brief The MainboardInfo class represents information about the mainboard (motherboard) of a computer system.
 * t provides details about the chipset, LPCIO (Low Pin Count I/O) controller, graphic interface, and general board information.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export MainboardInfo
{
public:
    /**
     * @brief Constructs a MainboardInfo object.
     */
    MainboardInfo();

    /**
     * @brief Destroys the MainboardInfo object.
     */
    ~MainboardInfo();

    /**
     * @struct Chipset
     * @brief Represents the chipset information of the mainboard.
     */
    struct Chipset final
    {
        Types::OptionalString brand {}; //!< Optional brand name of the chipset.
        Types::OptionalString model {}; //!< Optional model name of the chipset.
        Types::OptionalString rev   {}; //!< Optional revision information of the chipset.
    };

    /**
     * @struct Lpcio
     * @brief Represents the LPCIO (Low Pin Count I/O) controller information of the mainboard.
     */
    struct Lpcio final
    {
        Types::OptionalString brand {}; //!< Optional brand name of the LPCIO controller.
        Types::OptionalString model {}; //!< Optional model name of the LPCIO controller.
        Types::OptionalString rev   {}; //!< Optional revision information of the LPCIO controller.
    };

    /**
     * @struct GraphicInterface
     * @brief Represents the graphic interface information of the mainboard.
     */
    struct GraphicInterface final
    {
        Types::OptionalString version       {}; //!< Optional version of the graphic interface.
        Types::OptionalString linkWidth     {}; //!< Optional link width of the graphic interface.
        Types::OptionalString maxSupported  {}; //!< Optional maximum supported specifications of the graphic interface.
    };

    /**
     * @struct BoardInfo
     * @brief Represents the general board information of the mainboard.
     */
    struct BoardInfo final
    {
        Types::OptionalString       brand           {}; //!< Optional brand name of the mainboard.
        Types::OptionalString       model           {}; //!< Optional model name of the mainboard.
        Types::OptionalString       codeName        {}; //!< Optional code name of the mainboard.
        Types::OptionalString       chipset         {}; //!< Optional chipset information of the mainboard.
        Types::OptionalString       busSpecs        {}; //!< Optional bus specifications of the mainboard.
        Types::OptionalString       releasedDate    {}; //!< Optional release date of the mainboard.

        Types::Optional<Chipset>    southbridge     {}; //!< Optional information about the southbridge chipset.
        Types::Optional<Chipset>    northbridge     {}; //!< Optional information about the northbridge chipset.
        Types::Optional<Lpcio>      lpcio           {}; //!< Optional information about the LPCIO controller.

        Types::Optional<GraphicInterface>       gpuInterface    {}; //!< Optional information about the graphic interface.
    };

    /**
     * @brief Retrieves the board information of the mainboard.
     * @return The BoardInfo struct containing the details of the mainboard.
     */
    __cell_no_discard BoardInfo get() __cell_const_noexcept;

};

CELL_NAMESPACE_END

#endif // CELL_MAINBOARD_HPP
