/*!
 * @file        network.hpp
 * @brief       Network manager for handling HTTP requests and networking functionality in the Cell Engine.
 * @details     This file contains the Network class, which provides a thread-safe interface for managing
 *              network requests with features like rate limiting, retries, SSL/TLS configuration, and thread pooling.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2025
 * @copyright   Copyright (c) 2025 The Genyleap.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_NETWORK_HPP
#define CELL_NETWORK_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's \"common.hpp\" was not found!"
#endif

#if __has_include(<curl/curl.h>)
#   include <curl/curl.h>
#else
#   error "Lib Curl was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's \"core/logger.hpp\" was not found!"
#endif


#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's \"core/core.hpp\" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network)

/*!
 * @class Network
 * @brief A thread-safe utility class for advanced HTTP request management.
 *
 * The `Network` class leverages `libcurl` to handle various HTTP methods
 * with support for features like:
 * - Thread pooling for concurrent request execution
 * - Rate limiting to control request frequency
 * - Retry mechanisms for enhanced reliability
 * - Proxy and SSL/TLS configuration
 * - Metrics tracking for performance and error analysis
 */
class Network {
public:
    /*!
     * @enum HttpMethod
     * @brief Supported HTTP methods for requests.
     */
    enum class HttpMethod {
        GET,      ///< HTTP GET method
        POST,     ///< HTTP POST method
        PUT,      ///< HTTP PUT method
        DELETE,   ///< HTTP DELETE method
        PATCH     ///< HTTP PATCH method
    };

    /*!
     * @brief Typedef for HTTP request headers.
     */
    using Headers = std::map<std::string, std::string>;

    /*!
     * @brief Typedef for asynchronous response callback function.
     *
     * @param response The HTTP response content.
     * @param success Indicates if the request was successful.
     */
    using ResponseCallback = std::function<void(const std::string& response, bool success)>;

    /*!
     * @struct RequestMetrics
     * @brief Struct for storing metrics related to HTTP requests.
     */
    struct RequestMetrics {
        std::chrono::milliseconds responseTime;     ///< Time taken for the request
        bool success;                               ///< Indicates success or failure
        std::string errorMessage;                   ///< Error message in case of failure
    };

private:
    mutable std::shared_mutex networkMutex;         ///< Mutex for thread-safe operations
    std::atomic<int> requestTokens;                 ///< Tokens for rate limiting
    std::chrono::milliseconds rateLimitInterval;    ///< Interval for rate limiting

    std::mutex rateLimitMutex;                      ///< Mutex for rate limit management
    std::condition_variable rateLimitCV;            ///< Condition variable for rate limiting

    std::vector<std::thread> threadPool;            ///< Thread pool for concurrent processing
    std::queue<std::function<void()>> taskQueue;    ///< Task queue for thread pool
    std::mutex queueMutex;                          ///< Mutex for task queue access
    std::condition_variable queueCV;                ///< Condition variable for task queue
    std::atomic<bool> stopThreadPool;               ///< Flag to stop thread pool

    int maxRetries;                                 ///< Maximum number of retry attempts
    std::chrono::milliseconds retryDelay;           ///< Delay between retries

    std::string proxyUrl;                           ///< Proxy server URL
    std::string caCertPath;                         ///< SSL CA certificate path
    bool verifySSL;                                 ///< Flag to verify SSL/TLS certificates

    std::map<std::string, RequestMetrics> requestMetrics; ///< Metrics for HTTP requests

    /*!
     * @brief Callback for handling response data.
     */
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* outBuffer);

    /*!
     * @brief Internal function for sending HTTP requests.
     */
    bool sendRequestInternal(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, std::string& response, bool verbose, long timeout);

    /*!
     * @brief Enforces rate limiting for outgoing requests.
     */
    void waitForRateLimit();

    /*!
     * @brief Processes tasks in the thread pool.
     */
    void processTaskQueue();

    /*!
     * @brief Retries failed HTTP requests based on retry policy.
     */
    void retryRequest(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, ResponseCallback callback, bool verbose, long timeout, int retryCount);

public:
    /*!
     * @brief Constructor to initialize the Network object.
     * @param threadPoolSize Number of threads in the thread pool.
     */
    explicit Network(int threadPoolSize = 4);

    /*!
     * @brief Destructor to clean up resources.
     */
    ~Network();

    /*!
     * @brief Builds a query string from key-value pairs.
     * @param params Map of query parameters.
     * @return Constructed query string.
     */
    std::string buildQueryString(const std::map<std::string, std::string>& params) const;

    /*!
     * @brief Sends a synchronous HTTP GET request.
     */
    bool sendRequest(const std::string& url, std::string& response, bool verbose = false, long timeout = 0);

    /*!
     * @brief Sends a synchronous HTTP request with specified data and headers.
     */
    bool sendRequest(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, std::string& response, bool verbose = false, long timeout = 0);

    /*!
     * @brief Sends an asynchronous HTTP request.
     */
    void sendRequestAsync(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, ResponseCallback callback, bool verbose = false, long timeout = 0);

    /*!
     * @brief Sends a JSON HTTP request.
     */
    bool sendJsonRequest(const std::string& url, const std::string& jsonData, const Headers& headers, HttpMethod method, std::string& response, bool verbose = false, long timeout = 0);

    /*!
     * @brief Configures rate limiting.
     */
    void setRateLimit(int maxRequests, std::chrono::milliseconds interval);

    /*!
     * @brief Configures the retry policy.
     */
    void setRetryPolicy(int maxRetries, std::chrono::milliseconds retryDelay);

    /*!
     * @brief Sets a proxy server for network requests.
     */
    void setProxy(const std::string& proxyUrl);

    /*!
     * @brief Configures SSL/TLS settings.
     */
    void setSSLCertificate(const std::string& caCertPath, bool verifySSL = true);

    /*!
     * @brief Cancels all ongoing requests.
     */
    void cancelAllRequests();

    /*!
     * @brief Retrieves metrics for a specific URL.
     */
    RequestMetrics getRequestMetrics(const std::string& url) const;
};

CELL_NAMESPACE_END

#endif // CELL_NETWORK_HPP
