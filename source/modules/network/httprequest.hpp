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

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include(<curl/curl.h>)
#   include <curl/curl.h>
#else
#   error "Lib Curl was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network)

/**
 * @brief The HttpRowHeader class
 */
struct HttpRowHeader
{
    /*!
     * \brief The HTTP Authorization request header contains the credentials to authenticate a user agent with a server,
     *  usually after the server has responded with a 401 Unauthorized status and the WWW-Authenticate header.
     */
    inline constexpr static std::string_view Authorization = "Authorization";

    /*!
     * \brief USER_AGENT Contains a characteristic string that allows the network protocol peers to identify the application type, operating system,
     *  software vendor or software version of the requesting software user agent.
     */
    inline constexpr static std::string_view USER_AGENT =  "User-Agent";

    /*!
     * \brief The Keep-Alive general header allows the sender to hint about how the connection may be used to set a timeout and a maximum amount of requests.
     */
    inline constexpr static std::string_view KEEP_ALIVE = "Keep-Alive";
};

/**
 * @brief The HttpRowTypes class
 */
struct HttpRowTypes
{
    /**
     * @brief Basic is a common type for Authentication.
     */
    inline static std::string  Basic = "Basic";
};


/**
 * @brief The ContentTypeHeader class.
 * The Content-Type entity header is used to indicate the media type of the resource.
 */
struct ContentTypeHeader
{
    /*!
     * \brief The Media type of the body of the request (used with POST and PUT requests).
     * Default. All characters are encoded before sent (spaces are converted to "+" symbols, and special characters are converted to ASCII HEX values)
     */
    inline constexpr static std::string_view  APPLICATION_X_WWW_FROM_URLENCODED = "Content-Type: application/x-www-form-urlencoded";

    /*!
     * \brief The MIME type of this content
     * Spaces are converted to "+" symbols, but no special characters are encoded
     */
    inline constexpr static std::string_view  TEXT_HTML = "Content-Type: text/plain";

    /*!
     * \brief The XHtml type of this content
     */
    inline constexpr static std::string_view  APPLICATION_XHTML = "Content-Type: application/xhtml+xml";

    /*!
     * \brief The Xml type of this content
     */
    inline constexpr static std::string_view  APPLICATION_XML = "Content-Type: application/xml";

    /*!
     * \brief The JSon type of this content
     */
    inline constexpr static std::string_view  APPLICATION_JSON = "Content-Type: application/json";


    /*!
     * \brief No characters are encoded.
     * This value is required when you are using forms that have a file upload control.
     */
    inline constexpr static std::string_view  MULTIPART_FROM_DATA =  "Content-Type: multipart/form-data";

};

/**
 * @brief The Headers enum
 */
enum class Headers {
    X_Urlencoded,
    JSon,
    Html,
    XHtml,
    Xml,
    MultiPart
};

/*!
 * \brief The HTTP_METHOD enum
 * \param GET is used to request data from a specified resource.
 * \param POST is used to send data to a server to create/update a resource.
 * \param PUT is used to send data to a server to create/update a resource.
 * \param DELETE_EX method deletes the specified resource.
 * \param HEAD is almost identical to GET, but without the response body.
 * \param OPTIONS method describes the communication options for the target resource.
 * \param PATCH method is a request method supported by the HTTP protocol for making partial changes to an existing resource.
 */
enum class HTTP_METHOD {
    GET,
    POST,
    PUT,
    DELETE_EX,
    HEAD,
    OPTIONS,
    PATCH
};

/*!
 * Message:	Successful Description:
 * 200 OK	The request is OK (this is the standard response for successful HTTP requests)
 * 201 Created	The request has been fulfilled, and a new resource is created
 * 202 Accepted	The request has been accepted for processing, but the processing has not been completed
 * 203 Non-Authoritative Information	The request has been successfully processed, but is returning information that may be from another source
 * 204 No Content	The request has been successfully processed, but is not returning any content
 * 205 Reset Content	The request has been successfully processed, but is not returning any content, and requires that the requester reset the document view
 * 206 Partial Content	The server is delivering only part of the resource due to a range header sent by the client
 */
