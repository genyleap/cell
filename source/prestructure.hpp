/*!
 * Gen3 License
 *
 * @file        prestructure.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_PRESTRUCTURE_HPP
#define CELL_PRESTRUCTURE_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)


/*!
 * \brief The SystemStatus enum
 */
__cell_enum_class SystemStatus : Types::u8
{
    Off             = 0x1, //!< The system is off.
    On              = 0x2, //!< The system is on.
    Suspened        = 0x3, //!< The system is on suspended mode.
    Ready           = 0x4, //!< The system is ready.
    Maintainance    = 0x5, //!< The system is under maintainance.
    Unknown         = 0x6  //!< It is not clear what state the system is in.
};

/*!
 * \brief The SystemType enum
 */
__cell_enum_class SystemType: Types::u8
{
    Private      = 0x1, //!< Private.
    General      = 0x2, //!< General.
    Professional = 0x3, //!< Professional.
    Premium      = 0x4, //!< Premium.
    Default      = 0x5  //!< Default.
};

/*!
 * \brief The SystemLicense enum
 */
__cell_enum_class SystemLicense: Types::u8
{
    Free            = 0x1,  //!< This flag marks the system as the free version.
    Commercial      = 0x2   //!< This flag marks the system as the commercial version.
};

/*!
 * \brief The CompatibilityLevel struct
 */
struct CompatibilityLevel __cell_final
{
    Types::u8 NoneCompatibility;
    Types::u8 SimpleCompatibility;
    Types::u8 GreenCompatibility;
    Types::u8 PerfectCompatibility;
};

/*!
 * @title The SemanticVersion class
 * @brief Given a version number MAJOR.MINOR.PATCH, increment the:
 * ---------------------------------------------------------------
 * ---- MAJOR version when you make incompatible API changes.
 * ---- MINOR version when you add functionality in a backwards compatible manner.
 * ---- PATCH version when you make backwards compatible bug fixes.
 * Additional labels for pre-release and build metadata are available as extensions to the MAJOR.MINOR.PATCH format.
 * @version Semantic Versioning 2.0.0
 */
struct SemanticVersion __cell_final
{
    Types::uint Major                  {__cell_zero};
    Types::uint Minor                  {__cell_zero};
    Types::uint Patch                  {__cell_zero};
    Types::OptionalString  PreRelease  {__cell_null_str}; //!< Software release life cycle. https://en.wikipedia.org/wiki/Software_release_life_cycle
};

/*!
 * \brief The ApplicationType enum
 *  For the future. ;)
 *  Ability to switch between decentralized and centralized based software.
 */
enum class ApplicationType : Types::u8
{
    Centralized    =  0x1, //!< A centralized application.
    Decentralized  =  0x2, //!< A decentralized application (DApp).
};

/*!
 * \brief The SystemInfo struct
 */
struct SystemInfo __cell_final
{
    //!Basic Information
    Types::OptionalString              codeName        {__cell_null_str};
    Types::OptionalString              name            {__cell_null_str};
    Types::Optional<SemanticVersion>   version         {};
    Types::OptionalString              model           {__cell_null_str};
    Types::OptionalString              developer       {__cell_null_str};
    Types::OptionalString              compiledDate    {__cell_null_str};
    //!Extra
    Types::Optional<SystemType>        type            {SystemType::Default};
    Types::Optional<SystemLicense>     license         {SystemLicense::Free};
};

CELL_NAMESPACE_END

#endif // CELL_PRESTRUCTURE_HPP
