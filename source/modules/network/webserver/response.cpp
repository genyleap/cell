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
    return m_responseStructure.contentType.value();
}

OptionalString Response::content() const
{
    return m_responseStructure.content.value();
}

void Response::setStatusCode(int statusCode)
{
    m_responseStructure.statusCode = statusCode;
}

void Response::setContentType(const std::string& contentType)
{
    m_responseStructure.contentType = contentType;
}

void Response::setContent(const std::string& content)
{
    m_responseStructure.content = content;
}

void Response::setHeader(const std::string& key, const std::string& value)
{
    m_responseStructure.headers[key] = value;
}

std::unordered_map<std::string, std::string> Response::headers() const
{
    return m_responseStructure.headers;
}

void Response::setCookie(const std::string& name, const std::string& value, int maxAge, const std::string& path)
{
    EngineController ec;
    auto& engine = ec.getEngine();
    std::string cookie = name + "=" + value;
    if (maxAge >= 0) {
        cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::MAX_AGE) + std::to_string(maxAge);
    }
    cookie += engine.meta()->returnView(RESPONSE_CONSTANTS::PATH) + path;
    m_responseStructure.headers[engine.meta()->returnView(RESPONSE_CONSTANTS::SET_COOKIE)] = cookie;
}

void Response::setSessionIdCookie(const std::string& sessionId, int maxAge, const std::string& path)
{
    EngineController ec;
    auto& engine = ec.getEngine();
    setCookie(engine.meta()->returnView(RESPONSE_CONSTANTS::SESSION_ID), sessionId, maxAge, path);
}

CELL_NAMESPACE_END
