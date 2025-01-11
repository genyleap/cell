/*!
 * @file        webserver.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_WEBSERVER_ABSTRACT_HPP
#define CELL_WEBSERVER_ABSTRACT_HPP

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
# if __has_include("virtualhost.hpp")
#   include "virtualhost.hpp"
#else
#   error "Cell's "virtualhost.hpp" was not found!"
# endif
#endif


CELL_NAMESPACE_BEGIN(Cell::Abstracts::Modules::WebServer)

/**
 * @brief The abstract base class for a web server.
 */
class __cell_export AbstractWebServer {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractWebServer)

    /**
     * @brief Starts the server on the specified port.
     *
     * @param port The port number to listen on.
     */
    __cell_virtual void start(int port) =  __cell_zero;

    /**
     * @brief Stops the server.
     */
    __cell_virtual void stop() =  __cell_zero;

    /**
     * @brief Checks if the server is currently running.
     *
     * @return True if the server is running, false otherwise.
     */
    __cell_virtual bool isRunning() const =  __cell_zero;

    /**
     * @brief Sets the document root directory for serving static files.
     *
     * @param docRoot The document root directory path.
     */
    __cell_virtual void setDocumentRoot(const std::string& docRoot) =  __cell_zero;

    /**
     * @brief Sets the path to the custom error page to be displayed for 4xx and 5xx HTTP status codes.
     *
     * @param errorPage The path to the error page file.
     */
    __cell_virtual void setErrorPage(const std::string& errorPage) =  __cell_zero;

    /**
     * @brief Adds a route for handling a specific URL path.
     *
     * @param path The URL path to handle.
     * @param handler A function that takes a Request object and returns a Response object.
     */
//    __cell_virtual void addRoute(const std::string& path, const std::function<Response(const Request&)>& handler) =  __cell_zero;

    /**
     * @brief Adds a middleware function to be applied to all incoming requests.
     *
     * @param middleware A function that takes a Request object and a handler function, and returns a Response object.
     */
//    __cell_virtual void addMiddleWare(const std::function<Response(const Request&, const std::function<Response(const Request&)>&)>& middleware) =  __cell_zero;

    /**
     * @brief Sets the authentication handler function for handling HTTP Basic Authentication.
     *
     * @param authenticationHandler A function that takes a Request object and returns true if authentication is successful, false otherwise.
     */
//    __cell_virtual void setAuthenticationHandler(const std::function<bool(const Request&)>& authenticationHandler) =  __cell_zero;

    /**
     * @brief Sets the authorization handler function for handling access control.
     *
     * @param authorizationHandler A function that takes a Request object and returns true if the request is authorized, false otherwise.
     */
//    __cell_virtual void setAuthorizationHandler(const std::function<bool(const Request&)>& authorizationHandler) =  __cell_zero;

    /**
     * @brief Sets the caching handler function for caching static files.
     *
     * @param cachingHandler A function that takes a file path and a MIME type, and caches the file using the provided MIME type.
     */
    __cell_virtual void setCachingHandler(const std::function<void(const std::string&, const std::string&)>& cachingHandler) =  __cell_zero;

    /**
     * @brief Sets the load balancing algorithm for distributing incoming requests among multiple backend servers.
     *
     * @param algorithm The name of the load balancing algorithm to use.
     */
    __cell_virtual void setLoadBalancingAlgorithm(const std::string& algorithm) =  __cell_zero;

    /**
     * Set the rate limit for incoming requests.
     *
     * @param requestsPerSecond The maximum number of requests allowed per second.
     */
    __cell_virtual void setRateLimit(int requestsPerSecond) =  __cell_zero;

    /**
     * Set the size of the thread pool to use for handling requests.
     *
     * @param poolSize The number of threads in the pool.
     */
    __cell_virtual void setThreadPoolSize(int poolSize) =  __cell_zero;

    /**
     * Set the type of event loop to use.
     *
     * @param type The type of event loop.
     */
