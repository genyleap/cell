#if __has_include("serializer.hpp")
#   include "serializer.hpp"
#else
#   error "Cell's "serializer.hpp" was not found!"
#endif

#if __has_include("core.hpp")
#   include "core.hpp"
#else
#   error "Cell's "core.hpp" was not found!"
#endif

#if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::System::Serialization)

DataSerializer::DataSerializer()
{
}

DataSerializer::~DataSerializer()
{
}

std::string DataSerializer::serializeJson(const JSonValue& jsonValue)
{
#if defined(USE_BOOST)
    return dataSerializerStruct.builder(jsonValue);
#else
    dataSerializerStruct.builder["indentation"] = "";
    return Json::writeString(dataSerializerStruct.builder, jsonValue);
#endif
}

void DataSerializer::serializeJsonByFile(const std::string& file)
{
    // Open the JSON file for reading
    std::ifstream f(file);
    if (!f.is_open()) {
        (DeveloperMode::IsEnable) ? Log("Failed to open file!", LoggerType::Critical) : DO_NOTHING;
    }
    // Read the file contents into a string
    std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
#if defined(USE_BOOST)
    // Parse the JSON string into a boost::json::value object
    JSonValue jsonValue = boost::json::parse(str);
    // Serialize the JSON object into a string
    std::string serialized = boost::json::serialize(jsonValue);
#else
    JSonValue jsonValue;
    dataSerializerStruct.builder["indentation"] = "";
    std::string serialized = Json::writeString(dataSerializerStruct.builder, str);
#endif
    // Open the output file stream
    std::ofstream output_file(file);
    // Serialize the JSON value to a string and write it to the output file stream
    output_file << serializeJson(jsonValue);
    // Close the output file stream
    output_file.close();
}


CELL_NAMESPACE_END
