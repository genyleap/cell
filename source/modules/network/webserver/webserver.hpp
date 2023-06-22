/*!
 * @file        webserver.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_WEBSERVER_HPP
#define CELL_WEBSERVER_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("abstracts/modules/webserver/webserver.hpp")
#   include "abstracts/modules/webserver/webserver.hpp"
#else
#   error "Cell's "abstracts/modules/webserver/webserver.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("classes/eventloop.hpp")
#   include "classes/eventloop.hpp"
#else
#   error "Cell's "classes/eventloop.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("webserverprivate.hpp")
#   include "webserverprivate.hpp"
#else
#   error "Cell's "webserverprivate.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

/**
 * @brief Constants related to the WebServer.
 */
struct WEBSERVER_CONSTANTS final {
    /**
     * @brief The maximum number of connections allowed by the WebServer.
     */
    __cell_static_const_constexpr int MAX_CONNECTIONS = 100;
};

/**
 * @class WebServer
 * @brief Represents a web server implementation.
 *
 * The WebServer class is responsible for handling incoming HTTP requests, routing them to
 * appropriate handlers, managing server configurations, and providing various functionalities
 * related to web server operations. It inherits from the AbstractWebServer class and provides
 * overrides for its pure virtual functions.
 */
class WebServer : public Abstracts::Modules::WebServer::AbstractWebServer
{
public:
    /**
     * @brief Constructs a WebServer object.
     * @param loopType The type of event loop to be used by the server.
     */
    WebServer(EventLoopType loopType);

    /**
     * @brief Destroys the WebServer object.
     */
    ~WebServer();

    /**
     * @brief Starts the web server and listens on the specified port.
     *
     * This function starts the web server and makes it listen for incoming requests on the specified port.
     * @param port The port number on which the server should listen for incoming requests.
     */
    void start(int port) override;

    /**
     * @brief Stops the web server.
     *
     * This function stops the web server and terminates all active connections.
     */
    void stop() override;

    /**
     * @brief Checks if the web server is running.
     *
     * This function returns a boolean value indicating whether the web server is currently running or not.
     * @return True if the server is running, false otherwise.
     */
    bool isRunning() const override;

    /**
     * @brief Registers a router for handling incoming requests.
     *
     * This function registers a router object to handle incoming requests and route them to appropriate handlers.
     * @param router The router object to be registered.
     */
    void registerRouter(const Router& router);

    /**
     * @brief Parses a request string into a Request object.
     *
     * This function parses the provided request string and populates the given Request object with the parsed data.
     * @param requestString The string representing the HTTP request.
     * @param request The Request object to be populated with parsed data.
     */
    void parseRequest(const std::string& requestString, Request& request);

    /**
     * @brief Retrieves the status message for a given status code.
     *
     * This function returns the corresponding status message for the provided HTTP status code.
     * @param status_code The HTTP status code.
     * @return The status message associated with the provided status code.
     */
    std::string getStatusMessage(int status_code);

    /**
     * @brief Converts a Response object to a string representation.
     *
     * This function converts the provided Response object into its string representation.
     * @param response The Response object to be converted.
     * @return The string representation of the Response object.
     */
    std::string responseToString(const Response& response);

    /**
     * @brief Retrieves the IP address of the client associated with the given socket.
     *
     * This function returns the IP address of the client associated with the specified socket.
     * @param clientSocket The socket associated with the client.
     * @return The IP address of the client.
     */
    std::string getClientIP(Types::SocketType clientSocket);

    /**
     * @brief Handles the client request when SSL is not enabled.
     *
     * This function handles the client request received on the specified socket when SSL is not enabled.
     * @param clientSocket The socket associated with the client.
     */
    void handleClientRequestNoSSL(Types::SocketType clientSocket);

    /**
     * @brief Handles the client request when SSL is enabled.
     *
     * This function handles the client request received on the specified socket when SSL is enabled.
     * @param clientSocket The socket associated with the client.
     * @param ssl The SSL context associated with the client.
     */
    void handleClientRequestSSL(Types::SocketType clientSocket, SSL* ssl);

    /**
     * @brief Sets the document root directory for serving static files.
     *
     * This function sets the document root directory where the web server should look for static files to serve.
     * @param docRoot The path to the document root directory.
     */
    void setDocumentRoot(const std::string& docRoot) override;

    /**
     * @brief Sets the error page to be displayed for server errors.
     *
     * This function sets the error page that should be displayed when the server encounters an error.
     * @param errorPage The path to the error page file.
     */
    void setErrorPage(const std::string& errorPage) override;

