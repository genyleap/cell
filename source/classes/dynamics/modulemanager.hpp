/*!
 * @file        module.hpp
 * @brief       This file is part of the Cell System.
 * @details     Module manager for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_MANAGER_HPP
#define CELL_MODULE_MANAGER_HPP

#if __has_include("module.hpp")
#   include "module.hpp"
#else
#   error "Cell's "module.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

// Define the prototype for a function that should exist in the lib
// that is used to create and return the module type in the lib.

PointerToObject(Module, fnCreateModule)

// Destroys the module type from the lib before the library is unloaded.
using fnDestroyModule = PointerToFunction;

class ModuleManagerPimpl;

/*!
 * \brief The ModuleManager class
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export ModuleManager
{
public:
    DeclareSingletonInstance(ModuleManager)

  /*!
   * \brief load function loads the module and returns true if the module was loaded successfully; otherwise returns false.
   * \param module is module name.
   * \return module.
   */
  Module* load(const std::string& module);

  /*!
   * \brief unload function unloads the module and returns true if the module could be unloaded; otherwise returns false.
   * \param module
   */
  void unload(Module*& module);

  /*!
   * \brief isLoaded function returns true if the module is loaded; otherwise returns false.
   * \return bolean of status.
   */
  bool isLoaded() const;

private:
  CELL_DEFAULT_OCTORS(ModuleManager)
  bool m_status = {false};
  Scope<ModuleManagerPimpl> implementationPtr;
};

CELL_NAMESPACE_END

#endif // CELL_MODULE_MANAGER_HPP
