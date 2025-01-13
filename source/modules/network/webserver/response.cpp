#if __has_include("response.hpp")
#   include "response.hpp"
#else
#   error "Cell's response was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core/core.hpp was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

int Response::statusCode() const
{
    return m_responseStructure.statusCode;
}

OptionalString Response::contentType() const
{
    if (m_responseStructure.contentType.has_value()) {
        return m_responseStructure.contentType.value();
    }
    return std::nullopt;
}

OptionalString Response::content() const
{
    if (m_responseStructure.content.has_value()) {
        return m_responseStructure.content.value();
    }
    return std::nullopt;
}

void Response::setStatusCode(int statusCode)
{
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }
    m_responseStructure.statusCode = statusCode;
}

void Response::setContentType(std::string_view contentType)
{
    if (contentType.empty()) {
        throw std::invalid_argument("Content type must not be empty.");
    }
    m_responseStructure.contentType = contentType.data();
}

void Response::setContent(const std::string& content)
{
    m_responseStructure.content = content;
}

void Response::setHeader(const std::string& key, const std::string& value)
{
    m_responseStructure.headers[key] = value;
}

void Response::removeHeader(const std::string& key)
{
    m_responseStructure.headers.erase(key);
}

void Response::setCookie(const std::string& name, const std::string& value, int maxAge, const std::string& path,
    bool secure, bool httpOnly, const std::string& sameSite)
    {
        if (name.empty() || value.empty()) {
        throw std::invalid_argument("Cookie name and value must not be empty.");
    }

    EngineController ec;
    auto& engine = ec.getEngine();
    std::string cookie = name + "=" + value;
    if (maxAge >= 0) {
        cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::MAX_AGE) + std::to_string(maxAge);
    }
    cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::PATH) + path;
    if (secure) {
        cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::SECURE);
    }
    if (httpOnly) {
        cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::HTTP_ONLY);
    }
    if (!sameSite.empty()) {
        cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::SAME_SITE) + sameSite;
    }
    m_responseStructure.headers[engine.meta()->returnView(RESPONSE_CONSTANTS::SET_COOKIE)] = cookie;
}

void Response::setSessionIdCookie(const std::string& sessionId, int maxAge, const std::string& path,
                                  bool secure, bool httpOnly, const std::string& sameSite)
{
    if (sessionId.empty()) {
        throw std::invalid_argument("Session ID must not be empty.");
    }

    EngineController ec;
    auto& engine = ec.getEngine();
    setCookie(engine.meta()->returnView(RESPONSE_CONSTANTS::SESSION_ID), sessionId, maxAge, path, secure, httpOnly, sameSite);
}

const std::unordered_map<std::string, std::string>& Response::headers() const
{
    return m_responseStructure.headers;
}

CELL_NAMESPACE_END
