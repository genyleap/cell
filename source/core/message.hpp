/*!
 * @file        message.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Message system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MESSAGE_HPP
#define CELL_MESSAGE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif


CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The MessageStyle enum
 */
__cell_enum_class MessageStyle : u8
{
    Default,
    Information,
    Warning,
    Critical,
    Success,
    Custom
};

struct MessageData final
{
    OptionalString  message {}; //!< Message to send.
    OptionalString  author  {}; //!< Author of message.
    OptionalNumeric postId  {}; //!< Post id for message.
    MessageStyle    style   {}; //!< Message style for post section.
};

/*!
 * \brief The AbstractTags class
 */
class __cell_export Message
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Message)

    /*!
     * \brief create function will insert the message for post.
     * \param messageData is messsage's data.
     * \returns as boolean.
     */
    bool create(const MessageData& messageData) __cell_const_noexcept;

    /*!
     * \brief edit function will update the message of post.
     * \param id is unique number of post.
     * \param messageData is messsage's data.
     * \returns as boolean.
     */
    bool edit(const u32 id, const MessageData& messageData) __cell_const_noexcept;

    /*!
     * \brief remove function will remove the message of post.
     * \param id is unique number of post.
     * \param messageData is messsage's data.
     * \returns as boolean.
     */
    bool remove(const u32 id, const MessageData& messageData) __cell_const_noexcept;

private:
    CELL_DISABLE_COPY(Message)
    MessageData* m_messageData;
};

CELL_NAMESPACE_END

#endif  // CELL_MESSAGE_HPP
