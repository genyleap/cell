#if __has_include("webserver.hpp")
#   include "webserver.hpp"
#else
#   error "Cell's webserver was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core/core was not found!"
#endif

#if __has_include("classes/mediatypes.hpp")
#   include "classes/mediatypes.hpp"
#else
#   error "Cell's classes/mediatypes.hpp was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Globals;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Globals::Storage;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

WebServer::WebServer(EventLoopType loopType) : m_eventLoop(loopType)
{
    // Initialize the SSL library
    SSL_library_init();
    SSL_load_error_strings();
    m_eventLoopType = loopType;
}

WebServer::~WebServer()
{
    stop();
    ERR_free_strings();
    EVP_cleanup();
}

void WebServer::start(int port)
{
    EngineController ec;
    auto& engine = ec.getEngine();

    // Set the custom error 404 page handler
    m_serverStructure.router.setNotFoundHandler(m_serverStructure.notFoundHandler);

    // Set the custom other error page handler
    m_serverStructure.router.setExceptionHandler(m_serverStructure.exceptionErrorHandler);

    if (m_serverStructure.enableSsl) {
        if (m_serverStructure.isRunning) {
            Log("Web server is already running.", LoggerType::Success);
            return;
        }

        m_serverStructure.port = port;

        try {

            // Create an SSL context
            SSL_CTX* sslContext = SSL_CTX_new(TLS_server_method());
            if (!sslContext) {
                Log("Failed to create SSL context.", LoggerType::Critical);
                throw std::runtime_error("Failed to create SSL context.");
            }

            if (SSL_CTX_use_certificate_file(sslContext, m_serverStructure.sslCertFile.c_str(), SSL_FILETYPE_PEM) <= 0 ||
                SSL_CTX_use_PrivateKey_file(sslContext, m_serverStructure.sslKeyFile.c_str(), SSL_FILETYPE_PEM) <= 0)
            {
                Log("Failed to load server certificate or private key.", LoggerType::Critical);
                throw std::runtime_error("Failed to load server certificate or private key.");
            }

            int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (serverSocket < 0) {
                Log("Failed to create server socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to create server socket.");
            }

            sockaddr_in serverAddress{};
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            serverAddress.sin_port = htons(port);

            if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
                Log("Failed to bind server socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to bind server socket.");
            }

            if (listen(serverSocket, SOMAXCONN) < 0) {
                Log("Failed to listen on server socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to listen on server socket.");
            }

            m_serverStructure.isRunning = true;
            Log("Web server started on port: " + TO_CELL_STRING(port), LoggerType::Critical);
            // Start the event loop in a separate thread
            m_eventLoop.start();

            while (m_serverStructure.isRunning) {
                sockaddr_in clientAddress{};
                socklen_t clientAddressLength = sizeof(clientAddress);
                int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
                if (clientSocket < 0) {
                    Log("Failed to accept client connection: " + FROM_CELL_STRING(strerror(errno)), LoggerType::Critical);
                    continue;
                }

                SSL* ssl = SSL_new(sslContext);
                if (!ssl) {
                    Log("Failed to create SSL object.", LoggerType::Critical);
                    close(clientSocket);
                    continue;
                }

                if (SSL_set_fd(ssl, clientSocket) != 1) {
                    Log("Failed to set SSL file descriptor.", LoggerType::Critical);
                    SSL_free(ssl);
                    close(clientSocket);
                    continue;
                }

                if (SSL_accept(ssl) <= 0) {
                    Log("SSL handshake failed.", LoggerType::Warning);
                    ERR_print_errors_fp(stderr);
                    SSL_free(ssl);
                    close(clientSocket);
                    continue;
                }

                // Add a task to the event loop to handle the client request
                m_eventLoop.addTask([=]() {
                    handleClientRequestSSL(clientSocket, ssl);
                    int shutdownResult = SSL_shutdown(ssl);
                    if (shutdownResult == 0) {
                        shutdownResult = SSL_shutdown(ssl);
                    }
                    if (shutdownResult < 0) {
                        Log("SSL shutdown failed.", LoggerType::Warning);
                    }
                    SSL_free(ssl);
                    close(clientSocket);
                });
            }

            SSL_CTX_free(sslContext);


            close(serverSocket);
        } catch (const Exception& ex) {
            Log("Error starting web server: " + FROM_CELL_STRING(ex.what()), LoggerType::Critical);
        }
    } else {
        if (m_serverStructure.isRunning) {
            Log("Web server is already running.", LoggerType::Success);
            return;
        }

        m_serverStructure.port = port;

        try {
            // Initialize the socket library (Windows only)
#ifdef _WIN32
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                throw std::runtime_error("Failed to initialize winsock.");
            }
#endif

            // Create a socket for the server
            m_serverStructure.serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (m_serverStructure.serverSocket == -1) {
                Log("Failed to create socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to create socket.");
            }

            // Bind the socket to the specified port
            sockaddr_in serverAddress{};
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_addr.s_addr = INADDR_ANY;
            serverAddress.sin_port = htons(m_serverStructure.port);

            if (bind(m_serverStructure.serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
                Log("Failed to bind socket to port " + TO_CELL_STRING(m_serverStructure.port) + ".", LoggerType::Critical);
                throw std::runtime_error("Failed to bind socket to port " + std::to_string(m_serverStructure.port) + ".");
            }

            // Start listening for client connections
            if (listen(m_serverStructure.serverSocket, WEBSERVER_CONSTANTS::MAX_CONNECTIONS) < 0)
            {
                Log("Failed to start listening on port " + TO_CELL_STRING(m_serverStructure.port) + ".", LoggerType::Critical);
                throw std::runtime_error("Failed to start listening on port " + std::to_string(m_serverStructure.port) + ".");
            }

            m_serverStructure.isRunning = true;
            Log("Web server started on port " + TO_CELL_STRING(m_serverStructure.port) + ".", LoggerType::Info);

            // Start the event loop in a separate thread
            m_eventLoop.start();

            while (m_serverStructure.isRunning) {
                try {
                    sockaddr_in clientAddress{};
                    socklen_t clientAddressLength = sizeof(clientAddress);

                    // Accept a client connection
                    SocketType clientSocket = accept(m_serverStructure.serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
                    if (clientSocket < 0) {
                        Log("Failed to accept client connection.", LoggerType::Critical);
                        throw std::runtime_error("Failed to accept client connection.");
                    }

                    // Add a task to the event loop to handle the client request
                    m_eventLoop.addTask([=]() {
                        handleClientRequestNoSSL(clientSocket);
                        close(clientSocket);
                    });
                } catch (const Exception& ex) {
                    Log("An error occurred: " + FROM_CELL_STRING(ex.what()), LoggerType::Critical);
                    close(m_serverStructure.serverSocket);
                    stop(); // Stop the server to ensure proper cleanup
                }
            }

            // Close the server socket
            close(m_serverStructure.serverSocket);

// Cleanup the socket library (Windows only)
#ifdef _WIN32
            WSACleanup();
#endif
            Log("Web server stopped.", LoggerType::Critical);
        } catch (const Exception& ex) {
            Log("An error occurred: " + FROM_CELL_STRING(ex.what()), LoggerType::Critical);
            stop(); // Stop the server to ensure proper cleanup
        }
    }
}

