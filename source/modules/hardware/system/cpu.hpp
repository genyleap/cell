/*!
 * @file        cpu.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System processor information.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CPU_HPP
#define CELL_CPU_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif
CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

/**
 * @brief The CpuInfo struct contains information about the CPU.
 */
class __cell_export CpuInfo
{
public:
    CpuInfo();
    ~CpuInfo();
    /**
     * @brief The Specification struct contains detailed CPU specifications.
     */
    struct Specification final
    {
        Types::OptionalString  family       {}; //!< CPU family.
        Types::OptionalString  model        {}; //!< CPU model.
        Types::OptionalString  stepping     {}; //!< CPU stepping.
        Types::OptionalString  extFamily    {}; //!< Extended CPU family.
        Types::OptionalString  extModel     {}; //!< Extended CPU model.
        Types::OptionalString  technology   {}; //!< CPU technology (lithography).
        Types::OptionalString  revision     {}; //!< CPU revision.

        //! CPU Instructions
        Types::Optional<Types::VectorString> instructions {}; //!< CPU instructions.
    };

    /**
     * @brief The ClockInfo struct contains CPU clock information.
     */
    struct ClockInfo final
    {
        Types::OptionalString  coreSpeed    {}; //!< CPU core speed.
        Types::OptionalString  multiplier   {}; //!< CPU multiplier.
        Types::OptionalString  busSpeed     {}; //!< CPU bus speed.
        Types::OptionalString  ratedFsb     {}; //!< Rated FSB (Front Side Bus) speed.
    };

    struct Cache final
    {
        Types::OptionalString  level1    {}; //!< Level 1 cache.
        Types::OptionalString  level2    {}; //!< Level 2 cache.
        Types::OptionalString  level3    {}; //!< Level 3 cache.
    };

    Types::OptionalString           name            {}; //!< CPU name.
    Types::OptionalString           codeName        {}; //!< CPU code name.
    Types::OptionalString           maxTdp          {}; //!< Maximum thermal design power (TDP).
    Types::OptionalString           brand           {}; //!< CPU brand.
    Types::OptionalString           package         {}; //!< CPU package type.
    Types::OptionalString           socket          {}; //!< CPU socket type.
    Types::OptionalString           manufacturing   {}; //!< CPU manufacturing process.
    Types::OptionalString           voltage         {}; //!< CPU voltage.
    Types::Optional<Types::u8>      transistors     {}; //!< Number of transistors.
    Types::OptionalString           releaseDate     {}; //!< CPU release date.
    Types::OptionalBool             crossSupport    {}; //!< Crossfire support.
    Types::uint                     cores           {}; //!< Number of CPU cores.
    Types::uint                     threads         {}; //!< Number of CPU threads.

    //! More details.
    Types::Optional<Specification>              specification   {}; //!< Detailed CPU specifications.
    Types::Optional<Types::Vector<ClockInfo>>   clock           {}; //!< CPU clock information.
    Types::Optional<Types::Vector<Cache>>       cache           {}; //!< CPU cache information.
};


CELL_NAMESPACE_END

#endif // CELL_CPU_HPP
