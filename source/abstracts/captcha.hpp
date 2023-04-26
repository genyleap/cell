/*!
 * @file        captcha.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Captcha interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CAPTCHA_ABSTRACT_HPP
#define CELL_CAPTCHA_ABSTRACT_HPP

#include "common.hpp"

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The AbstractCaptcha class
 */
class __cell_export AbstractCaptcha
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractCaptcha)


    /*!
     * \brief Get the HTML code of the captcha.
     * \returns as string output.
     */
    __cell_constexpr_virtual Types::OptionalString getCode() __cell_const = __cell_zero;

    /*!
     * \brief Checking if the user passed the captcha or not.
     * \returns as boolean.
     */
    __cell_constexpr_virtual Types::OptionalBool checkCode() __cell_const = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractCaptcha)
};

CELL_NAMESPACE_END

#endif  // CELL_CAPTCHA_ABSTRACT_HPP
