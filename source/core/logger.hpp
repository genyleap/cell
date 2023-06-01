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

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("core/filesystem.hpp")
#   include "core/filesystem.hpp"
#else
#   error "Cell's "core/filesystem.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Utility)

/*!
 * \brief The LoggerType enum
 */
enum LoggerType : Types::u8
{
    Default     =   0x0,    //!<Print as default message.
    Info        =   0x1,    //!<Print as information message.
    Warning     =   0x2,    //!<Print as warning message.
    Critical    =   0x3,    //!<Print as critical (error) message.
    Failed      =   0x4,    //!<Print as failed message.
    Success     =   0x5,    //!<Print as success message.
    Done        =   0x6,    //!<Print as done message.
    Paused      =   0x7,    //!<Print as paused message.
    InProgress  =   0x8     //!<Print as in progress message.
};

static constexpr std::string_view LogFolder         = "logs";
static constexpr std::string_view LogFilePrefix     = "log";
static constexpr std::string_view TraceFolder       = "trace";
static constexpr std::string_view TraceFilePrefix   = "trc";

struct FileFormats final
{
    static constexpr std::string_view Dedicated     = ".clog";
    static constexpr std::string_view RawText       = ".txt";
    static constexpr std::string_view Json          = ".json";
    static constexpr std::string_view Xml           = ".xml";
    static constexpr std::string_view Csv           = ".csv";
};

/**
 * @brief The OutputFormat enum
 * Dedicated format is an extension such as .clog, ._clog for engine.
 */
enum class OutputFormat : Types::u8 { Dedicated = 0x0, Json = 0x1, Xml = 0x2, RawText = 0x3, Csv = 0x4};

/**
 * @brief The ReportMode enum
 * User reports are from apps used by the current user.
 * System reports are from operating system components that affect all users.
 * If you’re logged in as an administrator user, you can view all reports.
 * If you’re not logged in as an administrator, you can only view user reports.
 */
enum ReportMode : Types::u8
{
    None        =   0x0,   //!< Logs from nothing.

    Crash       =   0x1,    //!< System and user reports about apps or processes that crash.
    //!< Crash report names have the .cips extension.

    Spin        =   0x2,    //!< System and user reports with details about app or process issues.
    //!< Spin report names have a .cspin extension.

    Log         =   0x3,    //!< System and user reports with information about events that occur when the system or specific apps are processing.
    //!< Log report names have an extension such as .clog, ._clog, or .its.

    Diagnostic  =   0x4,    //!< System and user reports with information about hardware resources, system response times, and more.
    //!< Diagnostic report names have an extension such as .cdiag or .cdpsub.
    Analytics   =   0x5,    //!< Contents of the Message Tracer Store data found at cell/logs/DiagnosticMessages.

    System      =   0x6     //!< Contents of the legacy system log file at /cell/logs/system.clog.

};

/**
 * @brief The Software enum
 */
enum Software : Types::u8
{
    Core, Modules, Plugins
};

/**
 * @brief The TraceMode enum
 */
enum class TraceMode : Types::u8
{
    None        =   0x0,   //!< Logs from nothing.
    Hardware    =   0x1,   //!< Logs from low level hardware.
    Software    =   0x2,   //!< Logs from core & high-level, modules and plugins.
    User        =   0x3,   //!< Logs from user actions.
    Mixed       =   0x4,   //!< Logs from all sections.
    Custom      =   0x5,   //!< Logs from custom sections.
    Other       =   0x6,   //!< Logs from other sections.
};

enum class Mode : Types::u8
{
    User        =   0x0,    //!<Based on user log.
    Developer   =   0x1,    //!<Based on developer for debuging log.
    DataMining  =   0x2     //!<Based on data log.
};


enum class Storage : Types::u8
{
    Disable    =   0x0,    //!< Disable (No writing).
    InFile     =   0x1,    //!< Write in file.
    External   =   0x2,    //!< Write in external storage.
    Database   =   0x3     //!< Write in database.
};

/**
 * @brief The ConfigStruct class
 */
struct ConfigStruct
{
    ReportMode      reportMode      {   ReportMode::System      };
    TraceMode       traceMode       {   TraceMode::Mixed        };
    OutputFormat    outputFormat    {   OutputFormat::RawText   };
    Storage         storage         {   Storage::Disable        };
};

#define Log(message, type)                                                                 \
Logger::echo(__cell_compiler_counter,                                                      \
             std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),       \
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
    Logger();
    Logger(const Logger& rhsLogger) = delete;
    Logger(Logger&& rhsLogger) noexcept = delete;
    Logger& operator=(const Logger& rhsLogger) = delete;
    Logger& operator=(Logger&& rhsLogger) noexcept = delete;
    ~Logger();

    inline static Mode LoggerModel = Mode::User;
    inline static Storage StorageMode = Storage::Disable;

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

    void set(const ConfigStruct& config);
    Types::Optional<ConfigStruct> get();
    void reset();

private:
    static FileSystem::FileManager fileManager;
    bool validateConfig(const ConfigStruct& config);
    void adjustConfig(ConfigStruct& config);
    static Types::Optional<ConfigStruct> configStruct;

};

/**
 * @brief The Tracer class
 */
class __cell_export Tracer {
public:
    Tracer();
    ~Tracer();

    void set(const ConfigStruct& config);

    Types::Optional<ConfigStruct> get();

    template<typename Func, typename... Args>
        requires std::invocable<Func, Args...> && (!std::is_same_v<std::invoke_result_t<Func, Args...>, void>)
    auto trace(Func&& func, Args&&... args) {
        auto startTime = std::chrono::steady_clock::now();

        std::string functionName = getFunctionName(func);
        log("Entering " + functionName);

        // Call the traced function
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        log("Exiting " + functionName + " - Elapsed Time: " + std::to_string(elapsedTime.count()) + "ms");

        return result;
    }

    template<typename Func, typename... Args>
        requires std::invocable<Func, Args...> && std::is_same_v<std::invoke_result_t<Func, Args...>, void>
    void trace(Func&& func, Args&&... args) {
        auto startTime = std::chrono::steady_clock::now();

        std::string functionName = getFunctionName(func);
        log("Entering " + functionName);

        // Call the traced function
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        log("Exiting " + functionName + " - Elapsed Time: " + std::to_string(elapsedTime.count()) + "ms");
    }

private:
    std::string m_filename {};
    std::ofstream m_filestream {};
    static Types::Optional<ConfigStruct> configStruct;
    void log(const std::string& message);
    bool validateConfig(const ConfigStruct& config);
    void adjustConfig(ConfigStruct& config);

    template<typename Func>
    std::string getFunctionName(Func&& func)
    {
        std::string functionName = __cell_compiler_pretty_function;
        return functionName;
    }
};

CELL_NAMESPACE_END

#endif  // CELL_LOGGER_HPP
