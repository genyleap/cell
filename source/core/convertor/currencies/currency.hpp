/*!
 * @file        corrency.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Corrency convertor.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CORRENCY_CONVERTOR_HPP
#define CELL_CORRENCY_CONVERTOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("meta-currency.hpp")
#   include "meta-currency.hpp"
#else
#   error "Cell's "meta-currency.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Convertors::Currencies)

/**
 * @class Currency
 * @brief Represents a currency and provides functionality for converting amounts to words.
 */
class __cell_export Currency {
public:
    /**
     * @brief Default constructor.
     */
    Currency();

    /**
     * @brief Destructor.
     */
    ~Currency();

    /**
     * @brief Converts a given amount to words.
     *
     * @param amount The amount to convert.
     * @return An optional string containing the amount in words, or empty if conversion fails.
     */
    Types::OptionalString toWord(double amount);

    // Static constexpr variables representing string views

    __cell_static_const_constexpr std::string_view DIGITS      {"digits"};                    //!< String view representing digits.
    __cell_static_const_constexpr std::string_view UNIT_WORDS  {"unit_words"};                //!< String view representing unit words.
    __cell_static_const_constexpr std::string_view TENS_WORDS  {"tens_words"};                //!< String view representing tens words.
    __cell_static_const_constexpr std::string_view DIGIT_WORDS {"digit_words"};               //!< String view representing digit words
    __cell_static_const_constexpr std::string_view CURRENCIES  {"currencies"};                //!< String view representing currencies.
    __cell_static_const_constexpr std::string_view VIEW_FORMAT {"view_format"};               //!< String view representing view format.

    __cell_static_const_constexpr std::string_view MIN_CURRENCY_UNIT         {"main_currency_unit"};         //!< String view representing the main currency unit.
    __cell_static_const_constexpr std::string_view CURRENCY_MIXED_FORM       {"currency_mixed_form"};        //!<String view representing the mixed form of the currency.
    __cell_static_const_constexpr std::string_view FRACTIONAL_MONETARY_UNIT  {"fractional_monetary_unit"};   //!<String view representing the fractional monetary unit.

private:
    std::vector<std::string> units      {__cell_null_str};                      //!< Vector of units.
    std::vector<std::string> tens       {__cell_null_str, __cell_null_str};     //!< Vector of tens.
    std::vector<std::string> digitWords {};                                     //!< Vector of digit words.

    /**
     * @brief Converts a given number to text representation.
     *
     * @param number The number to convert.
     * @return The text representation of the number.
     */
    std::string numberToText(Types::ullongInt number);
};



CELL_NAMESPACE_END

#endif  // CELL_CORRENCY_CONVERTOR_HPP
