#include "fcli.hpp"

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's \"core/logger.hpp\" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Protocol::Farcaster)

void FCLI::prettyPrintJson(const std::string& json) {
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::string errors;

    std::istringstream stream(json);
    if (Json::parseFromStream(readerBuilder, stream, &jsonData, &errors)) {
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = "  ";
        std::string formattedJson = Json::writeString(writerBuilder, jsonData);
        // Logger::json(formattedJson);
    } else {
        Log("Failed to parse JSON response.", LoggerType::Critical);
        // Logger::info(json);
    }
}

void FCLI::handleHelp(const std::string& endpoint) {
    Log("Available Commands:", LoggerType::Info);
    Log("  /v1/info  - Fetch hub information.", LoggerType::Info);
    Log("  /v1/reactions - Fetch reactions for a cast or user.", LoggerType::Info);
    Log("  set-hub <hub_url> - Set a custom hub address.", LoggerType::Info);
    Log("\nExample:", LoggerType::Info);
    Log("  ./fcli /v1/info dbstats=1", LoggerType::Info);
    Log("  ./fcli set-hub https://mycustomhub.com", LoggerType::Info);
}

void FCLI::executeCommand(const std::string& endpoint, const std::map<std::string, std::string>& params, bool verbose) {
    std::string queryString = network.buildQueryString(params);

    // Ensure endpoint starts with '/'
    std::string cleanEndpoint = endpoint[0] == '/' ? endpoint : "/" + endpoint;

    // Construct the full URL
    std::string fullUrl = queryString.empty() ? baseUrl + cleanEndpoint : baseUrl + cleanEndpoint + "?" + queryString;

    Logger::formatted( LoggerType::Info, "Executing command with URL: {}", fullUrl);

    std::string response;
    if (network.sendRequest(fullUrl, response, verbose)) {
        prettyPrintJson(response);
    }
}

void FCLI::setHubUrl(const std::string& hubUrl) {
    if (hubUrl.empty() || hubUrl.find("http") != 0) {
        Log("Invalid hub URL. Please provide a valid URL starting with 'http' or 'https'.", LoggerType::Critical);
        return;
    }
    baseUrl = hubUrl;
    Logger::formatted( LoggerType::Info, "Hub URL updated to: {}", hubUrl);

}

void FCLI::run(int argc, char* argv[]) {
    if (argc < 2) {
        Log("Usage: fcli <endpoint|help|set-hub> <key=value> [key=value ...] [--verbose]", LoggerType::Info);
        return;
    }

    std::string command = argv[1];
    bool verbose = false;

    std::map<std::string, std::string> params;
    for (auto&& arg : std::ranges::subrange(argv + 2, argv + argc)) {
        std::string argument(arg); // Convert char* to std::string
        if (argument == "--verbose") {
            verbose = true;
        } else if (auto pos = argument.find('='); pos != std::string::npos) {
            params[argument.substr(0, pos)] = argument.substr(pos + 1);
        } else {
            Logger::formatted( LoggerType::Info, "Invalid parameter format: '{}'. Use key=value.", argument);
            return;
        }
    }

    if (command == "help") {
        handleHelp();
    } else if (command == "set-hub") {
        if (params.empty() || params.begin()->first.empty()) {
            Log("Please provide a hub URL.", LoggerType::Critical);
            return;
        }
        setHubUrl(params.begin()->first);
    } else {
        executeCommand(command, params, verbose);
    }
}

CELL_NAMESPACE_END
