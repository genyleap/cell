/*!
 * @file        calendar.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Calendar interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CALENDAR_ABSTRACT_HPP
#define CELL_CALENDAR_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @enum CalendarSystem
 * Enumeration representing various calendar systems used throughout history and across different cultures.
 */
enum class CalendarSystem : Types::u8
{
    Gregorian       = 0x0,       //!< The default calendar, used internationally.
    Julian          = 0x1,       //!< An ancient Roman calendar.
    Lunar           = 0x2,       //!< A calendar based on the cycles of the moon.
    Islamic         = 0x3,       //!< The Islamic (Hijri) calendar.
    Hebrew          = 0x4,       //!< The Hebrew calendar.
    Chinese         = 0x5,       //!< The Chinese calendar.
    Hindu           = 0x6,       //!< Hindu calendar.
    Mayan           = 0x7,       //!< Mayan calendar.
    Egyptian        = 0x8,       //!< Egyptian calendar.
    Persian         = 0x9,       //!< Persian (Islamic/Hijri-Solar) calendar.
    Ethiopian       = 0xA,       //!< Ethiopian calendar.
    Aztec           = 0xB,       //!< Aztec calendar.
    Inca            = 0xC,       //!< Inca calendar.
    Japanese        = 0xD,       //!< Japanese calendar.
    Korean          = 0xE,       //!< Korean calendar.
    Thai            = 0xF,       //!< Thai calendar.
    Zoroastrian     = 0x10,      //!< Zoroastrian calendar.
    AncientGreek    = 0x11,      //!< Ancient Greek calendar.
    Roman           = 0x12,      //!< Roman calendar.
    Babylonian      = 0x13       //!< Babylonian calendar.
};

/**
 * @class AbstractCalendar
 * @brief Abstract base class for calendar-related operations and functionality.
 *
 * This class defines a set of __cell_virtual methods that must be implemented by derived classes
 * to provide specific calendar functionalities. The class provides methods for date and time
 * calculations, timezone support, internationalization, holidays, historical dates, and more.
 *
 * The class is designed to be used as an interface or base class for concrete calendar
 * implementations. It provides a common set of methods that can be used interchangeably
 * with different calendar systems.
 */
