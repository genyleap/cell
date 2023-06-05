#if __has_include("calendar.hpp")
#   include "calendar.hpp"
#else
#   error "Cell's calendar was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::JSon;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Calendars)

GregorianCalendar::GregorianCalendar()
{
    m_calendarData.name = "Gregorian";
}

GregorianCalendar::~GregorianCalendar()
{
}

std::vector<std::string> GregorianCalendar::availableCalendars() const
{
    return m_calendarData.availableCalendars;
}

Types::OptionalString GregorianCalendar::dateFromParts(int year, int month, int day) const
{
    if (isDateValid(year, month, day)) {
        std::stringstream dateStream;
        dateStream << std::setw(4) << std::setfill('0') << year << "-"
                   << std::setw(2) << std::setfill('0') << month << "-"
                   << std::setw(2) << std::setfill('0') << day;
        return dateStream.str();
    }
    return __cell_null_optional;
}

Types::OptionalString GregorianCalendar::dateTimeToString(const std::string& format) const
{
    // Get the current date and time components
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime      = std::localtime(&currentTime);
    int year                = localTime->tm_year + 1900;
    int month               = localTime->tm_mon + 1;
    int day                 = localTime->tm_mday;
    int hour                = localTime->tm_hour;
    int minute              = localTime->tm_min;
    int second              = localTime->tm_sec;

    // Replace format placeholders with corresponding date and time values
    std::string formattedDateTime = format;
    formattedDateTime = Helper::replacePlaceholder(formattedDateTime, "YYYY", std::to_string(year));
    formattedDateTime = Helper::replacePlaceholder(formattedDateTime, "MM", std::to_string(month));
    formattedDateTime = Helper::replacePlaceholder(formattedDateTime, "DD", std::to_string(day));
    formattedDateTime = Helper::replacePlaceholder(formattedDateTime, "HH", std::to_string(hour));
    formattedDateTime = Helper::replacePlaceholder(formattedDateTime, "MM", std::to_string(minute));
    formattedDateTime = Helper::replacePlaceholder(formattedDateTime, "SS", std::to_string(second));

    return formattedDateTime;
}

int GregorianCalendar::dayOfWeek(const std::string& date) const
{
    // Assuming the date format is "YYYY-MM-DD"
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (month < 3) {
        month += 12;
        year--;
    }

    int century = year / 100;
    int yearOfCentury = year % 100;

    int dayOfWeek = (day + 2 * month + 3 * (month + 1) / 5 + yearOfCentury + yearOfCentury / 4 - yearOfCentury / 100 + yearOfCentury / 400 + century) % 7;

    // Adjust the result to have Sunday as 0 instead of 0
    if (dayOfWeek == 0) {
        dayOfWeek = 6;
    } else {
        dayOfWeek--;
    }

    return dayOfWeek;
}

