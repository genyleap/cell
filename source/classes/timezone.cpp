//! Cell's Tasks.
#if __has_include("timezone.hpp")
#   include "timezone.hpp"
#else
#   error "Cell's timezone was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

TimeZone::TimeZone() : timezone(__cell_null_str)
{
}

TimeZone::TimeZone(const std::string& tz)
    : timezone(tz)
{
}

std::time_t TimeZone::getCurrentTime() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm* timeInfo;
    if (!timezone.empty())
    {
        timeInfo = std::localtime(&currentTime);
        std::istringstream ss(timezone);
        int offsetHours = 0;
        int offsetMinutes = 0;
        char colon;
        ss >> offsetHours >> colon >> offsetMinutes;
        int totalOffsetMinutes = offsetHours * 60 + offsetMinutes;
        int adjustedMinutes = timeInfo->tm_min + totalOffsetMinutes;
        int extraHours = adjustedMinutes / 60;
        int finalMinutes = adjustedMinutes % 60;
        timeInfo->tm_hour = (timeInfo->tm_hour + extraHours) % 24;
        timeInfo->tm_min = finalMinutes;
        currentTime = std::mktime(timeInfo);
    }
    else
    {
        timeInfo = std::localtime(&currentTime);
    }

    return currentTime;
}

CELL_NAMESPACE_END