void WebServer::stop() {
    if (!m_serverStructure.isRunning) {
        return;
    }

    m_serverStructure.isRunning = false;

    // Close the server socket
    close(m_serverStructure.serverSocket);

    Log("Web server stopped.", LoggerType::Critical);
}

bool WebServer::isRunning() const {
    return m_serverStructure.isRunning;
}

void WebServer::registerRouter(const Router& router) {
    m_serverStructure.router = router;
}

void WebServer::parseRequest(const std::string& requestString, Request& request) {
    std::istringstream iss(requestString);

    // Parse the first line of the request
    std::string method, path, version;
    if (!(iss >> method >> path >> version)) {
        Log("Invalid request line", LoggerType::Critical);
        throw std::runtime_error("Invalid request line");
    }

    // Set the method and path in the request object
    request.setMethod(method);
    request.setPath(path);

    // Parse the headers
    std::string line;
    while (std::getline(iss, line) && !line.empty()) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            // Trim leading and trailing whitespace from the key and value
            key = std::regex_replace(key, std::regex("^\\s+|\\s+$"), "");
            value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
            // Set the header in the request object
            request.setHeader(key, value);
        }
    }

    // Set the remaining data as the request body
    std::ostringstream requestBodyStream;
    while (std::getline(iss, line)) {
        requestBodyStream << line << "\n";
    }

    // Set the body in the request object
    std::string requestBody = requestBodyStream.str();
    if (!requestBody.empty()) {
        // Remove the trailing newline character
        requestBody.pop_back();
        request.setBody(requestBody);
    }
}

