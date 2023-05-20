#if __has_include("restapi.hpp")
#   include "restapi.hpp"
#else
#   error "Cell's "restapi.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network)

RestfulApi::RestfulApi()
{
}

RestfulApi::RestfulApi(const std::string& url) : httpRequest(url)
{
}

void RestfulApi::setAuthUsernamePassword(const std::string& username, const std::string& password)
{
    httpRequest.setAuthUsernamePassword(username, password);
}

void RestfulApi::addHeader(const std::string& header)
{
    httpRequest.addHeader(header);
}

std::string RestfulApi::get(const Parameter& params)
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    httpRequest.setTimeout(CELL_DEFAULT_HTTP_TIMEOUT);
    httpRequest.setQuery(params);
    std::string response = engineSmartPtr->unescapeJson(httpRequest.performGet());
    m_lastRequestTime = std::chrono::high_resolution_clock::now();
    return response;
}

std::string RestfulApi::post(const Parameter& params)
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    httpRequest.setTimeout(CELL_DEFAULT_HTTP_TIMEOUT);
    httpRequest.setQuery(params);
    return engineSmartPtr->unescapeJson(httpRequest.performPost());
}

std::string RestfulApi::put(const Parameter &params)
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    httpRequest.setTimeout(CELL_DEFAULT_HTTP_TIMEOUT);
    httpRequest.setQuery(params);
    return engineSmartPtr->unescapeJson(httpRequest.performPut());
}

std::string RestfulApi::del(const Parameter &params)
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    httpRequest.setTimeout(CELL_DEFAULT_HTTP_TIMEOUT);
    httpRequest.setQuery(params);
    return engineSmartPtr->unescapeJson(httpRequest.performDelete());
}

std::string RestfulApi::patch(const Parameter &params)
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    httpRequest.setTimeout(CELL_DEFAULT_HTTP_TIMEOUT);
    httpRequest.setQuery(params);
    return engineSmartPtr->unescapeJson(httpRequest.performPost());
}

CELL_NAMESPACE_END
