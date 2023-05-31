/*!
 * @file        calendar-concepts.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Calendar concepts for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CALENDAR_CONCEPTS_HPP
#define CELL_CALENDAR_CONCEPTS_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Concepts)

template<typename T>
concept CalendarConcept = requires(T calendar)
{
    { calendar.availableCalendars() }               -> std::same_as<std::vector<std::string>>;
    { calendar.dateFromParts(0, 0, 0) }             -> std::same_as<std::optional<std::string>>;
    { calendar.dateTimeToString("") }               -> std::same_as<std::optional<std::string>>;
    { calendar.dayOfWeek("") }                      -> std::same_as<int>;
    { calendar.daysInMonth(0, 0) }                  -> std::same_as<int>;
    { calendar.daysInYear(0) }                      -> std::same_as<int>;
    { calendar.hasYearZero() }                      -> std::same_as<bool>;
    { calendar.isDateValid(0, 0, 0) }               -> std::same_as<bool>;
    { calendar.isDateTimeValid(0, 0, 0, 0, 0, 0) }  -> std::same_as<bool>;
    { calendar.isGregorian() }                      -> std::same_as<bool>;
    { calendar.isLeapYear(0) }                      -> std::same_as<bool>;
    { calendar.isLunar() }                          -> std::same_as<bool>;
    { calendar.isIslamic() }                        -> std::same_as<bool>;
    { calendar.isHebrew() }                         -> std::same_as<bool>;
    { calendar.isChinese() }                        -> std::same_as<bool>;
    { calendar.isValid("") }                        -> std::same_as<bool>;
    { calendar.maximumDaysInMonth() }               -> std::same_as<int>;
    { calendar.maximumMonthsInYear() }              -> std::same_as<int>;
    { calendar.minimumDaysInMonth() }               -> std::same_as<int>;
    { calendar.monthName(0) }                       -> std::same_as<std::optional<std::string>>;
    { calendar.monthsInYear() }                     -> std::same_as<int>;
    { calendar.name() }                             -> std::same_as<std::optional<std::string>>;
    { calendar.partsFromDate("") }                  -> std::same_as<std::vector<int>>;
    { calendar.standaloneMonthName(0) }             -> std::same_as<std::optional<std::string>>;
    { calendar.standaloneWeekDayName(0) }           -> std::same_as<std::optional<std::string>>;
    { calendar.weekDayName(0) }                     -> std::same_as<std::optional<std::string>>;

    // Methods for timezone support
    { calendar.getTimezone() }                      -> std::same_as<std::optional<std::string>>;
    { calendar.setTimezone("") }                    -> std::same_as<void>;
    { calendar.convertToTimezone("", "") }          -> std::same_as<std::optional<std::string>>;

    // Methods for internationalization support
    { calendar.getLocalizedMonthName(0, "") }       -> std::same_as<std::optional<std::string>>;
    { calendar.getLocalizedWeekDayName(0, "") }     -> std::same_as<std::optional<std::string>>;
    { calendar.getLocalizedDate("", "") }           -> std::same_as<std::optional<std::string>>;

    // Methods for holidays and special dates
    { calendar.isHoliday("") }                      -> std::same_as<bool>;
    { calendar.getHolidays(0) }                     -> std::same_as<std::vector<std::string>>;
    { calendar.isSpecialDate("") }                  -> std::same_as<bool>;
    { calendar.getSpecialDates(0) }                 -> std::same_as<std::vector<std::string>>;

    // Methods for date arithmetic
    { calendar.addDays("", 0) }                     -> std::same_as<std::optional<std::string>>;
    { calendar.addMonths("", 0) }                   -> std::same_as<std::optional<std::string>>;
    { calendar.addYears("", 0) }                    -> std::same_as<std::optional<std::string>>;
    { calendar.diffInDays("", "") }                 -> std::same_as<int>;
    { calendar.diffInMonths("", "") }               -> std::same_as<int>;
    { calendar.diffInYears("", "") }                -> std::same_as<int>;

    // Methods for astronomical data
    { calendar.getSunrise("", 0.0, 0.0) }           -> std::same_as<double>;
    { calendar.getSunset("", 0.0, 0.0) }            -> std::same_as<double>;
    { calendar.getMoonPhase("") }                   -> std::same_as<double>;

    // Methods for historical dates
    { calendar.isHistoricalDate("") }               -> std::same_as<bool>;
    { calendar.getHistoricalEvent("") }             -> std::same_as<std::optional<std::string>>;

    // Methods for localization and cultural settings
    { calendar.getLocale() }                        -> std::same_as<std::optional<std::string>>;
    { calendar.setLocale("") }                      -> std::same_as<void>;
    { calendar.getDateFormat() }                    -> std::same_as<std::optional<std::string>>;
    { calendar.setDateFormat("") }                  -> std::same_as<void>;
    { calendar.getTimeFormat() }                    -> std::same_as<std::optional<std::string>>;
    { calendar.setTimeFormat("") }                  -> std::same_as<void>;
    { calendar.getDateTimeFormat() }                -> std::same_as<std::optional<std::string>>;
    { calendar.setDateTimeFormat("") }              -> std::same_as<void>;

    // Methods for recurring events and reminders
    { calendar.addRecurringEvent("", "", "", "") }  -> std::same_as<void>;
    { calendar.removeRecurringEvent("") }           -> std::same_as<void>;
    { calendar.getRecurringEvents("", "") }         -> std::same_as<std::vector<std::string>>;
    { calendar.setReminder("", "", "") }            -> std::same_as<void>;
    { calendar.removeReminder("") }                 -> std::same_as<void>;
    { calendar.getReminders("", "") }               -> std::same_as<std::vector<std::string>>;
};

CELL_NAMESPACE_END

#endif  // CELL_CALENDAR_CONCEPTS_HPP
