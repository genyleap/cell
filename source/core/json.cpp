#ifdef __has_include
# if __has_include("json.hpp")
#   include "json.hpp"
#define header_is_avaialble
#else
#   error "Cell's json.hpp was not found!"
#undef header_is_avaialble
# endif
#endif

#ifdef header_is_avaialble

#ifdef __has_include
# if __has_include(<core>)
#   include <core>
#else
#   error "Cell's <core> was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("filesystem.hpp")
#   include "filesystem.hpp"
#else
#   error "Cell's "filesystem.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
# endif
#endif


CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::FileSystem;
CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::JSon)

JsonParser::JsonParser()
{
#ifdef USE_BOOST
    Log("Initialized Json engine: " + FROM_CELL_STRING(ENGINE_BOOST) + "::json", LoggerType::Success);
#else
    Log("Initialized Json engine: " + FROM_CELL_STRING(ENGINE_DEFAULT) + "[Default JsonCpp] ", LoggerType::Success);
#endif
}

JsonParser::~JsonParser()
{
}

bool JsonParser::parse(const JSonType& data, const InputType inputType) __cell_noexcept
{
#ifdef USE_BOOST
    try {
        auto fileIO = FileIO();
        switch (inputType) {
        case InputType::RawData:
            m_root = boost::json::parse(std::get<std::string>(data));
            break;
        case InputType::File:
            auto fileIO = FileIO();
            if (!fileIO.open(std::get<std::string>(data)))
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to open: " + FROM_CELL_STRING(std::get<std::string>(data)), LoggerType::Critical);
                }
            } else {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json File opened!", LoggerType::Success);
                }
            }
            auto data = fileIO.readAll();
            if (data.empty())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to read data from file", LoggerType::Critical);
                }
                if(fileIO.close())
                {
                    if(DeveloperMode::IsEnable)
                    {
                        Log("Json file closed!", LoggerType::Critical);
                    }
                }
            }
            if(fileIO.close())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json file closed!", LoggerType::Critical);
                }
            }
            m_root = boost::json::parse(data);
            break;
        }
        return true;
    } catch (const boost::json::error_code& e) {
        if(DeveloperMode::IsEnable) {
            Log("Parse error: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
        }
        return false;
    }
#else
    Json::Reader reader{};
    try {
        auto fileIO = FileIO();
        switch (inputType) {
        case InputType::RawData:
            reader.parse(std::get<std::string>(data), m_root);
            break;
        case InputType::File:
            auto fileIO = FileIO();
            if (!fileIO.open(std::get<std::string>(data)))
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to open: " + FROM_CELL_STRING(std::get<std::string>(data)), LoggerType::Critical);
                }
            } else {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json File opened!", LoggerType::Success);
                }
            }
            auto data = fileIO.readRawAll();
            if (!data.is_open())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to read data from file", LoggerType::Critical);
                }
                if(fileIO.close())
                {
                    if(DeveloperMode::IsEnable)
                    {
                        Log("Json file closed!", LoggerType::Critical);
                    }
                }
            }
            if(fileIO.close())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json file closed!", LoggerType::Critical);
                }
            }
            Json::CharReaderBuilder builder;
            if(!Json::parseFromStream(builder, data, &m_root, nullptr))
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Error on json file", LoggerType::Critical);
                }
            }
            break;
        }
        return true;
    } catch (const Json::Exception& e) {
        if(DeveloperMode::IsEnable)
        {
            Log("Parse error: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
        }
        return false;
    }
#endif
}

bool JsonParser::parse(const JSonType& data) __cell_noexcept
{
#ifdef USE_BOOST
    try {
        if (std::holds_alternative<std::string>(data))
        {
            m_root = boost::json::parse(std::get<std::string>(data));
        }
        if (std::holds_alternative<std::ifstream>(data))
        {
            auto fileIO = FileIO();
            if (!fileIO.open(std::get<std::string>(data)))
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to open: " + FROM_CELL_STRING(std::get<std::string>(data)), LoggerType::Critical);
                }
            }
            auto data = fileIO.readAll();
            if (data.empty())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to read data from file", LoggerType::Critical);
                }
                if(fileIO.close())
                {
                    if(DeveloperMode::IsEnable)
                    {
                        Log("Json file closed!", LoggerType::Critical);
                    }
                }
            }
            if(fileIO.close())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json file closed!", LoggerType::Critical);
                }
            }
            m_root = boost::json::parse(data);
        }
        return true;
    } catch (const boost::json::error_code& e) {
        if(DeveloperMode::IsEnable) {
            Log("Parse error: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
        }
        return false;
    }
#else
    Json::Reader reader{};
    try {
        reader.parse(std::get<std::string>(data), m_root);
        return true;
    } catch (const Json::Exception& e) {
        if(DeveloperMode::IsEnable)
        {
            Log("Parse error: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
        }
        return false;
    }
#endif
}

bool JsonParser::contains(const std::string& key) __cell_noexcept
{
#if defined(USE_BOOST)
    if (m_root.is_object()) {
        return m_root.as_object().find(key) != m_root.as_object().end();
    } else {
        if(DeveloperMode::IsEnable)
        {
            eLogger::Log("Parse error: " + FROM_CELL_STRING("Root is not an object."), eLogger::LoggerType::Critical);
        }
        return false;
    }
#else
    return m_root.isMember(key);
#endif
}

JSonValue JsonParser::get(const std::string& key) __cell_noexcept
{
#if defined(USE_BOOST)
    if (m_root.is_object()) {
        auto it = m_root.as_object().find(key);
        if (it != m_root.as_object().end()) {
            return it->value();
        } else {
            if(DeveloperMode::IsEnable)
            {
                eLogger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), eLogger::LoggerType::Critical);
            }
            return {};
        }
    } else {
        if(DeveloperMode::IsEnable)
        {
            eLogger::Log("Parse error: " + FROM_CELL_STRING("Root is not an object."), eLogger::LoggerType::Critical);
        }
        return {};
    }
#else
    if (m_root.isMember(key)) {
        return m_root[key];
    } else {
        if(DeveloperMode::IsEnable)
        {
            eLogger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), eLogger::LoggerType::Critical);
        }
        return {};
    }
#endif
}

#endif

CELL_NAMESPACE_END