enum class HTTP_MESSAGE_SUCCESS
{
    Ok                  = 200,  //!< OK
    Created             = 201,  //!< Created
    Accepted            = 202,  //!< Accepted
    Non_AI              = 203,  //!< Non-Authoritative Information (since HTTP/1.1)
    No_Content          = 204,  //!< No Content
    Reset_Content       = 205,  //!< Reset Content
    Partial_Content     = 206,  //!< Partial Content
    Multi_Status        = 207,  //!< Multi-Status (WebDAV; RFC 4918)
    Already_Reported    = 208,  //!< Already Reported (WebDAV; RFC 5842)
    IM_Used             = 226   //!< IM Used (RFC 3229)
};

/*!
 * Message:	Redirection Description:
 * 300 Multiple Choices	A link list. The user can select a link and go to that location. Maximum five addresses
 * 301 Moved Permanently	The requested page has moved to a new URL
 * 302 Found	The requested page has moved temporarily to a new URL
 * 303 See Other	The requested page can be found under a different URL
 * 304 Not Modified	Indicates the requested page has not been modified since last requested
 * 306 Switch Proxy	No longer used
 * 307 Temporary Redirect	The requested page has moved temporarily to a new URL
 * 308 Resume Incomplete	Used in the resumable requests proposal to resume aborted PUT or POST requests
 */
enum class HTTP_MESSAGE_REDIRECTION
{
    MultipleChoices     = 300,
    MovedPermanently    = 301,
    FoundNewUrl         = 302,
    See_Other           = 303,
    Not_Modified        = 304,
    Switch_Proxy        = 306,
    Temporary_Redirect  = 307,
    Resume_Incomplete   = 308
};

/*!
 * \brief The State enum
 */
enum State { ESCAPED, UNESCAPED };

/*!
 * \brief The Normal ReturnCode enum
 */
enum ReturnCode {
    Ret200    = 200,
    Ret400    = 400,
    Ret401    = 401,
    Ret402    = 402,
    Ret403    = 403,
    Ret404    = 404,
    Ret405    = 405,
    Ret406    = 406,
    Ret407    = 407,
    Ret408    = 408,
    Ret409    = 409,
    Ret411    = 411,
    Ret412    = 412,
    Ret413    = 413,
    Ret414    = 414,
    Ret415    = 415,
    Ret416    = 416,
    Ret417    = 417,
    Ret418    = 418,
    Ret419    = 419,
    Ret422    = 422,
    Ret424    = 424,
    Ret426    = 426,
    Ret428    = 428,
    Ret431    = 431,
    Ret432    = 432
};

struct CodeMessage final
{
    static constexpr std::string_view Ret400 {"The server cannot or will not process the request due to an apparent client error (e.g., malformed request syntax, size too large, invalid request message framing, or deceptive request routing)."};
    static constexpr std::string_view Ret402 {"The response must include a WWW-Authenticate header field containing a challenge applicable to the requested resource. See Basic access authentication and Digest access authentication."};
    //! Add More...
    //! May we'll added more message by globalization language :) via Cell [Engine] -> Translator System.
};

struct RequestStruct final
{
    // Pointer to Types::CURL
    Types::SmartCurlPtr     curlHandlePtr   { Types::curl_easy_init(), &Types::curl_easy_cleanup};

           // The query parameters to be sent with the HTTP request.
    Types::HttpQueryString  queries         {   };

    Types::OptionalString   url             { __cell_null_str  };  //!< Url address.
    Types::OptionalString   data            { __cell_null_str  };  //!< Http data.
    Types::VectorString     headers         { __cell_null_str  };  //!< List of http headers.



    Types::OptionalString   response        { __cell_null_str  };  //!< Http response.
    Types::OptionalString   authUsername    { __cell_null_str  };  //!< Username [for authorization]
    Types::OptionalString   authPassword    { __cell_null_str  };  //!< Password [for authorization]

    long                    timeout         {30L};  //!< Default timeout of 30 seconds

    Types::Mutex            curlHandleMutex; //!< mutex to guard curlHandlePtr


