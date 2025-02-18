/*!
 * @file        modulemanager.hpp
 * @brief       This file is part of the Cell System.
 * @details     Module manager interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_MANAGER_ABSTRACT_HPP
#define CELL_MODULE_MANAGER_ABSTRACT_HPP

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

//! Cell's Module interface.
#if __has_include("moduleinterface.hpp")
#   include "moduleinterface.hpp"
#else
#   error "Cell's module interface was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

// Define the prototype for a function that should exist in the lib
// that is used to create and return the module type in the lib.

CELL_POINTER_TO_AN_OBJECT(AbstractModule, fnCreateModule)

// Destroys the module type from the lib before the library is unloaded.
using fnDestroyModule = CELL_POINTER_TO_A_FUNCTION;

using ModuleMap  =  std::map<std::string, AbstractModule*>;

using LibraryMap =  std::map<std::string, void*>;

/*!
 * \brief The ModuleManagerData class
 */
class ModuleManagerData final
{
public:
    ModuleMap   modules {};
    LibraryMap  libs    {};
};

/*!
 * \brief The AbstractModuleManager class
 */
class __cell_export AbstractModuleManager
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractModuleManager)
    /*!
     * \brief load function loads the module and returns true if the module was loaded successfully; otherwise returns false.
     * \param module is module name.
     * \returns module.
     */
    __cell_no_discard_virtual AbstractModule* load(const std::string& module) = __cell_zero;

    /*!
     * \brief unload function unloads the module and returns true if the module could be unloaded; otherwise returns false.
     * \param module
     */
    __cell_virtual void unload(AbstractModule*& module) = __cell_zero;

    /*!
     * \brief isLoaded function returns true if the module is loaded; otherwise returns false.
     * \return bolean of status.
     */
    __cell_no_discard_virtual bool isLoaded() = __cell_zero;

private:
    ModuleManagerData* m_moduleManagerData;
    bool m_status = {false};
};

CELL_NAMESPACE_END

#endif  // CELL_MODULE_MANAGER_ABSTRACT_HPP
