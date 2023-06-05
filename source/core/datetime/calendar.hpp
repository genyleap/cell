/*!
 * @file        calendar.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Calendar for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CALENDAR_HPP
#define CELL_CALENDAR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("abstracts/calendar/calendar.hpp")
#   include "abstracts/calendar/calendar.hpp"
#else
#   error "Cell's "abstracts/calendar/calendar.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Calendars)

/**
 * @brief A structure that holds calendar data.
 */
struct CalendarData final
{
    Types::OptionalString name          {}; //!< The name of the calendar.

    Types::uint dayOfWeek               {}; //!< The day of the week.
    Types::uint daysInMonth             {}; //!< The number of days in a month.
    Types::uint daysInYear              {}; //!< The number of days in a year.
    Types::uint minimumDaysInMonth      {}; //!< The minimum number of days in a month.
    Types::uint maximumDaysInMonth      {}; //!< The maximum number of days in a month.
    Types::uint maximumMonthsInYear     {}; //!< The maximum number of months in a year.
    Types::uint monthsInYear            {}; //!< The number of months in a year.
    bool        isSpecialDate           {}; //!< Indicates if the date is special.
    bool        isHoliday               {}; //!< Indicates if the date is a holiday.
    bool        hasYearZero             {}; //!< Indicates if the calendar has year zero.
    bool        isDateValid             {}; //!< Indicates if the date is valid.
    bool        isGregorian             {}; //!< Indicates if the calendar is Gregorian.
    bool        isLeapYear              {}; //!< Indicates if the year is a leap year.
    bool        isValid                 {}; //!< Indicates if the calendar data is valid.

    std::vector<std::string> availableCalendars; //!< Pointer to a vector of available calendars.
};

struct Helper
{
    static std::string replacePlaceholder(const std::string& format, const std::string& placeholder, const std::string& value)
    {
        std::string result = format;
        std::size_t pos = result.find(placeholder);
        while (pos != std::string::npos) {
            result.replace(pos, placeholder.length(), value);
            pos = result.find(placeholder, pos + value.length());
        }
        return result;
    }
    // Function to retrieve timezone offset for a given timezone at a specific time point
    static int getTimezoneOffset(const std::string& timezone)
    {
        if (timezone == "Asia/Tehran") {
            return 3 * 3600 + 30 * 60;
        } else if (timezone == "America/New_York") {
            return -5 * 3600;
        }
        //! Add more timezone offset retrievals as needed
        //! Todo..
        //!
        throw std::runtime_error("Unknown timezone: " + timezone);
    }
};

struct GREGORIAN_CONSTANTS final
{
    __cell_static_const_constexpr Types::uint MIN_VALID_YEAR  {1583};
    __cell_static_const_constexpr Types::uint MAX_VALID_YEAR  {9999};

    __cell_static_const_constexpr std::string_view CALENDARS        {"calendars"};
    __cell_static_const_constexpr std::string_view CALENDAR_NAME    {"gregorian"};
    __cell_static_const_constexpr std::string_view CALENDAR_MONTHS  {"months"};
    __cell_static_const_constexpr std::string_view CALENDAR_DAYS    {"daysname"};
};

/**
 * @brief The Gregorian class represents the Gregorian calendar system.
 */
class GregorianCalendar : public Abstracts::AbstractCalendar {
public:
    GregorianCalendar();
    ~GregorianCalendar();


    /**
     * @brief Returns a vector of available calendars.
     *
     * @return A vector of strings representing available calendars.
     */
    std::vector<std::string> availableCalendars() const override;

    /**
     * @brief Returns a formatted date string from the given year, month, and day.
     *
     * @param year The year value.
     * @param month The month value.
     * @param day The day value.
     * @return An optional string representing the formatted date string if the date is valid; otherwise, an empty optional.
     */
    Types::OptionalString dateFromParts(int year, int month, int day) const override;

    /**
     * @brief Converts the current date and time to a string representation based on the specified format.
     *
     * @param format The format string specifying the desired date and time format.
     * @return An optional string representing the formatted date and time string if successful; otherwise, an empty optional.
     */
    Types::OptionalString dateTimeToString(const std::string& format) const override;

