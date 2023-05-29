#if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
#endif

#if __has_include("terminal.hpp")
#   include "terminal.hpp"
#else
#   error "Cell's "terminal.hpp" was not found!"
#endif

#if __has_include("filesystem.hpp")
#   include "filesystem.hpp"
#else
#   error "Cell's "filesystem.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Terminal;

CELL_NAMESPACE_BEGIN(Cell::Logger)

void Logger::set(const ConfigStruct& config)
{
    configStruct = config;
    if(get().has_value()) {
        get().emplace(config);
    }
}

bool Logger::validateConfig(const ConfigStruct& config)
{
    // Perform validation checks on the configuration and return true if the configuration is valid, false otherwise
    // Ensure that the report mode and trace mode are not both set to None
    if (config.reportMode == ReportMode::None && config.traceMode == TraceMode::None)
    {
        return false;
    }
    return true;  // Configuration is considered valid
}

void Logger::adjustConfig(ConfigStruct& config)
{
    // Perform adjustments or modifications to the configuration if needed.
    // If the storage is set to Database and the output format is RawText, change it to Csv
    if (config.storage == Storage::Database)
    {
        if(config.outputFormat == OutputFormat::RawText || config.outputFormat == OutputFormat::Xml || config.outputFormat == OutputFormat::Json || config.outputFormat == OutputFormat::Dedicated)
        {
            config.outputFormat = OutputFormat::Csv;
        }
    }
}

Types::Optional<ConfigStruct> Logger::get()
{
    if (configStruct) {
        // Perform additional validation or modification before returning the configuration.
        if (validateConfig(*configStruct)) {
            // Optionally perform some modification or adjustment to the configuration.
            adjustConfig(*configStruct);
            return *configStruct;
        }
    }
    return __cell_null_optional;
}

Logger::Logger()
{
}

Logger::~Logger()
{
    std::ostream& streamInStyle  = std::cout;
    streamInStyle << NativeTerminal::Reset << __cell_newline;
}

FileSystem::FileManager fileManager = FileSystem::FileManager();

Types::Optional<ConfigStruct> Logger::configStruct = ConfigStruct();

