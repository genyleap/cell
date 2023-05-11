/*!
 * @file        pluginschema.hpp
 * @brief       This file is part of the Cell System.
 * @details     Schema structs for plugin system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_SCHEMA_HPP
#define CELL_PLUGIN_SCHEMA_HPP

//!<  Cell's Common.
#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

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
 * \brief The PermissionType enum
 */
enum class PermissionType : Types::u8
{
    ReadOnly,
    EditableOnly,
    Restricted,
    FullAccess,
    ByService
};

/*!
 * \brief The PluginInfo class
 */
struct PluginInfo __cell_final
{
    //!<  Types of usage.
    PluginType                         pluginType      {}; //!< The type of plugin.

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

#endif  // CELL_PLUGIN_SCHEMA_HPP
