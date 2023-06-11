#if __has_include("sessions.hpp")
#   include "sessions.hpp"
#else
#   error "Cell's sessions was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core was not found!"
#endif


CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Globals::Storage)

Sessions::Sessions()
    : m_sessionId(generateSessionId().value()), m_expirationTime(getDefaultExpirationTime()) {}

Sessions::Sessions(const std::string& id, std::chrono::system_clock::time_point expiry)
    : m_sessionId(id), m_expirationTime(expiry) {}


OptionalString Sessions::generateSessionId()
{
    EngineController engineController;
    auto& engine = engineController.getEngine();
    OptionalString uid = engine.meta()->generateUid<char>(32, Meta::MetaEngine::CharacterSet::Alphanumeric);
    return uid.value();
}

std::chrono::system_clock::time_point Sessions::getDefaultExpirationTime()
{
    const int defaultSessionTime = 1440; // 1440 seconds = 24 minutes
    return std::chrono::system_clock::now() + std::chrono::seconds(defaultSessionTime);
}

bool Sessions::isExpired() const {
    return std::chrono::system_clock::now() > m_expirationTime;
}

OptionalString Sessions::getSessionValue(const std::string& key) const
{
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        return it->second;
    }
    return __cell_null_optional;
}

void Sessions::setSessionValue(const std::string& key, const std::string& value)
{
    m_data[key] = value;
}

void Sessions::removeSessionValue(const std::string& key)
{
    m_data.erase(key);
}

OptionalString Sessions::getSessionId() const {
    return m_sessionId;
}

void Sessions::setSessionId(const std::string& id) {
    m_sessionId = id;
}

// Set the expiration time for the session
void Sessions::setExpirationTime(const std::chrono::system_clock::time_point& expiry)
{
    m_expirationTime = expiry;
}

bool Sessions::isValidSessionId(const std::string& sessionId) {
    // Implement your validation logic here
    // For example, you can check if the session ID exists in the storage
    return true;
}

void Sessions::storeSessionData() {
    // Implement your session data storage logic here
    // Examples include storing in a database, a distributed cache, or encrypted files
    Log("Session data stored.", LoggerType::Warning);
}

Sessions Sessions::retrieveSessionData(const std::string& sessionId)
{
    // Implement your session data retrieval logic here
    // Examples include retrieving from a database, a distributed cache, or encrypted files
    return Sessions();
}

Sessions Sessions::createSession(std::chrono::system_clock::time_point expirationTime)
{
    std::string sessionId = generateSessionId().value();
    return Sessions(sessionId, expirationTime);
}

Sessions Sessions::startSession() {
    return createSession(getDefaultExpirationTime());
}

void Sessions::destroySession() {
    m_data.clear();
    m_expirationTime = std::chrono::system_clock::now();
    Log("Session destroyed.", LoggerType::Warning);
}


CELL_NAMESPACE_END
