/*!
 * @file        timezone.hpp
 * @brief       Timezone manager for the Cell Engine.
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

#ifndef CELL_TIMEZONE_MANAGER
#define CELL_TIMEZONE_MANAGER

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell)

/**
 * @brief The TimeZone class represents a time zone and provides utility functions for working with time.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export TimeZone
{
public:
    /**
     * @brief Default constructor.
     * Initializes the time zone to an empty string.
     */
    TimeZone();

    /**
     * @brief Constructs a TimeZone object with the specified time zone.
     * @param tz The time zone string in the format "+/-HH:MM".
     */
    explicit TimeZone(const std::string& tz);

    /**
     * @brief Gets the current time in the specified time zone.
     * @return The current time as a std::time_t object.
     */
    std::time_t getCurrentTime() const;

private:
    std::string timezone; //!< The time zone string in the format "+/-HH:MM".
};


CELL_NAMESPACE_END

#endif  // CELL_TIMEZONE_MANAGER