//    __cell_virtual void setEventLoopType(EventLoopType type) =  __cell_zero;

    /**
     * Set the SSL certificate file for the server.
     *
     * @param filePath The path to the SSL certificate file.
     */
    __cell_virtual void setSslCertFile(const std::string& filePath) =  __cell_zero;

    /**
     * Set the SSL key file for the server.
     *
     * @param filePath The path to the SSL key file.
     */
    __cell_virtual void setSslKeyFile(const std::string& filePath) =  __cell_zero;

    /**
     * Set the SSL CA file for the server.
     *
     * @param filePath The path to the SSL CA file.
     */
    __cell_virtual void setSslCaFile(const std::string& filePath) =  __cell_zero;

    /**
     * Set whether to verify the peer when using SSL.
     *
     * @param verifyPeer True if the peer should be verified, false otherwise.
     */
    __cell_virtual void setSslVerifyPeer(bool verifyPeer) =  __cell_zero;

    /**
     * @brief Enable or disable HTTP/2 support.
     *
     * @param enabled Whether HTTP/2 should be enabled or not.
     */
    __cell_virtual void setHttp2Enabled(bool enabled) =  __cell_zero;

    /**
     * @brief Enable or disable HTTP/3 support.
     *
     * @param enabled Whether HTTP/3 should be enabled or not.
     */
    __cell_virtual void setHttp3Enabled(bool enabled) =  __cell_zero;

    /**
     * @brief Add a CDN to the configuration.
     *
     * @param cdn_url The URL of the CDN to add.
     */
    __cell_virtual void addCdn(const std::string& cdn_url) =  __cell_zero;

    /**
     * @brief Enable CDN integration.
     */
    __cell_virtual void enableCdn() =  __cell_zero;

    /**
     * @brief Disable CDN integration.
     */
    __cell_virtual void disableCdn() =  __cell_zero;


    /**
     * @brief Enables or disables compression
     *
     * @param enabled True to enable compression, false to disable
     */
    __cell_virtual void setCompressionEnabled(bool enabled) =  __cell_zero;

    /**
     * @brief Sets the level of compression
     *
     * @param level The compression level to set
     */
    __cell_virtual void setCompressionLevel(int level) =  __cell_zero;

    /**
     * @brief Sets the types of content to compress
     *
     * @param types A vector of strings containing the types of content to compress
     */
    __cell_virtual void setCompressionTypes(const std::vector<std::string>& types) =  __cell_zero;

    /**
     * @brief Enables logging
     */
    __cell_virtual void enableLogging() =  __cell_zero;

    /**
     * @brief Disables logging
     */
    __cell_virtual void disableLogging() =  __cell_zero;

    /**
     * @brief Sets the path of the log file
     *
     * @param filePath The path of the log file
     */
    __cell_virtual void setLogFile(const std::string& filePath) =  __cell_zero;

    /**
     * @brief Enable or disable monitoring functionality
     */
    __cell_virtual void enableMonitoring() = __cell_zero;
    __cell_virtual void disableMonitoring() = __cell_zero;

    /**
     * @brief Set the port for monitoring functionality
     * @param port The port to set for monitoring
     */
    __cell_virtual void setMonitoringPort(int port) = __cell_zero;

    /**
     * @brief Enable or disable reverse proxy functionality
     */
    __cell_virtual void enableReverseProxy() = __cell_zero;
    __cell_virtual void disableReverseProxy() = __cell_zero;

    /**
     * @brief Set the upstream servers for reverse proxy functionality
     * @param upstreamServers A vector of upstream servers to set
     */
    __cell_virtual void setUpstreamServers(const std::vector<std::string>& upstreamServers) = __cell_zero;

    /**
     * @brief Set the proxy pass for reverse proxy functionality
     * @param proxyPass The proxy pass to set
     */
    __cell_virtual void setProxyPass(const std::string& proxyPass) = __cell_zero;

    /**
     * @brief Set the proxy buffer for buffering.
     * @param proxyPass The proxy buffer to set
     */
    __cell_virtual void setProxyBuffering(bool buffering) = __cell_zero;

    /**
     * @brief Set the proxy cache for reverse proxy functionality
     * @param proxyCache The proxy cache to set
     */
    __cell_virtual void setProxyCache(const std::string& proxyCache) = __cell_zero;

    /**
     * @brief Set the proxy cache TTL for reverse proxy functionality
     * @param proxyCacheTtl The proxy cache TTL to set
     */
    __cell_virtual void setProxyCacheTtl(int proxyCacheTtl) = __cell_zero;


    /**
     * @brief Adds a virtual host with the given hostname and configuration.
     *
     * @param hostname The hostname of the virtual host to add.
     * @param config The configuration for the virtual host to add.
     */