std::string WebServer::getStatusMessage(int statusCode)
{
    switch (statusCode) {
    case 200:
        return "OK";
    case 400:
        return "Bad Request";
    case 404:
        return "Not Found";
    case 500:
        return "Internal Server Error";
    // Add more status codes and messages as needed
    default:
        return "Unknown Status";
    }
}

std::string WebServer::responseToString(const Response& response)
{
    std::stringstream ss;

    // Write the status line
    ss << "HTTP/1.1 " << response.statusCode() << " " << getStatusMessage(response.statusCode()) << "\r\n";

    // Write the headers
    ss << "Content-Type: " << response.contentType().value() << "\r\n";
    ss << "Content-Length: " << response.content().value().length() << "\r\n";

    // Write a blank line to separate headers from content
    ss << "\r\n";

    // Write the content
    ss << response.content().value();

    return ss.str();
}

std::string WebServer::getClientIP(SocketType clientSocket) {
    struct sockaddr_storage addrStorage;
    socklen_t addrLength = sizeof(addrStorage);

    if (getpeername(clientSocket, reinterpret_cast<struct sockaddr*>(&addrStorage), &addrLength) < 0)
    {
        Log("Error getting client IP address.", LoggerType::Critical);
        return "";
    }

    if (addrStorage.ss_family == AF_INET) {
        struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(&addrStorage);
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr->sin_addr), clientIP, INET_ADDRSTRLEN);
        return std::string(clientIP);
    } else if (addrStorage.ss_family == AF_INET6) {
        struct sockaddr_in6* addr = reinterpret_cast<struct sockaddr_in6*>(&addrStorage);
        char clientIP[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(addr->sin6_addr), clientIP, INET6_ADDRSTRLEN);
        return std::string(clientIP);
    }
    Log("Unknown address family.", LoggerType::Critical);
    return "";
}