    /**
     * @brief Returns the day of the week for the given date.
     *
     * @param date The date string.
     * @return An integer representing the day of the week (0-6, where 0 is Sunday).
     */
    int dayOfWeek(const std::string& date) const override;

    /**
     * @brief Returns the number of days in the specified month and year.
     *
     * @param year The year value.
     * @param month The month value.
     * @return The number of days in the specified month and year.
     */
    int daysInMonth(int year, int month) const override;

    /**
     * @brief Returns the number of days in the specified year.
     *
     * @param year The year value.
     * @return The number of days in the specified year.
     */
    int daysInYear(int year) const override;

    /**
     * @brief Checks if the calendar has a year zero.
     *
     * @return True if the calendar has a year zero, false otherwise.
     */
    bool hasYearZero() const override;

    /**
     * @brief Checks if the given year, month, and day form a valid date.
     *
     * @param year The year value.
     * @param month The month value.
     * @param day The day value.
     * @return True if the date is valid, false otherwise.
     */
    bool isDateValid(int year, int month, int day) const override;

    /**
     * @brief Checks if the calendar is Gregorian.
     *
     * @return True if the calendar is Gregorian, false otherwise.
     */
    bool isGregorian() const override;

    /**
     * @brief Checks if the given year is a leap year.
     *
     * @param year The year value.
     * @return True if the year is a leap year, false otherwise.
     */
    bool isLeapYear(int year) const override;

    /**
     * @brief Checks if the calendar is lunar.
     *
     * @return True if the calendar is lunar, false otherwise.
     */
    bool isLunar() const override;

    /**
     * @brief Checks if the calendar is Islamic.
     *
     * @return True if the calendar is Islamic, false otherwise.
     */
    bool isIslamic() const override;

    /**
     * @brief Checks if the calendar is Hebrew.
     *
     * @return True if the calendar is Hebrew, false otherwise.
     */
    bool isHebrew() const override;

    /**
     * @brief Checks if the calendar is Chinese.
     *
     * @return True if the calendar is Chinese, false otherwise.
     */
    bool isChinese() const override;

    /**
     * @brief Checks if the given date string is valid.
     *
     * @param date The date string.
     * @return True if the date string is valid, false otherwise.
     */
    bool isValid(const std::string& date) const override;

    /**
     * @brief Returns the maximum number of days in a month.
     *
     * @return The maximum number of days in a month.
     */
    int maximumDaysInMonth() const override;

    /**
     * @brief Returns the maximum number of months in a year.
     *
     * @return The maximum number of months in a year.
     */
    int maximumMonthsInYear() const override;

    /**
     * @brief Returns the minimum number of days in a month.
     *
     * @return The minimum number of days in a month.
     */
    int minimumDaysInMonth() const override;

    /**
     * @brief Returns the name of the month for the given month value.
     *
     * @param month The month value.
     * @return An optional string representing the name of the month if the month value is valid; otherwise, an empty optional.
     */
    Types::OptionalString monthName(int month) const override;

    /**
     * @brief Returns the number of months in a year.
     *
     * @return The number of months in a year.
     */
    int monthsInYear() const override;

    /**
     * @brief Returns the name of the calendar.
     *
     * @return An optional string representing the name of the calendar.
     */
    Types::OptionalString name() const override;

    /**
     * @brief Returns a vector of integers representing the date parts from the given date string.
     *
     * @param date The date string.
     * @return A vector of integers representing the date parts [year, month, day].
     */
    std::vector<int> partsFromDate(const std::string& date) const override;

    /**
     * @brief Returns the standalone name of the month for the given month value.
     *
     * @param month The month value.
     * @return An optional string representing the standalone name of the month if the month value is valid; otherwise, an empty optional.
     */
    Types::OptionalString standaloneMonthName(int month) const override;

    /**
     * @brief Returns the standalone name of the week day for the given day value.
     *
     * @param day The day value.
     * @return An optional string representing the standalone name of the week day if the day value is valid; otherwise, an empty optional.
     */
    Types::OptionalString standaloneWeekDayName(int day) const override;

