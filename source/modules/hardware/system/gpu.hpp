/*!
 * @file        gpu.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System graphic chip information.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_GPU_HPP
#define CELL_GPU_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif
CELL_NAMESPACE_BEGIN(Cell::Modules::Hardware)

/**
 * @brief Struct representing display information.
 */
struct DisplayInfo final
{
    /**
     * @brief Struct representing screen size.
     */
    struct ScreenSize
    {
        Types::u32 width    {}; //!< Screen width in pixels.
        Types::u32 height   {}; //!< Screen height in pixels.
    };

    Types::OptionalString       displayType     {}; //!< Display type or name.
    Types::Optional<ScreenSize> screenSize      {}; //!< Screen size.
    Types::OptionalString       resolution      {}; //!< Screen resolution.
    Types::OptionalString       aspectRatio     {}; //!< Screen aspect ratio.
    Types::OptionalString       refreshRate     {}; //!< Screen refresh rate.
    Types::OptionalBool         isMainDisplay   {}; //!< Flag indicating if it is the main display.
};

/**
 * @brief Struct representing GPU information.
 */
struct GpuInfo final
{
    /**
     * @brief Struct representing 3D API support.
     */
    struct Api3dSupport
    {
        Types::u32 direct3d {}; //!< DirectX version.
        Types::u32 opengl   {}; //!< OpenGL version.
        Types::u32 metal    {}; //!< Metal version.
        Types::u32 vulkan   {}; //!< Vulkan version.
    };

    Types::OptionalString           chipsetModel     {}; //!< GPU chipset model.
    Types::OptionalString           type             {}; //!< GPU type or name.
    Types::OptionalString           bus              {}; //!< Bus type.
    Types::OptionalString           vendor           {}; //!< GPU vendor.
    Types::Optional<Api3dSupport>   api3dSupport     {}; //!< 3D API support information.
    Types::OptionalNumeric          totalCores       {}; //!< Total number of GPU cores.
};



/**
 * @brief The InformationData class
 */
struct GraghicData final
{
    GpuInfo                         processorInfo    {};
    Types::Optional<DisplayInfo>    displays         {};
};

class __cell_export GraphicInformation
{
public:
    GraphicInformation();
    ~GraphicInformation();

    std::vector<GpuInfo> get();

private:
    GraghicData graghicData {};
};

CELL_NAMESPACE_END

#endif // CELL_GPU_HPP
