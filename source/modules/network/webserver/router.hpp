/*!
 * @file        router.hpp
 * @brief       Router manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_ROUTER_HPP
#define CELL_ROUTER_HPP

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("request.hpp")
#   include "request.hpp"
#else
#   error "Cell's "request.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("response.hpp")
#   include "response.hpp"
#else
#   error "Cell's "response.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

using Handler = std::function<Response(const Request&)>;
using ExceptionErrorHandler = std::function<Response(const Request&, const std::exception&)>;
using Middleware = std::function<void(Request&, Response&, const Handler&)>;

/**
 * Router class for handling HTTP route mapping and request routing.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Router {
public:
    /**
     * Add a route to the router.
     *
     * @param path The path for the route.
     * @param handler The handler function for the route.
     * @param method The HTTP method for the route (default: "GET").
     */
    void addRoute(const std::string& path, const Handler& handler, const std::string& method = "GET");

    void addRoute(const std::vector<std::string>& paths, const Handler& handler, const std::string& method = "GET");

    /**
     * Add a middleware to the router.
     *
     * @param middleware The middleware function to add.
     */
    void addMiddleware(const Middleware& middleware);

    /**
     * Route the incoming request based on the registered routes and middleware.
     *
     * @param request The incoming request to route.
     * @return The response generated from the routing process.
     */
    Response routeRequest(const Request& request);

    /**
     * @brief Sets the handler function for handling 404 Not Found errors.
     *
     * When a requested resource is not found, this handler function will be called to generate
     * an appropriate response. The handler function should take a Request object as a parameter
     * and return a Response object.
     *
     * @param errorHandler The handler function to set for handling 404 Not Found errors.
     */
    void setNotFoundHandler(const Handler& errorHandler);

    /**
     * @brief Sets the handler function for handling exceptions that occur during request handling.
     *
     * When an exception is thrown during request handling, this handler function will be called
     * to handle the exception and generate an appropriate response. The handler function should
     * take a const std::exception& object as a parameter and return a Response object.
     *
     * @param handler The handler function to set for handling exceptions.
     */
    void setExceptionHandler(const ExceptionErrorHandler& handler);


private:
    /**
     * Normalize the path by removing trailing slashes and converting to lowercase.
     *
     * @param path The path to normalize.
     * @return The normalized path.
     */
    Types::OptionalString normalizePath(const std::string& path);

    /**
     * Normalize the HTTP method by converting to uppercase.
     *
     * @param method The HTTP method to normalize.
     * @return The normalized method.
     */
    Types::OptionalString normalizeMethod(const std::string& method);

    /**
     * Create a regular expression from the route path.
     *
     * @param routePath The route path to create the regex from.
     * @return The created regex.
     */
    std::regex createRouteRegex(const std::string& routePath);

    std::vector<std::string> extractParameterNames(const std::string& routePath);
    Response applyMiddlewares(Request& request, const Handler& handler);

    std::unordered_map<std::string, std::unordered_map<std::string, Handler>> m_routes;
    std::vector<Middleware> m_middleWares;
    Handler m_notFoundHandler;
    ExceptionErrorHandler m_exceptionHandler;
    System::EngineController engineController;
};


CELL_NAMESPACE_END

#endif  // CELL_ROUTER_HPP

