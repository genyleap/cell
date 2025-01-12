/*!
 * @file        ratelimiter.hpp
 * @brief       Rate limiter mechanism manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2025 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_RATE_LIMITER_HPP
#define CELL_RATE_LIMITER_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

/**
 * @class RateLimiter
 * @brief Class for rate limiting requests based on a maximum number of requests per minute.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export RateLimiter {
public:
    /**
     * @brief Constructs a RateLimiter object with the specified maximum requests per minute.
     * @param maxRequestsPerMinute The maximum number of requests allowed per minute.
     */
    RateLimiter(int maxRequestsPerMinute);

    /**
     * @brief Checks if a request from a client is allowed based on the rate limit.
     * @param clientId The unique identifier of the client.
     * @return True if the request is allowed, false otherwise.
     */
    bool allowRequest(const std::string& clientId);

private:
    int m_maxRequestsPerMinute;                             //!< The maximum number of requests allowed per minute.
    std::unordered_map<std::string, int> m_requestCounts;   //!< Request counts for each client.
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> m_lastRequestTimes; //!< Last request times for each client.
    std::mutex m_mutex; //!< Mutex for thread safety.

    /**
     * @brief Cleans up expired request counts based on the current time.
     * @param now The current time point.
     */
    void cleanupExpiredTokens(const std::chrono::steady_clock::time_point& now);
};


CELL_NAMESPACE_END

#endif  // CELL_RATE_LIMITER_HPP

