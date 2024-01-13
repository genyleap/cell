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


CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;

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

Response Router::routeRequest(const Request& request)
{
    auto& engine = engineController.getEngine();
    std::string methodKey = normalizeMethod(request.method().value()).value();
    std::string path = normalizePath(request.path().value()).value();

    // Find the handler for the requested path and method
    auto methodIt = m_routes.find(methodKey);
    if (methodIt != m_routes.end()) {
        auto& routesByMethod = methodIt->second;

        // Try to match the path with the registered routes
        for (const auto& route : routesByMethod) {
            const std::string& routePath = route.first;
            std::smatch match;
            std::regex routeRegex = createRouteRegex(routePath);

            if (std::regex_match(path, match, routeRegex)) {
                // Call the handler function and return its response
                Response response = route.second(request);

                // Apply middleware to the request and response
                for (const auto& middleware : m_middleWares) {
                    middleware(const_cast<Request&>(request), response, route.second);
                }

                return response;
            }
        }
    }

    // If no handler is found, call the custom error page handler if it's set
    if (m_notFoundHandler) {
        return m_notFoundHandler(request);
    }

    //! Todo for exception!?
    // If no handler is found and no custom error page handler is set, return a default 404 response
    Response response;
    response.setStatusCode(404);
    response.setContentType(engine.meta()->returnView(Globals::ContentTypes::HTML));
    std::string r = R"(<html><body><h1>Default 404 Not Found</h1><p>The requested page was not found.</p></body></html>)";
    response.setContent(r);
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

OptionalString Router::normalizePath(const std::string& path)
{
    // Normalize the path by removing trailing slashes
    std::string normalizedPath = path;
    if (!normalizedPath.empty() && normalizedPath.back() == '/')
    {
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


CELL_NAMESPACE_END
