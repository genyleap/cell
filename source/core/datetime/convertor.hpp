/*!
 * @file        convertor.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Date & Time convertor.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_DATE_TIME_CONVERTOR_HPP
#define CELL_DATE_TIME_CONVERTOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::DateTime)

/**
 * @class TimestampConverter
 * @brief A utility class for converting timestamps between different formats.
 */
class __cell_export TimestampConverter
{
public:
    /**
     * @brief Convert epoch time to Unix time.
     *
     * @param epochTime The epoch time to convert.
     * @return The Unix time equivalent of the epoch time.
     */
    static std::time_t epochToUnix(std::chrono::seconds epochTime);

    /**
     * @brief Convert Unix time to epoch time.
     *
     * @param unixTime The Unix time to convert.
     * @return The epoch time equivalent of the Unix time.
     */
    static std::chrono::seconds unixToEpoch(std::time_t unixTime);

    /**
     * @brief Get the relative time compared to the current time.
     *
     * @param unixTime The Unix time to compare.
     * @return A string representation of the relative time.
     */
    static Types::OptionalString getRelativeTime(std::time_t unixTime);

    /**
     * @brief Get the formatted date string from Unix time.
     *
     * @param unixTime The Unix time to format.
     * @param format The format string (default: "%Y-%m-%d %H:%M:%S").
     * @return A string representation of the formatted date.
     */
    static Types::OptionalString getFormattedDate(std::time_t unixTime, const std::string& format = "%Y-%m-%d %H:%M:%S");

    /**
     * @brief Convert epoch time to a human-readable date string.
     *
     * @param epochTime The epoch time to convert.
     * @param useGMT Flag indicating whether to use GMT (default: false).
     * @return A string representation of the human-readable date.
     */
    static Types::OptionalString epochToHumanReadable(std::chrono::seconds epochTime, bool useGMT = false);

    /**
     * @brief Convert epoch time to a human-readable date string with a custom format.
     *
     * @param epochTime The epoch time to convert.
     * @param format The custom format string.
     * @param useGMT Flag indicating whether to use GMT (default: false).
     * @return A string representation of the human-readable date with the custom format.
     */
    static Types::OptionalString epochToHumanReadable(std::chrono::seconds epochTime, const std::string& format, bool useGMT = false);

    /**
     * @brief Convert a human-readable date string to epoch time.
     *
     * @param humanReadableDate The human-readable date string.
     * @param useGMT Flag indicating whether to use GMT (default: false).
     * @return The epoch time equivalent of the human-readable date.
     */
    static std::chrono::seconds humanReadableToEpoch(const std::string& humanReadableDate, bool useGMT = false);

    /**
     * @brief Convert a human-readable date string to epoch time with a custom format.
     *
     * @param humanReadableDate The human-readable date string.
     * @param format The custom format string.
     * @param useGMT Flag indicating whether to use GMT (default: false).
     * @return The epoch time equivalent of the human-readable date with the custom format.
     */
    static std::chrono::seconds humanReadableToEpoch(const std::string& humanReadableDate, const std::string& format, bool useGMT = false);

    /**
     * @brief Get the time duration between two epoch times.
     *
     * @param start The start epoch time.
     * @param end The end epoch time.
     * @return A string representation of the time duration between the two epoch times.
     */
    static Types::OptionalString getTimeDuration(std::chrono::seconds start, std::chrono::seconds end);
};

CELL_NAMESPACE_END

#endif  // CELL_DATE_TIME_CONVERTOR_HPP