void WebServer::handleClientRequestNoSSL(SocketType clientSocket)
{
    // Receive the client request
    const int bufferSize = 4096;
    std::array<char, bufferSize> buffer;
    std::fill(buffer.begin(), buffer.end(), 0);
    ssize_t bytesRead = recv(clientSocket, buffer.data(), bufferSize - 1, 0);
    if (bytesRead < 0) {
        Log("Error reading client request.", LoggerType::Critical);
        close(clientSocket);
        return;
    }

    std::string_view requestString(buffer.data(), bytesRead);
    Request request;
    parseRequest(std::string(requestString), request);

    // Get the client IP address
    std::string clientIP = getClientIP(clientSocket);

    // Check if rate limiting is enabled and apply rate limit
    if (m_serverStructure.rateLimiter && !m_serverStructure.rateLimiter->allowRequest(clientIP)) {
        // Return a response indicating rate limit exceeded
        Response response;
        response.setStatusCode(429); // Too Many Requests
        response.setContentType("text/plain");
        response.setContent("Rate limit exceeded. Please try again later.");

        // Send the response to the client
        std::string responseString = responseToString(response);
        const char* responseData = responseString.c_str();
        size_t responseLength = responseString.length();
        ssize_t bytesSent = 0;
        while (bytesSent < responseLength) {
            ssize_t sent = send(clientSocket, responseData + bytesSent, responseLength - bytesSent, MSG_NOSIGNAL);
            if (sent < 0) {
                if (errno == EINTR) {
                    // The send operation was interrupted, try again
                    continue;
                } else if (errno == EPIPE || errno == ECONNRESET) {
                    // Client closed the connection, but we can continue processing requests
                    break;
                } else {
                    Log("Error sending response to client. Error code:" + TO_CELL_STRING(errno), LoggerType::Critical);
                    close(clientSocket);
                    return;
                }
            } else if (sent == 0) {
                // Client closed the connection, but we can continue processing requests
                break;
            }
            bytesSent += sent;
        }

        // Check if the entire response was sent successfully
        if (bytesSent == responseLength) {
            // Response sent successfully, connection remains open
            // Continue processing requests or wait for next request
        } else {
            // Error occurred while sending response or client closed the connection
            close(clientSocket);
        }

        return;
    }

    // Check if the requested URL corresponds to a static file
    std::string requestedPath = request.path().value();
    if (requestedPath.substr(0, m_serverStructure.documentRoot.length() + 1) == "/" + m_serverStructure.documentRoot) {
        std::string filePath = m_serverStructure.documentRoot + requestedPath.substr(m_serverStructure.documentRoot.length() + 1);
        std::ifstream file(filePath, std::ios::binary);
        if (file) {
            // Read the file content
            std::ostringstream fileContentStream;
            fileContentStream << file.rdbuf();
            std::string fileContent = fileContentStream.str();

            MediaTypes mt;
            std::string extension = filePath.substr(filePath.find_last_of(".") + 1);

            // Determine the MIME type based on the file extension
            std::string mimeType = mt.getMimeType(extension);

            // Create a response with the file content and MIME type
            Response response;
            response.setStatusCode(200);
            response.setContentType(mimeType);
            response.setContent(fileContent);

            // Check if the socket has any errors or closed connection
            struct pollfd pfd;
            pfd.fd = clientSocket;
            pfd.events = POLLRDNORM | POLLERR;
            int pollResult = poll(&pfd, 1, 0);
            if (pollResult < 0 || (pfd.revents & POLLERR) != 0) {
                Log("Socket error or closed connection detected." , LoggerType::Critical);
                close(clientSocket);
                return;
            }

            // Send the response to the client
            std::string responseString = responseToString(response);
            const char* responseData = responseString.c_str();
            size_t responseLength = responseString.length();
            ssize_t bytesSent = 0;
            while (bytesSent < responseLength) {
                ssize_t sent = send(clientSocket, responseData + bytesSent, responseLength - bytesSent, MSG_NOSIGNAL);
                if (sent < 0) {
                    if (errno == EINTR) {
                        // The send operation was interrupted, try again
                        continue;
                    } else if (errno == EPIPE || errno == ECONNRESET) {
                        // Client closed the connection, but we can continue processing requests
                        break;
                    } else {
                        Log("Error sending response to client. Error code: " + TO_CELL_STRING(errno), LoggerType::Critical);
                        close(clientSocket);
                        return;
                    }
                } else if (sent == 0) {
                    // Client closed the connection, but we can continue processing requests
                    break;
                }
                bytesSent += sent;
            }

            // Check if the entire response was sent successfully
            if (bytesSent == responseLength) {
                // Response sent successfully, connection remains open
                // Continue processing requests or wait for next request
            } else {
                // Error occurred while sending response or client closed the connection
                close(clientSocket);
            }


            file.close();
        } else {
            Log("Failed to open file: " + FROM_CELL_STRING(filePath), LoggerType::Critical);
        }
    }

    // Route the request and get the response
    Response response = m_serverStructure.router.routeRequest(request);

    // Check if sessions are enabled
    if (m_serverStructure.sessionsEnabled) {
        // Check if the request has a session ID cookie
        std::string sessionId = request.cookies().getSessionIdCookie().value();
        if (sessionId.empty()) {
            // If no session ID cookie is found, create a new session
            Sessions session = Sessions::startSession();
            sessionId = session.getSessionId().value();
            response.setCookie("sessionId", sessionId);
        } else {
            // If a session ID cookie is found, retrieve the session data
            Sessions session = Sessions::retrieveSessionData(sessionId);
            if (session.isExpired()) {
                // If the session is expired, destroy the session and create a new one
                session.destroySession();
                session = Sessions::startSession();
                sessionId = session.getSessionId().value();
                response.setCookie("sessionId", sessionId);
            } else {
                // If the session is valid, update the session expiration time
                session.setExpirationTime(Sessions::getDefaultExpirationTime());
                session.storeSessionData();
            }
        }

        // Update the session ID in the request
        request.setSessionId(sessionId);
    }

    // Send the response to the client
    std::string responseString = responseToString(response);
    ssize_t bytesSent = send(clientSocket, responseString.c_str(), responseString.length(), 0);
    if (bytesSent < 0) {
        Log("Error sending response to client.", LoggerType::Critical);
    }

    // Close the client socket
    close(clientSocket);
}