    /**
     * @brief Returns the name of the week day for the given day value.
     *
     * @param day The day value.
     * @return An optional string representing the name of the week day if the day value is valid; otherwise, an empty optional.
     */
    Types::OptionalString weekDayName(int day) const override;


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
    bool isDateTimeValid(int year, int month, int day, int hour, int minute, int second) const override;

    /**
     * @brief Returns the current timezone.
     *
     * @return An optional string representing the current timezone if set; otherwise, an empty optional.
     */
    Types::OptionalString getTimezone() const override;

    /**
     * @brief Sets the timezone to the specified value.
     *
     * @param timezone The timezone string.
     */
    void setTimezone(const std::string& timezone) override;

    /**
     * @brief Converts the given date to the specified timezone.
     *
     * @param date The date string.
     * @param timezone The timezone string.
     * @return An optional string representing the converted date in the specified timezone if successful; otherwise, an empty optional.
     */
    Types::OptionalString convertToTimezone(const std::string& date, const std::string& timezone) const override;

    /**
     * @brief Returns the localized name of the month for the given month value and language.
     *
     * @param month The month value.
     * @param language The language string.
     * @return An optional string representing the localized name of the month if the month value and language are valid; otherwise, an empty optional.
     */
    Types::OptionalString getLocalizedMonthName(int month, const std::string& language) const override;

    /**
     * @brief Returns the localized name of the week day for the given day value and language.
     *
     * @param day The day value.
     * @param language The language string.
     * @return An optional string representing the localized name of the week day if the day value and language are valid; otherwise, an empty optional.
     */
    Types::OptionalString getLocalizedWeekDayName(int day, const std::string& language) const override;

    /**
     * @brief Returns the localized representation of the given date for the specified language.
     *
     * @param date The date string.
     * @param language The language string.
     * @return An optional string representing the localized date if the date and language are valid; otherwise, an empty optional.
     */
    Types::OptionalString getLocalizedDate(const std::string& date, const std::string& language) const override;

    /**
     * @brief Checks if the given date is a holiday.
     *
     * @param date The date string.
     * @return True if the date is a holiday, false otherwise.
     */
    bool isHoliday(const std::string& date) const override;

    /**
     * @brief Returns a vector of holidays for the specified year.
     *
     * @param year The year value.
     * @return A vector of strings representing the holidays for the specified year.
     */
    std::vector<std::string> getHolidays(int year) const override;

    /**
     * @brief Checks if the given date is a special date.
     *
     * @param date The date string.
     * @return True if the date is a special date, false otherwise.
     */
    bool isSpecialDate(const std::string& date) const override;

    /**
     * @brief Returns a vector of special dates for the specified year.
     *
     * @param year The year value.
     * @return A vector of strings representing the special dates for the specified year.
     */
    std::vector<std::string> getSpecialDates(int year) const override;

    /**
     * @brief Adds the specified number of days to the given date.
     *
     * @param date The date string.
     * @param days The number of days to add.
     * @return An optional string representing the resulting date after adding the days if successful; otherwise, an empty optional.
     */
    Types::OptionalString addDays(const std::string& date, int days) const override;

    /**
     * @brief Adds the specified number of months to the given date.
     *
     * @param date The date string.
     * @param months The number of months to add.
     * @return An optional string representing the resulting date after adding the months if successful; otherwise, an empty optional.
     */
    Types::OptionalString addMonths(const std::string& date, int months) const override;

    /**
     * @brief Adds the specified number of years to the given date.
     *
     * @param date The date string.
     * @param years The number of years to add.
     * @return An optional string representing the resulting date after adding the years if successful; otherwise, an empty optional.
     */
    Types::OptionalString addYears(const std::string& date, int years) const override;

    /**
     * @brief Calculates the difference in days between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in days between the two dates.
     */
    int diffInDays(const std::string& date1, const std::string& date2) const override;

    /**
     * @brief Calculates the difference in months between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in months between the two dates.
     */
    int diffInMonths(const std::string& date1, const std::string& date2) const override;