void Logger::echo(const unsigned int    counter,
                  const time_t          occurTime,
                  const unsigned int    line,
                  std::string_view      function,
                  std::string_view      file,
                  std::string_view      message,
                  const int             type)
{
    std::thread::id threadId = std::this_thread::get_id();
    std::stringstream strThreadId;
    strThreadId << threadId;

    std::mutex           mutex_l;
    std::string          typeStr         = __cell_null_str;
    std::ostream&        streamInStyle   = std::cout;
    std::string          beginStyle      = __cell_null_str;
    std::string          endStyle        = __cell_null_str;

    namespace fs = std::filesystem;

    const std::string folderPath = LogFolder.data();

    std::string logfileTemp = folderPath + "/" + LogFilePrefix.data();

    //! Maybe we can produce the file based on time in this section.
    //! Use std::chrono...
    //! Todo...
    if(configStruct.value().outputFormat == OutputFormat::Dedicated)
        logfileTemp.append(FileFormats::Dedicated.data());
    if(configStruct.value().outputFormat == OutputFormat::RawText)
        logfileTemp.append(FileFormats::RawText.data());
    if(configStruct.value().outputFormat == OutputFormat::Json)
        logfileTemp.append(FileFormats::Json.data());
    if(configStruct.value().outputFormat == OutputFormat::Xml)
        logfileTemp.append(FileFormats::Xml.data());
    if(configStruct.value().outputFormat == OutputFormat::Csv)
        logfileTemp.append(FileFormats::Csv.data());

    // Create the folder if it does not exist
    if (!fs::exists(folderPath)) {
        if (!fs::create_directory(folderPath)) {
            (System::DeveloperMode::IsEnable) ? Log("Failed to create folder.", LoggerType::Critical) : DO_NOTHING;
            return;
        }
    }

    // Open the log file in append mode
    std::ofstream logFile(logfileTemp, std::ios::app);
    if (!logFile.is_open()) {
        (System::DeveloperMode::IsEnable) ? Log("Failed to open log file.", LoggerType::Critical) : DO_NOTHING;
    }

    switch (type) {
    case LoggerType::Default:
        typeStr     =  "Default";
        streamInStyle       << NativeTerminal::Default;
        beginStyle  = "\033[0m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Info:
        typeStr =  "Info" ;
        streamInStyle       << NativeTerminal::Info;
        beginStyle  = "\033[0;37m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Warning:
        typeStr =  "Warning" ;
        streamInStyle       << NativeTerminal::Warning;
        beginStyle  = "\033[0;33m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Critical:
        typeStr =  "Critical" ;
        streamInStyle       << NativeTerminal::Critical;
        beginStyle  = "\033[0;31m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Failed:
        typeStr =  "Failed" ;
        streamInStyle       << NativeTerminal::Error;
        beginStyle  = "\033[41m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Success:
        typeStr =  "Success" ;
        streamInStyle       << NativeTerminal::Success;
        beginStyle  = "\033[0;32m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Done:
        typeStr =  "Done" ;
        streamInStyle       << NativeTerminal::Done;
        beginStyle  = "\033[42m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::Paused:
        typeStr =  "Paused" ;
        streamInStyle       << NativeTerminal::Paused;
        beginStyle  = "\033[0;36m";
        endStyle    = "\033[0m";
        break;
    case LoggerType::InProgress:
        typeStr =  "InProgress" ;
        streamInStyle       << NativeTerminal::InProgress;
        beginStyle  = "\033[1;93m";
        endStyle    = "\033[0m";
        break;
    }

    if(LoggerModel == Mode::User) {

        streamInStyle << " => Log Id : [" << counter
                      << "] : ["  << typeStr << "] "
                      << message << " { DateTime: "
                      << std::put_time(localtime(&occurTime), "%Y/%m/%d %H:%M:%S") << " }"
                      << NativeTerminal::Reset << __cell_newline;

        if(configStruct->storage == Storage::Disable)
        {
            // Todo..
        }
        if(configStruct->storage == Storage::InFile)
        {
            if (logFile.is_open())
            {
                // Write the current time and the message to the file
                logFile << " => Log Id : [" << counter
                        << "] : ["  << typeStr << "] "
                        << message << " { DateTime: "
                        << std::put_time(localtime(&occurTime), "%Y/%m/%d %H:%M:%S") << " }"
                        << __cell_newline;
                // Close the file
                logFile.close();
            }
            else
            {
                (System::DeveloperMode::IsEnable) ? Log("Failed to open log file.", LoggerType::Critical) : DO_NOTHING;
            }
        }
        if(configStruct->storage == Storage::External)
        {
            // Todo..
        }
        if(configStruct->storage == Storage::Database)
        {
            // Todo..
        }

        std::lock_guard<std::mutex> lock(mutex_l);

    } else if(LoggerModel == Mode::Developer) {

        streamInStyle << " => Log Id : [" << counter  << "]"
                      << "[ Line : "  << line << "] "
                      << "[ Function : "  << function << "] "
                      << "[ Thread Id : "  << strThreadId.str() << "] "
                      << "[ File : "  << file << "] "
                      << "] : ["    << typeStr << "] "
                      << message    << " { DateTime: "
                      << std::put_time(localtime(&occurTime), "%Y/%m/%d %H:%M:%S") << " }"
                      << NativeTerminal::Reset << __cell_newline;

        if(configStruct->storage == Storage::Disable)
        {
            // Todo..
        }
        if(configStruct->storage == Storage::InFile)
        {
            if (logFile.is_open())
            {
                // Write the current time and the message to the file
                logFile << " => Log Id : [" << counter  << "]"
                        << "[ Line : "  << line << "] "
                        << "[ Function : "  << function << "] "
                        << "[ Thread Id : "  << strThreadId.str() << "] "
                        << "[ File : "  << file << "] "
                        << "] : ["    << typeStr << "] "
                        << message    << " { DateTime: "
                        << std::put_time(localtime(&occurTime), "%Y/%m/%d %H:%M:%S") << " }" << __cell_newline;
                // Close the file
                logFile.close();
            }
            else
            {
                (System::DeveloperMode::IsEnable) ? Log("Failed to open log file.", LoggerType::Critical) : DO_NOTHING;
            }

        }
        if(configStruct->storage == Storage::External)
        {
            // Todo..
        }
        if(configStruct->storage == Storage::Database)
        {
            // Todo..
        }

        std::lock_guard<std::mutex> lock(mutex_l);

    } else if(LoggerModel == Mode::DataMining) {

        streamInStyle << " => Log Id : [" << counter  << "]"
                      << "[ Line : "  << line << "] "
                      << "[ Function : "  << function << "] "
                      << "[ Thread Id : "  << strThreadId.str() << "] "
                      << "[ File : "  << file << "] "
                      << "] : ["    << typeStr << "] "
                      << message    << " { DateTime: "
                      << std::put_time(localtime(&occurTime), "%Y/%m/%d %H:%M:%S") << " }"
                      << NativeTerminal::Reset << __cell_newline;

        if(configStruct->storage == Storage::Disable)
        {
            // Todo..
        }
        if(configStruct->storage == Storage::InFile)
        {
            if (logFile.is_open())
            {
                // Write the current time and the message to the file
                logFile << " => Log Id : [" << counter  << "]"
                        << "[ Line : "  << line << "] "
                        << "[ Function : "  << function << "] "
                        << "[ Thread Id : "  << strThreadId.str() << "] "
                        << "[ File : "  << file << "] "
                        << "] : ["    << typeStr << "] "
                        << message    << " { DateTime: "
                        << std::put_time(localtime(&occurTime), "%Y/%m/%d %H:%M:%S") << " }" << __cell_newline;
                // Close the file
                logFile.close();
            }
            else
            {
                (System::DeveloperMode::IsEnable) ? Log("Failed to open log file.", LoggerType::Critical) : DO_NOTHING;
            }

        }
        if(configStruct->storage == Storage::External)
        {
            // Todo..
        }
        if(configStruct->storage == Storage::Database)
        {
            // Todo..
        }

        std::lock_guard<std::mutex> lock(mutex_l);
    }

    // Close the file
    logFile.close();
}

