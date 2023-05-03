/*!
 * @file        request.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver request for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_REQUEST_ABSTRACT_HPP
#define CELL_REQUEST_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @brief Structure that represents the parts of a HTTP request
 */
struct RequestStructure final
{
    Types::Headers          headers     {}; //!< The headers of the request.
    Types::OptionalString   method      {}; //!< The HTTP method of the request.
    Types::OptionalString   uri         {}; //!< The URI of the request.
    Types::OptionalString   httpVersion {}; //!< The HTTP version of the request.
    Types::OptionalString   body        {}; //!< The body of the request.
};

/**
 * @brief Class that represents a HTTP request
 */
class __cell_export Request {
public:
    /**
     * @brief Constructor for a HTTP request
     *
     * @param method The HTTP method of the request
     * @param uri The URI of the request
     * @param httpVersion The HTTP version of the request
     * @param headers The headers of the request
     * @param body The body of the request
     */
    Request(const Types::OptionalString& method,
            const Types::OptionalString& uri,
            const Types::OptionalString& httpVersion,
            Types::Headers& headers,
            const Types::OptionalString& body);

    /**
     * @brief destructor for the Request.
     */
    ~Request();

    /**
     * @brief Returns the HTTP method of the request
     *
     * @return The HTTP method of the request
     */
    const Types::OptionalString& method() const;

    /**
     * @brief Returns the URI of the request
     *
     * @return The URI of the request
     */
    const Types::OptionalString& uri() const;

    /**
     * @brief Returns the HTTP version of the request
     *
     * @return The HTTP version of the request
     */
    const Types::OptionalString& httpVersion() const;

    /**
     * @brief Returns the headers of the request
     *
     * @return The headers of the request as an unordered map with string keys and values
     */
    const std::unordered_map<Types::OptionalString, Types::OptionalString>& headers() const;

    /**
     * @brief Returns the body of the request
     *
     * @return The body of the request
     */
    const Types::OptionalString& body() const;

private:
    RequestStructure requestStructure {}; //!< The structure that holds the parts of the request.
};

CELL_NAMESPACE_END

#endif  // CELL_REQUEST_ABSTRACT_HPP
