/*!
 * @file        memory.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System main memory (Ram) information.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MEMORY_HPP
#define CELL_MEMORY_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

class __cell_export MemoryInfo
{
public:
    /**
     * @brief Constructs a MemoryInfo object.
     */
    MemoryInfo();

    /**
     * @brief Destroys the MemoryInfo object.
     */
    ~MemoryInfo();

    /**
     * @brief The MemoryType enum class represents different types of memory.
     * @details DDR stands for Double Data Rate, and it refers to a type of synchronous dynamic random-access memory (SDRAM) that is commonly used in computer systems. DDR memory types have evolved over time, with each iteration offering improved performance and capabilities. Here's a brief overview of different DDR memory types:
     * 1. DDR: DDR, or DDR1, was the first generation of DDR memory. It provided a significant improvement over the previous SDRAM technology by allowing data to be transferred on both the rising and falling edges of the clock cycle.
     * 2. DDR2: DDR2 improved upon DDR by providing higher data transfer rates and increased memory bandwidth. It also introduced lower operating voltages, which resulted in improved power efficiency.
     * 3. DDR3: DDR3 further enhanced performance by increasing the data transfer rates and memory density compared to DDR2. It introduced higher clock speeds, improved power management features, and reduced power consumption.
     * 4. DDR4: DDR4 is the next iteration of DDR memory and offers even higher data transfer rates, increased memory density, and improved power efficiency compared to DDR3. It also introduced features like higher module capacities, improved error correction, and lower operating voltages.
     * 5. DDR5: DDR5 is the latest generation of DDR memory, offering even higher data transfer rates and increased memory capacities compared to DDR4. It introduces new features such as higher channel densities, improved power management, and on-die ECC (Error Correction Code) for enhanced reliability.
     *
     * Each DDR memory type is backward compatible, meaning that newer DDR memory modules can generally be used in systems designed for older DDR versions, although they will operate at the maximum speed supported by the system.
     * It's important to note that the specific features, timings, and performance characteristics of DDR memory modules may vary depending on the manufacturer and the specific product.
     */
    enum class MemoryType
    {
        DDR,    //!< DDR memory type.
        DDR2,   //!< DDR2 memory type.
        DDR3,   //!< DDR3 memory type.
        DDR4,   //!< DDR4 memory type.
        DDR5    //!< DDR5 memory type.
    };

    /**
     * @brief The MemoryInfo class
     */
    struct MemoryStruct final
    {
        Types::llong totalMemory    {}; //!< Total physical memory size.
        Types::llong usedMemory     {}; //!< Total physical used memory size.
        Types::llong freeMemory     {}; //!< Total physical free memory size.
    };

    struct TimingStruct final
    {
        Types::llong          dramFrequency {}; //!< DRAM frequency.
        Types::OptionalString fsbDram       {}; //!< FSB-DRAM ratio.
        Types::OptionalString casLatency    {}; //!< CAS latency (CL).
        Types::OptionalString casDelay      {}; //!< CAS delay (tRCD).
        Types::OptionalString precharge     {}; //!< Precharge (tRP).
        Types::OptionalString cycleTime     {}; //!< Cycle time (tRAS).
        Types::OptionalString bankCycleTime {}; //!< Bank cycle time (tRC).
        Types::OptionalString commandRate   {}; //!< Command rate (CR).

        Types::OptionalString dramIdleTimer {}; //!< DRAM idle timer.
        Types::OptionalString totalCas      {}; //!< Total CAS (tRDRAM).
        Types::OptionalString rowToColumn   {}; //!< Row to column (tRCD).
    };


    struct General final
    {
        Types::OptionalString           name                {}; //!< Memory name.
        Types::OptionalString           type                {}; //!< Memory type.
        Types::OptionalString           memoryClock         {}; //!< Memory clock.
        Types::OptionalString           ioBusClock          {}; //!< I/O bus clock.
        Types::OptionalString           dataRate            {}; //!< Data rate.
        Types::OptionalString           moduleName          {}; //!< Module name.
        Types::OptionalString           peakTransferRate    {}; //!< Peak transfer rate.
        Types::OptionalString           channel             {}; //!< Channel.
        Types::OptionalString           dcMode              {}; //!< DC mode.
        Types::llong                    nbFrequency         {}; //!< NB frequency.

        Types::Optional<MemoryStruct>   size                {}; //!< Memory size information.
        Types::Optional<TimingStruct>   timing              {}; //!< Memory timing information.
    };

};


CELL_NAMESPACE_END

#endif // CELL_MEMORY_HPP
