/*!
 * @file        digestauth.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Digestauth interface for apis.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_DIGEST_AUTH_ABSTRACT_HPP
#define CELL_DIGEST_AUTH_ABSTRACT_HPP
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
 * The digest data for mixing.
 */
struct AuthorizationInfo __cell_final
{
    OptionalString username;    //!< Username of user.
    OptionalString password;    //!< Password of user.
    OptionalString realm;       //!< A string describing a protected area.
    OptionalString nonce;       //!< A server-specified quoted string that the server can use to control the lifetime in which particular credentials will be considered valid.
    OptionalString algorithm;   //!< Algorithm used to produce the digest.
    OptionalString qop;         //!< Quoted string indicating the quality of protection supported by the server.
    OptionalString nonceCount;  //!< The nonce counter.
    OptionalString clientNonce; //!< The nonce value is opaque to the client.
    OptionalString opaque;      //!< A server-specified quoted string that should be returned unchanged in the Authorization.
    OptionalString result;      //!< Result of final mixed string.
};

/*!
 * \brief HTTP Digest Auth.
 * A Bearer Token is an opaque string, not intended to have any meaning to clients using it.
 */
class __cell_export AbstractDigestAuth : protected AbstractApi
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractDigestAuth)

    /*!
     * \brief get function will gets output of access string.
     * \returns as final string.
     */
   __cell_no_discard __cell_virtual OptionalString get() __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractDigestAuth)
};

CELL_NAMESPACE_END

#endif  // CELL_DIGEST_AUTH_ABSTRACT_HPP
