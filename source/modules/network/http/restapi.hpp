/*!
 * @file        restapi.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Restful api manager.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_RESTAPI_HPP
#define CELL_RESTAPI_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("httprequest.hpp")
#   include "httprequest.hpp"
#else
#   error "Cell's "httprequest.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network)

using Parameter =  std::unordered_map<std::string, std::string>;

struct RateLimitCounter
{
    std::chrono::system_clock::time_point startTime;
    int count;
};

/**
 * An HTTP client class for performing RESTful API requests with authentication and custom headers.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export RestfulApi : public HttpRequest {
public:
    RestfulApi();
    /**
     * Constructs a RestfulApi object with the given URL.
     *
     * @param url The URL of the RESTful API.
     */
    explicit RestfulApi(const std::string& url);

    /**
     * Sets the username and password for HTTP authentication.
     *
     * @param username The username for authentication.
     * @param password The password for authentication.
     */
    void setAuthUsernamePassword(const std::string& username, const std::string& password);

    /**
     * Adds a custom header to the HTTP request.
     *
     * @param header The header string to add.
     */
    void addHeader(const std::string& header);

    /**
     * Performs an HTTP GET request on the specified API endpoint with the given query parameters.
     *
     * @param endpoint The API endpoint to perform the GET request on.
     * @param params The query parameters to send with the request.
     * @return The response body as a string.
     */
    std::string get(const Parameter& params);

    /**
     * Performs an HTTP POST request on the specified API endpoint with the given data.
     *
     * @param endpoint The API endpoint to perform the POST request on.
     * @param data The data to send with the request.
     * @return The response body as a string.
     */
    std::string post(const Parameter& params);

    /**
     * Performs an HTTP PUT request on the specified API endpoint with the given data.
     *
     * @param endpoint The API endpoint to perform the PUT request on.
     * @param data The data to send with the request.
     * @return The response body as a string.
     */
    std::string put(const Parameter& params);

    /**
     * Performs an HTTP DELETE request on the specified API endpoint with the given data.
     *
     * @param endpoint The API endpoint to perform the DELETE request on.
     * @param data The data to send with the request.
     * @return The response body as a string.
     */
    std::string del(const Parameter& params);

    /**
     * Performs an HTTP PATCH request on the specified API endpoint with the given data.
     *
     * @param endpoint The API endpoint to perform the PATCH request on.
     * @param data The data to send with the request.
     * @return The response body as a string.
     */
    std::string patch(const Parameter& params);

private:
    HttpRequest httpRequest; // The HTTP request object.
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastRequestTime;
};

CELL_NAMESPACE_END

#endif // CELL_RESTAPI_HPP
