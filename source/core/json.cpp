#if __has_include("json.hpp")
#   include "json.hpp"
#define header_is_avaialble
#else
#   error "Cell's json.hpp was not found!"
#undef header_is_avaialble
#endif

#ifdef header_is_avaialble

#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's <core> was not found!"
#endif

#if __has_include("filesystem.hpp")
#   include "filesystem.hpp"
#else
#   error "Cell's "filesystem.hpp" was not found!"
#endif

#if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
#endif


CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::FileSystem;
CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::JSon)

JsonManager::JsonManager()
{
#ifdef USE_BOOST
    if(DeveloperMode::IsEnable)
    {
        Log("Initialized Json engine: " + FROM_CELL_STRING(ENGINE_BOOST) + "::json", LoggerType::Success);
    }
#else
    if(DeveloperMode::IsEnable)
    {
        Log("Initialized Json engine: " + FROM_CELL_STRING(ENGINE_DEFAULT) + "[Default JsonCpp] ", LoggerType::Success);
    }
#endif
}

JsonManager::~JsonManager()
{
}

bool JsonManager::parse(const JSonType& data, const InputType inputType) __cell_noexcept
{
#ifdef USE_BOOST
    try {
        switch (inputType) {
        case InputType::RawData:
            m_root = boost::json::parse(std::get<std::string>(data));
            break;
        case InputType::File:
            auto d = fileManager.read(std::get<std::string>(data));
            if (!fileManager.isOpen())
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
            if (d.empty())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to read data from file", LoggerType::Critical);
                }
                if(fileManager.isClose())
                {
                    if(DeveloperMode::IsEnable)
                    {
                        Log("Json file closed!", LoggerType::Info);
                    }
                }
            }
            if(fileManager.isClose())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json file closed!", LoggerType::Info);
                }
            }
            m_root = boost::json::parse(d);
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
        switch (inputType) {
        case InputType::RawData:
            reader.parse(std::get<std::string>(data), m_root);
            break;
        case InputType::File:
            auto d = fileManager.read(std::get<std::string>(data));
            if (!fileManager.isOpen())
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
            if (!fileManager.isOpen())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to read data from file", LoggerType::Critical);
                }
                if(fileManager.isClose())
                {
                    if(DeveloperMode::IsEnable)
                    {
                        Log("Json file closed!", LoggerType::Info);
                    }
                }
            }
            if(fileManager.isClose())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json file closed!", LoggerType::Info);
                }
            }
            Json::CharReaderBuilder builder;

            std::istringstream is(d);

            if(!Json::parseFromStream(builder, is, &m_root, nullptr))
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

bool JsonManager::parse(const JSonType& data) __cell_noexcept
{
#ifdef USE_BOOST
    try {
        if (std::holds_alternative<std::string>(data))
        {
            m_root = boost::json::parse(std::get<std::string>(data));
        }
        if (std::holds_alternative<std::ifstream>(data))
        {
            auto d = fileManager.read(std::get<std::string>(data));
            if (!fileManager.isOpen())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to open: " + FROM_CELL_STRING(std::get<std::string>(data)), LoggerType::Critical);
                }
            }
            if (d.empty())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Failed to read data from file", LoggerType::Critical);
                }
                if(fileManager.isClose())
                {
                    if(DeveloperMode::IsEnable)
                    {
                        Log("Json file closed!", LoggerType::Info);
                    }
                }
            }
            if(fileManager.isClose())
            {
                if(DeveloperMode::IsEnable)
                {
                    Log("Json file closed!", LoggerType::Info);
                }
            }
            m_root = boost::json::parse(d);
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

bool JsonManager::contains(const std::string& key) __cell_noexcept
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

JSonValue JsonManager::getData() __cell_noexcept
{
#if defined(USE_BOOST)
    if (m_root.is_object()) {
        auto it = m_root.as_object();
//        if (it != m_root.as_object().end()) {
//        vectorJsonPtr.push_back(it);

        return it;
//        } else {
//            if(DeveloperMode::IsEnable)
//            {
//                eLogger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), eLogger::LoggerType::Critical);
//            }
//            return {};
//        }
    } else {
        if(DeveloperMode::IsEnable)
        {
            eLogger::Log("Parse error: " + FROM_CELL_STRING("Root is not an object."), eLogger::LoggerType::Critical);
        }
        return {};
    }
#else
//    if (m_root.isMember("")) {
//        return m_root[key];
//    vectorJsonPtr->push_back(m_root);
    return m_root;
//    } else {
//        if(DeveloperMode::IsEnable)
//        {
//            eLogger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), eLogger::LoggerType::Critical);
//        }
//        return {};
//    }
#endif
}

JSonValue JsonManager::get(const std::string& key) __cell_noexcept
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

std::vector<Types::JSonValue> JsonManager::getVectorJsonPtr()
{
    return vectorJsonPtr;
}


#endif

void JsonManager::setVectorJsonPtr(const JSonValue& data)
{
    vectorJsonPtr.push_back(std::move(data));
}

CELL_NAMESPACE_END