void WebServer::handleClientRequestSSL(SocketType clientSocket, SSL* ssl)
{
    try {

        // Receive the client request over SSL
        constexpr const int bufferSize = 4096;
        std::vector<char> buffer(bufferSize);  // Use a resizable buffer
        ssize_t bytesRead = SSL_read(ssl, buffer.data(), buffer.size() - 1);
        if (bytesRead <= 0) {
            Log("Error reading client request.", LoggerType::Critical);
            throw std::runtime_error("Error reading client request.");
        }

        std::string_view requestString(buffer.data(), bytesRead);
        Request request;
        parseRequest(std::string(requestString), request);

        // Get the client IP address
        std::string clientIP = getClientIP(clientSocket);

        // Check if rate limiting is enabled and apply rate limit
        if (m_serverStructure.rateLimiter && !m_serverStructure.rateLimiter->allowRequest(clientIP)) {
            // Return a response indicating rate limit exceeded
            Response response;
            response.setStatusCode(429); // Too Many Requests
            response.setContentType("text/plain");
            response.setContent("Rate limit exceeded. Please try again later.");

            // Send the response to the client over SSL
            std::stringstream responseStream;
            responseStream << "HTTP/1.1 " << response.statusCode() << " OK\r\n";
            responseStream << "Content-Type: " << response.contentType().value() << "\r\n";
            for (const auto& header : response.headers()) {
                responseStream << header.first << ": " << header.second << "\r\n";
            }
            responseStream << "\r\n";
            responseStream << response.content().value();

            std::string responseString = responseStream.str();
            ssize_t bytesSent = SSL_write(ssl, responseString.c_str(), responseString.length());
            if (bytesSent < 0) {
                Log("Error sending response to client.", LoggerType::Critical);
                throw std::runtime_error("Error sending response to client.");
            }
            Log("Rate limit exceeded.", LoggerType::Critical);
            throw std::runtime_error("Rate limit exceeded.");
        }
        // Check if the requested URL corresponds to a static file
        std::string requestedPath = request.path().value();

        if (requestedPath.substr(0, m_serverStructure.documentRoot.length() + 1) == "/" + m_serverStructure.documentRoot)
        {
            std::string filePath = m_serverStructure.documentRoot + requestedPath.substr(m_serverStructure.documentRoot.length() + 1);
            std::ifstream file(filePath, std::ios::binary);
            if (file) {
                // Read the file content
                std::ostringstream fileContentStream;
                fileContentStream << file.rdbuf();
                std::string fileContent = fileContentStream.str();

                MediaTypes mt;
                std::string extension = filePath.substr(filePath.find_last_of(".") + 1);

                // Determine the MIME type based on the file extension
                std::string mimeType = mt.getMimeType(extension);

                // Create a response with the file content and MIME type
                Response response;
                response.setStatusCode(200);
                response.setContentType(mimeType);
                response.setContent(fileContent);

                // Check if the socket has any errors or closed connection
                struct pollfd pfd;
                pfd.fd = clientSocket;
                pfd.events = POLLRDNORM | POLLERR;
                int pollResult = poll(&pfd, 1, 0);
                if (pollResult < 0 || (pfd.revents & POLLERR) != 0) {
                    Log("Socket error or closed connection detected.", LoggerType::Critical);
                    close(clientSocket);
                    return;
                }

                // Send the response to the client
                std::string responseString = responseToString(response);
                const char* responseData = responseString.c_str();
                size_t responseLength = responseString.length();
                ssize_t bytesSent = 0;
                while (bytesSent < responseLength) {
                    ssize_t sent = SSL_write(ssl, responseString.c_str(), responseString.length());
                    if (sent < 0) {
                        if (errno == EINTR) {
                            // The send operation was interrupted, try again
                            continue;
                        } else if (errno == EPIPE || errno == ECONNRESET) {
                            // Client closed the connection, but we can continue processing requests
                            break;
                        } else {
                            Log("Error sending response to client. Error code" + TO_CELL_STRING(errno), LoggerType::Critical);
                            close(clientSocket);
                            return;
                        }
                    } else if (sent == 0) {
                        // Client closed the connection, but we can continue processing requests
                        break;
                    }
                    bytesSent += sent;
                }

                // Check if the entire response was sent successfully
                if (bytesSent == responseLength) {
                    // Response sent successfully, connection remains open
                    // Continue processing requests or wait for next request
                } else {
                    // Error occurred while sending response or client closed the connection
                    close(clientSocket);
                }


                file.close();
            } else {
                Log("Failed to open file: " + FROM_CELL_STRING(filePath), LoggerType::Critical);
            }
        }

        // Route the request and get the response
        Response response = m_serverStructure.router.routeRequest(request);

        // Check if sessions are enabled
        if (m_serverStructure.sessionsEnabled) {
            // Check if the request has a session ID cookie
            std::string sessionId = request.cookies().getSessionIdCookie().value();
            if (sessionId.empty()) {
                // If no session ID cookie is found, create a new session
                Sessions session = Sessions::startSession();
                sessionId = session.getSessionId().value();
                response.setCookie("sessionId", sessionId);
            } else {
                // If a session ID cookie is found, retrieve the session data
                Sessions session = Sessions::retrieveSessionData(sessionId);
                if (session.isExpired()) {
                    // If the session is expired, destroy the session and create a new one
                    session.destroySession();
                    session = Sessions::startSession();
                    sessionId = session.getSessionId().value();
                    response.setCookie("sessionId", sessionId);
                } else {
                    // If the session is valid, update the session expiration time
                    session.setExpirationTime(Sessions::getDefaultExpirationTime());
                    session.storeSessionData();
                }
            }

            // Update the session ID in the request
            request.setSessionId(sessionId);
        }

        // Prepare the response string
        std::stringstream responseStream;
        responseStream << "HTTP/1.1 " << response.statusCode() << " OK\r\n";
        responseStream << "Content-Type: " << response.contentType().value() << "\r\n";
        for (const auto& header : response.headers()) {
            responseStream << header.first << ": " << header.second << "\r\n";
        }
        responseStream << "\r\n";
        responseStream << response.content().value();

        // Send the response to the client over SSL
        std::string responseString = responseToString(response);
        const char* responseData = responseString.c_str();
        size_t responseLength = responseString.length();
        ssize_t bytesSent = 0;
        while (bytesSent < responseLength) {
            ssize_t sent = SSL_write(ssl, responseData + bytesSent, responseLength - bytesSent);
            if (sent < 0) {
                if (errno == EINTR) {
                    // The send operation was interrupted, try again
                    continue;
                } else if (errno == EPIPE || errno == ECONNRESET) {
                    // Client closed the connection, but we can continue processing requests
                    break;
                } else {
                    Log("Error sending response to client. Error code: " + TO_CELL_STRING(errno), LoggerType::Critical);
                    close(clientSocket);
                    return;
                }
            } else if (sent == 0) {
                // Client closed the connection, but we can continue processing requests
                break;
            }
            bytesSent += sent;
        }


    } catch (const Exception& e) {
        Log("SSL Error: " + FROM_CELL_STRING(e.what()), LoggerType::Critical);
    }

}

