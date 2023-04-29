/*!
 * @file        httprequest.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Http Request manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_HTTPREQUEST_HPP
#define CELL_HTTPREQUEST_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include(<curl/curl.h>)
#   include <curl/curl.h>
#else
#   error "Lib Curl was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::Network)

struct RequestStruct final
{
    Types::SmartCurlPtr     curlHandlePtr   {Types::curl_easy_init(), &Types::curl_easy_cleanup};
    std::string             url             {   };  ///<! Url address.
    Types::VectorString     headers         {   };  ///<! List of http headers.
    std::string             data            {   };  ///<! Http data.
    std::string             response        {   };  ///<! Http response.
    std::string             authUsername    {   };  ///<! Username [for authorization]
    std::string             authPassword    {   };  ///<! Password [for authorization]
    long                    timeout         {30L};  ///<! Default timeout of 30 seconds
    Types::Mutex            curlHandleMutex; ///<! mutex to guard curlHandlePtr
};

/**
 * @brief The HttpRequest class
 * An HTTP client class for performing GET, POST, PUT, and DELETE requests with authentication and custom headers.
 */
class HttpRequest {
public:
    /**
     * @brief Constructs an HttpRequest object with the given URL.
     * @param url The URL of the HTTP request.
     */
    HttpRequest(const std::string& url);

    /**
     * Destructor for the HttpRequest object.
     */
    virtual ~HttpRequest();

    /**
     * @brief Sets the username and password for HTTP authentication.
     * @param username The username for authentication.
     * @param password The password for authentication.
     */
    void setAuthUsernamePassword(const std::string& username, const std::string& password);

    /**
     * @brief Adds a custom header to the HTTP request.
     * @param header The header string to add.
     */
    void addHeader(const std::string& header);

    /**
     * @brief Sets the data to be sent with the HTTP request.
     * @param data The data to send with the request.
     */
    void setData(const std::string& data);

    /**
     * @brief Sets the timeout for the HTTP request.
     * @param timeout The timeout in seconds.
     */
    void setTimeout(long timeout);

    /**
     * @brief Performs an HTTP GET request.
     * @return The response body as a string.
     */
    std::string performGet();

    /**
     * @brief Performs an HTTP POST request.
     * @return The response body as a string.
     */
    std::string performPost();

    /**
     * @brief Performs an HTTP PUT request.
     * @return The response body as a string.
     */
    std::string performPut();

    /**
     * @brief Performs an HTTP DELETE request.
     * @return The response body as a string.
     */
    std::string performDelete();

    /**
     * @brief Returns the mutex used to synchronize access to libcurl.
     * @return The mutex object.
     */
    Types::Mutex& getMutex();

private:
    /**
     * @brief Static function to handle the libcurl write callback.
     * @return as size_t.
     */
    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);

    /**
     * @brief Static function to handle the libcurl authentication callback.
     * @return as int.
     */
    static int authCallback(char* buffer, size_t size, size_t nitems, void* userdata);

    /**
     * @brief Performs an HTTP request with the given method.
     * @param method The HTTP method to use.
     * @return The response body as a string.
     */
    std::string performRequest(const std::string& method);

    /**
     * @brief Performs an HTTP request with a mutex guard to synchronize access to libcurl.
     * @param func The function to call with the libcurl handle.
     */
    void performRequestWithGuard(const Types::FunctionCurl& func);
private:
    RequestStruct requestStruct {}; ///<!The struct to hold libcurl options and data.

};


CELL_NAMESPACE_END


#endif // CELL_HTTPREQUEST_HPP
