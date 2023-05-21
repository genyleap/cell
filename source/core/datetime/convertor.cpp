#if __has_include("convertor.hpp")
#   include "convertor.hpp"
#else
#   error "Cell's "convertor.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::DateTime)

std::time_t TimestampConverter::epochToUnix(std::chrono::seconds epochTime)
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(epochTime));
}

std::chrono::seconds TimestampConverter::unixToEpoch(std::time_t unixTime)
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::from_time_t(unixTime).time_since_epoch());
}

Types::OptionalString TimestampConverter::getRelativeTime(std::time_t unixTime)
{
    std::time_t currentTime = std::time(nullptr);
    std::time_t timeDifference = currentTime - unixTime;

    auto language = Multilangual::Language();
    auto lcode = language.getLanguageCode();
    const std::string pluralWord = safeTranslate(lcode,"core", "plural_word");

    if (timeDifference < 0) {
        return safeTranslate(lcode,"core", "in_the_future");
    } else if (timeDifference < 60) {
        return safeTranslate(lcode,"core", "afew_seconds_ago");
    } else if (timeDifference < 3600) {
        int minutes = timeDifference / 60;
        return Format::print(safeTranslate(lcode,"core", "minute"), minutes, (minutes > 1 ? pluralWord : ""));
    } else if (timeDifference < 86400) {
        int hours = timeDifference / 3600;
        return Format::print(safeTranslate(lcode,"core", "hour"), hours, (hours > 1 ? pluralWord : ""));
    } else if (timeDifference < 604800) {
        int days = timeDifference / 86400;
        return Format::print(safeTranslate(lcode,"core", "day"), days, (days > 1 ? pluralWord : ""));
    } else if (timeDifference < 2592000) {
        int weeks = timeDifference / 604800;
        return Format::print(safeTranslate(lcode,"core", "week"), weeks, (weeks > 1 ? pluralWord : ""));
    } else if (timeDifference < 31536000) {
        int months = timeDifference / 2592000;
        return Format::print(safeTranslate(lcode,"core", "month"), months, (months > 1 ? pluralWord : ""));
    } else {
        int years = timeDifference / 31536000;
        return Format::print(safeTranslate(lcode,"core", "year"), years, (years > 1 ? pluralWord : ""));
    }
}

Types::OptionalString TimestampConverter::getFormattedDate(std::time_t unixTime, const std::string& format)
{
    std::tm* timeInfo = std::localtime(&unixTime);
    std::stringstream ss;
    ss << std::put_time(timeInfo, format.c_str());
    std::string relativeTime = getRelativeTime(unixTime).value();
    ss<< relativeTime;
    return ss.str();
}

Types::OptionalString TimestampConverter::epochToHumanReadable(std::chrono::seconds epochTime, bool useGMT)
{
    std::time_t unixTime = epochToUnix(epochTime);
    std::tm* timeInfo;
    if (useGMT) {
        timeInfo = std::gmtime(&unixTime);
    } else {
        timeInfo = std::localtime(&unixTime);
    }
    std::stringstream ss;
    ss << std::put_time(timeInfo, "%A, %B %d, %Y %I:%M:%S %p");
    return ss.str();
}

Types::OptionalString TimestampConverter::epochToHumanReadable(std::chrono::seconds epochTime, const std::string& format, bool useGMT)
{
    std::time_t unixTime = epochToUnix(epochTime);
    std::tm* timeInfo;
    if (useGMT) {
        timeInfo = std::gmtime(&unixTime);
    } else {
        timeInfo = std::localtime(&unixTime);
    }
    std::stringstream ss;
    ss << std::put_time(timeInfo, format.c_str());
    return ss.str();
}

std::chrono::seconds TimestampConverter::humanReadableToEpoch(const std::string& humanReadableDate, bool useGMT)
{
    std::tm timeInfo = {};
    std::istringstream ss(humanReadableDate);
    if (useGMT) {
        ss >> std::get_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
    } else {
        ss >> std::get_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
        timeInfo.tm_isdst = -1; // Set daylight saving flag to -1 to let the system determine it.
    }

    std::time_t unixTime;
    if (useGMT) {
        unixTime = std::mktime(&timeInfo);
    } else {
        unixTime = std::mktime(&timeInfo) - timeInfo.tm_gmtoff;
    }

    return unixToEpoch(unixTime);
}

std::chrono::seconds TimestampConverter::humanReadableToEpoch(const std::string& humanReadableDate, const std::string& format, bool useGMT)
{
    std::tm timeInfo = {};
    std::istringstream ss(humanReadableDate);
    ss >> std::get_time(&timeInfo, format.c_str());
    if (useGMT) {
        return unixToEpoch(std::mktime(&timeInfo));
    } else {
        return unixToEpoch(std::mktime(&timeInfo)) + std::chrono::seconds(timeInfo.tm_gmtoff);
    }
}

Types::OptionalString TimestampConverter::getTimeDuration(std::chrono::seconds start, std::chrono::seconds end)
{
    auto language = Multilangual::Language();
    auto lcode = language.getLanguageCode();
    std::chrono::seconds duration = end - start;
    int seconds = duration.count();
    const std::string pluralWord = safeTranslate(lcode,"core", "plural_word");
    int days = seconds / 86400;
    seconds %= 86400;
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;
    std::stringstream ss;
    if (days > 0)
        ss << days << Format::print(safeTranslate(lcode,"core", "day"), days, (days > 1 ? pluralWord : "")) << ", ";
    if (hours > 0)
        ss << hours << Format::print(safeTranslate(lcode,"core", "hour"), hours, (hours > 1 ? pluralWord : "")) << ", ";
    if (minutes > 0)
        ss << minutes << Format::print(safeTranslate(lcode,"core", "minute"), minutes, (minutes > 1 ? pluralWord : "")) << ", ";
    ss << seconds << Format::print(safeTranslate(lcode,"core", "second"), seconds, (seconds > 1 ? pluralWord : ""));
    return ss.str();
}


CELL_NAMESPACE_END

