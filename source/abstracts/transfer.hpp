/*!
 * @file        transfer.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Transfer interface for services.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_TRANSFER_ABSTRACT_HPP
#define CELL_TRANSFER_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("api.hpp")
#   include "api.hpp"
#else
#   error "Cell's "api.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Method of sending and receiving information.
 */
__cell_enum_class TransferMethodState : Types::u8
{
    Internal    =   0x1,  //!< Transfer from internal method.
    ExternalApi =   0x2,  //!< Transfer from external method like api.
    Customized  =   0x3   //!< Transfer from an other method.
};

struct TransferData __cell_final
{
    TransferMethodState         method   {};  //!< Transfer method for api service.
    AuthenticationType          auth     {};  //!< Authentication type for api service.
    Types::OptionalString       path     {};  //!< Path for api service.
    Types::OptionalString       output   {};  //!< Output from api service.
};

/*!
 * \brief The AbstractTransferMethod class
 */
class __cell_export AbstractTransferMethod
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractTransferMethod)

    /*!
     * \brief The get function receives data through the interface.
     * \returns as optional string.
     */
    __cell_virtual Types::OptionalString get() __cell_const_noexcept = __cell_zero;

    /*!
     * \brief Getting transfer method for service.
     * \returns method.
     */
    __cell_virtual TransferMethodState getMethod() = __cell_zero;

    /*!
     * \brief Change the method of service usage.
     * \param method is type of transfering between services.
     */
    __cell_virtual void change(const TransferMethodState& method) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractTransferMethod)
};
CELL_NAMESPACE_END

#endif  // CELL_TRANSFER_ABSTRACT_HPP
