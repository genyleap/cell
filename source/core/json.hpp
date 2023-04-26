/*!
 * @file        json.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Json system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_JSON_HPP
#define CELL_JSON_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::JSon)

/**
 * @brief The InputType enum
 */
enum class InputType { File, RawData };

/**
 * @brief The JsonParser class
 */
class __cell_export JsonParser {
public:
    JsonParser();
    ~JsonParser();

    /**
     * Parse a JSON data from a given input and populate root node of the JSON object.
     * @param data Input data in JSonType format.
     * @param inputType as InputType for select type of input data [file or raw string].
     * @return true if parsing is successful, false otherwise.
     */
    bool parse(const Types::JSonType& data, const InputType inputType) __cell_noexcept;

    /**
     * Parse a JSON data from a given input and populate root node of the JSON object.
     * @param data Input data in JSonType format.
     * @return true if parsing is successful, false otherwise.
     */
    bool parse(const Types::JSonType& data) __cell_noexcept;

    /**
     * Check if a given key is present in the JSON object.
     * @param key as string to be checked.
     * @return true if key is present in the JSON object, false otherwise.
     */
    bool contains(const std::string& key) __cell_noexcept;

    /**
     * Get the value associated with a given key in the JSON object.
     * @param key as stroing for which the value is to be retrieved.
     * @return Value associated with the key if found, else a null JSON value.
     */
    Types::JSonValue get(const std::string& key) __cell_noexcept;

private:
    Types::JSonValue m_root{}; // Root node of the JSON object
};

CELL_NAMESPACE_END

#endif  // CELL_JSON_HPP
