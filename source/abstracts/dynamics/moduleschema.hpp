/*!
 * @file        moduleschema.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Schema structs for module.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_SCHEMA_ABSTRACT_HPP
#define CELL_MODULE_SCHEMA_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The ModuleType enum
 */
__cell_enum_class ModuleType : Types::u8
{
    Index,      //!For global user service.
    Admin,      //!For administrator service.
    Root,       //!For root service.
    System,     //!For system service.
    Cron,       //!For cron job service.
    Core,       //!For system core service.
    Theme,      //!For system template.
    Default,    //!For default global service.
    Custom      //!For custom global service.
};

/*!
 * \brief The PermissionType enum
 */
__cell_enum_class PermissionType
{
    ReadOnly,
    EditableOnly,
    Restricted,
    FullAccess,
    ByService
};

/*!
 * \brief The ModuleInfo class
 */
struct ModuleInfo __cell_final
{
    Types::Optional<Types::u32>        codeName        {}; //!< A unique code for module.
    Types::OptionalString              name            {}; //!< A name for module.
    Types::OptionalString              description     {}; //!< A description for explanation module.
    Types::OptionalString              compiledDate    {}; //!< Compiled date for module.
    Types::Optional<SystemLicense>     license         {}; //!< License type for module.
    ModuleType                         moduleType      {}; //!< The type of module.
    Types::Optional<SemanticVersion>   version         {}; //!< Version of module.
    Types::OptionalString              author          {}; //!< Author of module.
    Types::OptionalString              url             {}; //!< Url of module.
};

CELL_NAMESPACE_END

#endif  // CELL_MODULE_SCHEMA_ABSTRACT_HPP
