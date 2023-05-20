/*!
 * @file        basic.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Basic interface for apis.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_BASIC_API_ABSTRACT_HPP
#define CELL_BASIC_API_ABSTRACT_HPP
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
 * The user’s username and password are combined with a colon.
 * The resulting string is base64 encoded.
 */
struct AuthorizationInfo __cell_final
{
    OptionalString username;  //!< Username of user.
    OptionalString password;  //!< Password of user.
    OptionalString result;    //!< Result of encoded.
};

/*!
 * \brief HTTP Basic Authentication.
 * The simplest way to handle authentication is through the use of HTTP, where the username and password are sent alongside every API call.
 * You can use an HTTP header and encode the username and password. Note that does not mean.
 * If you end up using HTTP Basic Authentication, use it through HTTPS so the connection between the parties is encrypted.
 */
class __cell_export AbstractBasicApi : protected AbstractApi
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractBasicApi)

    /*!
     * \brief get function will gets output of access string.
     * \returns as final string.
     */
   __cell_no_discard __cell_virtual OptionalString get() __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractBasicApi)
};

CELL_NAMESPACE_END

#endif  // CELL_BASIC_API_ABSTRACT_HPP
