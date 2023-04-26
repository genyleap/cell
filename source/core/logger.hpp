/*!
 * Gen3 License
 *
 * @file        logger.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_LOGGER_HPP
#define CELL_LOGGER_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::eLogger)

/*!
 * \brief The LoggerType enum
 */
enum LoggerType : Types::u8
{
    Default     =   0x0,    ///<Print as default message.
    Info        =   0x1,    ///<Print as information message.
    Warning     =   0x2,    ///<Print as warning message.
    Critical    =   0x3,    ///<Print as critical (error) message.
    Failed      =   0x4,    ///<Print as failed message.
    Success     =   0x5,    ///<Print as success message.
    Done        =   0x6,    ///<Print as done message.
    Paused      =   0x7,    ///<Print as paused message.
    InProgress  =   0x8     ///<Print as in progress message.
};

enum class Mode : Types::u8
{
    User        =   0x0,    ///<Based on user log.
    Developer   =   0x1,    ///<Based on developer for debuging log.
    DataMining  =   0x2     ///<Based on data log.
};


#define Log(message, type)                                                                  \
Logger::echo(__cell_compiler_counter,                                                      \
             std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),        \
             __cell_compiler_line,                                                         \
             __cell_compiler_function,                                                     \
             __cell_compiler_file,                                                         \
             message, type)

class Logger;
/*!
 * \brief The Logger class
 */
class __cell_export Logger
{
public:
    Logger() = default;
    Logger(const Logger& rhsLogger) = delete;
    Logger(Logger&& rhsLogger) noexcept = delete;
    Logger& operator=(const Logger& rhsLogger) = delete;
    Logger& operator=(Logger&& rhsLogger) noexcept = delete;
    ~Logger();

    inline static Mode LoggerModel = Mode::User;

    /*!
     * \brief echo function will prints all data inline of usage!
     * \param counter as total called number.
     * \param occurTime shows the time of usage.
     * \param line shows the line of code.
     * \param function will gets function name.
     * \param file will gets file name [file.cpp] as example.
     * \param message gets message of information.
     * \param type gets type of log [success, warning and etc.]
     */
    __cell_maybe_unused static void echo(
        const uint          counter,
        const time_t        occurTime,
        const uint          line,
        std::string_view    function,
        std::string_view    file,
        std::string_view    message,
        const int           type);

};

CELL_NAMESPACE_END

#endif  // CELL_LOGGER_HPP
