#if __has_include("ratelimiter.hpp")
#   include "ratelimiter.hpp"
#else
#   error "Cell's ratelimiter was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

RateLimiter::RateLimiter(int maxRequestsPerMinute) : m_maxRequestsPerMinute(maxRequestsPerMinute) {}

bool RateLimiter::allowRequest(const std::string& clientId)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // Get the current time
    auto now = std::chrono::steady_clock::now();

    // Cleanup expired tokens
    cleanupExpiredTokens(now);

    // Check if the client has exceeded the rate limit
    if (m_requestCounts[clientId] >= m_maxRequestsPerMinute) {
        return false;
    }

    // Increment the request count for the client
    m_requestCounts[clientId]++;

    // Update the last request time for the client
    m_lastRequestTimes[clientId] = now;

    return true;
}

void RateLimiter::cleanupExpiredTokens(const std::chrono::steady_clock::time_point& now)
{
    auto it = m_lastRequestTimes.begin();
    while (it != m_lastRequestTimes.end()) {
        if (now - it->second >= std::chrono::minutes(1)) {
            m_requestCounts.erase(it->first);
            it = m_lastRequestTimes.erase(it);
        } else {
            ++it;
        }
    }
}


CELL_NAMESPACE_END