//    __cell_virtual void addVirtualHost(const std::string& hostname, const VirtualHostConfig& config) = __cell_zero;

    /**
     * @brief Sets the connection timeout in seconds.
     *
     * @param seconds The number of seconds for the connection timeout.
     */
    __cell_virtual void setConnectionTimeout(int seconds) = __cell_zero;

    /**
     * @brief Adds the given IP to the list of blocked IPs.
     *
     * @param ip The IP to block.
     */
    __cell_virtual void addBlockedIp(const std::string& ip) = __cell_zero;

    /**
     * @brief Adds the given IP to the list of allowed IPs.
     *
     * @param ip The IP to allow.
     */
    __cell_virtual void addAllowedIp(const std::string& ip) = __cell_zero;

    /**
     * @brief Enables access logging.
     */
    __cell_virtual void enableAccessLogging() = __cell_zero;

    /**
     * @brief Disables access logging.
     */
    __cell_virtual void disableAccessLogging() = __cell_zero;

    /**
     * @brief Sets the error handler for the server.
     *
     * @param handler The function to handle errors.
     */
//    __cell_virtual void setErrorHandler(const std::function<Response(const Request&, const std::exception&)>& handler) = __cell_zero;

    /**
     * @brief Sets the server header with the given name.
     *
     * @param serverName The name to set the server header to.
     */
    __cell_virtual void setServerHeader(const std::string& serverName) = __cell_zero;

    /**
     * @brief Enables or disables static file caching.
     *
     * @param enabled Whether or not static file caching should be enabled.
     */
    __cell_virtual void setStaticFileCacheEnabled(bool enabled) = __cell_zero;

    /**
     * @brief Sets the TTL for static file caching in seconds.
     *
     * @param ttlSeconds The number of seconds for the TTL of static file caching.
     */
    __cell_virtual void setStaticFileCacheTtl(int ttlSeconds) = __cell_zero;

    /**
     * @brief Enables or disables load balancing.
     *
     * @param enabled Whether or not load balancing should be enabled.
     */
    __cell_virtual void setLoadBalancingEnabled(bool enabled) = __cell_zero;

    /**
     * @brief Sets the backend servers for load balancing.
     *
     * @param backendServers The list of backend servers to use for load balancing.
     */
    __cell_virtual void setBackendServers(const std::vector<std::string>& backendServers) = __cell_zero;

    /**
     * @brief Sets the session lifetime in seconds.
     *
     * @param lifetimeSeconds The number of seconds for the session lifetime.
     */
    __cell_virtual void setSessionLifetime(int lifetimeSeconds) = __cell_zero;

    /**
     * @brief Sets the name of the session cookie.
     *
     * @param name The name to use for the session cookie.
     */
    __cell_virtual void setSessionCookieName(const std::string& name) = __cell_zero;

    /**
     * @brief Sets the lifetime of the session cookie in seconds.
     *
     * @param lifetimeSeconds The number of seconds for the session cookie lifetime.
     */
    __cell_virtual void setSessionCookieLifetime(int lifetimeSeconds) = __cell_zero;

    /**
     * @brief Enables sessions.
     */
    __cell_virtual void enableSessions() = __cell_zero;

    /**
     * @brief disables sessions.
     */
    __cell_virtual void disableSessions() = __cell_zero;

};

CELL_NAMESPACE_END

#endif  // CELL_WEBSERVER_ABSTRACT_HPP