    std::chrono::time_point<std::chrono::high_resolution_clock> lastRequestTime;
};

/**
 * @brief The HttpRequest class
 * An HTTP client class for performing GET, POST, PUT, and DELETE requests with authentication and custom headers.
 */
class HttpRequest {
public:

    HttpRequest();
    /**
     * @brief Constructs an HttpRequest object with the given URL.
     * @param url The URL of the HTTP request.
     */
    HttpRequest(const std::string& url);

    /**
     * Destructor for the HttpRequest object.
     */
    __cell_virtual ~HttpRequest();

    /**
     * @brief setContentType will sets string of standard headers.
     * @param c as Headers.
     */
    void setContentType(Headers c);

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
     * @brief Sets the query parameters to be sent with the HTTP request.
     * @param params The key-value pairs to add to the URL.
     */
    void setQuery(const Types::HttpQueryString& params);

    /**
     * @brief Sets the timeout for the HTTP request.
     * @details Is a function that sets the timeout value for an HTTP request. It specifies the maximum amount of time that the client should wait for a response from the server before timing out.
     * @param timeout The timeout in seconds.
     */
    __cell_virtual void setTimeout(long timeout) final;

    /**
     * Sets the rate limit threshold for rate limiting.
     *
     * @param limit The maximum number of requests allowed within the time duration.
     * @param requestsPerSecond is second.
     */
    __cell_virtual void setRateLimit(const unsigned int requestsPerSecond) final;

    /**
     * @brief rateLimit
     * @return
     */
    unsigned int rateLimit();
    /**
     * @brief isEnableLimit checks rate limitation status.
     * @return The response status as a boolean.
     */
    bool isEnableRateLimit();

    /**
     * @brief Performs an HTTP GET request.
     * @return The response body as a string.
     */
    std::string performGet();

    /**
     * @brief Asynchronously performs a GET request and returns a future object that will hold the response.
     * @return A future object holding the response string. The future will be valid until the response is received or an error occurs.
     */
    Types::FutureStringObject performGetAsync();

    /**
     * @brief Performs an HTTP POST request.
     * @return The response body as a string.
     */
    std::string performPost();

    /**
     * @brief Asynchronously performs a POST request and returns a future object that will hold the response.
     * @return A future object holding the response string. The future will be valid until the response is received or an error occurs.
     */
    Types::FutureStringObject performPostAsync();

    /**
     * @brief Performs an HTTP PUT request.
     * @return The response body as a string.
     */
    std::string performPut();

    /**
     * @brief Asynchronously performs a Put request and returns a future object that will hold the response.
     * @return A future object holding the response string. The future will be valid until the response is received or an error occurs.
     */
    Types::FutureStringObject performPutAsync();

    /**
     * @brief Performs an HTTP DELETE request.
     * @return The response body as a string.
     */
    std::string performDelete();

    /**
     * @brief Asynchronously performs a DELETE request and returns a future object that will hold the response.
     * @return A future object holding the response string. The future will be valid until the response is received or an error occurs.
     */
    Types::FutureStringObject performDeleteAsync();


private:

    /**
     * @brief Returns the mutex used to synchronize access to libcurl.
     * @return The mutex object.
     */
    Types::Mutex& getMutex();

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

    /**
     * @brief This function takes an rvalue reference to a PromiseStringObject and a string specifying the HTTP request method.
     * @param promise is a rvalue reference to an object of type Types::PromiseStringObject.
     * This object is used to store the result of the asynchronous operation and provide it to the caller through a future object.
     * @param method is a const reference to a string that specifies the HTTP method to use for the request.
     * It can be one of "GET", "POST", "PUT", or "DELETE". The function will use this method to perform the HTTP request asynchronously.
     */
    void performAsyncThread(Types::PromiseStringObject&& promise, const std::string& method);

    inline static std::string_view headerType = {""};

    static unsigned int m_rateLimit;

protected:
    RequestStruct requestStruct; //!<The struct to hold libcurl options and data.
};


CELL_NAMESPACE_END


#endif // CELL_HTTPREQUEST_HPP