    /**
     * @brief Calculates the difference in years between two dates.
     *
     * @param date1 The first date string.
     * @param date2 The second date string.
     * @return The difference in years between the two dates.
     */
    int diffInYears(const std::string& date1, const std::string& date2) const override;

    /**
     * @brief Returns the time of sunrise for the specified date, latitude, and longitude.
     *
     * @param date The date string.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     * @return The time of sunrise as a double value representing the number of hours since midnight if successful; otherwise, NaN.
     */
    double getSunrise(const std::string& date, double latitude, double longitude) const override;

    /**
     * @brief Returns the time of sunset for the specified date, latitude, and longitude.
     *
     * @param date The date string.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     * @return The time of sunset as a double value representing the number of hours since midnight if successful; otherwise, NaN.
     */
    double getSunset(const std::string& date, double latitude, double longitude) const override;

    /**
     * @brief Returns the moon phase for the specified date.
     *
     * @param date The date string.
     * @return The moon phase as a double value representing the phase in radians if successful; otherwise, NaN.
     */
    double getMoonPhase(const std::string& date) const override;

    /**
     * @brief Checks if the given date is a historical date.
     *
     * @param date The date string.
     * @return True if the date is a historical date, false otherwise.
     */
    bool isHistoricalDate(const std::string& date) const override;

    /**
     * @brief Returns the historical event for the specified date.
     *
     * @param date The date string.
     * @return An optional string representing the historical event if available; otherwise, an empty optional.
     */
    Types::OptionalString getHistoricalEvent(const std::string& date) const override;


    /**
     * @brief Returns the current locale.
     *
     * @return An optional string representing the current locale if set; otherwise, an empty optional.
     */
    Types::OptionalString getLocale() const override;

    /**
     * @brief Sets the locale to the specified value.
     *
     * @param locale The locale string.
     */
    void setLocale(const std::string& locale) override;

    /**
     * @brief Returns the current date format.
     *
     * @return An optional string representing the current date format if set; otherwise, an empty optional.
     */
    Types::OptionalString getDateFormat() const override;

    /**
     * @brief Sets the date format to the specified value.
     *
     * @param dateFormat The date format string.
     */
    void setDateFormat(const std::string& dateFormat) override;

    /**
     * @brief Returns the current time format.
     *
     * @return An optional string representing the current time format if set; otherwise, an empty optional.
     */
    Types::OptionalString getTimeFormat() const override;

    /**
     * @brief Sets the time format to the specified value.
     *
     * @param timeFormat The time format string.
     */
    void setTimeFormat(const std::string& timeFormat) override;

    /**
     * @brief Returns the current date and time format.
     *
     * @return An optional string representing the current date and time format if set; otherwise, an empty optional.
     */
    Types::OptionalString getDateTimeFormat() const override;

    /**
     * @brief Sets the date and time format to the specified value.
     *
     * @param dateTimeFormat The date and time format string.
     */
    void setDateTimeFormat(const std::string& dateTimeFormat) override;

    /**
     * @brief Adds a recurring event with the specified details.
     *
     * @param eventName The name of the recurring event.
     * @param startDate The start date of the recurring event.
     * @param endDate The end date of the recurring event.
     * @param recurrenceRule The recurrence rule defining the pattern of the recurring event.
     */
    void addRecurringEvent(const std::string& eventName, const std::string& startDate, const std::string& endDate, const std::string& recurrenceRule) override;

    /**
     * @brief Removes a recurring event with the specified name.
     *
     * @param eventName The name of the recurring event to remove.
     */
    void removeRecurringEvent(const std::string& eventName) override;

    /**
     * @brief Returns a vector of recurring events between the specified start and end dates.
     *
     * @param startDate The start date to filter recurring events.
     * @param endDate The end date to filter recurring events.
     * @return A vector of strings representing the recurring events within the specified date range.
     */
    std::vector<std::string> getRecurringEvents(const std::string& startDate, const std::string& endDate) const override;

    /**
     * @brief Sets a reminder for the specified event at the given reminder date and time.
     *
     * @param eventName The name of the event for which to set the reminder.
     * @param reminderDate The date of the reminder.
     * @param reminderTime The time of the reminder.
     */
    void setReminder(const std::string& eventName, const std::string& reminderDate, const std::string& reminderTime) override;

