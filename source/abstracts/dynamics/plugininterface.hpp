/*!
 * @file        plugininterface.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Plugin interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_INTERFACE_ABSTRACT_HPP
#define CELL_PLUGIN_INTERFACE_ABSTRACT_HPP

#include "common.hpp"
#include "plugin.hpp"

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

//struct PluginDetail
//{
//  OptionalString            codeName      {}; ///< Code Name.
//  OptionalString            name          {}; ///< Name.
//  OptionalString            description   {}; ///< Description.
//  OptionalString            compiledDate  {}; ///< Compiled Date.
//  Optional<SystemLicense>   license       {}; ///< License.
//  Optional<PluginType>      type          {}; ///< Type.
//  Optional<SemanticVersion> version       {}; ///< Version.
//  OptionalString            author        {}; ///< Author.
//  OptionalString            url           {}; ///< Url.
//};

using NameList      =   std::vector<std::string>;
using PluginList    =   std::vector<PluginInfo>;
using ErrorString   =   std::vector<std::string>;

/*!
 * \brief The PluginInterfaceData class
 */
struct PluginInterfaceData final
{
public:
    NameList    nameList    {};     ///< List of plugins name.
    PluginList  pluginList  {};     ///< List of plugins by info.
    ErrorString errors      {};     ///< List of errors.
};

class __cell_export AbstractPluginInterface
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractPluginInterface)
    //Return a static instance of this class
    static AbstractPluginInterface& instance();

    /*!
     * \brief addDetail function sets all information of plugins.
     * \param plist is type of PluginList [std::vector<PluginDetail>]
     */
    __cell_virtual void addDetail(const PluginList& plist) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief addName function sets name of plugins.
     * \param name of plugin.
     */
    __cell_virtual void addName(const std::string& name) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief setError function sets message of error inside plugins.
     * \param var is message of error.
     */
    __cell_virtual void setError(const std::string& var) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getDetail function gets detail from plugins.
     * \returns list of detail such as name, version and etc.
     */
    __cell_no_discard_virtual const PluginList& getDetail() __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getNames function gets name of plugins.
     * \returns list of plugin.
     */
    __cell_no_discard_virtual const NameList& getNames() __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getErrors function gets list of errors.
     * \returns list of errors as string [ErrorString : std::vector<std::string>].
     */
    __cell_no_discard_virtual const ErrorString& getErrors() __cell_const_noexcept = __cell_zero;

private:
    PluginInterfaceData*  m_pluginInterfaceData;
};


CELL_NAMESPACE_END

#endif  // CELL_PLUGIN_INTERFACE_ABSTRACT_HPP
