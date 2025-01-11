/*!
 * @file        cronjob.hpp
 * @brief       Cronjob manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_CRON_JOB
#define CELL_CRON_JOB

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef __has_include
# if __has_include("timezone.hpp")
#   include "timezone.hpp"
#else
#   error "Cell's "timezone.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell)

struct CronStruct final
{
    std::vector<int> minutes;       //!< The minutes field of the cron schedule.
    std::vector<int> hours;         //!< The hours field of the cron schedule.
    std::vector<int> daysOfMonth;   //!< The days of the month field of the cron schedule.
    std::vector<int> months;        //!< The months field of the cron schedule.
    std::vector<int> daysOfWeek;    //!< The days of the week field of the cron schedule.

    TimeZone timezone;              //!< The timezone for the cron schedule.

    std::function<void()> task;     //!< The callback function to execute the task.
    std::mutex mtx;                 //!< Mutex for thread-safe access.
};

/**
 * @class CronJob
 * @brief Represents a cron job that executes a task based on a cron schedule.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export CronJob
{
public:
    /**
     * @brief Constructs a CronJob object with the specified cron expression and task.
     * @param cronExpression The cron expression representing the schedule.
     * @param function The callback function to execute as the task.
     * @param delay The delay between executions (in seconds).
     * @param duration The duration of the program's execution (in seconds).
     * @param tz The timezone for the cron schedule.
     */
    CronJob(const std::string& cronExpression, const std::function<void()>& function, int delay, int duration, const std::string& tz);

    /**
     * @brief Starts executing the cron job based on the specified schedule.
     */
    void start();

private:
    /**
     * @brief Checks if the given time matches the cron schedule.
     * @param timeInfo The time information to match against the cron schedule.
     * @return True if the time matches the cron schedule, false otherwise.
     */
    bool match(const std::tm& timeInfo);

    /**
     * @brief Parses the cron expression and initializes the cron job fields.
     * @param cronExpression The cron expression representing the schedule.
     */
    void parseCronJob(const std::string& cron);

    /**
     * @brief Parses a field from the cron expression and stores the parsed values.
     * @param field The field to parse from the cron expression.
     * @param output The vector to store the parsed values.
     */
    void parseField(const std::string& field, std::vector<int>& output);

    /**
     * @brief Parses a step field from the cron expression and updates the start and step values.
     * @param field The step field to parse.
     * @param start The start value of the step field.
     * @param step The step value of the step field.
     */
    void parseStepField(const std::string& field, int& start, int& step);

    /**
     * @brief Parses a range field from the cron expression and updates the start and end values.
     * @param field The range field to parse.
     * @param start The start value of the range field.
     * @param end The end value of the range field.
     */
    void parseRangeField(const std::string& field, int& start, int& end);

    /**
     * @brief Checks if a field value matches the values specified in the cron schedule.
     * @param values The values specified in the cron schedule for a field.
     * @param fieldValue The value to match against the cron schedule.
     * @return True if the field value matches the cron schedule, false otherwise.
     */
    bool matchField(const std::vector<int>& values, int fieldValue);

    /**
     * @brief Increments the given time by 1 minute and handles rollover to the next hour, day, month, and year if necessary.
     * @param timeInfo The time to increment.
     */
    void incrementTime(std::tm& timeInfo);

    /**
     * @brief Parses a value from a token in the cron expression.
     * @param token The token to parse.
     * @return The parsed value.
     */
    int parseValue(const std::string& token);

    /**
     * @brief Returns the maximum value from a vector of values.
     * @param values The vector of values.
     * @return The maximum value.
     */
    int getMaxValue(const std::vector<int>& values);

    /**
     * @brief Calculates the delay until the next execution based on the given time.
     * @param timeInfo The current time.
     * @return The delay until the next execution (in seconds).
     */
    int getNextExecutionDelay(const std::tm& timeInfo);

private:
    CronStruct cronStruct;
    int executionDelay;             //!< The delay between executions (in seconds).
    int executionDuration;          //!< The duration of the program's execution (in seconds).
    System::EngineController engineController;
};

CELL_NAMESPACE_END

#endif  // CELL_CRON_JOB
