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
CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

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
     * @brief The GraphicCard class
     */
    struct GraphicCard final
    {
        Types::OptionalString           name         {};
        Types::OptionalString           brand        {};
        Types::Optional<Types::u8>      dieSize      {};
        Types::Optional<Types::u8>      revision     {};
        Types::Optional<Types::u8>      transistors  {};
        Types::OptionalString           releaseDate  {};
        Types::OptionalBool             crossSupport {};
    };

    /**
     * @brief The Graphic3dApi class
     */
    struct Graphic3dApi final
    {
        Types::OptionalString   title           {};     //!< Title of api.
        Types::OptionalString   version         {};     //!< Version of api.

        /**
         * @brief The MultipleGraphicCard enum
         */
        enum class MultipleGraphicCard : Types::u8
        {
            None, SLI, Crossfire
        };

        MultipleGraphicCard multiGpuSupport;     //!< Cross Card Support.
    };

    /**
     * @brief Struct representing 3D API support.
     */
    struct Api3dSupport
    {
        Graphic3dApi direct3d {}; //!< DirectX version.
        Graphic3dApi opengl   {}; //!< OpenGL version.
        Graphic3dApi metal    {}; //!< Metal version.
        Graphic3dApi vulkan   {}; //!< Vulkan version.
    };

    /**
     * @brief The MemoryInfo class
     */
    struct MemoryInfo final
    {
        Types::OptionalString   type            {}; //!< Memory type such as DDR,GDDR and versions.
        Types::OptionalString   busWidth        {}; //!< Memory bus width.
        Types::OptionalString   bandWidth       {}; //!< Memory band width.
        Types::llong            totalMemorySize {}; //!< Total physical memory size.
        Types::llong            usedMemorySize  {}; //!< Total physical used memory Size.
        Types::llong            freeMemorySize  {}; //!< Total physical free memory Size.
    };

    /**
     * @brief The ClockInfo class
     */
    struct ClockInfo final
    {
        Types::llong   base     {}; //!< GPU base clock speed.
        Types::llong   memory   {}; //!< GPU memory base clock speed.
        Types::llong   boost    {}; //!< GPU boost clock speed.
    };

    /**
     * @brief The Computing
     */
    struct Computing
    {
        enum t { OpenCL, Cuda, PhysX, DirectCompute, DirectMl };
        Types::OptionalBool openCl          {false};
        Types::OptionalBool cuda            {false};
        Types::OptionalBool physx           {false};
        Types::OptionalBool directCompute   {false};
        Types::OptionalBool directMl        {false};
    };

    /**
     * @brief The Technologies
     */
    struct Technologies
    {
        enum t { Vulkan, RayTracing, OpenGL };
        Types::OptionalBool vulkan          {false};
        Types::OptionalBool rayTracing      {false};
        Types::OptionalBool openGl          {false};
        Types::OptionalBool directCompute   {false};
    };

    Types::OptionalString           chipsetModel     {}; //!< GPU chipset model.
    Types::OptionalString           type             {}; //!< GPU type or name.
    Types::OptionalString           releaseDate      {}; //!< Graphic Card release date.
    Types::OptionalString           bus              {}; //!< Bus type.
    Types::OptionalString           vendor           {}; //!< GPU vendor.
    Types::OptionalString           biosVersion      {}; //!< GPU bios version.
    Types::OptionalString           driverVersion    {}; //!< GPU driver version.
    Types::OptionalString           digitalSignature {}; //!< Driver digital signature.
    Types::Optional<ClockInfo>      clockInfo        {}; //!< Clock speed info.
    Types::Optional<MemoryInfo>     memorySize       {}; //!< Video memory size.
    Types::Optional<Api3dSupport>   api3dSupport     {}; //!< 3D API support information.
    Types::OptionalNumeric          totalCores       {}; //!< Total number of GPU cores.
    Types::Optional<Computing>      computing        {}; //!< Computing technology.
    Types::Optional<Technologies>   technologies     {}; //!< Graphic technologies support.
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
