#include "websocket.hpp"
#include <iostream>
#include <system_error>
#include <cstring>
#include <stdexcept>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

WebSocket::WebSocket(int clientSocket, size_t bufferSize)
    : m_clientSocket(clientSocket), m_bufferSize(bufferSize), m_messageHandler(nullptr),
      m_closeHandler(nullptr), m_errorHandler(nullptr) {
    if (m_clientSocket < 0) {
        throw std::invalid_argument("Invalid client socket");
    }
}

WebSocket::~WebSocket() {
    close();
}

void WebSocket::sendText(const std::string& message) {
    std::vector<uint8_t> frame = encodeFrame(message, 0x81); // Text frame opcode
    sendFrame(frame);
}

void WebSocket::sendBinary(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> frame = encodeFrame(data);
    sendFrame(frame);
}

void WebSocket::sendPing(const std::string& payload) {
    if (payload.size() > 125) {
        throw std::invalid_argument("Ping payload too large");
    }
    std::vector<uint8_t> frame = encodeFrame(payload, 0x89); // Ping frame opcode
    sendFrame(frame);
}

void WebSocket::sendPong(const std::string& payload) {
    if (payload.size() > 125) {
        throw std::invalid_argument("Pong payload too large");
    }
    std::vector<uint8_t> frame = encodeFrame(payload, 0x8A); // Pong frame opcode
    sendFrame(frame);
}

void WebSocket::onMessage(MessageHandler handler) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_messageHandler = handler;
}

void WebSocket::onClose(CloseHandler handler) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_closeHandler = handler;
}

void WebSocket::onError(ErrorHandler handler) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_errorHandler = handler;
}

void WebSocket::handleFrame(const std::vector<uint8_t>& frame) {
    if (frame.size() < 2) {
        if (m_errorHandler) {
            m_errorHandler(std::make_error_code(std::errc::invalid_argument));
        }
        return;
    }

    uint8_t opcode = frame[0] & 0x0F;
    bool isMasked = (frame[1] & 0x80) != 0;

    if (!isMasked) {
        // Frames from the client must be masked
        if (m_errorHandler) {
            m_errorHandler(std::make_error_code(std::errc::protocol_error));
        }
        close(1002, "Protocol error: Unmasked frame");
        return;
    }

    size_t payloadLength = frame[1] & 0x7F;
    size_t maskOffset = 2;

    if (payloadLength == 126) {
        maskOffset += 2;
    } else if (payloadLength == 127) {
        maskOffset += 8;
    }

    if (frame.size() < maskOffset + 4 + payloadLength) {
        if (m_errorHandler) {
            m_errorHandler(std::make_error_code(std::errc::invalid_argument));
        }
        return;
    }

    std::string message;
    for (size_t i = 0; i < payloadLength; ++i) {
        message.push_back(frame[maskOffset + 4 + i] ^ frame[maskOffset + (i % 4)]);
    }

    switch (opcode) {
    case 0x01: // Text frame
    case 0x02: // Binary frame
        if (m_messageHandler) {
            m_messageHandler(message);
        }
        break;
    case 0x08: // Close frame
        handleCloseFrame(frame);
        break;
    case 0x09: // Ping frame
        handlePingFrame(frame);
        break;
    case 0x0A: // Pong frame
        handlePongFrame(frame);
        break;
    default:
        if (m_errorHandler) {
            m_errorHandler(std::make_error_code(std::errc::protocol_error));
        }
        close(1002, "Protocol error: Invalid opcode");
        break;
    }
}

void WebSocket::close(uint16_t code, const std::string& reason) {
    if (m_clientSocket < 0) {
        return; // Socket already closed
    }

    std::vector<uint8_t> frame;
    frame.push_back(0x88); // Close frame opcode
    frame.push_back(static_cast<uint8_t>(reason.size() + 2));
    frame.push_back(static_cast<uint8_t>((code >> 8) & 0xFF));
    frame.push_back(static_cast<uint8_t>(code & 0xFF));
    frame.insert(frame.end(), reason.begin(), reason.end());
    sendFrame(frame);

    if (m_closeHandler) {
        m_closeHandler();
    }

    ::close(m_clientSocket);
    m_clientSocket = -1;
}

std::vector<uint8_t> WebSocket::encodeFrame(const std::string& message, uint8_t opcode) {
    std::vector<uint8_t> frame;
    frame.push_back(opcode); // FIN + opcode

    if (message.size() <= 125) {
        frame.push_back(static_cast<uint8_t>(message.size()));
    } else if (message.size() <= 65535) {
        frame.push_back(126);
        frame.push_back(static_cast<uint8_t>((message.size() >> 8) & 0xFF));
        frame.push_back(static_cast<uint8_t>(message.size() & 0xFF));
    } else {
        frame.push_back(127);
        for (int i = 7; i >= 0; --i) {
            frame.push_back(static_cast<uint8_t>((message.size() >> (8 * i)) & 0xFF));
        }
    }

    frame.insert(frame.end(), message.begin(), message.end());
    return frame;
}

