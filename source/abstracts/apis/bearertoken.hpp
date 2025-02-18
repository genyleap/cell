/*!
 * @file        bearertoken.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Bearertoken interface for apis.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_BEARER_TOKEN_ABSTRACT_HPP
#define CELL_BEARER_TOKEN_ABSTRACT_HPP
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif
#if __has_include("abstracts/api.hpp")
#   include "abstracts/api.hpp"
#else
#   error "Cell's "abstracts/api.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Apis)

/*!
 * \brief The AuthorizationInfo class
 */
struct AuthorizationInfo __cell_final
{
    OptionalString token;  //!< The bearer token is a cryptic string.
};

/*!
 * \brief HTTP Bearer Authentication
 * Bearer authentication (also called token authentication) is an HTTP authentication scheme that involves security tokens called bearer tokens.
 * The name “Bearer authentication” can be understood as “give access to the bearer of this token.” The bearer token is a cryptic string, usually generated by the server in response to a login request.
 */
class __cell_export AbstractBearerToken : protected AbstractApi
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractBearerToken)

    /*!
     * \brief get function will gets output of access string.
     * \returns as final string.
     */
   __cell_no_discard __cell_virtual OptionalString get() __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractBearerToken)
};

CELL_NAMESPACE_END

#endif  // CELL_BEARER_TOKEN_ABSTRACT_HPP
