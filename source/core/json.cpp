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
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::JSon)

JsonManager::JsonManager()
{
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
            Logger::Log("Parse error: " + FROM_CELL_STRING("Root is not an object."), LoggerType::Critical);
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
        //                Logger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), LoggerType::Critical);
        //            }
        //            return {};
        //        }
    } else {
        if(DeveloperMode::IsEnable)
        {
            Logger::Log("Parse error: " + FROM_CELL_STRING("Root is not an object."), LoggerType::Critical);
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
//            Logger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), LoggerType::Critical);
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
                Logger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), LoggerType::Critical);
            }
            return {};
        }
    } else {
        if(DeveloperMode::IsEnable)
        {
            Logger::Log("Parse error: " + FROM_CELL_STRING("Root is not an object."), LoggerType::Critical);
        }
        return {};
    }
#else
    if (m_root.isMember(key)) {
        return m_root[key];
    } else {
        if(DeveloperMode::IsEnable)
        {
            Logger::Log("Parse error: " + FROM_CELL_STRING("Key not found."), LoggerType::Critical);
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

JsonDocument::JsonDocument(const JSonValue& value) : m_root(value) {}

bool JsonDocument::parse(const JSonType& data, const InputType inputType) __cell_noexcept
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

bool JsonDocument::parse(const JSonType& data) __cell_noexcept
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

std::string JsonDocument::toString() const {
#ifdef USE_BOOST
    return boost::json::serialize(m_root);
#else
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, m_root);
#endif
}

JSonValue JsonDocument::getJson() const {
    return m_root;
}

bool JsonDocument::hasKey(const std::string& key) const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        return obj.find(key) != obj.end();
    }
    return false;
#else
    return m_root.isMember(key);
#endif
}

int JsonDocument::getInt(const std::string& key) const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        if (obj.contains(key)) {
            auto jsonValue = obj.at(key);
            if (jsonValue.is_int64()) {
                return static_cast<int>(jsonValue.get_int64());
            } else if (jsonValue.is_uint64()) {
                return static_cast<int>(jsonValue.get_uint64());
            } else if (jsonValue.is_double()) {
                return static_cast<int>(jsonValue.get_double());
            }
        }
    }
#else
    if (m_root.isObject() && m_root.isMember(key) && m_root[key].isNumeric()) {
        return m_root[key].asInt();
    }
#endif
    throw std::runtime_error("Key '" + key + "' does not exist or is not an integer value.");
}

std::string JsonDocument::getString(const std::string& key) const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        if (obj.contains(key)) {
            auto jsonValue = obj.at(key);
            if (jsonValue.is_string()) {
                return jsonValue.get_string().c_str();
            }
        }
    }
#else
    if (m_root.isObject() && m_root.isMember(key) && m_root[key].isString()) {
        return m_root[key].asString();
    }
#endif
    throw std::runtime_error("Key '" + key + "' does not exist or is not a string value.");
}


bool JsonDocument::hasArray(const std::string& key) const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        if (obj.contains(key)) {
            auto jsonValue = obj.at(key);
            return jsonValue.is_array();
        }
    }
    return false;
#else
    if (m_root.isObject() && m_root.isMember(key) && m_root[key].isArray()) {
        return true;
    }
    return false;
#endif
}

std::vector<Types::JSonValue> JsonDocument::getVectorJsonPtr()
{
    return vectorJsonPtr;
}

void JsonDocument::setVectorJsonPtr(const JSonValue& data)
{
    vectorJsonPtr.push_back(std::move(data));
}

size_t JsonDocument::getArraySize(const std::string& key) const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        if (obj.contains(key)) {
            auto jsonValue = obj.at(key);
            if (jsonValue.is_array()) {
                return jsonValue.get_array().size();
            }
        }
    }
#else
    if (m_root.isObject() && m_root.isMember(key) && m_root[key].isArray()) {
        return m_root[key].size();
    }
#endif
    throw std::runtime_error("Key '" + key + "' does not exist or is not an array.");
}

std::vector<std::string> JsonDocument::getKeys() const {
    std::vector<std::string> keys;

#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        for (const auto& item : obj) {
            keys.push_back(item.key());
        }
    }
#else
    if (m_root.isObject()) {
        const Json::Value& obj = m_root;
        for (Json::Value::const_iterator it = obj.begin(); it != obj.end(); ++it) {
            keys.push_back(it.key().asString());
        }
    }
#endif

    return keys;
}

JsonDocument JsonDocument::getObject(const std::string& key) const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        if (obj.contains(key)) {
            auto jsonValue = obj.at(key);
            if (jsonValue.is_object()) {
                JsonDocument nestedObjectWrapper;
                nestedObjectWrapper.m_root = jsonValue;
                return nestedObjectWrapper;
            }
        }
    }
#else
    if (m_root.isObject() && m_root.isMember(key) && m_root[key].isObject()) {
        JsonDocument nestedObjectWrapper;
        nestedObjectWrapper.m_root = m_root[key];
        return nestedObjectWrapper;
    }
#endif
    throw std::runtime_error("Key '" + key + "' does not exist or is not an object.");
}

JsonDocument JsonDocument::getObject() const {
#ifdef USE_BOOST
    if (m_root.is_object()) {
        auto obj = m_root.as_object();
        auto jsonValue = obj;
        JsonDocument nestedObjectWrapper;
        nestedObjectWrapper.m_root = jsonValue;
        return nestedObjectWrapper;
    }
#else
    if (m_root.isObject()) {
        JsonDocument nestedObjectWrapper;
        nestedObjectWrapper.m_root = m_root;
        return nestedObjectWrapper;
    }
#endif
    throw std::runtime_error("Does not exist or is not an object.");
}


CELL_NAMESPACE_END