    /**
     * @brief Adds a route to the web server for handling requests.
     *
     * This function adds a route to the web server, associating a specific URL path with a request handler function.
     * @param path The URL path to associate with the handler.
     * @param handler The function to handle requests for the specified path.
     */
    void addRoute(const std::string& path, const std::function<Response(const Request&)>& handler);

    /**
     * @brief Adds a middleware function to the web server.
     *
     * This function adds a middleware function to the web server, which will be invoked for each incoming request before reaching the final handler.
     * @param middleware The middleware function to be added.
     */
    void addMiddleWare(const std::function<Response(const Request&, const std::function<Response(const Request&)>&)>& middleware);

    /**
     * @brief Sets the authentication handler for the web server.
     *
     * This function sets the authentication handler for the web server, which will be used to authenticate incoming requests.
     * @param authenticationHandler The function that performs authentication for requests.
     */
    void setAuthenticationHandler(const std::function<bool(const Request&)>& authenticationHandler);

    /**
     * @brief Sets the authorization handler for the web server.
     *
     * This function sets the authorization handler for the web server, which will be used to authorize incoming requests.
     * @param authorizationHandler The function that performs authorization for requests.
     */
    void setAuthorizationHandler(const std::function<bool(const Request&)>& authorizationHandler);

    /**
     * @brief Sets the caching handler for the web server.
     *
     * This function sets the caching handler for the web server, which will be responsible for managing caching headers in responses.
     * @param cachingHandler The function that handles caching headers.
     */
    void setCachingHandler(const std::function<void(const std::string&, const std::string&)>& cachingHandler) override;

    /**
     * @brief Sets the load balancing algorithm for the web server.
     *
     * This function sets the load balancing algorithm to be used by the web server when distributing requests among backend servers.
     * @param algorithm The name of the load balancing algorithm.
     */
    void setLoadBalancingAlgorithm(const std::string& algorithm) override;

    /**
     * @brief Sets the rate limit for the web server.
     *
     * This function sets the maximum number of requests allowed per minute for the web server.
     * @param maxRequestsPerMinute The maximum number of requests per minute.
     */
    void setRateLimit(int maxRequestsPerMinute) override;

    /**
     * @brief Sets the thread pool size for the web server.
     *
     * This function sets the size of the thread pool used by the web server for handling incoming requests.
     * @param poolSize The size of the thread pool.
     */
    void setThreadPoolSize(int poolSize) override;

    /**
     * @brief Sets the event loop type for the web server.
     *
     * This function sets the event loop type to be used by the web server for handling incoming requests.
     * @param type The event loop type.
     */
    void setEventLoopType(EventLoopType type);

    /**
     * @brief Enables or disables SSL/TLS encryption for the web server.
     *
     * This function enables or disables SSL/TLS encryption for the web server. When enabled, the web server will use secure HTTPS connections.
     * @param status Set to `true` to enable SSL/TLS encryption, or `false` to disable it.
     */
    void enableSSL(const bool status);

    /**
     * @brief Sets the SSL/TLS certificate file path for the web server.
     *
     * This function sets the file path to the SSL/TLS certificate that the web server should use for secure connections.
     * @param filePath The path to the SSL/TLS certificate file.
     */
    void setSslCertFile(const std::string& filePath) override;

    /**
     * @brief Sets the SSL/TLS private key file path for the web server.
     *
     * This function sets the file path to the private key that corresponds to the SSL/TLS certificate used by the web server.
     * @param filePath The path to the SSL/TLS private key file.
     */
    void setSslKeyFile(const std::string& filePath) override;

    /**
     * @brief Sets the SSL/TLS CA (Certificate Authority) file path for the web server.
     *
     * This function sets the file path to the CA file that contains trusted certificate authorities for validating client certificates.
     * @param filePath The path to the SSL/TLS CA file.
     */
    void setSslCaFile(const std::string& filePath) override;

    /**
     * @brief Sets whether the web server should verify the peer's SSL/TLS certificate.
     *
     * This function sets whether the web server should verify the SSL/TLS certificate presented by the peer during the handshake.
     * @param verifyPeer Set to `true` to enable peer certificate verification, or `false` to disable it.
     */
    void setSslVerifyPeer(bool verifyPeer) override;

    /**
     * @brief Enables or disables HTTP/2 support for the web server.
     *
     * This function enables or disables HTTP/2 support for the web server. When enabled, the web server will accept and handle HTTP/2 requests.
     * @param enabled Set to `true` to enable HTTP/2 support, or `false` to disable it.
     */
    void setHttp2Enabled(bool enabled) override;

