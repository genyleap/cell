/*!
 * @file        calendar.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Calendar interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
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

enum class CalendarSystem : Types::u8
{
    Gregorian,      //!< The default calendar, used internationally.
    Julian,         //!< An ancient Roman calendar.
    Lunar,          //!< A calendar based on the cycles of the moon.
    Islamic,        //!< The Islamic (Hijri) calendar.
    Hebrew,         //!< The Hebrew calendar.
    Chinese         //!< The Chinese calendar.
};

/**
 * @class AbstractCalendar
 * @brief Abstract base class for calendar-related operations and functionality.
 *
 * This class defines a set of virtual methods that must be implemented by derived classes
 * to provide specific calendar functionalities. The class provides methods for date and time
 * calculations, timezone support, internationalization, holidays, historical dates, and more.
 *
 * The class is designed to be used as an interface or base class for concrete calendar
 * implementations. It provides a common set of methods that can be used interchangeably
 * with different calendar systems.
 */
class __cell_export AbstractCalendar {
public:
    /**
     * @brief Returns a vector of available calendars.
     *
     * @return A vector of strings representing available calendars.
     */
    virtual std::vector<std::string> availableCalendars() const = 0;

    /**
     * @brief Returns a formatted date string from the given year, month, and day.
     *
     * @param year The year value.
     * @param month The month value.
     * @param day The day value.
     * @return An optional string representing the formatted date string if the date is valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString dateFromParts(int year, int month, int day) const = 0;

    /**
     * @brief Converts the current date and time to a string representation based on the specified format.
     *
     * @param format The format string specifying the desired date and time format.
     * @return An optional string representing the formatted date and time string if successful; otherwise, an empty optional.
     */
    virtual Types::OptionalString dateTimeToString(const std::string& format) const = 0;

    /**
     * @brief Returns the day of the week for the given date.
     *
     * @param date The date string.
     * @return An integer representing the day of the week (0-6, where 0 is Sunday).
     */
    virtual int dayOfWeek(const std::string& date) const = 0;

    /**
     * @brief Returns the number of days in the specified month and year.
     *
     * @param year The year value.
     * @param month The month value.
     * @return The number of days in the specified month and year.
     */
    virtual int daysInMonth(int year, int month) const = 0;

    /**
     * @brief Returns the number of days in the specified year.
     *
     * @param year The year value.
     * @return The number of days in the specified year.
     */
    virtual int daysInYear(int year) const = 0;

    /**
     * @brief Checks if the calendar has a year zero.
     *
     * @return True if the calendar has a year zero, false otherwise.
     */
    virtual bool hasYearZero() const = 0;

    /**
     * @brief Checks if the given year, month, and day form a valid date.
     *
     * @param year The year value.
     * @param month The month value.
     * @param day The day value.
     * @return True if the date is valid, false otherwise.
     */
    virtual bool isDateValid(int year, int month, int day) const = 0;

    /**
     * @brief Checks if the calendar is Gregorian.
     *
     * @return True if the calendar is Gregorian, false otherwise.
     */
    virtual bool isGregorian() const = 0;

    /**
     * @brief Checks if the given year is a leap year.
     *
     * @param year The year value.
     * @return True if the year is a leap year, false otherwise.
     */
    virtual bool isLeapYear(int year) const = 0;

    /**
     * @brief Checks if the calendar is lunar.
     *
     * @return True if the calendar is lunar, false otherwise.
     */
    virtual bool isLunar() const = 0;

    /**
     * @brief Checks if the calendar is Islamic.
     *
     * @return True if the calendar is Islamic, false otherwise.
     */
    virtual bool isIslamic() const = 0;

    /**
     * @brief Checks if the calendar is Hebrew.
     *
     * @return True if the calendar is Hebrew, false otherwise.
     */
    virtual bool isHebrew() const = 0;

    /**
     * @brief Checks if the calendar is Chinese.
     *
     * @return True if the calendar is Chinese, false otherwise.
     */
    virtual bool isChinese() const = 0;

    /**
     * @brief Checks if the given date string is valid.
     *
     * @param date The date string.
     * @return True if the date string is valid, false otherwise.
     */
    virtual bool isValid(const std::string& date) const = 0;

    /**
     * @brief Returns the maximum number of days in a month.
     *
     * @return The maximum number of days in a month.
     */
    virtual int maximumDaysInMonth() const = 0;

    /**
     * @brief Returns the maximum number of months in a year.
     *
     * @return The maximum number of months in a year.
     */
    virtual int maximumMonthsInYear() const = 0;

    /**
     * @brief Returns the minimum number of days in a month.
     *
     * @return The minimum number of days in a month.
     */
    virtual int minimumDaysInMonth() const = 0;

    /**
     * @brief Returns the name of the month for the given month value.
     *
     * @param month The month value.
     * @return An optional string representing the name of the month if the month value is valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString monthName(int month) const = 0;

    /**
     * @brief Returns the number of months in a year.
     *
     * @return The number of months in a year.
     */
    virtual int monthsInYear() const = 0;

