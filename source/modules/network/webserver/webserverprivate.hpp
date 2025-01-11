/*!
 * @file        webserverprivate.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_WEBSERVER_PRIVATE_HPP
#define CELL_WEBSERVER_PRIVATE_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("request.hpp")
#   include "request.hpp"
#else
#   error "Cell's "request.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("response.hpp")
#   include "response.hpp"
#else
#   error "Cell's "response.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("router.hpp")
#   include "router.hpp"
#else
#   error "Cell's "router.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("ratelimiter.hpp")
#   include "ratelimiter.hpp"
#else
#   error "Cell's "ratelimiter.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("virtualhost.hpp")
#   include "virtualhost.hpp"
#else
#   error "Cell's "virtualhost.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("classes/sessions.hpp")
#   include "classes/sessions.hpp"
#else
#   error "Cell's "classes/sessions.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

enum class HttpMethod
{
    GET,
    POST,
    PUT,
    DELETE
};

using Handler = std::function<Response(const Request&)>;

/**
 * @brief The structure representing the server configuration.
 */
struct ServerStructure final {
    /**
     * @brief Indicates whether the server is running.
     */
    bool isRunning { false };

    /**
     * @brief Server running port.
     */
    unsigned int port { 0 };

    /**
     * @brief Indicates whether SSL/TLS is enabled.
     */
    bool enableSsl { false };

    /**
     * @brief Indicates whether HTTP/2 is enabled.
     */
    bool http2Enabled { false };

    /**
     * @brief Indicates whether HTTP/3 is enabled.
     */
    bool http3Enabled { false };

    /**
     * @brief Indicates whether CDN (Content Delivery Network) is enabled.
     */
    bool cdnEnabled { false };

    /**
     * @brief Indicates whether static file caching is enabled.
     */
    bool staticFileCacheEnabled { false };

    /**
     * @brief Indicates whether load balancing is enabled.
     */
    bool loadBalancingEnabled { false };

    /**
     * @brief Indicates whether sessions are enabled.
     */
    bool sessionsEnabled { false };

    /**
     * @brief Indicates whether SSL peer verification is enabled.
     */
    bool sslVerifyPeer { false };

    /**
     * @brief Indicates whether response compression is enabled.
     */
    bool compressionEnabled { false };

    /**
     * @brief Indicates whether logging is enabled.
     */
    bool loggingEnabled { false };

    /**
     * @brief Indicates whether monitoring is enabled.
     */
    bool monitoringEnabled { false };

    /**
     * @brief Indicates whether reverse proxy is enabled.
     */
    bool reverseProxyEnabled { false };

    /**
     * @brief Indicates whether proxy buffering is enabled.
     */
    bool proxyBuffering { false };


    /**
     * @brief Access logging status.
     */
    bool isAccessLoggingEnabled { false};

    /**
     * @brief Time-to-live for static file cache in seconds.
     */
    int staticFileCacheTtl {};

    /**
     * @brief Lifetime of a session in seconds.
     */
    int sessionLifetime {};

    /**
     * @brief Lifetime of a session cookie in seconds.
     */
    int sessionCookieLifetime {};

    /**
     * @brief Maximum request size in bytes.
     */
    int maxRequestSize {};

    /**
     * @brief Maximum number of connections.
     */
    int maxConnections {};

    /**
     * @brief Timeout for keeping alive an idle connection in seconds.
     */
    int keepAliveTimeout {};

    /**
     * @brief Maximum number of requests per connection.
     */
    int maxRequestsPerConnection {};

    /**
     * @brief Rate limit for incoming requests.
     */
    int rateLimit {};

    /**
     * @brief Size of the thread pool for handling requests.
     */
    int threadPoolSize {};

    /**
     * @brief Level of compression for response data.
     */
    int compressionLevel {};

    /**
     * @brief Monitoring port for server statistics.
     */
    int monitoringPort {};

    /**
     * @brief The document root directory for serving static files.
     */
    std::string documentRoot {};

    /**
     * @brief The server header string.
     */
    std::string serverHeader {};

    /**
     * @brief The name of the session cookie.
     */
    std::string sessionCookieName {};

    /**
     * @brief The error page to display for errors.
     */
    std::string errorPage {};

    /**
     * @brief The load balancing algorithm to use.
     */
    std::string loadBalancingAlgorithm {};

    /**
     * @brief The path to the SSL certificate file.
     */
    std::string sslCertFile {};

    /**
     * @brief The path to the SSL key file.
     */
    std::string sslKeyFile {};

    /**
     * @brief The path to the SSL CA (Certificate Authority) file.
     */
    std::string sslCaFile {};

    /**
     * @brief The path to the log file.
     */
    std::string logFile {};

    /**
     * @brief The URL to proxy requests to in reverse proxy mode.
     */
    std::string proxyPass {};

    /**
     * @brief Map of static file mappings.
     */
    std::unordered_map<std::string, std::string> staticFiles {};

    /**
     * @brief Map of session data.
     */
    std::unordered_map<std::string, Cell::Globals::Storage::Sessions> sessions {};

    /**
     * @brief Map of routes and their associated handlers.
     */
    std::unordered_map<std::string, Handler> routes {};

    /**
     * @brief Map of virtual hosts and their configurations.
     */
    std::unordered_map<std::string, VirtualHostConfig> virtualHosts {};

    /**
     * @brief List of backend servers for load balancing.
     */
    std::vector<std::string> backendServers {};

    /**
     * @brief List of trusted proxies.
     */
    std::vector<std::string> trustedProxies {};

    /**
     * @brief List of CDN URLs.
     */
    std::vector<std::string> cdnUrls {};

    /**
     * @brief List of compression types.
     */
    std::vector<std::string> compressionTypes {};

    /**
     * @brief List of upstream servers for reverse proxy.
     */
    std::vector<std::string> upstreamServers {};

    /**
     * @brief Handler function for authentication.
     * @param request The incoming request.
     * @return true if authentication is successful, false otherwise.
     */
    std::function<bool(const Request&)> authenticationHandler {};

    /**
     * @brief Handler function for authorization.
     * @param request The incoming request.
     * @return true if authorization is granted, false otherwise.
     */
    std::function<bool(const Request&)> authorizationHandler {};

    /**
     * @brief Handler function for caching.
     * @param key The cache key.
     * @param value The cache value.
     */
    std::function<void(const std::string&, const std::string&)> cachingHandler {};

    /**
     * @brief Handler function for error responses.
     * @param request The incoming request.
     * @param exception The exception that occurred.
     * @return The response to be sent back to the client.
     */
    std::function<Response(const Request&, const std::exception&)> exceptionErrorHandler {};

    /**
     * @brief The rate limiter for controlling request rate.
     */
    std::unique_ptr<RateLimiter> rateLimiter {};

    /**
     * @brief The type of socket used by the server.
     */
    Types::SocketType serverSocket {};

    /**
     * @brief The router for handling incoming requests.
     */
    Router router {};

    /**
     * @brief The handler for handling not found (404) responses.
     */
    Handler notFoundHandler {};

    /**
     * @brief List of middleware functions to be executed.
     */
    std::vector<std::function<Response(const Request&, const std::function<Response(const Request&)>&)>> middleware {};
};

CELL_NAMESPACE_END

#endif  // CELL_WEBSERVER_PRIVATE_HPP

