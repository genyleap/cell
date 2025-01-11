/*!
 * @file        plugininterface.hpp
 * @brief       This file is part of the Cell System.
 * @details     Plugin interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_INTERFACE_HPP
#define CELL_PLUGIN_INTERFACE_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Module Schema.
#if __has_include("pluginschema.hpp")
#   include "pluginschema.hpp"
#else
#   error "Cell's plugin schema was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

using NameList      =   std::vector<std::string>;
using PluginList    =   std::vector<PluginInfo>;
using ErrorString   =   std::vector<std::string>;

/*!
 * \brief The PluginInterfaceData class
 */
struct PluginInterfaceData final
{
public:
    NameList    nameList    {};     //!< List of plugins name.
    PluginList  pluginList  {};     //!< List of plugins by info.
    ErrorString errors      {};     //!< List of errors.
};

class PluginInterfaceImpl;

/*!
 * \brief The PluginInterface class is exported from the mail library.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export PluginInterface {
public:
  //Return a static instance of this class
    DeclareSingletonInstance(PluginInterface)

  /*!
   * \brief addDetail function sets all information of plugins.
   * \param plist is type of PluginList [std::vector<PluginDetail>]
   */
  void addDetail(const PluginList& plist);

  /*!
   * \brief addName function sets name of plugins.
   * \param name of plugin.
   */
  void addName(const std::string& name);

  /*!
   * \brief setError function sets message of error inside plugins.
   * \param var is message of error.
   */
  void setError(const std::string& var);

  /*!
   * \brief getDetail function gets detail from plugins.
   * \return list of detail such as name, version and etc.
   */
  const PluginList& getDetail() const;

  /*!
   * \brief getNames function gets name of plugins.
   * \return list of plugin.
   */
  const NameList& getNames() const;

  /*!
   * \brief getErrors function gets list of errors.
   * \return list of errors as string [ErrorString : std::vector<std::string>].
   */
  const ErrorString& getErrors() const;

private:
  CELL_DEFAULT_INTERFACE_OCTORS(PluginInterface)
  Scope<PluginInterfaceImpl> pImplPtr;
  PluginInterfaceData  m_pluginInterfaceData;

};

CELL_NAMESPACE_END

#endif // CELL_PLUGIN_INTERFACE_HPP