    /**
     * @brief Enables or disables HTTP/3 support for the web server.
     *
     * This function enables or disables HTTP/3 support for the web server. When enabled, the web server will accept and handle HTTP/3 requests.
     * @param enabled Set to `true` to enable HTTP/3 support, or `false` to disable it.
     */
    void setHttp3Enabled(bool enabled) override;

    /**
     * @brief Adds a CDN (Content Delivery Network) URL to the web server.
     *
     * This function adds a CDN URL to the web server, allowing the server to serve static content from the specified CDN.
     * @param cdn_url The URL of the CDN.
     */
    void addCdn(const std::string& cdn_url) override;

    /**
     * @brief Enables the use of a CDN for serving static content.
     *
     * This function enables the use of a CDN for serving static content. When enabled, the web server will utilize the configured CDN for serving static files.
     */
    void enableCdn() override;

    /**
     * @brief Disables the use of a CDN for serving static content.
     *
     * This function disables the use of a CDN for serving static content. When disabled, the web server will serve static files directly without utilizing a CDN.
     */
    void disableCdn() override;

    /**
     * @brief Enables or disables compression for the web server responses.
     *
     * This function enables or disables compression for the web server responses. When enabled, the server will compress the response content before sending it to the client.
     * @param enabled Set to `true` to enable compression, or `false` to disable it.
     */
    void setCompressionEnabled(bool enabled) override;

    /**
     * @brief Sets the compression level for the web server responses.
     *
     * This function sets the compression level for the web server responses. The compression level determines the trade-off between compression ratio and CPU usage.
     * @param level The compression level to be set. Valid values typically range from 0 (no compression) to 9 (maximum compression).
     */
    void setCompressionLevel(int level) override;

    /**
     * @brief Sets the supported compression types for the web server.
     *
     * This function sets the supported compression types for the web server. The server will compress the response using one of the specified compression algorithms based on client support.
     * @param types A vector of strings representing the supported compression types, such as "gzip" or "deflate".
     */
    void setCompressionTypes(const std::vector<std::string>& types) override;

    /**
     * @brief Enables logging for the web server.
     *
     * This function enables logging for the web server. When enabled, the server will log relevant events and requests for analysis and debugging purposes.
     */
    void enableLogging() override;

    /**
     * @brief Disables logging for the web server.
     *
     * This function disables logging for the web server. When disabled, the server will not generate any log files or log any events or requests.
     */
    void disableLogging() override;

    /**
     * @brief Sets the log file path for the web server.
     *
     * This function sets the file path where the web server should write the log files. The server will write log messages and events to the specified file.
     * @param filePath The path to the log file.
     */
    void setLogFile(const std::string& filePath) override;

    /**
     * @brief Enables monitoring for the web server.
     *
     * This function enables monitoring for the web server. When enabled, the server will provide monitoring and metrics data to track its performance and health.
     */
    void enableMonitoring() override;

    /**
     * @brief Disables monitoring for the web server.
     *
     * This function disables monitoring for the web server. When disabled, the server will not provide any monitoring or metrics data.
     */
    void disableMonitoring() override;

    /**
     * @brief Sets the monitoring port for the web server.
     *
     * This function sets the port number on which the monitoring service will be accessible. Clients can connect to this port to retrieve monitoring and metrics data.
     * @param port The port number for the monitoring service.
     */
    void setMonitoringPort(int port) override;

    /**
     * @brief Enables reverse proxy support for the web server.
     *
     * This function enables reverse proxy support for the web server. When enabled, the server acts as a reverse proxy, forwarding client requests to backend servers.
     */
    void enableReverseProxy() override;

    /**
     * @brief Disables reverse proxy support for the web server.
     *
     * This function disables reverse proxy support for the web server. When disabled, the server operates in standalone mode without acting as a reverse proxy.
     */
    void disableReverseProxy() override;

    /**
     * @brief Sets the upstream servers for reverse proxy configuration.
     *
     * This function sets the list of upstream servers to which the reverse proxy will forward client requests.
     * @param upstreamServers A vector of strings representing the upstream server addresses or URLs.
     */
    void setUpstreamServers(const std::vector<std::string>& upstreamServers) override;

    /**
     * @brief Sets the proxy pass configuration for reverse proxy.
     *
     * This function sets the proxy pass configuration for the reverse proxy. It specifies the destination URL where the reverse proxy will forward the client requests.
     * @param proxyPass The destination URL for the reverse proxy.
     */
    void setProxyPass(const std::string& proxyPass) override;

