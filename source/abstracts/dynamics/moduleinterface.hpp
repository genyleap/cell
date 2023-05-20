/*!
 * @file        moduleinterface.hpp
 * @brief       This file is part of the Cell System.
 * @details     Module interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_INTERFACE_ABSTRACT_HPP
#define CELL_MODULE_INTERFACE_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Module.
#if __has_include("module.hpp")
#   include "module.hpp"
#else
#   error "Cell's module was not found!"
#endif


CELL_NAMESPACE_BEGIN(Cell::Abstracts)

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

class __cell_export AbstractModuleInterface
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractModuleInterface)
    //Return a static instance of this class
    static AbstractModuleInterface& instance();

    /*!
     * \brief addDetail function sets all information of modules.
     * \param plist is type of ModuleList [std::vector<ModuleDetail>]
     */
    __cell_virtual void addDetail(const ModuleList& plist) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief addName function sets name of modules.
     * \param name of module.
     */
    __cell_virtual void addName(const std::string& name) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief setError function sets message of error inside modules.
     * \param var is message of error.
     */
    __cell_virtual void setError(const std::string& var) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getDetail function gets detail from modules.
     * \returns list of detail such as name, version and etc.
     */
    __cell_no_discard_virtual const ModuleList& getDetail() __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getNames function gets name of modules.
     * \returns list of module.
     */
    __cell_no_discard_virtual const NameList& getNames() __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getErrors function gets list of errors.
     * \returns list of errors as string [ErrorString : std::vector<std::string>].
     */
    __cell_no_discard_virtual const ErrorString& getErrors() __cell_const_noexcept = __cell_zero;

private:
    ModuleInterfaceData*  m_moduleInterfaceData;
};

CELL_NAMESPACE_END

#endif  // CELL_MODULE_INTERFACE_ABSTRACT_HPP