void WebServer::addStaticFile(const std::string& urlPath, const std::string& filePath)
{
    m_serverStructure.staticFiles[urlPath] = filePath;
}

void WebServer::setDocumentRoot(const std::string& docRoot)
{
    m_serverStructure.documentRoot = docRoot;
}

void WebServer::setErrorPage(const std::string& errorPage)
{
    m_serverStructure.errorPage = errorPage;
}

void WebServer::addRoute(const std::string& path, const Handler& handler)
{
    m_serverStructure.routes[path] = handler;
}


void WebServer::addMiddleWare(const std::function<Response(const Request&, const std::function<Response(const Request&)>&)>& middleware)
{
    m_serverStructure.middleware.push_back(middleware);
}

void WebServer::setAuthenticationHandler(const std::function<bool(const Request&)>& authenticationHandler)
{
    m_serverStructure.authenticationHandler = authenticationHandler;
}

void WebServer::setAuthorizationHandler(const std::function<bool(const Request&)>& authorizationHandler)
{
    m_serverStructure.authorizationHandler = authorizationHandler;
}

void WebServer::setCachingHandler(const std::function<void(const std::string&, const std::string&)>& cachingHandler)
{
    m_serverStructure.cachingHandler = cachingHandler;
}

void WebServer::setLoadBalancingAlgorithm(const std::string& algorithm)
{
    m_serverStructure.loadBalancingAlgorithm = algorithm;
}

