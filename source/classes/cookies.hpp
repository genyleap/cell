/*!
 * @file        cookies.hpp
 * @brief       Cookies manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2025 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_COOKIES_HPP
#define CELL_COOKIES_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Globals::Storage)

struct COOKIES_CONSTANTS final
{
    __cell_static_const_constexpr std::string_view SESSION_ID {"sessionId"};
};

/**
 * @class Cookies
 * @brief Class representing cookies.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Cookies {
public:
    /**
     * @brief Get the value of a cookie by name.
     * @param name The name of the cookie.
     * @return An optional string containing the value of the cookie, if found. Empty optional otherwise.
     */
    Types::OptionalString getCookie(const std::string& name) const;

    /**
     * @brief Get the value of the session ID cookie.
     * @return An optional string containing the value of the session ID cookie, if found. Empty optional otherwise.
     */
    Types::OptionalString getSessionIdCookie() const;

    /**
     * @brief Add a new cookie.
     * @param name The name of the cookie.
     * @param value The value of the cookie.
     */
    void addCookie(const std::string& name, const std::string& value);

private:
    std::unordered_map<std::string, std::string> m_cookies;
};




CELL_NAMESPACE_END

#endif  // CELL_COOKIES_HPP