    /**
     * @brief Removes the reminder for the specified event.
     *
     * @param eventName The name of the event for which to remove the reminder.
     */
    void removeReminder(const std::string& eventName) override;

    /**
     * @brief Returns a vector of reminders between the specified start and end dates.
     *
     * @param startDate The start date to filter reminders.
     * @param endDate The end date to filter reminders.
     * @return A vector of strings representing the reminders within the specified date range.
     */
    std::vector<std::string> getReminders(const std::string& startDate, const std::string& endDate) const override;

private:
    CalendarData m_calendarData;
    System::EngineController engineController;
};

/**
 * @brief The CalendarContainer class allows you to register and retrieve different types of calendars. Here's an overview of what the class does:
 *
 * - The class maintains an `std::unordered_map` named `calendars`, which stores unique pointers to instances of calendar objects. The keys in the map are string names associated with each calendar.
 * - The `registerCalendar` function template allows you to register a calendar with a given name. The template parameter `CalendarType` represents the type of calendar you want to register. It must be derived from the `Cell::Abstracts::AbstractCalendar` base class. The function creates a new instance of the specified calendar type using `std::make_unique` and associates it with the provided name in the `calendars` map.
 * - The `getCalendar` function template retrieves a calendar by its name. It takes the template parameter `CalendarType`, representing the type of calendar you want to retrieve, and the name of the calendar. It returns an `std::optional` containing a pointer to the requested calendar if it exists in the map. The function performs a dynamic cast to ensure that the retrieved calendar object is of the specified type.
 * - The `getAllCalendars` function returns a vector of pointers to all registered calendar instances. It iterates over the `calendars` map and collects the pointers to the calendar objects, which are stored in the `allCalendars` vector.
 *
 * In summary, the `CalendarContainer` class provides a convenient way to register and retrieve different types of calendars by name.
 * It allows for flexible management of calendar objects within the container.
 *
 */
class CalendarContainer {
private:
    std::unordered_map<std::string, std::unique_ptr<Cell::Abstracts::AbstractCalendar>> calendars;

public:
    /*!
     * \brief Register a calendar with a given name.
     * \tparam CalendarType The type of the calendar to register.
     * \param name The name of the calendar.
     * \throws std::runtime_error if the CalendarType is not default constructible.
     * \note The CalendarType must be derived from Cell::Abstracts::AbstractCalendar.
     */
    template <typename CalendarType>
        requires std::derived_from<CalendarType, Cell::Abstracts::AbstractCalendar>
    void registerCalendar(const std::string& name) {
        static_assert(std::is_default_constructible_v<CalendarType>,
                      "CalendarType must be default constructible");
        calendars[name] = std::make_unique<CalendarType>();
    }

    /*!
     * \brief Get a calendar by name.
     * \tparam CalendarType The type of the calendar to retrieve.
     * \param name The name of the calendar.
     * \return A pointer to the requested calendar, or std::nullopt if the calendar was not found.
     * \note The CalendarType must be derived from Cell::Abstracts::AbstractCalendar.
     */
    template <typename CalendarType>
        requires std::derived_from<CalendarType, Cell::Abstracts::AbstractCalendar>
    std::optional<CalendarType*> getCalendar(const std::string& name)
    {
        auto it = calendars.find(name);
        if (it != calendars.end()) {
            Cell::Abstracts::AbstractCalendar* calendarPtr = it->second.get();
            return dynamic_cast<CalendarType*>(calendarPtr);
        }
        return std::nullopt;
    }

    /*!
     * \brief Get all registered calendar classes.
     * \return A vector of pointers to all registered calendar instances.
     */
    std::vector<Cell::Abstracts::AbstractCalendar*> getAllCalendars() const {
        std::vector<Cell::Abstracts::AbstractCalendar*> allCalendars;
        for (const auto& pair : calendars) {
            allCalendars.push_back(pair.second.get());
        }
        return allCalendars;
    }
};

CELL_NAMESPACE_END

#endif  // CELL_CALENDAR_HPP
