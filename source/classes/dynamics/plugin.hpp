/*!
 * @file        plugin.hpp
 * @brief       This file is part of the Cell System.
 * @details     Plugin for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_HPP
#define CELL_PLUGIN_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("pluginschema.hpp")
#   include "pluginschema.hpp"
#else
#   error "Cell's "pluginschema.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

class __cell_export Plugin
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS_WITHOUT_IMPL(Plugin)

    /*!
     * \brief getCodeName function returns a unique code of plugin.
     * \returns a code as unique type.
     */
    __cell_no_discard_virtual Types::OptionalString getCodeName()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getName function returns name of plugin.
     * \returns a name as string.
     */
    __cell_no_discard_virtual Types::OptionalString getName()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getDescription function returns description of plugin.
     * \returns a description about plugin as string.
     */
    __cell_no_discard_virtual Types::OptionalString getDescription()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getCompiledDate function returns date of plugin's compile date.
     * \returns a name as string.
     */
    __cell_no_discard_virtual Types::OptionalString getCompiledDate()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getLicense function returns license of plugin.
     * \returns a license as SystemLicense.
     */
    __cell_no_discard_virtual Types::Optional<SystemLicense> getLicense()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getPluginType function returns type of plugin.
     * \returns a type as PluginType.
     */
    __cell_no_discard_virtual Types::Optional<PluginType> getPluginType()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getVersion function returns version of plugin.
     * \returns a version as SemanticVersion.
     */
    __cell_no_discard_virtual Types::Optional<SemanticVersion> getVersion()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getAuthor function returns author of plugin.
     * \returns a name as string.
     */
    __cell_no_discard_virtual Types::OptionalString getAuthor()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getUrl function returns url of plugin.
     * \returns a url as string.
     */
    __cell_no_discard_virtual Types::OptionalString getUrl()  __cell_const_noexcept = __cell_zero;

    /**
     * @brief getPermission function will returns plugin permission.
     * @return an optional type of permision.
     */
    __cell_no_discard_virtual Types::Optional<PermissionType> getPermission()  __cell_const_noexcept = __cell_zero;

    /**
     * @brief getState function will returns plugin status.
     * @return an optional state.
     */
    __cell_no_discard_virtual Types::Optional<PluginState> getState()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief run is action function for plugins.
     */
    __cell_virtual void run()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief runAsTemplate is action function for plugins based on template.
     * \param val is a parameter as multi type support.
     */
    template <typename... Args>
    auto runAsTemplate(const auto& val)
    {
        return val;
    }

    /*!
     * \brief type function returns type of plugin.
     * \returns as PluginType.
     */
    __cell_virtual PluginType type() __cell_const_noexcept = __cell_zero;

    __cell_virtual PluginInfo getData()  __cell_const_noexcept = __cell_zero;

};

CELL_NAMESPACE_END

#endif // CELL_PLUGIN_HPP
