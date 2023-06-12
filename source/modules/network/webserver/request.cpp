#if __has_include("request.hpp")
#   include "request.hpp"
#else
#   error "Cell's request was not found!"
#endif

#if __has_include("classes/cookies.hpp")
#   include "classes/cookies.hpp"
#else
#   error "Cell's classes/cookies.hpp was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Globals::Storage;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

OptionalString Request::method() const
{
    return m_requestStructure.method;
}

OptionalString Request::path() const
{
    return m_requestStructure.uri.value();
}

const std::unordered_map<std::string, std::string> Request::headers() const
{
    return m_requestStructure.headers;
}

OptionalString Request::body() const
{
    return m_requestStructure.body.value();
}

void Request::setMethod(const std::string& method)
{
    m_requestStructure.method = method;
}

void Request::setPath(const std::string& uri)
{
    m_requestStructure.uri = uri;
}

void Request::setHeader(const std::string& key, const std::string& value)
{
    m_requestStructure.headers[key] = value;
}

void Request::setBody(const std::string& body)
{
    m_requestStructure.body = body;
}

void Request::setSessionId(const std::string& sessionId)
{
    m_requestStructure.cookies.addCookie("sessionId", sessionId);
}

const Cookies& Request::cookies() const {
    return m_requestStructure.cookies;
}

CELL_NAMESPACE_END