    /**
     * @brief Sets the proxy buffering option for reverse proxy.
     *
     * This function sets the proxy buffering option for the reverse proxy. When buffering is enabled, the reverse proxy will store the response from the upstream server before sending it to the client.
     * @param buffering Set to `true` to enable proxy buffering, or `false` to disable it.
     */
    void setProxyBuffering(bool buffering) override;

    /**
     * @brief Sets the proxy cache configuration for reverse proxy.
     *
     * This function sets the proxy cache configuration for the reverse proxy. It specifies the caching mechanism and options for the reverse proxy.
     * @param proxyCache The configuration string specifying the proxy cache options.
     */
    void setProxyCache(const std::string& proxyCache) override;

    /**
     * @brief Sets the proxy cache time-to-live (TTL) for reverse proxy.
     *
     * This function sets the time-to-live (TTL) value for the reverse proxy cache. It determines how long the cached responses will be considered valid before they expire.
     * @param proxyCacheTtl The TTL value in seconds for the reverse proxy cache.
     */
    void setProxyCacheTtl(int proxyCacheTtl) override;

    /**
     * @brief Adds a virtual host configuration to the web server.
     *
     * This function adds a virtual host configuration to the web server. It associates the specified hostname with the provided virtual host configuration.
     * @param hostname The hostname for the virtual host.
     * @param config The virtual host configuration to be associated with the hostname.
     */
    void addVirtualHost(const std::string& hostname, const VirtualHostConfig& config);

    /**
     * @brief Sets the connection timeout value for the web server.
     *
     * This function sets the maximum time in seconds that the server will wait for a client to establish a connection before timing out.
     * @param seconds The connection timeout value in seconds.
     */
    void setConnectionTimeout(int seconds) override;

    /**
     * @brief Adds an IP address to the list of blocked IPs.
     *
     * This function adds an IP address to the list of blocked IPs. Requests originating from the blocked IPs will be denied by the server.
     * @param ip The IP address to be blocked.
     */
    void addBlockedIp(const std::string& ip) override;

    /**
     * @brief Adds an IP address to the list of allowed IPs.
     *
     * This function adds an IP address to the list of allowed IPs. Requests originating from the allowed IPs will be accepted by the server.
     * @param ip The IP address to be allowed.
     */
    void addAllowedIp(const std::string& ip) override;

    /**
     * @brief Sets the handler for the not found (404) error.
     *
     * This function sets the handler for the not found (404) error. It specifies the function or callback to be executed when a requested resource is not found.
     * @param handler The handler function or callback for the not found error.
     */
    void setNotFoundHandler(const Handler& handler);

    /**
     * @brief Enables access logging for the web server.
     *
     * This function enables access logging for the web server. When enabled, the server will log each incoming request for access analysis and auditing.
     */
    void enableAccessLogging() override;

    /**
     * @brief Disables access logging for the web server.
     *
     * This function disables access logging for the web server. When disabled, the server will not generate access logs for incoming requests.
     */
    void disableAccessLogging() override;

    /**
     * @brief Sets the exception error handler for the web server.
     *
     * This function sets the exception error handler for the web server. It specifies the function or callback to be executed when an exception occurs during request handling.
     * @param handler The handler function or callback for exception errors.
     */
    void setExceptionHandler(const ExceptionErrorHandler& handler);

    /**
     * @brief Sets the server header name for the web server.
     *
     * This function sets the server header name for the web server. It specifies the name or identifier that will be included in the response headers to identify the server.
     * @param serverName The name or identifier to be used in the server header.
     */
    void setServerHeader(const std::string& serverName) override;

    /**
     * @brief Sets whether static file caching is enabled.
     *
     * This function sets whether static file caching is enabled for the web server. When enabled, the server will cache static files to improve performance.
     * @param enabled Set to `true` to enable static file caching, or `false` to disable it.
     */
    void setStaticFileCacheEnabled(bool enabled) override;

    /**
     * @brief Sets the time-to-live (TTL) value for static file cache.
     *
     * This function sets the time-to-live (TTL) value for the static file cache. It determines how long the cached static files will be considered valid before they expire.
     * @param ttlSeconds The TTL value in seconds for the static file cache.
     */
    void setStaticFileCacheTtl(int ttlSeconds) override;

    /**
     * @brief Sets whether load balancing is enabled.
     *
     * This function sets whether load balancing is enabled for the web server. When enabled, the server will distribute incoming requests across multiple backend servers.
     * @param enabled Set to `true` to enable load balancing, or `false` to disable it.
     */
    void setLoadBalancingEnabled(bool enabled) override;

