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

void WebServer::start(int port) {
    EngineController ec;
    auto& engine = ec.getEngine();

    m_serverStructure.router.setNotFoundHandler(m_serverStructure.notFoundHandler);
    m_serverStructure.router.setExceptionHandler(m_serverStructure.exceptionErrorHandler);

    if (m_serverStructure.enableSsl) {
        if (m_serverStructure.isRunning) {
            Log("Web server is already running.", LoggerType::Success);
            return;
        }

        m_serverStructure.port = port;

        try {
            // Initialize SSL library
            SSL_library_init();
            OpenSSL_add_all_algorithms();
            SSL_load_error_strings();

            // Create an SSL context
            SSL_CTX* sslContext = SSL_CTX_new(TLS_server_method());
            if (!sslContext) {
                Log("Failed to create SSL context.", LoggerType::Critical);
                throw std::runtime_error("Failed to create SSL context.");
            }

            // Disable insecure protocols
            SSL_CTX_set_options(sslContext, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);
            SSL_CTX_set_min_proto_version(sslContext, TLS1_3_VERSION);

                   // Set cipher list
            if (SSL_CTX_set_cipher_list(sslContext, "HIGH:!aNULL:!MD5:!RC4") != 1) {
                Log("Failed to set cipher list.", LoggerType::Critical);
                throw std::runtime_error("Failed to set cipher list.");
            }

            // Load certificate and private key
            if (SSL_CTX_use_certificate_file(sslContext, m_serverStructure.sslCertFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
                Log("Failed to load server certificate.", LoggerType::Critical);
                throw std::runtime_error("Failed to load server certificate.");
            }

            if (SSL_CTX_use_PrivateKey_file(sslContext, m_serverStructure.sslKeyFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
                Log("Failed to load private key.", LoggerType::Critical);
                throw std::runtime_error("Failed to load private key.");
            }

            // Verify private key matches the certificate
            if (!SSL_CTX_check_private_key(sslContext)) {
                Log("Private key does not match the certificate.", LoggerType::Critical);
                throw std::runtime_error("Private key does not match the certificate.");
            }

            // Create server socket
            int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (serverSocket < 0) {
                Log("Failed to create server socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to create server socket.");
            }

            // Set socket options to reuse address
            int opt = 1;
            if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
                Log("Failed to set socket options.", LoggerType::Warning);
            }

            // Bind server socket
            sockaddr_in serverAddress{};
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            serverAddress.sin_port = htons(port);

            if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
                Log("Failed to bind server socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to bind server socket.");
            }

            // Listen for incoming connections
            if (listen(serverSocket, SOMAXCONN) < 0) {
                Log("Failed to listen on server socket.", LoggerType::Critical);
                throw std::runtime_error("Failed to listen on server socket.");
            }

            m_serverStructure.isRunning = true;
            Log("Web server started on port: " + TO_CELL_STRING(port), LoggerType::Success);

            // Start the event loop in a separate thread
            m_eventLoop.start();

            while (m_serverStructure.isRunning) {
                sockaddr_in clientAddress{};
                socklen_t clientAddressLength = sizeof(clientAddress);

                // Accept client connection
                int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
                if (clientSocket < 0) {
                    Log("Failed to accept client connection: " + FROM_CELL_STRING(strerror(errno)), LoggerType::Critical);
                    continue;
                }

                // Create SSL object
                SSL* ssl = SSL_new(sslContext);
                if (!ssl) {
                    Log("Failed to create SSL object.", LoggerType::Critical);
                    close(clientSocket);
                    continue;
                }

                // Associate SSL object with the client socket
                if (SSL_set_fd(ssl, clientSocket) != 1) {
                    Log("Failed to set SSL file descriptor.", LoggerType::Critical);
                    SSL_free(ssl);
                    close(clientSocket);
                    continue;
                }

                // Perform SSL handshake
                if (SSL_accept(ssl) <= 0) {
                    int sslError = SSL_get_error(ssl, -1);
                    Log("SSL handshake failed. Error: " + std::to_string(sslError), LoggerType::Warning);
                    ERR_print_errors_fp(stderr); // Print detailed SSL errors
                    SSL_free(ssl);
                    close(clientSocket);
                    continue;
                }

                // Add a task to the event loop to handle the client request
                m_eventLoop.addTask([=, this]() {
                    handleClientRequestSSL(clientSocket, ssl);

                    // Shutdown SSL connection
                    int shutdownResult = SSL_shutdown(ssl);
                    if (shutdownResult == 0) {
                        shutdownResult = SSL_shutdown(ssl); // Perform second phase of shutdown
                    }
                    if (shutdownResult < 0) {
                        Log("SSL shutdown failed.", LoggerType::Warning);
                    }

                    SSL_free(ssl);
                    close(clientSocket);
                });
            }

            // Clean up SSL context
            SSL_CTX_free(sslContext);
            close(serverSocket);
        } catch (const Exception& ex) {
            Log("Error starting web server: " + FROM_CELL_STRING(ex.what()), LoggerType::Critical);
        }
    } else {
        // Non-SSL mode (same as before)
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
            if (listen(m_serverStructure.serverSocket, WEBSERVER_CONSTANTS::MAX_CONNECTIONS) < 0) {
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
                    m_eventLoop.addTask([=, this]() {
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
        return; // If the server is not running, no need to proceed
    }

    m_serverStructure.isRunning = false; // Mark the server as stopped

    // Close all active client connections
    {
        std::lock_guard<std::mutex> lock(m_activeClientsMutex); // Ensure thread safety
        for (const auto& clientPair : m_activeClients) {
            const Types::SocketType& clientSocket = clientPair.first;
            if (clientSocket >= 0) { // Check if the socket is valid (POSIX sockets are non-negative integers)
                close(clientSocket); // Close each client socket
            }
        }
        m_activeClients.clear(); // Clear the map of active clients
    }

    // Close the server socket
    if (m_serverStructure.serverSocket >= 0) { // Check if the server socket is valid
        close(m_serverStructure.serverSocket);
        m_serverStructure.serverSocket = -1; // Reset the server socket to an invalid state
    }

    Log("Web server stopped.", LoggerType::Critical); // Log the server stop event
}


bool WebServer::isRunning() const {
    return m_serverStructure.isRunning;
}

size_t WebServer::getActiveClientCount() const {
    std::lock_guard<std::mutex> lock(m_activeClientsMutex); // Ensure thread safety
    return m_activeClients.size(); // Return the number of active clients
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

Response WebServer::error404Handler(const Request& request) {
    Response response;
    response.setStatusCode(404);
    response.setContentType("text/html");
    response.setContent(
        "<html>"
        "<head><title>404 Not Found</title></head>"
        "<body>"
        "<h1>404 Not Found</h1>"
        "<p>The requested page was not found!</p>"
        "</body>"
        "</html>"
        );
    return response;
}

void WebServer::handleClientRequestNoSSL(SocketType clientSocket) {
    try {
        // Add client to active connections
        {
            std::lock_guard<std::mutex> lock(m_activeClientsMutex);
            m_activeClients[clientSocket] = {
                clientSocket,
                getClientIP(clientSocket),
                std::chrono::steady_clock::now()
            };
        }

        for (const auto& [socket, clientInfo] : m_activeClients) {
            Log("Client: " + clientInfo.ipAddress + ", Connected at: " + std::to_string(clientInfo.connectionTime.time_since_epoch().count()), LoggerType::Info);
        }

        constexpr const int bufferSize = 4096;
        std::array<char, bufferSize> buffer;
        std::fill(buffer.begin(), buffer.end(), 0);

        // Receive the client request
        ssize_t bytesRead = recv(clientSocket, buffer.data(), bufferSize - 1, 0);
        if (bytesRead < 0) {
            Log("Error reading client request.", LoggerType::Critical);
            close(clientSocket);
            return;
        }

        std::string_view requestString(buffer.data(), bytesRead);
        Request request;
        parseRequest(std::string(requestString), request);

        Log("Received request: Method=" + request.method().value() + ", Path=" + request.path().value(), LoggerType::Info);

        // Rate limiting
        std::string clientIP = getClientIP(clientSocket);
        if (m_serverStructure.rateLimiter && !m_serverStructure.rateLimiter->allowRequest(clientIP)) {
            Response rateLimitResponse;
            rateLimitResponse.setStatusCode(429); // Too Many Requests
            rateLimitResponse.setContentType("text/plain");
            rateLimitResponse.setContent("Rate limit exceeded. Please try again later.");
            std::string responseString = responseToString(rateLimitResponse);
            ssize_t bytesSent = send(clientSocket, responseString.c_str(), responseString.length(), 0);
            if (bytesSent < 0) {
                Log("Error sending rate limit response to client.", LoggerType::Critical);
            }
            close(clientSocket);
            return; // Exit after sending the rate limit response
        }

        // Sanitize the requested path to prevent directory traversal attacks
        std::string requestedPath = sanitizePath(request.path().value());

        // Check if the request path matches a route handler
        if (requestedPath == "/") {
            // Handle the home page route explicitly
            Response homeResponse = m_serverStructure.router.routeRequest(request);
            std::string responseString = responseToString(homeResponse);
            ssize_t bytesSent = send(clientSocket, responseString.c_str(), responseString.length(), 0);
            if (bytesSent < 0) {
                Log("Error sending home page response to client.", LoggerType::Critical);
            }
            close(clientSocket);
            return; // Exit after sending the home page response
        }

        // Check if the requested path is a static file
        std::string filePath = m_serverStructure.documentRoot + requestedPath;
        std::ifstream file(filePath, std::ios::binary);

        if (file) {
            // Read the file content
            std::ostringstream fileContentStream;
            fileContentStream << file.rdbuf();
            std::string fileContent = fileContentStream.str();

            // Determine the MIME type based on the file extension
            MediaTypes mt;
            std::string extension = filePath.substr(filePath.find_last_of('.') + 1);
            std::string mimeType = mt.getMimeType(extension.empty() ? "bin" : extension);

            // Create a response with the file content and MIME type
            Response response;
            response.setStatusCode(200);
            response.setContentType(mimeType);
            response.setContent(fileContent);

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
            // If the file is not found, delegate to the router to handle the request
            Response response = m_serverStructure.router.routeRequest(request);
            std::string responseString = responseToString(response);
            ssize_t bytesSent = send(clientSocket, responseString.c_str(), responseString.length(), 0);
            if (bytesSent < 0) {
                Log("Error sending response to client.", LoggerType::Critical);
            }
            close(clientSocket);
        }

    } catch (const std::exception& e) {
        std::string clientIP = getClientIP(clientSocket);
        Log("Error in handleClientRequestNoSSL for client IP: " + clientIP + " - " + std::string(e.what()), LoggerType::Critical);

               // Internal Server Error response
        Response errorResponse;
        errorResponse.setStatusCode(500);
        errorResponse.setContentType("text/plain");
        errorResponse.setContent("Internal server error.");

               // Send the error response to the client
        std::string responseString = responseToString(errorResponse);
        ssize_t bytesSent = send(clientSocket, responseString.c_str(), responseString.length(), 0);
        if (bytesSent < 0) {
            Log("Error sending error response to client.", LoggerType::Critical);
        }

               // Remove client from active connections
        {
            std::lock_guard<std::mutex> lock(m_activeClientsMutex);
            m_activeClients.erase(clientSocket);
        }

        close(clientSocket);
    }
}

void WebServer::sendResponseSSL(SSL* ssl, const Response& response) {
    std::ostringstream responseStream;

    responseStream << "HTTP/1.1 " << response.statusCode() << " " << getStatusMessage(response.statusCode()) << "\r\n";

    if (response.contentType().has_value()) {
        responseStream << "Content-Type: " << response.contentType().value() << "\r\n";
    }
    if (response.content().has_value()) {
        responseStream << "Content-Length: " << response.content().value().length() << "\r\n";
    }
    responseStream << "Connection: close\r\n";

    for (const auto& header : response.headers()) {
        responseStream << header.first << ": " << header.second << "\r\n";
    }

    responseStream << "\r\n";

    if (response.content().has_value()) {
        responseStream << response.content().value();
    }

    std::string responseString = responseStream.str();
    const char* responseData = responseString.c_str();
    size_t responseLength = responseString.length();

    ssize_t bytesSent = 0;
    while (bytesSent < responseLength) {
        ssize_t sent = SSL_write(ssl, responseData + bytesSent, responseLength - bytesSent);
        if (sent < 0) {
            if (errno == EINTR) {
                continue; // Retry if interrupted
            }
            Log("Error sending response. Errno: " + std::to_string(errno), LoggerType::Critical);
            break;
        } else if (sent == 0) {
            break; // Client closed the connection
        }
        bytesSent += sent;
    }

    if (bytesSent < responseLength) {
        Log("Failed to send the entire response. Sent " + std::to_string(bytesSent) + " of " + std::to_string(responseLength) + " bytes.", LoggerType::Warning);
    }
}

std::string WebServer::getDocumentRoot() const {
    return m_serverStructure.documentRoot;
}

std::string WebServer::sanitizePath(const std::string& requestedPath) {
    try {
        // Ensure the path starts with a '/'
        std::string sanitized = requestedPath;
        if (!sanitized.empty() && sanitized[0] != '/') {
            sanitized = "/" + sanitized;
        }

               // Remove any ".." or attempts at directory traversal
        std::vector<std::string> pathParts;
        std::istringstream pathStream(sanitized);
        std::string segment;

        while (std::getline(pathStream, segment, '/')) {
            if (segment == "..") {
                if (!pathParts.empty()) {
                    // Remove the last valid directory if ".." is encountered
                    pathParts.pop_back();
                }
            } else if (!segment.empty() && segment != ".") {
                // Add valid segments
                pathParts.push_back(segment);
            }
        }

               // Reconstruct the sanitized path
        std::ostringstream cleanPathStream;
        for (const auto& part : pathParts) {
            cleanPathStream << "/" << part;
        }

        std::string cleanPath = cleanPathStream.str();

               // If the path resolves to the root, return "/"
        if (cleanPath.empty()) {
            return "/";
        }

               // Only perform canonical path check for static files
        if (cleanPath.rfind("/static/", 0) == 0) { // Check if the path starts with "/static/"
            std::string fullPath = m_serverStructure.documentRoot + cleanPath;
            std::string canonicalPath = std::filesystem::canonical(fullPath);

                   // Ensure the canonical path is within the document root
            if (canonicalPath.find(m_serverStructure.documentRoot) != 0) {
                // If the path escapes the document root, return "/" (root) or an error path
                return "/";
            }
        }

        return cleanPath;
    } catch (const std::exception& e) {
        // Log the error and return the root path
        Log("Error sanitizing path: " + std::string(e.what()), LoggerType::Warning);
        return "/";
    }
}

void WebServer::handleClientRequestSSL(SocketType clientSocket, SSL* ssl) {

    try {
        // Add client to active connections
        {
            std::lock_guard<std::mutex> lock(m_activeClientsMutex);
            m_activeClients[clientSocket] = {
                clientSocket,
                getClientIP(clientSocket),
                std::chrono::steady_clock::now()
            };
        }

               // Log active clients
        for (const auto& [socket, clientInfo] : m_activeClients) {
            Log("Client: " + clientInfo.ipAddress + ", Connected at: " + std::to_string(clientInfo.connectionTime.time_since_epoch().count()), LoggerType::Info);
        }

        // Buffer to hold the client request
        constexpr const int bufferSize = 4096;
        std::array<char, bufferSize> buffer;
        std::fill(buffer.begin(), buffer.end(), 0);

        // Receive the client request
        ssize_t bytesRead = SSL_read(ssl, buffer.data(), bufferSize - 1);
        if (bytesRead < 0) {
            int sslError = SSL_get_error(ssl, bytesRead);
            Log("Error reading client request. SSL error: " + std::to_string(sslError), LoggerType::Critical);
            return;
        }

        // Parse the request
        std::string_view requestString(buffer.data(), bytesRead);
        Request request;
        parseRequest(std::string(requestString), request);

        Log("Received request: Method=" + request.method().value() + ", Path=" + request.path().value(), LoggerType::Info);

        // Rate limiting
        std::string clientIP = getClientIP(clientSocket);
        if (m_serverStructure.rateLimiter && !m_serverStructure.rateLimiter->allowRequest(clientIP)) {
            Response rateLimitResponse;
            rateLimitResponse.setStatusCode(429); // Too Many Requests
            rateLimitResponse.setContentType("text/plain");
            rateLimitResponse.setContent("Rate limit exceeded. Please try again later.");
            sendResponseSSL(ssl, rateLimitResponse);
            return;
        }

        // Sanitize the requested path to prevent directory traversal attacks
        std::string requestedPath = sanitizePath(request.path().value());

        // Check if the request path matches a route handler
        if (requestedPath == "/") {
            // Handle the home page route explicitly
            Response homeResponse = m_serverStructure.router.routeRequest(request);
            sendResponseSSL(ssl, homeResponse);
            return;
        }

               // Check if the requested path is a static file
        std::string filePath = m_serverStructure.documentRoot + requestedPath;
        std::ifstream file(filePath, std::ios::binary);

        if (file) {
            // Read the file content
            std::ostringstream fileContentStream;
            fileContentStream << file.rdbuf();
            std::string fileContent = fileContentStream.str();

                   // Determine the MIME type based on the file extension
            MediaTypes mt;
            std::string extension = filePath.substr(filePath.find_last_of('.') + 1);
            std::string mimeType = mt.getMimeType(extension.empty() ? "bin" : extension);

                   // Create a response with the file content and MIME type
            Response response;
            response.setStatusCode(200);
            response.setContentType(mimeType);
            response.setContent(fileContent);

                   // Send the response to the client
            sendResponseSSL(ssl, response);

            file.close();
        } else {
            // If the file is not found, delegate to the router to handle the request
            Response response = m_serverStructure.router.routeRequest(request);
            sendResponseSSL(ssl, response);
        }

    } catch (const std::exception& e) {
        std::string clientIP = getClientIP(clientSocket);
        Log("Error in handleClientRequestSSL for client IP: " + clientIP + " - " + std::string(e.what()), LoggerType::Critical);

        // Internal Server Error response
        Response errorResponse;
        errorResponse.setStatusCode(500);
        errorResponse.setContentType("text/plain");
        errorResponse.setContent("Internal server error.");

        // Send the error response to the client
        sendResponseSSL(ssl, errorResponse);

        // Remove client from active connections
        {
            std::lock_guard<std::mutex> lock(m_activeClientsMutex);
            m_activeClients.erase(clientSocket);
        }
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
