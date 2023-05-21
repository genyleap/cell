#if __has_include("json.hpp")
#   include "json.hpp"
#else
#   error "Cell's "ini.hpp" was not found!"
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

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

#if __has_include("core/serializer.hpp")
#   include "core/serializer.hpp"
#else
#   error "Cell's "core/serializer.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::FileSystem;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::System::Serialization;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

JsonSetting::JsonSetting()
{
}
JsonSetting::~JsonSetting()
{
}

bool JsonSetting::read(const std::string& filename)
{
    m_filename = filename;
    auto fileIO = FileManager();

    try {
        auto file = fileIO.get(m_filename.value());
        if (!file.is_open()) {
            (DeveloperMode::IsEnable) ? Log("Could not open file: " + m_filename.value() , LoggerType::Critical) : DO_NOTHING;
        }
#if !defined(USE_BOOST)
        Json::Value root;
        file >> root;
        if (root.isNull()) {
            (DeveloperMode::IsEnable) ? Log("Failed to parse JSON file: " + m_filename.value() , LoggerType::Critical) : DO_NOTHING;
            throw std::runtime_error("Failed to parse JSON file " + m_filename.value());
        }
        m_jsonValue = root;
#else
        // Check file size
        file.seekg(0, std::ios::end);
        const std::streampos fileSize = file.tellg();
        if (fileSize == std::streampos(0)) {
            (DeveloperMode::IsEnable) ? Log("JSON file : " + m_filename.value() , LoggerType::Critical) : DO_NOTHING;
        }
        file.seekg(0, std::ios::beg);
        std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if (data.empty()) {
            (DeveloperMode::IsEnable) ? Log("Failed to read JSON data from file : " + m_filename.value() , LoggerType::Critical) : DO_NOTHING;
        }
        boost::json::error_code ec;
        m_jsonValue = boost::json::parse(data, ec);
        if (ec) {
            (DeveloperMode::IsEnable) ? Log("Failed to parse JSON data from file : " + m_filename.value() , LoggerType::Critical) : DO_NOTHING;
        }
#endif

    } catch (std::exception& e) {
        (DeveloperMode::IsEnable) ? Log(e.what() , LoggerType::Critical) : DO_NOTHING;
        return false;
    }

    return true;
}

bool JsonSetting::save()
{
    std::ofstream file(m_filename.value());
    auto serializer = DataSerializer();
    if (!file.is_open()) {
        (DeveloperMode::IsEnable) ? Log("Could not open file : " + m_filename.value() + " for writing." , LoggerType::Critical) : DO_NOTHING;
        throw std::runtime_error("Could not open file " + m_filename.value() + " for writing.");
    }
    file << serializer.serializeJson(m_jsonValue);
    if (file.fail()) {
        (DeveloperMode::IsEnable) ? Log("Failed to write JSON data to file " + m_filename.value(), LoggerType::Critical) : DO_NOTHING;
        throw std::runtime_error("Failed to write JSON data to file " + m_filename.value());
    }
    return true;
}

bool JsonSetting::getValue(const std::string& key, JSonValue& value, const std::string& defaultValue) const
{
#if !defined(USE_BOOST)
    if (!m_jsonValue.isObject()) {
        return false;
    }
    value = m_jsonValue[key];
#else
    if (!m_jsonValue.is_object()) {
        return false;
    }
    value = m_jsonValue.at(key);
#endif

    return true;
}

bool JsonSetting::getValue(const std::string& section, const std::string& key, std::string& value, const std::string& defaultValue) const
{
#if !defined(USE_BOOST)
    if (!m_jsonValue.isMember(section)) {
        return false;
    }

    const auto& sectionObj = m_jsonValue[section];
    if (!sectionObj.isObject() || !sectionObj.isMember(key)) {
        return false;
    }

    const auto& keyObj = sectionObj[key];
    if (!keyObj.isString()) {
        return false;
    }
    value = keyObj.asString();
#else
    if (!m_jsonValue.is_object()) {
        return false;
    }

    auto sectionIt = m_jsonValue.as_object().find(section);
    if (sectionIt == m_jsonValue.as_object().end()) {
        return false;
    }

    auto& sectionObj = sectionIt->value().as_object();
    auto keyIt = sectionObj.find(key);
    if (keyIt == sectionObj.end()) {
        value = defaultValue;
        return false;
    }

    if (!keyIt->value().is_string()) {
        return false;
    }

    value = keyIt->value().as_string();
#endif

    return true;
}


bool JsonSetting::getValueArray(const std::string& section, const std::string& key, std::vector<std::string>& value, const std::string& defaultValue) const
{
#if !defined(USE_BOOST)
    if (!m_jsonValue.isMember(section)) {
        return false;
    }
    const JSonValue& langsArray = m_jsonValue[section];
    for (const JSonValue& object : langsArray)
    {
        value.push_back(object[key].asString());
    }
#else
    if (!m_jsonValue.is_object()) {
        return false;
    }

    auto sectionIt = m_jsonValue.as_object().find(section);
    if (sectionIt == m_jsonValue.as_object().end()) {
        return false;
    }
    const boost::json::array& jsonArray = sectionIt->value().as_array();
    for (const boost::json::value& element : jsonArray)
    {
        for (const auto& v : element.as_object())
        {
            if(v.key()==key) {
                value.push_back(v.value().as_string().c_str());
            }
        }
    }
#endif
    return true;
}


void JsonSetting::setValue(const std::string& section, const std::string& key, const std::string& value)
{
#if  !defined(USE_BOOST)
    Json::Value& sectionObj = m_jsonValue[section];
    if (!sectionObj.isObject()) {
        sectionObj = Json::Value(Json::objectValue);
    }
    sectionObj[key] = value;
#else
    boost::json::value& sectionValue = m_jsonValue.at(section);
    if (sectionValue.is_null()) {
        sectionValue = boost::json::object();
    }
    boost::json::object& sectionObj = sectionValue.as_object();

    sectionObj[key] = value;
#endif
}

void JsonSetting::addComment(const std::string& section, const std::string& comment)
{
    (DeveloperMode::IsEnable) ? Log("Error: setComment not supported in json!", LoggerType::Warning) : DO_NOTHING;
}

bool JsonSetting::getValueMulti(const std::string &section, std::vector<JSonValue>& value, const std::string &defaultValue) const
{
#if !defined(USE_BOOST)
    if (!m_jsonValue.isMember(section)) {
        return false;
    }
    const JSonValue& langsArray = m_jsonValue[section];
    for (const JSonValue& object : langsArray)
    {
        value.push_back(object);
    }
#else
    if (!m_jsonValue.is_object()) {
        return false;
    }

    auto sectionIt = m_jsonValue.as_object().find(section);
    if (sectionIt == m_jsonValue.as_object().end()) {
        return false;
    }
    const boost::json::array& jsonArray = sectionIt->value().as_array();
    for (const boost::json::value& element : jsonArray)
    {
        //        for (const auto& object : element.as_object())
        //        {
        value.push_back(element);

        //            if(v.key()==key) {
        //                std::cout << v.value() << std::endl;
        //            }
        //        }
    }
#endif
    return true;
}

CELL_NAMESPACE_END
