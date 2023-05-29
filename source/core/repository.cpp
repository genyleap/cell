#if __has_include("repository.hpp")
#   include "repository.hpp"
#else
#   error "Cell's "repository.hpp" was not found!"
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

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Logger;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Maintenance)

Repository::Repository(const std::string& repoUrl)
{
    repositoryData.repoUrl = repoUrl;
}

Repository::~Repository()
{
}

double Repository::measureSpeed(const std::string& mirrorUrl) {
    // Check if the result is already in the cache
    auto it = repositoryData.mirrorSpeedCache.find(mirrorUrl);
    if (it != repositoryData.mirrorSpeedCache.end()) {
        return it->second;
    }
    try {
        // Ping the mirror and measure the response time
        std::string ping_command = CELL_PING_COMMAND + mirrorUrl;
        auto start_time = std::chrono::high_resolution_clock::now();
        System::command(ping_command.c_str());
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        // Wait for a short time to avoid overloading the network with too many requests
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Store the result in the cache and return it
        double speed = static_cast<double>(duration.count()) / 1000.0;
        repositoryData.mirrorSpeedCache[mirrorUrl] = speed;
        return speed;
    } catch (const std::exception& e) {
        // Handle any exceptions that occur while pinging the mirror
        if(DeveloperMode::IsEnable)
        {
            Log("Exception occurred while pinging mirror: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
        }
        return 0.0;
    }
}

void Repository::addMirror(const std::string& mirrorUrl)
{
    if (std::ranges::find(repositoryData.mirrors, mirrorUrl) == repositoryData.mirrors.end())
    {
        repositoryData.mirrors.push_back(mirrorUrl);
    }
}

void Repository::removeMirror(const std::string& mirrorUrl)
{
    auto it = std::ranges::find(repositoryData.mirrors, mirrorUrl);
    if (it != repositoryData.mirrors.end()) {
        repositoryData.mirrors.erase(it);
        if(DeveloperMode::IsEnable)
        {
            Log("Removed mirror: " + FROM_CELL_STRING(mirrorUrl), LoggerType::Warning);
        }
    } else {
        if(DeveloperMode::IsEnable)
        {
            Log("Mirror not found: " + FROM_CELL_STRING(mirrorUrl), LoggerType::Info);
        }
    }
}

std::string Repository::getFastestMirror()
{
    if (repositoryData.mirrors.empty()) {
        return {};
    }
    auto speed = [this](const std::string& mirrorUrl) -> double
    {
        return measureSpeed(mirrorUrl);
    };
    auto fastestMirror = std::ranges::min_element(repositoryData.mirrors, std::less{}, speed);
    return *fastestMirror;
}

double Repository::getMirrorSpeed(const std::string& repoUrl)
{
     return measureSpeed(repoUrl);
}

CELL_NAMESPACE_END
