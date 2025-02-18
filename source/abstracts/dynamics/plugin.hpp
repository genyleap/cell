/*!
 * @file        plugin.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Plugin interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_ABSTRACT_HPP
#define CELL_PLUGIN_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The PluginType enum
 */
__cell_enum_class PluginType : Types::u8
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

/*!
 * \brief The PluginInfo class
 */
struct PluginInfo __cell_final
{
    Types::OptionalString              codeName        {}; //!< A unique code for plugin.
    Types::OptionalString              name            {}; //!< A name for plugin.
    Types::OptionalString              description     {}; //!< A description for explanation plugin.
    Types::OptionalString              compiledDate    {}; //!< Compiled date for plugin.
    Types::Optional<SystemLicense>     license         {}; //!< License type for plugin.
    PluginType                         pluginType      {}; //!< The type of plugin.
    Types::Optional<SemanticVersion>   version         {}; //!< Version of plugin.
    Types::OptionalString              author          {}; //!< Author of plugin.
    Types::OptionalString              url             {}; //!< Url of plugin.
};

/*!
 * \brief The AbstractBaseClass class
 */
class __cell_export AbstractPlugin
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractPlugin)

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

protected:
    PluginInfo* m_pluginInfo;
    friend class AbstractPluginManager;
    void setCodeName(const Types::Optional<Types::u32>& codename);
    void setName(const Types::OptionalString& name);
    void setDescription(const Types::OptionalString& desc);
    void setCompiledDate(const Types::OptionalString& compiledDate);
    void setLicense(const Types::Optional<SystemLicense>& licese);
    void setPluginType(const PluginType pluginType);
    void setVersion(const Types::Optional<SemanticVersion>& version);
    void setAuthor(const Types::OptionalString& author);
    void setUrl(const Types::OptionalString& url);

private:
    CELL_DISABLE_COPY(AbstractPlugin)
};

CELL_NAMESPACE_END

#endif  // CELL_PLUGIN_ABSTRACT_HPP