std::vector<uint8_t> WebSocket::encodeFrame(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> frame;
    frame.push_back(0x82); // Binary frame opcode

    if (data.size() <= 125) {
        frame.push_back(static_cast<uint8_t>(data.size()));
    } else if (data.size() <= 65535) {
        frame.push_back(126);
        frame.push_back(static_cast<uint8_t>((data.size() >> 8) & 0xFF));
        frame.push_back(static_cast<uint8_t>(data.size() & 0xFF));
    } else {
        frame.push_back(127);
        for (int i = 7; i >= 0; --i) {
            frame.push_back(static_cast<uint8_t>((data.size() >> (8 * i)) & 0xFF));
        }
    }

    frame.insert(frame.end(), data.begin(), data.end());
    return frame;
}

std::string WebSocket::decodeFrame(const std::vector<uint8_t>& frame) {
    size_t payloadLength = frame[1] & 0x7F;
    size_t maskOffset = 2;

    if (payloadLength == 126) {
        maskOffset += 2;
    } else if (payloadLength == 127) {
        maskOffset += 8;
    }

    std::string message;
    for (size_t i = 0; i < payloadLength; ++i) {
        message.push_back(frame[maskOffset + 4 + i] ^ frame[maskOffset + (i % 4)]);
    }

    return message;
}

void WebSocket::sendFrame(const std::vector<uint8_t>& frame) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_clientSocket < 0) {
        if (m_errorHandler) {
            m_errorHandler(std::make_error_code(std::errc::not_connected));
        }
        return;
    }

    ssize_t bytesSent = ::send(m_clientSocket, frame.data(), frame.size(), 0);
    if (bytesSent < 0) {
        if (m_errorHandler) {
            m_errorHandler(std::make_error_code(std::errc::io_error));
        }
    }
}

void WebSocket::handleCloseFrame(const std::vector<uint8_t>& frame) {
    if (m_closeHandler) {
        m_closeHandler();
    }
    close();
}

void WebSocket::handlePingFrame(const std::vector<uint8_t>& frame) {
    std::string payload = decodeFrame(frame);
    sendPong(payload);
}

std::string WebSocket::base64_encode(const std::string &input) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input.c_str(), input.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    std::string result(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);

    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    return result;
}

bool WebSocket::performHandshake(const std::string &request) {
    const std::string magicString = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string key;

    size_t keyStart = request.find("Sec-WebSocket-Key: ");
    if (keyStart != std::string::npos) {
        keyStart += 19;
        size_t keyEnd = request.find("\r\n", keyStart);
        key = request.substr(keyStart, keyEnd - keyStart);
    } else {
        return false;
    }

    std::string combinedKey = key + magicString;
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char *>(combinedKey.c_str()), combinedKey.length(), hash);

    std::string acceptKey = base64_encode(std::string(reinterpret_cast<char *>(hash), SHA_DIGEST_LENGTH));

    std::string response =
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: " + acceptKey + "\r\n\r\n";

    send(m_clientSocket, response.c_str(), response.length(), 0);
    return true;
}

void WebSocket::handlePongFrame(const std::vector<uint8_t>& frame) {
    // Decode the Pong frame payload (if any)
    std::string payload = decodeFrame(frame);

    // Log the Pong frame (optional)
    std::cout << "Pong received" << (payload.empty() ? "" : " with payload: " + payload) << std::endl;

    // No further action is required for Pong frames
    // You can use this method to track connection health or debug issues
}

void WebSocket::handleClient() {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    // Receive WebSocket handshake request
    ssize_t bytesReceived = recv(m_clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0) {
        close();
        return;
    }

    std::string request(buffer, bytesReceived);

    // Perform WebSocket handshake
    if (!performHandshake(request)) {
        std::cerr << "WebSocket handshake failed" << std::endl;
        close();
        return;
    }

    // Set up message handler
    onMessage([this](const std::string &message) {
        std::cout << "Received message: " << message << std::endl;
        sendText("Echo: " + message);
    });

    // Set up close handler
    onClose([this]() {
        std::cout << "Client disconnected: " << m_clientSocket << std::endl;
    });

    // Set up error handler
    onError([](const std::error_code &ec) {
        std::cerr << "WebSocket error: " << ec.message() << std::endl;
    });

           // Send a welcome message to the client
    sendText("Welcome to the WebSocket server!");

    // Handle WebSocket frames
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        bytesReceived = recv(m_clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            close();
            break;
        }

        std::vector<uint8_t> frame(buffer, buffer + bytesReceived);
        handleFrame(frame);
    }

    close();
}

CELL_NAMESPACE_END
