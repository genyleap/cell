/*!
 * @file        os.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Operation system information.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_PRODUCT_HPP
#define CELL_PRODUCT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

class __cell_export ProductInfo
{
public:
    /**
     * @brief Constructs a ProductInfo object.
     */
    ProductInfo();

    /**
     * @brief Destroys the ProductInfo object.
     */
    ~ProductInfo();

};

CELL_NAMESPACE_END

#endif // CELL_PRODUCT_HPP
