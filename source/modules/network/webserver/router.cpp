#if __has_include("router.hpp")
#   include "router.hpp"
#else
#   error "Cell's router was not found!"
#endif

#if __has_include("classes/mediatypes.hpp")
#   include "classes/mediatypes.hpp"
#else
#   error "Cell's classes/mediatypes.hpp was not found!"
#endif

#include "core/logger.hpp"

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

void Router::addRoute(const std::string& path, const Handler& handler, const std::string& method)
{
    std::string normalizedPath = normalizePath(path).value();
    std::string methodKey = normalizeMethod(method).value();
    m_routes[methodKey][normalizedPath] = handler;
}

void Router::addRoute(const std::vector<std::string>& paths, const Handler& handler, const std::string& method)
{
    std::string methodKey = normalizeMethod(method).value();

    for (const std::string& path : paths) {
        std::string normalizedPath = normalizePath(path).value();
        m_routes[methodKey][normalizedPath] = handler;
    }
}

void Router::addMiddleware(const Middleware& middleware)
{
    m_middleWares.push_back(middleware);
}

Response Router::routeRequest(const Request& request) {
    auto& engine = engineController.getEngine();
    std::string methodKey = normalizeMethod(request.method().value()).value();
    std::string path = normalizePath(request.path().value()).value();

    Log("Routing request: Method=" + methodKey + ", Path=" + path, Utility::LoggerType::Info);

    auto methodIt = m_routes.find(methodKey);
    if (methodIt != m_routes.end()) {
        auto& routesByMethod = methodIt->second;

        for (const auto& route : routesByMethod) {
            const std::string& routePath = route.first;
            std::smatch match;
            std::regex routeRegex = createRouteRegex(routePath);

            if (std::regex_match(path, match, routeRegex)) {
                Log("Matched route: " + routePath, Utility::LoggerType::Info);

                std::unordered_map<std::string, std::string> pathParams;
                auto paramNames = extractParameterNames(routePath);
                for (size_t i = 0; i < paramNames.size(); ++i) {
                    pathParams[paramNames[i]] = match[i + 1].str();
                }

                const_cast<Request&>(request).setPathParameters(pathParams);

                Response response = route.second(request);

                for (const auto& middleware : m_middleWares) {
                    middleware(const_cast<Request&>(request), response, route.second);
                }

                return response;
            }
        }
    }

    Log("No route matched for path: " + path, Utility::LoggerType::Warning);

    if (m_notFoundHandler) {
        return m_notFoundHandler(request);
    }

    Response response;
    response.setStatusCode(404);
    response.setContentType(engine.meta()->returnView(Globals::ContentTypes::HTML));
    response.setContent("<html><body><h1>404 Not Found</h1><p>The requested page was not found.</p></body></html>");
    return response;
}

void Router::setNotFoundHandler(const Handler& notFoundHandler)
{
    m_notFoundHandler = notFoundHandler;
}

void Router::setExceptionHandler(const ExceptionErrorHandler& handler)
{
    m_exceptionHandler = handler;
}

Types::OptionalString Router::normalizePath(const std::string& path) const {
    // Normalize the path by removing trailing slashes
    std::string normalizedPath = path;
    if (!normalizedPath.empty() && normalizedPath.back() == '/') {
        normalizedPath.pop_back();
    }
    return normalizedPath;
}

OptionalString Router::normalizeMethod(const std::string& method)
{
    // Normalize the method by converting to uppercase
    std::string normalizedMethod = method;
    std::transform(normalizedMethod.begin(), normalizedMethod.end(), normalizedMethod.begin(), ::toupper);
    return normalizedMethod;
}

std::regex Router::createRouteRegex(const std::string& routePath) {
    std::string regexPattern = "^" + std::regex_replace(routePath, std::regex(R"(\{(\w+)\})"), R"(([^/]+))") + "$";
    return std::regex(regexPattern);
}

std::vector<std::string> Router::extractParameterNames(const std::string& routePath) {
    std::vector<std::string> paramNames;
    std::regex paramRegex(R"(\{(\w+)\})");
    auto words_begin = std::sregex_iterator(routePath.begin(), routePath.end(), paramRegex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        paramNames.push_back(match.str(1));
    }

    return paramNames;
}

bool Router::hasRoute(const std::string& path) const {
    std::string normalizedPath = normalizePath(path).value();

           // Iterate through all methods (GET, POST, etc.) and check if the path exists in any of them.
    for (const auto& methodRoutes : m_routes) {
        if (methodRoutes.second.find(normalizedPath) != methodRoutes.second.end()) {
            return true;
        }
    }

    return false;
}

CELL_NAMESPACE_END