class __cell_export AbstractCalendar {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractCalendar)

    /**
     * @brief Returns a vector of available calendars.
     *
     * @return A vector of strings representing available calendars.
     */
    __cell_virtual std::vector<std::string> availableCalendars() const = 0;

    /**
     * @brief Returns a formatted date string from the given year, month, and day.
     *
     * @param year The year value.
     * @param month The month value.
     * @param day The day value.
     * @return An optional string representing the formatted date string if the date is valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString dateFromParts(int year, int month, int day) const = 0;

    /**
     * @brief Converts the current date and time to a string representation based on the specified format.
     *
     * @param format The format string specifying the desired date and time format.
     * @return An optional string representing the formatted date and time string if successful; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString dateTimeToString(const std::string& format) const = 0;

    /**
     * @brief Returns the day of the week for the given date.
     *
     * @param date The date string.
     * @return An integer representing the day of the week (0-6, where 0 is Sunday).
     */
    __cell_virtual int dayOfWeek(const std::string& date) const = 0;

    /**
     * @brief Returns the number of days in the specified month and year.
     *
     * @param year The year value.
     * @param month The month value.
     * @return The number of days in the specified month and year.
     */
    __cell_virtual int daysInMonth(int year, int month) const = 0;

    /**
     * @brief Returns the number of days in the specified year.
     *
     * @param year The year value.
     * @return The number of days in the specified year.
     */
    __cell_virtual int daysInYear(int year) const = 0;

    /**
     * @brief Checks if the calendar has a year zero.
     *
     * @return True if the calendar has a year zero, false otherwise.
     */
    __cell_virtual bool hasYearZero() const = 0;

    /**
     * @brief Checks if the given year, month, and day form a valid date.
     *
     * @param year The year value.
     * @param month The month value.
     * @param day The day value.
     * @return True if the date is valid, false otherwise.
     */
    __cell_virtual bool isDateValid(int year, int month, int day) const = 0;

    /**
     * @brief Checks if the calendar is Gregorian.
     *
     * @return True if the calendar is Gregorian, false otherwise.
     */
    __cell_virtual bool isGregorian() const = 0;

    /**
     * @brief Checks if the given year is a leap year.
     *
     * @param year The year value.
     * @return True if the year is a leap year, false otherwise.
     */
    __cell_virtual bool isLeapYear(int year) const = 0;

    /**
     * @brief Checks if the calendar is lunar.
     *
     * @return True if the calendar is lunar, false otherwise.
     */
    __cell_virtual bool isLunar() const = 0;

    /**
     * @brief Checks if the calendar is Islamic.
     *
     * @return True if the calendar is Islamic, false otherwise.
     */
    __cell_virtual bool isIslamic() const = 0;

    /**
     * @brief Checks if the calendar is Hebrew.
     *
     * @return True if the calendar is Hebrew, false otherwise.
     */
    __cell_virtual bool isHebrew() const = 0;

    /**
     * @brief Checks if the calendar is Chinese.
     *
     * @return True if the calendar is Chinese, false otherwise.
     */
    __cell_virtual bool isChinese() const = 0;

    /**
     * @brief Checks if the given date string is valid.
     *
     * @param date The date string.
     * @return True if the date string is valid, false otherwise.
     */
    __cell_virtual bool isValid(const std::string& date) const = 0;

    /**
     * @brief Returns the maximum number of days in a month.
     *
     * @return The maximum number of days in a month.
     */
    __cell_virtual int maximumDaysInMonth() const = 0;

    /**
     * @brief Returns the maximum number of months in a year.
     *
     * @return The maximum number of months in a year.
     */
    __cell_virtual int maximumMonthsInYear() const = 0;

    /**
     * @brief Returns the minimum number of days in a month.
     *
     * @return The minimum number of days in a month.
     */
    __cell_virtual int minimumDaysInMonth() const = 0;

    /**
     * @brief Returns the name of the month for the given month value.
     *
     * @param month The month value.
     * @return An optional string representing the name of the month if the month value is valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString monthName(int month) const = 0;

    /**
     * @brief Returns the number of months in a year.
     *
     * @return The number of months in a year.
     */
    __cell_virtual int monthsInYear() const = 0;

    /**
     * @brief Returns the name of the calendar.
     *
     * @return An optional string representing the name of the calendar.
     */
    __cell_virtual Types::OptionalString name() const = 0;

    /**
     * @brief Returns a vector of integers representing the date parts from the given date string.
     *
     * @param date The date string.
     * @return A vector of integers representing the date parts [year, month, day].
     */
    __cell_virtual std::vector<int> partsFromDate(const std::string& date) const = 0;

    /**
     * @brief Returns the standalone name of the month for the given month value.
     *
     * @param month The month value.
     * @return An optional string representing the standalone name of the month if the month value is valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString standaloneMonthName(int month) const = 0;

    /**
     * @brief Returns the standalone name of the week day for the given day value.
     *
     * @param day The day value.
     * @return An optional string representing the standalone name of the week day if the day value is valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString standaloneWeekDayName(int day) const = 0;

    /**
     * @brief Returns the name of the week day for the given day value.
     *
     * @param day The day value.
     * @return An optional string representing the name of the week day if the day value is valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString weekDayName(int day) const = 0;


    /**
     * @brief Check if a date and time values are valid in the selected calendar.
     *
     * @param year The year value.
     * @param month The month value (1-12).
     * @param day The day value (1-31).
     * @param hour The hour value (0-23).
     * @param minute The minute value (0-59).
     * @param second The second value (0-59).
     *
     * @return True if the date and time values are valid, false otherwise.
     */
    __cell_virtual bool isDateTimeValid(int year, int month, int day, int hour, int minute, int second) const = 0;

    /**
     * @brief Returns the current timezone.
     *
     * @return An optional string representing the current timezone if set; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getTimezone() const = 0;

    /**
     * @brief Sets the timezone to the specified value.
     *
     * @param timezone The timezone string.
     */
    __cell_virtual void setTimezone(const std::string& timezone) = 0;

    /**
     * @brief Converts the given date to the specified timezone.
     *
     * @param date The date string.
     * @param timezone The timezone string.
     * @return An optional string representing the converted date in the specified timezone if successful; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString convertToTimezone(const std::string& date, const std::string& timezone) const = 0;

    /**
     * @brief Returns the localized name of the month for the given month value and language.
     *
     * @param month The month value.
     * @param language The language string.
     * @return An optional string representing the localized name of the month if the month value and language are valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getLocalizedMonthName(int month, const std::string& language) const = 0;

    /**
     * @brief Returns the localized name of the week day for the given day value and language.
     *
     * @param day The day value.
     * @param language The language string.
     * @return An optional string representing the localized name of the week day if the day value and language are valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getLocalizedWeekDayName(int day, const std::string& language) const = 0;

    /**
     * @brief Returns the localized representation of the given date for the specified language.
     *
     * @param date The date string.
     * @param language The language string.
     * @return An optional string representing the localized date if the date and language are valid; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getLocalizedDate(const std::string& date, const std::string& language) const = 0;

    /**
     * @brief Checks if the given date is a holiday.
     *
     * @param date The date string.
     * @return True if the date is a holiday, false otherwise.
     */
    __cell_virtual bool isHoliday(const std::string& date) const = 0;

    /**
     * @brief Returns a vector of holidays for the specified year.
     *
     * @param year The year value.
     * @return A vector of strings representing the holidays for the specified year.
     */
    __cell_virtual std::vector<std::string> getHolidays(int year) const = 0;

    /**
     * @brief Checks if the given date is a special date.
     *
     * @param date The date string.
     * @return True if the date is a special date, false otherwise.
     */
    __cell_virtual bool isSpecialDate(const std::string& date) const = 0;

    /**
     * @brief Returns a vector of special dates for the specified year.
     *
     * @param year The year value.
     * @return A vector of strings representing the special dates for the specified year.
     */
    __cell_virtual std::vector<std::string> getSpecialDates(int year) const = 0;

    /**
     * @brief Adds the specified number of days to the given date.
     *
     * @param date The date string.
     * @param days The number of days to add.
     * @return An optional string representing the resulting date after adding the days if successful; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString addDays(const std::string& date, int days) const = 0;

    /**
     * @brief Adds the specified number of months to the given date.
     *
     * @param date The date string.
     * @param months The number of months to add.
     * @return An optional string representing the resulting date after adding the months if successful; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString addMonths(const std::string& date, int months) const = 0;

    /**
     * @brief Adds the specified number of years to the given date.
     *
     * @param date The date string.
     * @param years The number of years to add.
     * @return An optional string representing the resulting date after adding the years if successful; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString addYears(const std::string& date, int years) const = 0;

    /**
     * @brief Calculates the difference in days between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in days between the two dates.
     */
    __cell_virtual int diffInDays(const std::string& date1, const std::string& date2) const = 0;

    /**
     * @brief Calculates the difference in months between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in months between the two dates.
     */
    __cell_virtual int diffInMonths(const std::string& date1, const std::string& date2) const = 0;

    /**
     * @brief Calculates the difference in years between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in years between the two dates.
     */
    __cell_virtual int diffInYears(const std::string& date1, const std::string& date2) const = 0;


    /**
     * @brief Returns the time of sunrise for the specified date, latitude, and longitude.
     *
     * @param date The date string.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     * @return The time of sunrise as a double value representing the number of hours since midnight if successful; otherwise, NaN.
     */
    __cell_virtual double getSunrise(const std::string& date, double latitude, double longitude) const = 0;

    /**
     * @brief Returns the time of sunset for the specified date, latitude, and longitude.
     *
     * @param date The date string.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     * @return The time of sunset as a double value representing the number of hours since midnight if successful; otherwise, NaN.
     */
    __cell_virtual double getSunset(const std::string& date, double latitude, double longitude) const = 0;

    /**
     * @brief Returns the moon phase for the specified date.
     *
     * @param date The date string.
     * @return The moon phase as a double value representing the phase in radians if successful; otherwise, NaN.
     */
    __cell_virtual double getMoonPhase(const std::string& date) const = 0;

    /**
     * @brief Checks if the given date is a historical date.
     *
     * @param date The date string.
     * @return True if the date is a historical date, false otherwise.
     */
    __cell_virtual bool isHistoricalDate(const std::string& date) const = 0;

    /**
     * @brief Returns the historical event for the specified date.
     *
     * @param date The date string.
     * @return An optional string representing the historical event if available; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getHistoricalEvent(const std::string& date) const = 0;


    /**
     * @brief Returns the current locale.
     *
     * @return An optional string representing the current locale if set; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getLocale() const = 0;

    /**
     * @brief Sets the locale to the specified value.
     *
     * @param locale The locale string.
     */
    __cell_virtual void setLocale(const std::string& locale) = 0;

    /**
     * @brief Returns the current date format.
     *
     * @return An optional string representing the current date format if set; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getDateFormat() const = 0;

    /**
     * @brief Sets the date format to the specified value.
     *
     * @param dateFormat The date format string.
     */
    __cell_virtual void setDateFormat(const std::string& dateFormat) = 0;

    /**
     * @brief Returns the current time format.
     *
     * @return An optional string representing the current time format if set; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getTimeFormat() const = 0;

    /**
     * @brief Sets the time format to the specified value.
     *
     * @param timeFormat The time format string.
     */
    __cell_virtual void setTimeFormat(const std::string& timeFormat) = 0;

    /**
     * @brief Returns the current date and time format.
     *
     * @return An optional string representing the current date and time format if set; otherwise, an empty optional.
     */
    __cell_virtual Types::OptionalString getDateTimeFormat() const = 0;

    /**
     * @brief Sets the date and time format to the specified value.
     *
     * @param dateTimeFormat The date and time format string.
     */
    __cell_virtual void setDateTimeFormat(const std::string& dateTimeFormat) = 0;

    /**
     * @brief Adds a recurring event with the specified details.
     *
     * @param eventName The name of the recurring event.
     * @param startDate The start date of the recurring event.
     * @param endDate The end date of the recurring event.
     * @param recurrenceRule The recurrence rule defining the pattern of the recurring event.
     */
    __cell_virtual void addRecurringEvent(const std::string& eventName, const std::string& startDate, const std::string& endDate, const std::string& recurrenceRule) = 0;

    /**
     * @brief Removes a recurring event with the specified name.
     *
     * @param eventName The name of the recurring event to remove.
     */
        __cell_virtual void removeRecurringEvent(const std::string& eventName) = 0;

    /**
     * @brief Returns a vector of recurring events between the specified start and end dates.
     *
     * @param startDate The start date to filter recurring events.
     * @param endDate The end date to filter recurring events.
     * @return A vector of strings representing the recurring events within the specified date range.
     */
    __cell_virtual std::vector<std::string> getRecurringEvents(const std::string& startDate, const std::string& endDate) const = 0;

    /**
     * @brief Sets a reminder for the specified event at the given reminder date and time.
     *
     * @param eventName The name of the event for which to set the reminder.
     * @param reminderDate The date of the reminder.
     * @param reminderTime The time of the reminder.
     */
    __cell_virtual void setReminder(const std::string& eventName, const std::string& reminderDate, const std::string& reminderTime) = 0;

    /**
     * @brief Removes the reminder for the specified event.
     *
     * @param eventName The name of the event for which to remove the reminder.
     */
    __cell_virtual void removeReminder(const std::string& eventName) = 0;

    /**
     * @brief Returns a vector of reminders between the specified start and end dates.
     *
     * @param startDate The start date to filter reminders.
     * @param endDate The end date to filter reminders.
     * @return A vector of strings representing the reminders within the specified date range.
     */
    __cell_virtual std::vector<std::string> getReminders(const std::string& startDate, const std::string& endDate) const = 0;
};

CELL_NAMESPACE_END

#endif  // CELL_CALENDAR_ABSTRACT_HPP
