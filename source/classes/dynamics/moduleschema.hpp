/*!
 * @file        moduleschema.hpp
 * @brief       This file is part of the Cell System.
 * @details     Schema structs for module system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_SCHEMA_HPP
#define CELL_MODULE_SCHEMA_HPP

//!<  Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

//!<  Cell's Common.
#if __has_include("abstracts/account/groups.hpp")
#   include "abstracts/account/groups.hpp"
#else
#   error "Cell's abstracts/account/groups.hpp was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

using GroupListAccess = std::vector<Cell::Abstracts::Account::GroupData>;
/*!
 * \brief The ModuleType enum
 */
enum class ModuleType : Types::u8
{
    Index,      //!< For global user service.
    Admin,      //!< For administrator service.
    Root,       //!< For root service.
    System,     //!< For system service.
    Cron,       //!< For cron job service.
    Core,       //!< For system core service.
    Theme,      //!< For system template.
    Default,    //!< For default global service.
    Custom      //!< For custom global service.
};

enum class ModuleState : Types::u8
{
    Active,     //!< Active when module is activated.
    InActive,   //!< Disable when module is not activated.
    Suspended   //!< When the module is disabled it will be suspended due to some restrictions.
};


/*!
 * \brief The ModuleInfo class
 */
struct __cell_export ModuleInfo __cell_final
{
    /*!
     * \brief The PermissionType enum
     */
    enum PermissionType : Types::u8
    {
        ReadOnly,
        EditableOnly,
        Restricted,
        FullAccess,
        ByService
    };

    //!<  Types of usage.
    ModuleType                         moduleType      {}; //!< The type of module.
    GroupListAccess                    groupAccess     {}; //!< The group of users that can be access to the module.
    Types::u8                          position        {}; //!< The position of module in the list.

    //!< Basic information
    Types::OptionalString              codeName        {}; //!< A unique code for module.
    Types::OptionalString              name            {}; //!< A name for module.
    Types::OptionalString              description     {}; //!< A description for explanation module.
    Types::OptionalString              compiledDate    {}; //!< Compiled date for module.
    Types::OptionalString              author          {}; //!< Author of module.
    Types::OptionalString              url             {}; //!< Url of module.

    //!< Optionals
    Types::Optional<SystemLicense>     license         {}; //!< License type for module.
    Types::Optional<SemanticVersion>   version         {}; //!< Version of module.
    Types::Optional<PermissionType>    permission      {}; //!< Permissions of module.
    Types::Optional<ModuleState>       state           {}; //!< Status of module.
};

CELL_NAMESPACE_END

#endif  // CELL_MODULE_SCHEMA_HPP
