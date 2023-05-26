/*!
 * @file        core-concepts.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System meta core programming.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CORE_CONCEPTS_HPP
#define CELL_CORE_CONCEPTS_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Concepts)

/**
 * @brief Concept to check if a type is a floating-point type.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept FloatingPoint = std::floating_point<T>;

/**
 * @brief Concept to check if a type can be converted to std::string.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept ConvertibleToString = requires(T t) {
    { std::ostringstream() << t } -> std::convertible_to<std::string>;
};


/**
 * @brief Concept to check if a type is convertible to std::string_view.
 *
 * This concept verifies that the template argument is convertible to std::string_view.
 */
template <typename T>
concept ConvertibleToStringView = std::convertible_to<T, std::string_view>;

CELL_NAMESPACE_END

#endif // CELL_CORE_CONCEPTS_HPP
