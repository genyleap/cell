/*!
 * @file        base.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Base class interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_BASE_ABSTRACT_HPP
#define CELL_BASE_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The AbstractBaseClass class
 */
class __cell_export AbstractBaseClass
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractBaseClass)


private:
    CELL_DISABLE_COPY(AbstractBaseClass)
};

CELL_NAMESPACE_END

#endif  // CELL_BASE_ABSTRACT_HPP
