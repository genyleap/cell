/*!
 * @file        websocket.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     WebSocket interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_WEBSOCKET_HPP
#define CELL_WEBSOCKET_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#include <functional>
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <system_error>

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

/**
 * @class WebSocket
 * @brief Represents a WebSocket connection.
 *
 * This class handles WebSocket connections, including sending and receiving messages.
 */
class WebSocket {
public:
    using MessageHandler = std::function<void(const std::string&)>;
    using CloseHandler = std::function<void()>;
    using ErrorHandler = std::function<void(const std::error_code&)>;

    /**
     * @brief Constructs a WebSocket object.
     * @param clientSocket The client socket associated with the WebSocket connection.
     * @param bufferSize The buffer size for receiving frames (default: 4096 bytes).
     */
    explicit WebSocket(int clientSocket, size_t bufferSize = 4096);

    /**
     * @brief Destructor. Closes the WebSocket connection.
     */
    ~WebSocket();

    /**
     * @brief Sends a text message to the client.
     * @param message The message to send.
     */
    void sendText(const std::string& message);

    /**
     * @brief Sends binary data to the client.
     * @param data The binary data to send.
     */
    void sendBinary(const std::vector<uint8_t>& data);

    /**
     * @brief Sends a ping frame to the client.
     * @param payload Optional ping payload (max 125 bytes).
     */
    void sendPing(const std::string& payload = "");

    /**
     * @brief Sends a pong frame to the client.
     * @param payload Optional pong payload (max 125 bytes).
     */
    void sendPong(const std::string& payload = "");

    /**
     * @brief Sets the message handler.
     * @param handler The handler to call when a message is received.
     */
    void onMessage(MessageHandler handler);

    /**
     * @brief Sets the close handler.
     * @param handler The handler to call when the connection is closed.
     */
    void onClose(CloseHandler handler);

    /**
     * @brief Sets the error handler.
     * @param handler The handler to call when an error occurs.
     */
    void onError(ErrorHandler handler);

    /**
     * @brief Handles an incoming WebSocket frame.
     * @param frame The received WebSocket frame.
     */
    void handleFrame(const std::vector<uint8_t>& frame);

    /**
     * @brief Closes the WebSocket connection.
     * @param code The close status code (default: 1000 - Normal Closure).
     * @param reason The close reason (optional).
     */
    void close(uint16_t code = 1000, const std::string& reason = "");

    bool performHandshake(const std::string& request);

    void handleClient();

private:
    int m_clientSocket; // The client socket
    size_t m_bufferSize; // Buffer size for receiving frames
    MessageHandler m_messageHandler; // Handler for incoming messages
    CloseHandler m_closeHandler; // Handler for connection close
    ErrorHandler m_errorHandler; // Handler for errors
    std::mutex m_mutex; // Mutex for thread safety

    /**
     * @brief Encodes a message into a WebSocket frame.
     * @param message The message to encode.
     * @param opcode The WebSocket opcode (e.g., text, binary, ping, pong).
     * @return The encoded WebSocket frame.
     */
    std::vector<uint8_t> encodeFrame(const std::string& message, uint8_t opcode);

    /**
     * @brief Encodes binary data into a WebSocket frame.
     * @param data The binary data to encode.
     * @return The encoded WebSocket frame.
     */
    std::vector<uint8_t> encodeFrame(const std::vector<uint8_t>& data);

    /**
     * @brief Decodes a WebSocket frame into a message or binary data.
     * @param frame The WebSocket frame to decode.
     * @return The decoded message or binary data.
     */
    std::string decodeFrame(const std::vector<uint8_t>& frame);

    /**
     * @brief Sends a WebSocket frame to the client.
     * @param frame The frame to send.
     */
    void sendFrame(const std::vector<uint8_t>& frame);

    /**
     * @brief Handles a close frame.
     * @param frame The close frame.
     */
    void handleCloseFrame(const std::vector<uint8_t>& frame);

    /**
     * @brief Handles a ping frame.
     * @param frame The ping frame.
     */
    void handlePingFrame(const std::vector<uint8_t>& frame);

    /**
     * @brief Handles a pong frame.
     * @param frame The pong frame.
     */
    void handlePongFrame(const std::vector<uint8_t>& frame);

    std::string base64_encode(const std::string& input);

};

CELL_NAMESPACE_END

#endif // CELL_WEBSOCKET_HPP
