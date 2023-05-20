/*!
 * @file        apikey.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Apikey interface for apis.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @link        https://genyleap.com/technology/cell
 *
 */

#ifndef CELL_APIKEY_ABSTRACT_HPP
#define CELL_APIKEY_ABSTRACT_HPP
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
 * The user’s key and value.
 * The resulting string is simple.
 */
struct AuthorizationInfo __cell_final
{
    OptionalString key;     //!< Key of user.
    OptionalString value;   //!< Value of user.
    OptionalString result;  //!< Result of string.
};

/*!
 * \brief The AddType enum
 */
__cell_enum_class AddType : u8
{
    Header          =   0x0, //!< Add to header.
    QueryParameter  =   0x1, //!< Add to query as parameter.
};

/*!
 * \brief HTTP Basic Authentication.
 * The simplest way to handle authentication is through the use of HTTP, where the username and password are sent alongside every API call.
 * You can use an HTTP header and encode the username and password. Note that does not mean.
 * If you end up using HTTP Basic Authentication, use it through HTTPS so the connection between the parties is encrypted.
 */
class __cell_export AbstractApiKey : protected AbstractApi
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractApiKey)

    /*!
     * \brief get function will gets output of access string.
     * \returns as final string.
     */
   __cell_no_discard __cell_virtual OptionalString get() __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractApiKey)
};

CELL_NAMESPACE_END

#endif  // CELL_APIKEY_ABSTRACT_HPP
