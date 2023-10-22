/*!
 * @file        sessions.hpp
 * @brief       Sessions manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_SESSIONS_HPP
#define CELL_SESSIONS_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Globals::Storage)

/**
 * @class Sessions
 * @brief Class representing a session.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Sessions {
public:
    /**
     * @brief Default constructor for Sessions.
     */
    Sessions();

    /**
     * @brief Constructor for Sessions.
     * @param id The session ID.
     * @param expiry The expiration time of the session.
     */
    Sessions(const std::string& id, std::chrono::system_clock::time_point expiry);

    /**
     * @brief Generate a new session ID.
     * @return An optional string containing the generated session ID.
     */
    static Types::OptionalString generateSessionId();

    /**
     * @brief Get the value of a session variable.
     * @param key The key of the session variable.
     * @return An optional string containing the value of the session variable.
     */
    Types::OptionalString getSessionValue(const std::string& key) const;

    /**
     * @brief Get the session ID.
     * @return An optional string containing the session ID.
     */
    Types::OptionalString getSessionId() const;

    /**
     * @brief Check if the session is expired.
     * @return True if the session is expired, false otherwise.
     */
    bool isExpired() const;

    /**
     * @brief Remove a session variable.
     * @param key The key of the session variable to remove.
     */
    void removeSessionValue(const std::string& key);

    /**
     * @brief Set the value of a session variable.
     * @param key The key of the session variable.
     * @param value The value to set.
     */
    void setSessionValue(const std::string& key, const std::string& value);

    /**
     * @brief Store the session data securely.
     */
    void storeSessionData();

    /**
     * @brief Destroy the current session.
     */
    void destroySession();

    /**
     * @brief Set the session ID.
     * @param id The session ID to set.
     */
    void setSessionId(const std::string& id);

    /**
     * @brief Set the expiration time for the session.
     * @param expiry The expiration time to set.
     */
    void setExpirationTime(const std::chrono::system_clock::time_point& expiry);

    /**
     * @brief Check if a session ID is valid.
     * @param sessionId The session ID to validate.
     * @return True if the session ID is valid, false otherwise.
     */
    static bool isValidSessionId(const std::string& sessionId);

    /**
     * @brief Get the default expiration time for a session.
     * @return The default expiration time.
     */
    static std::chrono::system_clock::time_point getDefaultExpirationTime();

    /**
     * @brief Retrieve the session data for a given session ID.
     * @param sessionId The session ID to retrieve the data for.
     * @return A Sessions object containing the retrieved session data.
     */
    static Sessions retrieveSessionData(const std::string& sessionId);

    /**
     * @brief Create a new session with a specified expiration time.
     * @param expirationTime The expiration time for the session.
     * @return A Sessions object representing the new session.
     */
    static Sessions createSession(std::chrono::system_clock::time_point expirationTime);

    /**
     * @brief Start a new session with the default expiration time.
     * @return A Sessions object representing the new session.
     */
    static Sessions startSession();

private:
    std::string m_sessionId;
    std::chrono::system_clock::time_point m_expirationTime;
    std::unordered_map<std::string, std::string> m_data;
};


CELL_NAMESPACE_END

#endif  // CELL_SESSIONS_HPP