int GregorianCalendar::daysInMonth(int year, int month) const
{
    if (month == 2) {
        if (isLeapYear(year)) {
            return 29;
        } else {
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int GregorianCalendar::daysInYear(int year) const
{
    if (isLeapYear(year)) {
        return 366;
    } else {
        return 365;
    }
}

bool GregorianCalendar::hasYearZero() const
{
    return false;
}

bool GregorianCalendar::isDateValid(int year, int month, int day) const
{
    // Check if the year is within a valid range
    if (year < GREGORIAN_CONSTANTS::MIN_VALID_YEAR || year > GREGORIAN_CONSTANTS::MAX_VALID_YEAR) {
        return false;
    }

    // Check if the month is within a valid range
    if (month < 1 || month > 12) {
        return false;
    }

    // Check if the day is within a valid range for the given month and year
    int maxDaysInMonth = daysInMonth(year, month);
    if (day < 1 || day > maxDaysInMonth) {
        return false;
    }

    // The date is valid
    return true;
}

bool GregorianCalendar::isGregorian() const
{
    return true;
}

bool GregorianCalendar::isLeapYear(int year) const
{
    if (year % 4 != 0) {
        return false;  // Not divisible by 4, not a leap year
    } else if (year % 100 != 0) {
        return true;   // Divisible by 4 but not by 100, a leap year
    } else if (year % 400 != 0) {
        return false;  // Divisible by 100 but not by 400, not a leap year
    } else {
        return true;   // Divisible by 400, a leap year
    }
}

bool GregorianCalendar::isLunar() const
{
    return false;
}

bool GregorianCalendar::isIslamic() const
{
    return false;
}

bool GregorianCalendar::isHebrew() const
{
    return false;
}

bool GregorianCalendar::isChinese() const
{
    return false;
}

bool GregorianCalendar::isValid(const std::string& date) const
{
    // Check if the date string has the correct format (YYYY-MM-DD)
    std::regex pattern("\\d{4}-\\d{2}-\\d{2}");
    if (!std::regex_match(date, pattern)) {
        return false;  // Invalid format
    }

    // Extract the year, month, and day components from the date string
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    // Check if the year is within the valid range
    if (year < GREGORIAN_CONSTANTS::MIN_VALID_YEAR || year > GREGORIAN_CONSTANTS::MAX_VALID_YEAR) {
        return false;  // Invalid year
    }

    // Check if the month is within the valid range
    if (month < 1 || month > 12) {
        return false;  // Invalid month
    }

    // Check if the day is within the valid range for the given month
    int days = daysInMonth(year, month);
    if (day < 1 || day > days) {
        return false;  // Invalid day
    }

    // All checks passed, the date is valid
    return true;
}

int GregorianCalendar::maximumDaysInMonth() const
{
    return 31;
}

int GregorianCalendar::maximumMonthsInYear() const
{
    return 12;
}

int GregorianCalendar::minimumDaysInMonth() const
{
    return 28;
}

Types::OptionalString GregorianCalendar::monthName(int month) const
{
    // Create a secure instance of the engine to access all features.
    auto& engine  = engineController.getEngine();

    // Getting the standard code of the user's current language
    auto language = createLanguageObject()->getLanguageCode();

    // Parse and retrieve the language-spec section.
    JsonDocument json(engine.translator().getLanguageSpec(language));

    // Retrieve the array of month names.
    const auto& array = json.getMultipleArray<std::string>(
        engine.meta()->returnView(GREGORIAN_CONSTANTS::CALENDARS),
        engine.meta()->returnView(GREGORIAN_CONSTANTS::CALENDAR_NAME),
        engine.meta()->returnView(GREGORIAN_CONSTANTS::CALENDAR_MONTHS)
        );

    // Check if the month index is within the valid range.
    if (month >= 0 && month < array.size())
    {
        // Return the month name at the specified index.
        return array[month];
    }

    // Return std::nullopt if the month index is out of range.
    return std::nullopt;
}

int GregorianCalendar::monthsInYear() const
{
    return 12; // In the Gregorian calendar, there are always 12 months in a year
}

Types::OptionalString GregorianCalendar::name() const
{
    return Types::OptionalString(m_calendarData.name);
}

std::vector<int> GregorianCalendar::partsFromDate(const std::string& date) const
{
    std::vector<int> parts;

    // Extract year, month, and day from the date string
    std::istringstream iss(date);
    std::string token;
    while (std::getline(iss, token, '-')) {
        parts.push_back(std::stoi(token));
    }

    return parts;
}

Types::OptionalString GregorianCalendar::standaloneMonthName(int month) const
{
    // Check if the month is within the valid range
    if (month < 1 || month > 12) {
        return __cell_null_optional;  // Invalid month, return an empty optional
    }

    // Define an array of standalone month names
    const std::array<std::string, 12> standaloneMonthNames = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Return the standalone month name for the given month
    return standaloneMonthNames[month - 1];
}

Types::OptionalString GregorianCalendar::standaloneWeekDayName(int day) const
{
    // Check if the day is within the valid range
    if (day < 1 || day > 7) {
        return __cell_null_optional;  // Invalid day, return an empty optional
    }

    // Define an array of standalone day names
    const std::array<std::string, 7> standaloneDayNames = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    // Return the standalone day name for the given day
    return standaloneDayNames[day - 1];

}

Types::OptionalString GregorianCalendar::weekDayName(int day) const
{
    // Check if the day is within the valid range
    if (day < 1 || day > 7) {
        return __cell_null_optional;  // Invalid day, return an empty optional
    }

    // Define an array of day names
    const std::array<std::string, 7> dayNames = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    // Return the day name for the given day
    return dayNames[day - 1];
}

bool GregorianCalendar::isDateTimeValid(int year, int month, int day, int hour, int minute, int second) const
{
    // Check if the year is within the valid range
    if (year < GREGORIAN_CONSTANTS::MIN_VALID_YEAR || year > GREGORIAN_CONSTANTS::MAX_VALID_YEAR) {
        return false;  // Invalid year
    }

    // Check if the month is within the valid range
    if (month < 1 || month > 12) {
        return false;  // Invalid month
    }

    // Check if the day is within the valid range
    if (day < 1 || day > daysInMonth(year, month)) {
        return false;  // Invalid day
    }

    // Check if the hour is within the valid range
    if (hour < 0 || hour > 23) {
        return false;  // Invalid hour
    }

    // Check if the minute is within the valid range
    if (minute < 0 || minute > 59) {
        return false;  // Invalid minute
    }

    // Check if the second is within the valid range
    if (second < 0 || second > 59) {
        return false;  // Invalid second
    }

    // The date and time values are valid
    return true;
}

Types::OptionalString GregorianCalendar::getTimezone() const
{
    std::string timezone = "GMT+0";  // Replace with your actual implementation

    return timezone;
}

void GregorianCalendar::setTimezone(const std::string& timezone)
{
    std::string current_timezone = getTimezone().value_or("");  // Get the current timezone

    // Update the current timezone with the provided timezone
    current_timezone = timezone;
}

Types::OptionalString GregorianCalendar::convertToTimezone(const std::string& datetime, const std::string& timezone)  const
{
    try {
        std::istringstream iss(datetime);
        std::tm tm = {};
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

        if (iss.fail()) {
            return __cell_null_optional;
        }

        std::time_t time = std::mktime(&tm);
        std::tm* utc_tm = std::gmtime(&time);

        int offset_seconds = Helper::getTimezoneOffset(timezone);

        std::time_t adjusted_time = std::mktime(utc_tm) + offset_seconds;
        std::tm* adjusted_tm = std::localtime(&adjusted_time);

        std::ostringstream oss;
        oss << std::put_time(adjusted_tm, "%Y-%m-%d %H:%M:%S");

        return oss.str();
    } catch (...) {
        return __cell_null_optional;
    }
}

Types::OptionalString GregorianCalendar::getLocalizedMonthName(int month, const std::string& language) const
{
    std::string localized_month_name = "";  // Replace with your actual implementation

    return localized_month_name;
}

Types::OptionalString GregorianCalendar::getLocalizedWeekDayName(int day, const std::string& language) const
{
    std::string localized_weekday_name = "";  // Replace with your actual implementation

    return localized_weekday_name;
}

Types::OptionalString GregorianCalendar::getLocalizedDate(const std::string& date, const std::string& language) const
{
    // Check if the specified language is "en_US"
    if (language == "en_US") {
        try {
            std::tm timeStruct = {};
            std::istringstream iss(date);
            iss >> std::get_time(&timeStruct, "%Y-%m-%d");

            // Check if the parsing was successful
            if (!iss.fail()) {
                // Set the locale to "en_US" for formatting the date
                std::locale locale("en_US.UTF-8");
                std::ostringstream oss;
                oss.imbue(locale);
                oss << std::put_time(&timeStruct, "%B %d, %Y");
                return oss.str();
            }
        } catch (...) {
            // Handle any exceptions thrown during parsing or formatting
            // Return an appropriate error message or take necessary action
            // For example:
            std::cerr << "Error occurred during date formatting." << std::endl;
        }
    }

    // Return empty optional for unsupported language or invalid date format
    return __cell_null_optional;
}

bool GregorianCalendar::isHoliday(const std::string& date) const
{
    std::vector<std::string> holidays = getHolidays(std::stoi(date.substr(0, 4)));

    return std::find(holidays.begin(), holidays.end(), date) != holidays.end();
}

std::vector<std::string> GregorianCalendar::getHolidays(int year) const
{
    std::vector<std::string> holidays;

    //!Todo...
    //!

    return holidays;
}

bool GregorianCalendar::isSpecialDate(const std::string& date) const
{
    // Replace the following example implementation with your own logic
    std::vector<std::string> special_dates = getSpecialDates(std::stoi(date.substr(0, 4)));
    return std::find(special_dates.begin(), special_dates.end(), date) != special_dates.end();
}

std::vector<std::string> GregorianCalendar::getSpecialDates(int year) const
{
    std::vector<std::string> special_dates;

    //!Todo...
    //!

    return special_dates;
}

Types::OptionalString GregorianCalendar::addDays(const std::string& date, int days) const
{
    std::tm time = {};
    std::istringstream ss(date);
    ss >> std::get_time(&time, "%Y-%m-%d");

    if (ss.fail()) {
        return __cell_null_optional; // Return empty optional if parsing fails
    }

    std::time_t t = std::mktime(&time);
    t += days * (60 * 60 * 24); // Add the specified number of seconds (days) to the time

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d");
    std::string result_date = oss.str();

    return result_date;
}

Types::OptionalString GregorianCalendar::addMonths(const std::string& date, int months) const
{
    std::tm time = {};
    std::istringstream ss(date);
    ss >> std::get_time(&time, "%Y-%m-%d");

    if (ss.fail()) {
        return __cell_null_optional; // Return empty optional if parsing fails
    }

    // Adjust the month value
    time.tm_mon += months;

    // Normalize the month value
    time.tm_year += time.tm_mon / 12;
    time.tm_mon %= 12;

    std::time_t t = std::mktime(&time);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d");
    std::string result_date = oss.str();

    return result_date;
}

Types::OptionalString GregorianCalendar::addYears(const std::string& date, int years) const {
    std::tm time = {};
    std::istringstream ss(date);
    ss >> std::get_time(&time, "%Y-%m-%d");

    if (ss.fail()) {
        return __cell_null_optional; // Return empty optional if parsing fails
    }

    // Adjust the year value
    time.tm_year += years;

    std::time_t t = std::mktime(&time);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d");
    std::string result_date = oss.str();

    return result_date;
}

int GregorianCalendar::diffInDays(const std::string& dateOne, const std::string& dateTwo) const
{
    // Convert date strings to tm structures
    std::tm timeOne = {};
    std::istringstream ss1(dateOne);
    ss1 >> std::get_time(&timeOne, "%Y-%m-%d");
    std::time_t t1 = std::mktime(&timeOne);

    std::tm timeTwo = {};
    std::istringstream ss2(dateTwo);
    ss2 >> std::get_time(&timeTwo, "%Y-%m-%d");
    std::time_t t2 = std::mktime(&timeTwo);

    // Calculate the difference in seconds
    std::time_t diffSeconds = std::difftime(t2, t1);

    // Convert the difference to days
    int diffDays = diffSeconds / (60 * 60 * 24);

    return diffDays;
}

int GregorianCalendar::diffInMonths(const std::string& dateOne, const std::string& dateTwo) const
{
    // Convert date strings to tm structures
    std::tm timeOne = {};
    std::istringstream ss1(dateOne);
    ss1 >> std::get_time(&timeOne, "%Y-%m-%d");
    std::time_t t1 = std::mktime(&timeOne);

    std::tm timeTwo = {};
    std::istringstream ss2(dateTwo);
    ss2 >> std::get_time(&timeTwo, "%Y-%m-%d");
    std::time_t t2 = std::mktime(&timeTwo);

    // Calculate the difference in months
    int diffYears = timeTwo.tm_year - timeOne.tm_year;
    int diffMonths = diffYears * 12 + timeTwo.tm_mon - timeOne.tm_mon;

    // Adjust the difference if the days of the second date are earlier than the first date
    if (timeTwo.tm_mday < timeOne.tm_mday) {
        diffMonths--;
    }

    return diffMonths;
}

int GregorianCalendar::diffInYears(const std::string& dateOne, const std::string& dateTwo) const
{
    // Convert date strings to tm structures
    std::tm timeOne = {};
    std::istringstream ss1(dateOne);
    ss1 >> std::get_time(&timeOne, "%Y-%m-%d");
    std::time_t t1 = std::mktime(&timeOne);

    std::tm timeTwo = {};
    std::istringstream ss2(dateTwo);
    ss2 >> std::get_time(&timeTwo, "%Y-%m-%d");
    std::time_t t2 = std::mktime(&timeTwo);

    // Calculate the difference in years
    int diffYears = timeTwo.tm_year - timeOne.tm_year;

    // Adjust the difference if the months and days of the second date are earlier than the first date
    if (timeTwo.tm_mon < timeOne.tm_mon || (timeTwo.tm_mon == timeOne.tm_mon && timeTwo.tm_mday < timeOne.tm_mday)) {
        diffYears--;
    }

    return diffYears;
}

double GregorianCalendar::getSunrise(const std::string& date, double latitude, double longitude) const {}

double GregorianCalendar::getSunset(const std::string& date, double latitude, double longitude) const {}

double GregorianCalendar::getMoonPhase(const std::string& date) const {}

bool GregorianCalendar::isHistoricalDate(const std::string& date) const {}

Types::OptionalString GregorianCalendar::getHistoricalEvent(const std::string& date) const {}

Types::OptionalString GregorianCalendar::getLocale() const {}

void GregorianCalendar::setLocale(const std::string& locale) {}

Types::OptionalString GregorianCalendar::getDateFormat() const {}

void GregorianCalendar::setDateFormat(const std::string& dateFormat) {}

Types::OptionalString GregorianCalendar::getTimeFormat() const {}

void GregorianCalendar::setTimeFormat(const std::string& timeFormat) {}

Types::OptionalString GregorianCalendar::getDateTimeFormat() const {}

void GregorianCalendar::setDateTimeFormat(const std::string& dateTimeFormat) {}

void GregorianCalendar::addRecurringEvent(const std::string& eventName, const std::string& startDate, const std::string& endDate, const std::string& recurrenceRule) {}

void GregorianCalendar::removeRecurringEvent(const std::string& eventName) {}

std::vector<std::string> GregorianCalendar::getRecurringEvents(const std::string& startDate, const std::string& endDate) const {}

void GregorianCalendar::setReminder(const std::string& eventName, const std::string& reminderDate, const std::string& reminderTime) {}

void GregorianCalendar::removeReminder(const std::string& eventName) {}

std::vector<std::string> GregorianCalendar::getReminders(const std::string& startDate, const std::string& endDate) const
{

}


CELL_NAMESPACE_END
