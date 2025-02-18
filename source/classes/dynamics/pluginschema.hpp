/*!
 * @file        pluginschema.hpp
 * @brief       This file is part of the Cell System.
 * @details     Schema structs for plugin system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_SCHEMA_HPP
#define CELL_PLUGIN_SCHEMA_HPP

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
 * \brief The PluginType enum
 */
enum class PluginType : Types::u8
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

enum class PluginState : Types::u8
{
    Active,     //!< Active when plugin is activated.
    InActive,   //!< Disable when plugin is not activated.
    Suspended   //!< When the plugin is disabled it will be suspended due to some restrictions.
};


/*!
 * \brief The PluginInfo class
 */
struct PluginInfo __cell_final
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
    PluginType                         pluginType      {}; //!< The type of plugin.
    GroupListAccess                    groupAccess     {}; //!< The group of users that can be access to the module.

    //!< Basic information
    Types::OptionalString              codeName        {}; //!< A unique code for plugin.
    Types::OptionalString              name            {}; //!< A name for plugin.
    Types::OptionalString              description     {}; //!< A description for explanation plugin.
    Types::OptionalString              compiledDate    {}; //!< Compiled date for plugin.
    Types::OptionalString              author          {}; //!< Author of plugin.
    Types::OptionalString              url             {}; //!< Url of plugin.

    //!< Optionals
    Types::Optional<SystemLicense>     license         {}; //!< License type for plugin.
    Types::Optional<SemanticVersion>   version         {}; //!< Version of plugin.
    Types::Optional<PermissionType>    permission      {}; //!< Permissions of plugin.
    Types::Optional<PluginState>       state           {}; //!< Status of plugin.
};

CELL_NAMESPACE_END

#endif  // CELL_PLUGIN_SCHEMA_HPP
