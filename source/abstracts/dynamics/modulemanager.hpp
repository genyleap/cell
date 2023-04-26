/*!
 * @file        modulemanager.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Module manager interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PLUGIN_MANAGER_ABSTRACT_HPP
#define CELL_PLUGIN_MANAGER_ABSTRACT_HPP

#include "common.hpp"
#include "module.hpp"
#include "moduleinterface.hpp"

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
    static AbstractModuleManager& instance();

    /*!
     * \brief load function loads the module and returns true if the module was loaded successfully; otherwise returns false.
     * \param module is module name.
     * \returns module.
     */
    __cell_no_discard_virtual AbstractModule* load(const std::string& module) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief unload function unloads the module and returns true if the module could be unloaded; otherwise returns false.
     * \param module
     */
    __cell_virtual void unload(AbstractModule*& module) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief isLoaded function returns true if the module is loaded; otherwise returns false.
     * \return bolean of status.
     */
    __cell_no_discard_virtual bool isLoaded() __cell_const_noexcept = __cell_zero;

private:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractModuleManager)
    ModuleManagerData* m_moduleManagerData;
    bool m_status = {false};
};

CELL_NAMESPACE_END

#endif  // CELL_PLUGIN_MANAGER_ABSTRACT_HPP
