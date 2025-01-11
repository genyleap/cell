/*!
 * @file        api.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Api interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_API_ABSTRACT_HPP
#define CELL_API_ABSTRACT_HPP
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The API authentication process validates the identity of the client attempting to make a connection by using an authentication protocol.
 * And for this there are different methods that we cover.
 */
__cell_enum_class AuthenticationType : Types::u8
{
    NoAuth          =   0x0,  //!< No any authorization.
    ApiKey          =   0x1,  //!< Authentication based on ApiKey.
    BearerToken     =   0x2,  //!< Authentication based on BearerToken.
    BasicAuth       =   0x3,  //!< Authentication based on BasicAuth.
    DigestAuth      =   0x4,  //!< Authentication based on DigestAuth.
    OAuth1_0        =   0x5,  //!< Authentication based on OAuth1.0.
    OAuth2_0        =   0x6,  //!< Authentication based on OAuth2.0.
    Hawk            =   0x7,  //!< Authentication based on Hawk.
    AwsSignature    =   0x8,  //!< Authentication based on AWS Signature.
    Customized      =   0x9   //!< Authentication based on Customized method.
};

/*!
 * \brief The AbstractApi class
 */
class __cell_export AbstractApi
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractApi)

    /*!
     * \brief get function will gets output of access string.
     * \returns as final string.
     */
    __cell_no_discard __cell_virtual Types::OptionalString get() __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractApi)
};

CELL_NAMESPACE_END

#endif  // CELL_API_ABSTRACT_HPP
