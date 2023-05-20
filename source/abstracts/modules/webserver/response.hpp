/*!
 * @file        response.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver request for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_RESPONSE_ABSTRACT_HPP
#define CELL_RESPONSE_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @brief Structure representing an HTTP response.
 *
 * This structure contains information about an HTTP response, including the status code, content,
 * and content type.
 */
struct ResponseStructure final
{
    int                     statusCode  {}; //!< The HTTP status code.
    Types::OptionalString   content     {}; //!< The response body content.
    Types::OptionalString   contentType {}; //!< The MIME type of the response body.
};

/**
 * @brief Class representing an HTTP response.
 *
 * This class contains information about an HTTP response, including the status code, content,
 * and content type. It also provides accessor methods to retrieve this information.
 */
class __cell_export Response {
public:
    /**
     * @brief Constructor for creating an HTTP response.
     *
     * @param status_code The HTTP status code to set in the response.
     * @param content An optional string representing the response body content.
     * @param contentType An optional string representing the MIME type of the response body.
     */
    Response(int status_code,
             const Types::OptionalString& content,
             const Types::OptionalString& contentType);

    /**
     * @brief destructor for the Response.
     */
    ~Response();

    /**
     * @brief Returns the HTTP status code of the response.
     *
     * @return An integer representing the HTTP status code of the response.
     */
    int statusCode() const;

    /**
     * @brief Returns the response body content.
     *
     * @return An optional string representing the response body content.
     */
    const Types::OptionalString& content() const;

    /**
     * @brief Returns the MIME type of the response body.
     *
     * @return An optional string representing the MIME type of the response body.
     */
    const Types::OptionalString& contentType() const;

private:
    ResponseStructure responseStructure {}; //!< The internal representation of the HTTP response.
};


CELL_NAMESPACE_END

#endif  // CELL_RESPONSE_ABSTRACT_HPP