    /**
     * @brief Sets the backend servers for load balancing.
     *
     * This function sets the backend servers for load balancing. It specifies the addresses or URLs of the backend servers to which the server will distribute incoming requests.
     * @param backendServers A vector of strings representing the backend server addresses or URLs.
     */
    void setBackendServers(const std::vector<std::string>& backendServers) override;

    /**
     * @brief Sets the session lifetime for the web server.
     *
     * This function sets the session lifetime for the web server. It determines the duration in seconds for which a session will remain active before expiring.
     * @param lifetimeSeconds The session lifetime value in seconds.
     */
    void setSessionLifetime(int lifetimeSeconds) override;

    /**
     * @brief Sets the session cookie name for the web server.
     *
     * This function sets the session cookie name for the web server. It specifies the name of the cookie used to store the session ID.
     * @param name The name of the session cookie.
     */
    void setSessionCookieName(const std::string& name) override;

    /**
     * @brief Sets the session cookie lifetime for the web server.
     *
     * This function sets the session cookie lifetime for the web server. It determines the duration in seconds for which the session cookie will remain valid.
     * @param lifetimeSeconds The session cookie lifetime value in seconds.
     */
    void setSessionCookieLifetime(int lifetimeSeconds) override;

    /**
     * @brief Enables sessions for the web server.
     *
     * This function enables sessions for the web server. When enabled, the server will manage and maintain session data for client requests.
     */
    void enableSessions() override;

    /**
     * @brief Disables sessions for the web server.
     *
     * This function disables sessions for the web server. When disabled, the server will not manage or maintain session data for client requests.
     */
    void disableSessions() override;

    /**
     * @brief Adds a trusted proxy IP address.
     *
     * This function adds a trusted proxy IP address to the web server's list of trusted proxies. Requests coming from these IP addresses will be considered secure and trustworthy.
     * @param ip The IP address of the trusted proxy to add.
     */
    void addTrustedProxy(const std::string& ip);

    /**
     * @brief Sets the maximum request size.
     *
     * This function sets the maximum size of incoming requests that the web server can handle. Requests larger than this size will be rejected or handled differently based on server configuration.
     * @param maxSize The maximum request size in bytes.
     */
    void setMaxRequestSize(int maxSize);

    /**
     * @brief Sets the maximum number of connections.
     *
     * This function sets the maximum number of simultaneous connections that the web server can handle. Once this limit is reached, new connections will be rejected until existing connections are closed.
     * @param maxConnections The maximum number of connections.
     */
    void setMaxConnections(int maxConnections);

    /**
     * @brief Sets the keep-alive timeout.
     *
     * This function sets the timeout value for keep-alive connections. After the specified duration of inactivity, keep-alive connections will be closed by the server.
     * @param timeoutSeconds The keep-alive timeout value in seconds.
     */
    void setKeepAliveTimeout(int timeoutSeconds);

    /**
     * @brief Sets the maximum number of requests per connection.
     *
     * This function sets the maximum number of requests that can be processed on a single connection before the connection is closed. This helps prevent excessive resource usage.
     * @param maxRequests The maximum number of requests per connection.
     */
    void setMaxRequestsPerConnection(int maxRequests);

    /**
     * @brief Reads the content of a file.
     *
     * This function reads the content of a file and returns it as a string.
     * @param filePath The path to the file to read.
     * @return The content of the file as a string.
     */
    std::string readFileContent(const std::string& filePath);

    /**
     * @brief Gets the MIME type of a file.
     *
     * This function determines the MIME type of a file based on its file extension.
     * @param filePath The path to the file for which to determine the MIME type.
     * @return The MIME type of the file.
     */
    std::string getMimeType(const std::string& filePath);

    /**
     * @brief Adds a static file mapping.
     *
     * This function adds a mapping between a URL path and a corresponding static file. When a request matches the specified URL path, the server will serve the corresponding file.
     * @param urlPath The URL path for which to serve the static file.
     * @param filePath The path to the static file on the server's filesystem.
     */
    void addStaticFile(const std::string& urlPath, const std::string& filePath);

private:
    ServerStructure m_serverStructure;  //!< The server structure object.
    EventLoop m_eventLoop;              //!< The event loop object.
    EventLoopType m_eventLoopType;      //!< The type of event loop used by the server.

};

CELL_NAMESPACE_END

#endif  // CELL_WEBSERVER_HPP