void WebServer::setRateLimit(int maxRequestsPerMinute) {
    m_serverStructure.rateLimiter = std::make_unique<RateLimiter>(maxRequestsPerMinute);
}

void WebServer::setThreadPoolSize(int poolSize)
{
    m_serverStructure.threadPoolSize = poolSize;
}

void WebServer::setEventLoopType(EventLoopType type)
{
    m_eventLoopType = type;
}

void WebServer::enableSSL(const bool status)
{
    m_serverStructure.enableSsl = status;
}

void WebServer::setSslCertFile(const std::string& filePath)
{
    m_serverStructure.sslCertFile = filePath;
}

void WebServer::setSslKeyFile(const std::string& filePath)
{
    m_serverStructure.sslKeyFile = filePath;
}

void WebServer::setSslCaFile(const std::string& filePath)
{
    m_serverStructure.sslCaFile = filePath;
}

void WebServer::setSslVerifyPeer(bool verifyPeer)
{
    m_serverStructure.sslVerifyPeer = verifyPeer;
}

void WebServer::setHttp2Enabled(bool enabled)
{
    m_serverStructure.http2Enabled = enabled;
}

void WebServer::setHttp3Enabled(bool enabled)
{
    m_serverStructure.http3Enabled = enabled;
}

void WebServer::addCdn(const std::string& cdn_url)
{
    m_serverStructure.cdnUrls.push_back(cdn_url);
}

void WebServer::enableCdn()
{
    m_serverStructure.cdnEnabled = true;
}

void WebServer::disableCdn()
{
    m_serverStructure.cdnEnabled = false;
}

void WebServer::setCompressionEnabled(bool enabled)
{
    m_serverStructure.compressionEnabled = enabled;
}

void WebServer::setCompressionLevel(int level)
{
    m_serverStructure.compressionLevel = level;
}

void WebServer::setCompressionTypes(const std::vector<std::string>& types)
{
    m_serverStructure.compressionTypes = types;
}

void WebServer::enableLogging()
{
    m_serverStructure.loggingEnabled = true;
}

void WebServer::disableLogging()
{
    m_serverStructure.loggingEnabled = false;
}

void WebServer::setLogFile(const std::string& filePath)
{
    m_serverStructure.logFile = filePath;
}

void WebServer::enableMonitoring()
{
    m_serverStructure.monitoringEnabled = true;
}

