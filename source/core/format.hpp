/*!
 * @file        format.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     String formatting class.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_FORMAT_HPP
#define CELL_FORMAT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

#ifdef USE_BOOST_FORMAT
static std::string convertPlaceholders(const std::string& formatString);
#endif

class Format {
public:
    template <typename... Args>
    static std::string print(const std::string& formatString, const Args&... args) {

#ifdef USE_BOOST_FORMAT
        boost::format formatter(convertPlaceholders(formatString));
        try {
            formatter.exceptions(boost::io::all_error_bits ^ (boost::io::too_many_args_bit | boost::io::too_few_args_bit));
            formatArgs(formatter, args...);
        } catch (const boost::io::format_error& e) {
            return e.what();
        }
        return formatter.str();
#endif
#ifdef USE_FMT_FORMAT
        try {
            auto formatter = fmt::format(fmt::runtime(formatString), args...);
            return formatter;
        } catch (const fmt::format_error& e) {
            return e.what();
        }
#endif
#ifdef USE_STL_FORMAT
        try {
            auto formatter = std::format(formatString), args...;
            return formatter;
        } catch (const std::format_error& e) {
            return e.what();
        }
#endif
    }
#ifdef USE_BOOST_FORMAT
private:
    // Helper function to convert {} placeholders to %1%, %2%, etc. format
    static std::string convertPlaceholders(const std::string& formatString)
    {
        std::string convertedFormatString;
        std::size_t argIndex = 1;
        for (std::size_t i = 0; i < formatString.size(); ++i) {
            if (formatString[i] == '{' && i + 1 < formatString.size() && formatString[i + 1] == '}') {
                convertedFormatString += "%" + std::to_string(argIndex) + "%";
                ++argIndex;
                ++i;
            } else {
                convertedFormatString += formatString[i];
            }
        }
        return convertedFormatString;
    }
    // Recursive base case for Boost.Format argument formatting
    static void formatArgs(boost::format&) {}
    template <typename T, typename... Args>
    static void formatArgs(boost::format& formatter, const T& value, const Args&... args) {
        formatter % value;
        formatArgs(formatter, args...);
    }
#endif
};

CELL_NAMESPACE_END

#endif  // CELL_FORMAT_HPP
