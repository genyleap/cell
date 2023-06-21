//! Cell's Cron Jobs.
#if __has_include("cronjob.hpp")
#   include "cronjob.hpp"
#else
#   error "Cell's cronjob was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core/core was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell)

CronJob::CronJob(const std::string& cronExpression, const std::function<void()>& function, int delay, int duration, const std::string& tz)
    : cronStruct{}, executionDelay(delay), executionDuration(duration)
{
    cronStruct.task = function;
    cronStruct.timezone = TimeZone(tz);
    parseCronJob(cronExpression);
}

void CronJob::start()
{
    std::time_t startTime = std::time(__cell_nullptr);
    std::time_t endTime = startTime + executionDuration;

    while (std::time(__cell_nullptr) < endTime)
    {
        std::time_t currentTime = cronStruct.timezone.getCurrentTime();
        std::tm* timeInfo = std::localtime(&currentTime);

        if (match(*timeInfo))
        {
            std::lock_guard<std::mutex> lock(cronStruct.mtx);
           cronStruct.task();
        }

        std::this_thread::sleep_for(std::chrono::seconds(getNextExecutionDelay(*timeInfo)));
    }
}

bool CronJob::match(const std::tm& timeInfo)
{
    return (matchField(cronStruct.minutes, timeInfo.tm_min) &&
            matchField(cronStruct.hours, timeInfo.tm_hour) &&
            matchField(cronStruct.daysOfMonth, timeInfo.tm_mday) &&
            matchField(cronStruct.months, timeInfo.tm_mon + 1) &&
            matchField(cronStruct.daysOfWeek, timeInfo.tm_wday));
}

void CronJob::parseCronJob(const std::string& CronJob)
{
    std::istringstream iss(CronJob);
    std::string field;
    std::vector<std::string> fields;

    while (std::getline(iss, field, ' '))
    {
        fields.push_back(field);
    }

    if (fields.size() != 5)
    {
        Log("Invalid cron expression", LoggerType::Warning);
        throw std::invalid_argument("Invalid cron expression");
    }

    parseField(fields[0], cronStruct.minutes);
    parseField(fields[1], cronStruct.hours);
    parseField(fields[2], cronStruct.daysOfMonth);
    parseField(fields[3], cronStruct.months);
    parseField(fields[4], cronStruct.daysOfWeek);
}

void CronJob::parseField(const std::string& field, std::vector<int>& output)
{
    std::istringstream iss(field);
    std::string token;

    while (std::getline(iss, token, ','))
    {
        if (token == "*")
        {
            output.push_back(-1);
        }
        else if (token.find('/') != std::string::npos)
        {
            int start, step;
            parseStepField(token, start, step);
            for (int value = start; value <= getMaxValue(output); value += step)
            {
                output.push_back(value);
            }
        }
        else if (token.find('-') != std::string::npos)
        {
            int start, end;
            parseRangeField(token, start, end);
            for (int value = start; value <= end; ++value)
            {
                output.push_back(value);
            }
        }
        else
        {
            try
            {
                output.push_back(std::stoi(token));
            }
            catch (const Exception& e)
            {
                std::string r = "Error parsing token: " + FROM_CELL_STRING(token + ", " + e.what());
                Log(r, LoggerType::Critical);
                throw r;
            }
        }
    }

    std::sort(output.begin(), output.end());
    output.erase(std::unique(output.begin(), output.end()), output.end());
}

void CronJob::parseStepField(const std::string& field, int& start, int& step)
{
    std::string startToken = field.substr(0, field.find('/'));
    std::string stepToken = field.substr(field.find('/') + 1);

    start = parseValue(startToken);
    step = parseValue(stepToken);

    if (start >= getMaxValue(cronStruct.minutes) || step <= 0)
    {
        Log("Invalid cron expression", LoggerType::Warning);
        throw std::invalid_argument("Invalid cron expression");
    }
}

void CronJob::parseRangeField(const std::string& field, int& start, int& end)
{
    std::string startToken = field.substr(0, field.find('-'));
    std::string endToken = field.substr(field.find('-') + 1);

    start = parseValue(startToken);
    end = parseValue(endToken);

    if (start >= getMaxValue(cronStruct.minutes) || end >= getMaxValue(cronStruct.minutes) || start > end)
    {
        Log("Invalid cron expression", LoggerType::Warning);
        throw std::invalid_argument("Invalid cron expression");
    }
}

int CronJob::parseValue(const std::string& token)
{
    try
    {
        if (token == "*")
        {
            return -1;
        }

        return std::stoi(token);
    }
    catch (const Exception& e)
    {
        Log("Error parsing value: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
        throw e.what();
    }
}

int CronJob::getMaxValue(const std::vector<int>& values)
{
    if (!values.empty())
    {
        return values.back();
    }

    return 0;
}

bool CronJob::matchField(const std::vector<int>& values, int fieldValue)
{
    return values.empty() || std::binary_search(values.begin(), values.end(), fieldValue) || std::binary_search(values.begin(), values.end(), -1);
}

int CronJob::getNextExecutionDelay(const std::tm& timeInfo)
{
    std::time_t currentTime = std::mktime(const_cast<std::tm*>(&timeInfo));
    std::tm nextTimeInfo = timeInfo;
    std::time_t nextTime;

    do
    {
        incrementTime(nextTimeInfo);
        nextTime = std::mktime(&nextTimeInfo);
    } while (nextTime <= currentTime);

    return static_cast<int>(std::difftime(nextTime, currentTime));
}

void CronJob::incrementTime(std::tm& timeInfo)
{
    timeInfo.tm_min++;

    if (timeInfo.tm_min >= 60)
    {
        timeInfo.tm_min = 0;
        timeInfo.tm_hour++;
    }
    if (timeInfo.tm_hour >= 24)
    {
        timeInfo.tm_hour = 0;
        timeInfo.tm_mday++;
    }
    if (timeInfo.tm_mday > 31)
    {
        timeInfo.tm_mday = 1;
        timeInfo.tm_mon++;
    }
    if (timeInfo.tm_mon >= 12)
    {
        timeInfo.tm_mon = 0;
        timeInfo.tm_year++;
    }
}

CELL_NAMESPACE_END
