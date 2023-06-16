/*!
 * @file        request.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver request for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_REQUEST_ABSTRACT_HPP
#define CELL_REQUEST_ABSTRACT_HPP

#include "classes/cookies.hpp"
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Modules::WebServer)

/**
 * @brief Structure that represents the parts of a HTTP request
 */
struct RequestStructure final
{
    Types::Headers          headers     {}; //!< The headers of the request.
    Types::OptionalString   method      {}; //!< The HTTP method of the request.
    Types::OptionalString   uri         {}; //!< The URI of the request.
    Types::OptionalString   httpVersion {}; //!< The HTTP version of the request.
    Types::OptionalString   body        {}; //!< The body of the request.
};

/**
 * @brief Class that represents a HTTP request
 */
class __cell_export Request {
public:
    /**
     * @brief Returns the HTTP method of the request
     *
     * @return The HTTP method of the request
     */
    const Types::OptionalString& method() const;

    /**
     * @brief Returns the Path of the request
     *
     * @return The Path of the request
     */
    const Types::OptionalString& path() const;

    /**
     * @brief Returns the HTTP version of the request
     *
     * @return The HTTP version of the request
     */
    const Types::OptionalString& httpVersion() const;

    /**
     * @brief Returns the headers of the request
     *
     * @return The headers of the request as an unordered map with string keys and values
     */
    const std::unordered_map<std::string, std::string> headers()  const;

    /**
     * @brief Returns the body of the request
     *
     * @return The body of the request
     */
    const Types::OptionalString& body() const;

    /**
     * @brief Set the HTTP method of the request.
     * @param method The HTTP method to set.
     */
    void setMethod(const std::string& method);

    /**
     * @brief Set the path of the request.
     * @param path The path to set.
     */
    void setPath(const std::string& path);

    /**
     * @brief Set a header in the request.
     * @param key The key of the header.
     * @param value The value of the header.
     */
    void setHeader(const std::string& key, const std::string& value);

    /**
     * @brief Set the body of the request.
     * @param body The body to set.
     */
    void setBody(const std::string& body);

    /**
     * @brief Set the session ID of the request.
     * @param sessionId The session ID to set.
     */
    void setSessionId(const std::string& sessionId);

    /**
     * @brief Get the cookies received in the request.
     * @return The cookies received in the request.
     */
    const Cell::Globals::Storage::Cookies& cookies() const;

private:
    RequestStructure requestStructure {}; //!< The structure that holds the parts of the request.
};

CELL_NAMESPACE_END

#endif  // CELL_REQUEST_ABSTRACT_HPP
