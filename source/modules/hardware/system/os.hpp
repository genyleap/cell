/*!
 * @file        os.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Operation system information.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_OS_HPP
#define CELL_OS_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

class __cell_export OsInfo
{
public:
    /**
     * @brief Constructs a OsInfo object.
     */
    OsInfo();

    /**
     * @brief Destroys the OsInfo object.
     */
    ~OsInfo();

};

CELL_NAMESPACE_END

#endif // CELL_OS_HPP