void WebServer::disableMonitoring()
{
    m_serverStructure.monitoringEnabled = false;
}

void WebServer::setMonitoringPort(int port)
{
    m_serverStructure.monitoringPort = port;
}

void WebServer::enableReverseProxy() {
    m_serverStructure.reverseProxyEnabled = true;
}

void WebServer::disableReverseProxy() {
    m_serverStructure.reverseProxyEnabled = false;
}

void WebServer::setUpstreamServers(const std::vector<std::string>& upstreamServers)
{
    m_serverStructure.upstreamServers = upstreamServers;
}

void WebServer::setProxyPass(const std::string& proxyPass) {
    m_serverStructure.proxyPass = proxyPass;
}

void WebServer::setProxyBuffering(bool buffering) {
    m_serverStructure.proxyBuffering = buffering;
}

void WebServer::setProxyCache(const std::string& proxyCache)
{

}

void WebServer::setProxyCacheTtl(int proxyCacheTtl)
{

}

void WebServer::addVirtualHost(const std::string& hostname, const VirtualHostConfig& config)
{
    m_serverStructure.virtualHosts[hostname] = config;
}

void WebServer::setConnectionTimeout(int seconds)
{

}

void WebServer::addBlockedIp(const std::string& ip)
{

}

void WebServer::addAllowedIp(const std::string& ip)
{

}

void WebServer::setNotFoundHandler(const Handler& handler)
{
    m_serverStructure.notFoundHandler = handler;
}

void WebServer::enableAccessLogging()
{
    m_serverStructure.isAccessLoggingEnabled = true;
}

void WebServer::disableAccessLogging()
{
    m_serverStructure.isAccessLoggingEnabled = true;
}

void WebServer::setExceptionHandler(const ExceptionErrorHandler& exceptionErrorHandler)
{
    m_serverStructure.exceptionErrorHandler = exceptionErrorHandler;
}

void WebServer::setServerHeader(const std::string& serverName)
{
    m_serverStructure.serverHeader = serverName;
}

void WebServer::setStaticFileCacheEnabled(bool enabled)
{
    m_serverStructure.staticFileCacheEnabled = enabled;
}

void WebServer::setStaticFileCacheTtl(int ttlSeconds)
{
    m_serverStructure.staticFileCacheTtl = ttlSeconds;
}

void WebServer::setLoadBalancingEnabled(bool enabled)
{
    m_serverStructure.loadBalancingEnabled = enabled;
}

void WebServer::setBackendServers(const std::vector<std::string>& backendServers)
{
    m_serverStructure.backendServers = backendServers;
}

void WebServer::setSessionLifetime(int lifetimeSeconds) {
    m_serverStructure.sessionLifetime = lifetimeSeconds;
}

void WebServer::setSessionCookieName(const std::string& name)
{
    m_serverStructure.sessionCookieName = name;
}

void WebServer::setSessionCookieLifetime(int lifetimeSeconds)
{
    m_serverStructure.sessionCookieLifetime = lifetimeSeconds;
}

void WebServer::enableSessions()
{
    m_serverStructure.sessionsEnabled = true;
}

void WebServer::disableSessions()
{
    m_serverStructure.sessionsEnabled = false;
}

void WebServer::addTrustedProxy(const std::string& ip)
{
    m_serverStructure.trustedProxies.push_back(ip);
}

void WebServer::setMaxRequestSize(int maxSize)
{
    m_serverStructure.maxRequestSize = maxSize;
}

void WebServer::setMaxConnections(int maxConnections)
{
    m_serverStructure.maxConnections = maxConnections;
}

void WebServer::setKeepAliveTimeout(int timeoutSeconds)
{
    m_serverStructure.keepAliveTimeout = timeoutSeconds;
}

void WebServer::setMaxRequestsPerConnection(int maxRequests)
{
    m_serverStructure.maxRequestsPerConnection = maxRequests;
}

std::string WebServer::readFileContent(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (file) {
        // Read the file content into a string
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } else {
        // File not found or unable to open
        return "";
    }
}

CELL_NAMESPACE_END
