/*!
 * @file        moduleinterface.hpp
 * @brief       This file is part of the Cell System.
 * @details     Module interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_INTERFACE_HPP
#define CELL_MODULE_INTERFACE_HPP

//! Cell's Common.
#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
# endif
#endif

//! Cell's Module Schema.
#ifdef __has_include
# if __has_include("moduleschema.hpp")
#   include "moduleschema.hpp"
#else
#   error "Cell's module schema was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

using NameList      =   std::vector<std::string>;
using ModuleList    =   std::vector<ModuleInfo>;
using ErrorString   =   std::vector<std::string>;

/*!
 * \brief The ModuleInterfaceData class
 */
struct ModuleInterfaceData final
{
public:
    NameList    nameList    {};     //!< List of modules name.
    ModuleList  moduleList  {};     //!< List of modules by info.
    ErrorString errors      {};     //!< List of errors.
};

class ModuleInterfaceImpl;

/*!
 * \brief The ModuleInterface class is exported from the mail library.
 */
class __cell_export ModuleInterface {
public:
  //Return a static instance of this class
    DeclareSingletonInstance(ModuleInterface)

  /*!
   * \brief addDetail function sets all information of modules.
   * \param plist is type of ModuleList [std::vector<ModuleDetail>]
   */
  void addDetail(const ModuleList& plist);

  /*!
   * \brief addName function sets name of modules.
   * \param name of module.
   */
  void addName(const std::string& name);

  /*!
   * \brief setError function sets message of error inside modules.
   * \param var is message of error.
   */
  void setError(const std::string& var);

  /*!
   * \brief getDetail function gets detail from modules.
   * \return list of detail such as name, version and etc.
   */
  const ModuleList& getDetail() const;

  /*!
   * \brief getNames function gets name of modules.
   * \return list of module.
   */
  const NameList& getNames() const;

  /*!
   * \brief getErrors function gets list of errors.
   * \return list of errors as string [ErrorString : std::vector<std::string>].
   */
  const ErrorString& getErrors() const;

private:
  CELL_DEFAULT_INTERFACE_OCTORS(ModuleInterface)
  Scope<ModuleInterfaceImpl> pImplPtr;
  ModuleInterfaceData  m_moduleInterfaceData;

};

CELL_NAMESPACE_END

#endif // CELL_MODULE_INTERFACE_HPP