Tracer::Tracer()
{
    namespace fs = std::filesystem;

    const std::string folderPath = TraceFolder.data();

    std::string tracefileTemp = folderPath + "/" + TraceFilePrefix.data();

    //! Maybe we can produce the file based on time in this section.
    //! Use std::chrono...
    //! Todo...
    if(configStruct.value().outputFormat == OutputFormat::Dedicated)
        tracefileTemp.append(FileFormats::Dedicated.data());
    if(configStruct.value().outputFormat == OutputFormat::RawText)
        tracefileTemp.append(FileFormats::RawText.data());
    if(configStruct.value().outputFormat == OutputFormat::Json)
        tracefileTemp.append(FileFormats::Json.data());
    if(configStruct.value().outputFormat == OutputFormat::Xml)
        tracefileTemp.append(FileFormats::Xml.data());
    if(configStruct.value().outputFormat == OutputFormat::Csv)
        tracefileTemp.append(FileFormats::Csv.data());

    // Create the folder if it does not exist
    if (!fs::exists(folderPath)) {
        if (!fs::create_directory(folderPath)) {
            (System::DeveloperMode::IsEnable) ? Log("Failed to create folder.", LoggerType::Critical) : DO_NOTHING;
            return;
        }
    }

    // Open the log file in append mode
    m_filestream.open(tracefileTemp, std::ios::app);
    if (!m_filestream.is_open()) {
        (System::DeveloperMode::IsEnable) ? Log("Failed to open trace file.", LoggerType::Critical) : DO_NOTHING;
    }
}

Tracer::~Tracer() {
    if (m_filestream.is_open()) {
        m_filestream.close();
    }
}

Types::Optional<ConfigStruct> Tracer::configStruct = ConfigStruct();

void Tracer::set(const ConfigStruct& config)
{
    configStruct = config;
    if(get().has_value()) {
        get().emplace(config);
    }
}

void Tracer::log(const std::string& message)
{
    if (m_filestream.is_open()) {
        m_filestream << message << std::endl;
    }
}

bool Tracer::validateConfig(const ConfigStruct& config)
{
    // Perform validation checks on the configuration and return true if the configuration is valid, false otherwise
    // Ensure that the report mode and trace mode are not both set to None
    if (config.reportMode == ReportMode::None && config.traceMode == TraceMode::None)
    {
        return false;
    }
    return true;  // Configuration is considered valid
}

void Tracer::adjustConfig(ConfigStruct& config)
{
    // Perform adjustments or modifications to the configuration if needed.
    // If the storage is set to Database and the output format is RawText, change it to Csv
    if (config.storage == Storage::Database)
    {
        if(config.outputFormat == OutputFormat::RawText || config.outputFormat == OutputFormat::Xml || config.outputFormat == OutputFormat::Json || config.outputFormat == OutputFormat::Dedicated)
        {
            config.outputFormat = OutputFormat::Csv;
        }
    }
}

Types::Optional<ConfigStruct> Tracer::get()
{
    if (configStruct) {
        // Perform additional validation or modification before returning the configuration.
        if (validateConfig(*configStruct)) {
            // Optionally perform some modification or adjustment to the configuration.
            adjustConfig(*configStruct);
            return *configStruct;
        }
    }
    return __cell_null_optional;
}


CELL_NAMESPACE_END