    /**
     * @brief Returns the name of the calendar.
     *
     * @return An optional string representing the name of the calendar.
     */
    virtual Types::OptionalString name() const = 0;

    /**
     * @brief Returns a vector of integers representing the date parts from the given date string.
     *
     * @param date The date string.
     * @return A vector of integers representing the date parts [year, month, day].
     */
    virtual std::vector<int> partsFromDate(const std::string& date) const = 0;

    /**
     * @brief Returns the standalone name of the month for the given month value.
     *
     * @param month The month value.
     * @return An optional string representing the standalone name of the month if the month value is valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString standaloneMonthName(int month) const = 0;

    /**
     * @brief Returns the standalone name of the week day for the given day value.
     *
     * @param day The day value.
     * @return An optional string representing the standalone name of the week day if the day value is valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString standaloneWeekDayName(int day) const = 0;

    /**
     * @brief Returns the name of the week day for the given day value.
     *
     * @param day The day value.
     * @return An optional string representing the name of the week day if the day value is valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString weekDayName(int day) const = 0;


    /**
     * @brief Returns the current timezone.
     *
     * @return An optional string representing the current timezone if set; otherwise, an empty optional.
     */
    virtual Types::OptionalString getTimezone() const = 0;

    /**
     * @brief Sets the timezone to the specified value.
     *
     * @param timezone The timezone string.
     */
    virtual void setTimezone(const std::string& timezone) = 0;

    /**
     * @brief Converts the given date to the specified timezone.
     *
     * @param date The date string.
     * @param timezone The timezone string.
     * @return An optional string representing the converted date in the specified timezone if successful; otherwise, an empty optional.
     */
    virtual Types::OptionalString convertToTimezone(const std::string& date, const std::string& timezone) const = 0;

    /**
     * @brief Returns the localized name of the month for the given month value and language.
     *
     * @param month The month value.
     * @param language The language string.
     * @return An optional string representing the localized name of the month if the month value and language are valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString getLocalizedMonthName(int month, const std::string& language) const = 0;

    /**
     * @brief Returns the localized name of the week day for the given day value and language.
     *
     * @param day The day value.
     * @param language The language string.
     * @return An optional string representing the localized name of the week day if the day value and language are valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString getLocalizedWeekDayName(int day, const std::string& language) const = 0;

    /**
     * @brief Returns the localized representation of the given date for the specified language.
     *
     * @param date The date string.
     * @param language The language string.
     * @return An optional string representing the localized date if the date and language are valid; otherwise, an empty optional.
     */
    virtual Types::OptionalString getLocalizedDate(const std::string& date, const std::string& language) const = 0;

    /**
     * @brief Checks if the given date is a holiday.
     *
     * @param date The date string.
     * @return True if the date is a holiday, false otherwise.
     */
    virtual bool isHoliday(const std::string& date) const = 0;

    /**
     * @brief Returns a vector of holidays for the specified year.
     *
     * @param year The year value.
     * @return A vector of strings representing the holidays for the specified year.
     */
    virtual std::vector<std::string> getHolidays(int year) const = 0;

    /**
     * @brief Checks if the given date is a special date.
     *
     * @param date The date string.
     * @return True if the date is a special date, false otherwise.
     */
    virtual bool isSpecialDate(const std::string& date) const = 0;

    /**
     * @brief Returns a vector of special dates for the specified year.
     *
     * @param year The year value.
     * @return A vector of strings representing the special dates for the specified year.
     */
    virtual std::vector<std::string> getSpecialDates(int year) const = 0;

    /**
     * @brief Adds the specified number of days to the given date.
     *
     * @param date The date string.
     * @param days The number of days to add.
     * @return An optional string representing the resulting date after adding the days if successful; otherwise, an empty optional.
     */
    virtual Types::OptionalString addDays(const std::string& date, int days) const = 0;

    /**
     * @brief Adds the specified number of months to the given date.
     *
     * @param date The date string.
     * @param months The number of months to add.
     * @return An optional string representing the resulting date after adding the months if successful; otherwise, an empty optional.
     */
    virtual Types::OptionalString addMonths(const std::string& date, int months) const = 0;

    /**
     * @brief Adds the specified number of years to the given date.
     *
     * @param date The date string.
     * @param years The number of years to add.
     * @return An optional string representing the resulting date after adding the years if successful; otherwise, an empty optional.
     */
    virtual Types::OptionalString addYears(const std::string& date, int years) const = 0;

    /**
     * @brief Calculates the difference in days between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in days between the two dates.
     */
    virtual int diffInDays(const std::string& date1, const std::string& date2) const = 0;

    /**
     * @brief Calculates the difference in months between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in months between the two dates.
     */
    virtual int diffInMonths(const std::string& date1, const std::string& date2) const = 0;

    /**
     * @brief Calculates the difference in years between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in years between the two dates.
     */
    virtual int diffInYears(const std::string& date1, const std::string& date2) const = 0;


    /**
     * @brief Returns the time of sunrise for the specified date, latitude, and longitude.
     *
     * @param date The date string.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     * @return The time of sunrise as a double value representing the number of hours since midnight if successful; otherwise, NaN.
     */
    virtual double getSunrise(const std::string& date, double latitude, double longitude) const = 0;

