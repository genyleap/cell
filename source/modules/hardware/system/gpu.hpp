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
     * @brief The MemoryType enum class represents different types of graphics double data rate (GDDR) memory.
     * @details The `MemoryType` enum class you provided represents different types of graphics double data rate (GDDR) memory.
     *
     * GDDR memory is a specialized type of memory specifically designed for graphics processing units (GPUs). Here's a brief overview of the different GDDR memory types:
     * 1. GDDR: GDDR, or GDDR1, was the first generation of graphics double data rate memory. It provided improved performance compared to standard DDR memory and was primarily used in early graphics cards.
     * 2. GDDR2: GDDR2 improved upon GDDR1 by offering higher data transfer rates, increased memory bandwidth, and reduced power consumption. It was utilized in mid-range graphics cards.
     * 3. GDDR3: GDDR3 further enhanced performance by increasing the data transfer rates and memory density compared to GDDR2. It introduced higher clock speeds, improved power management features, and was widely adopted in high-end graphics cards.
     * 4. GDDR4: GDDR4 introduced even higher data transfer rates and increased memory capacities compared to GDDR3. However, it did not gain widespread adoption and was quickly surpassed by newer memory technologies.
     * 5. GDDR5: GDDR5 marked a significant leap in performance and capabilities. It offered higher data transfer rates, increased memory densities, and improved power efficiency compared to GDDR4. GDDR5 became the standard memory type for high-performance graphics cards.
     * 6. GDDR5X: GDDR5X is an enhanced version of GDDR5 that further increased the memory bandwidth and data transfer rates. It was designed as a bridge technology between GDDR5 and the next-generation GDDR6 memory.
     * 7. GDDR6: GDDR6 introduced a substantial increase in memory bandwidth and data transfer rates compared to GDDR5. It offered improved performance, power efficiency, and memory capacities, making it suitable for high-end graphics cards.
     * 8. GDDR6X: GDDR6X is an advanced version of GDDR6 that further pushed the memory bandwidth limits. It introduced innovative signaling techniques to achieve even higher data transfer rates, primarily used in top-of-the-line graphics cards.
     *
     * Each GDDR memory type represents advancements in memory technology to meet the increasing demands of graphics-intensive applications and gaming.
     * It's important to note that the specific features, timings, and performance characteristics of GDDR memory modules may vary depending on the manufacturer and the specific product.
     */
    enum class MemoryType
    {
        GDDR,    //!< GDDR memory type.
        GDDR2,   //!< GDDR2 memory type.
        GDDR3,   //!< GDDR3 memory type.
        GDDR4,   //!< GDDR4 memory type.
        GDDR5,   //!< GDDR5 memory type.
        GDDR5X,  //!< GDDR5X memory type.
        GDDR6,   //!< GDDR6 memory type.
        GDDR6X   //!< GDDR6X memory type.
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
    Types::OptionalString           name             {}; //!< GPU type or name.
    Types::Optional<MemoryType>     type             {}; //!< GPU memory type technology.
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