    /**
     * @brief Returns the time of sunset for the specified date, latitude, and longitude.
     *
     * @param date The date string.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     * @return The time of sunset as a double value representing the number of hours since midnight if successful; otherwise, NaN.
     */
    virtual double getSunset(const std::string& date, double latitude, double longitude) const = 0;

    /**
     * @brief Returns the moon phase for the specified date.
     *
     * @param date The date string.
     * @return The moon phase as a double value representing the phase in radians if successful; otherwise, NaN.
     */
    virtual double getMoonPhase(const std::string& date) const = 0;

    /**
     * @brief Checks if the given date is a historical date.
     *
     * @param date The date string.
     * @return True if the date is a historical date, false otherwise.
     */
    virtual bool isHistoricalDate(const std::string& date) const = 0;

    /**
     * @brief Returns the historical event for the specified date.
     *
     * @param date The date string.
     * @return An optional string representing the historical event if available; otherwise, an empty optional.
     */
    virtual Types::OptionalString getHistoricalEvent(const std::string& date) const = 0;


    /**
     * @brief Returns the current locale.
     *
     * @return An optional string representing the current locale if set; otherwise, an empty optional.
     */
    virtual Types::OptionalString getLocale() const = 0;

    /**
     * @brief Sets the locale to the specified value.
     *
     * @param locale The locale string.
     */
    virtual void setLocale(const std::string& locale) = 0;

    /**
     * @brief Returns the current date format.
     *
     * @return An optional string representing the current date format if set; otherwise, an empty optional.
     */
    virtual Types::OptionalString getDateFormat() const = 0;

    /**
     * @brief Sets the date format to the specified value.
     *
     * @param dateFormat The date format string.
     */
    virtual void setDateFormat(const std::string& dateFormat) = 0;

    /**
     * @brief Returns the current time format.
     *
     * @return An optional string representing the current time format if set; otherwise, an empty optional.
     */
    virtual Types::OptionalString getTimeFormat() const = 0;

    /**
     * @brief Sets the time format to the specified value.
     *
     * @param timeFormat The time format string.
     */
    virtual void setTimeFormat(const std::string& timeFormat) = 0;

    /**
     * @brief Returns the current date and time format.
     *
     * @return An optional string representing the current date and time format if set; otherwise, an empty optional.
     */
    virtual Types::OptionalString getDateTimeFormat() const = 0;

    /**
     * @brief Sets the date and time format to the specified value.
     *
     * @param dateTimeFormat The date and time format string.
     */
    virtual void setDateTimeFormat(const std::string& dateTimeFormat) = 0;

    /**
     * @brief Adds a recurring event with the specified details.
     *
     * @param eventName The name of the recurring event.
     * @param startDate The start date of the recurring event.
     * @param endDate The end date of the recurring event.
     * @param recurrenceRule The recurrence rule defining the pattern of the recurring event.
     */
    virtual void addRecurringEvent(const std::string& eventName, const std::string& startDate, const std::string& endDate, const std::string& recurrenceRule) = 0;

    /**
     * @brief Removes a recurring event with the specified name.
     *
     * @param eventName The name of the recurring event to remove.
     */
        virtual void removeRecurringEvent(const std::string& eventName) = 0;

    /**
     * @brief Returns a vector of recurring events between the specified start and end dates.
     *
     * @param startDate The start date to filter recurring events.
     * @param endDate The end date to filter recurring events.
     * @return A vector of strings representing the recurring events within the specified date range.
     */
    virtual std::vector<std::string> getRecurringEvents(const std::string& startDate, const std::string& endDate) const = 0;

    /**
     * @brief Sets a reminder for the specified event at the given reminder date and time.
     *
     * @param eventName The name of the event for which to set the reminder.
     * @param reminderDate The date of the reminder.
     * @param reminderTime The time of the reminder.
     */
    virtual void setReminder(const std::string& eventName, const std::string& reminderDate, const std::string& reminderTime) = 0;

    /**
     * @brief Removes the reminder for the specified event.
     *
     * @param eventName The name of the event for which to remove the reminder.
     */
    virtual void removeReminder(const std::string& eventName) = 0;

    /**
     * @brief Returns a vector of reminders between the specified start and end dates.
     *
     * @param startDate The start date to filter reminders.
     * @param endDate The end date to filter reminders.
     * @return A vector of strings representing the reminders within the specified date range.
     */
    virtual std::vector<std::string> getReminders(const std::string& startDate, const std::string& endDate) const = 0;

    /**
     * @brief Virtual destructor for the AbstractCalendar class.
     *
     * This destructor is responsible for properly cleaning up any resources
     * held by the AbstractCalendar object when it is being destroyed.
     * Subclasses should override this destructor if they need to perform
     * additional cleanup operations.
     */
    virtual ~AbstractCalendar();
};

CELL_NAMESPACE_END

#endif  // CELL_CALENDAR_ABSTRACT_HPP
