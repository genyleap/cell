/*!
 * @file        message.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Message interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MESSAGE_ABSTRACT_HPP
#define CELL_MESSAGE_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("abstracts/account/usermanager.hpp")
#   include "abstracts/account/usermanager.hpp"
#else
#   error "Cell's "abstracts/account/usermanager.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @class AbstractMessage
 * @brief Represents an abstract message.
 */
class __cell_export AbstractMessage {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractMessage)

    /**
     * @brief Get the message ID.
     * @return The message ID.
     */
    __cell_virtual std::string getMessageId() __cell_const = __cell_zero;

    /**
     * @brief Get the sender ID.
     * @return The sender ID.
     */
    __cell_virtual std::string getSenderId() __cell_const = __cell_zero;

    /**
     * @brief Get the receiver ID.
     * @return The receiver ID.
     */
    __cell_virtual std::string getReceiverId() __cell_const = __cell_zero;

    /**
     * @brief Get the message content.
     * @return The message content.
     */
    __cell_virtual std::string getContent() __cell_const = __cell_zero;

    /**
     * @brief Get the timestamp of the message.
     * @return The timestamp of the message.
     */
    __cell_virtual std::chrono::system_clock::time_point getTimestamp() __cell_const = __cell_zero;

    /**
     * @brief Check if the message is read.
     * @return True if the message is read, false otherwise.
     */
    __cell_virtual bool isRead() __cell_const = __cell_zero;

    /**
     * @brief Mark the message as read.
     */
    __cell_virtual void markAsRead() = __cell_zero;

    /**
     * @brief Get the like count of the message.
     * @return The like count of the message.
     */
    __cell_virtual int getLikeCount() __cell_const = __cell_zero;

    /**
     * @brief Check if the message is liked by a user.
     * @param userId The user ID.
     * @return True if the message is liked by the user, false otherwise.
     */
    __cell_virtual bool isLikedByUser(const std::string& userId) __cell_const = __cell_zero;

    /**
     * @brief Add a like to the message.
     * @param userId The user ID.
     */
    __cell_virtual void addLike(const std::string& userId) = __cell_zero;

    /**
     * @brief Remove a like from the message.
     * @param userId The user ID.
     */
    __cell_virtual void removeLike(const std::string& userId) = __cell_zero;

    /**
     * @brief Get the comments of the message.
     * @return The comments of the message.
     */
    __cell_virtual std::vector<std::string> getComments() __cell_const = __cell_zero;

    /**
     * @brief Add a comment to the message.
     * @param comment The comment to add.
     */
    __cell_virtual void addComment(const std::string& comment) = __cell_zero;

    /**
     * @brief Get the ID of the message being replied to.
     * @return The ID of the message being replied to.
     */
    __cell_virtual std::string getReplyToMessageId() __cell_const = __cell_zero;

    /**
     * @brief Check if the message can be edited by a user.
     * @param user The user manager.
     * @return True if the message can be edited by the user, false otherwise.
     */
    __cell_virtual bool canEdit(const Account::AbstractUserManager& user) __cell_const = __cell_zero;

    /**
     * @brief Edit the content of the message.
     * @param newContent The new content of the message.
     */
    __cell_virtual void editContent(const std::string& newContent) = __cell_zero;

    /**
     * @brief Check if the message is pinned.
     * @return True if the message is pinned, false otherwise.
     */
    __cell_virtual bool isPinned() __cell_const = __cell_zero;

    /**
     * @brief Pin the message.
     */
    __cell_virtual void pin() = __cell_zero;

    /**
     * @brief Unpin the message.
     */
    __cell_virtual void unpin() = __cell_zero;

    /**
     * @brief Delete the message.
     */
    __cell_virtual void deleteMessage() = __cell_zero;

    /**
     * @brief Forward the message to a receiver.
     * @param receiverId The ID of the receiver.
     */
    __cell_virtual void forwardMessage(const std::string& receiverId) = __cell_zero;

    /**
     * @brief Add a reaction to the message.
     * @param userId The user ID.
     * @param reaction The reaction to add.
     */
    __cell_virtual void addReaction(const std::string& userId, const std::string& reaction) = __cell_zero;

    /**
     * @brief Remove a reaction from the message.
     * @param userId The user ID.
     * @param reaction The reaction to remove.
     */
    __cell_virtual void removeReaction(const std::string& userId, const std::string& reaction) = __cell_zero;

    /**
     * @brief Get the users who reacted with a specific reaction to the message.
     * @param reaction The reaction to search for.
     * @return The users who reacted with the specified reaction.
     */
    __cell_virtual std::vector<std::string> getReactions(const std::string& reaction) __cell_const = __cell_zero;

    /**
     * @brief Search for messages containing a keyword.
     * @param keyword The keyword to search for.
     * @return The messages containing the keyword.
     */
    __cell_virtual std::vector<std::string> searchMessages(const std::string& keyword) __cell_const = __cell_zero;

    /**
     * @brief Translate the message to a target language.
     * @param targetLanguage The target language.
     */
    __cell_virtual void translateMessage(const std::string& targetLanguage) = __cell_zero;

    /**
     * @brief Schedule the message to be sent at a specific time.
     * @param scheduledTime The scheduled time.
     */
    __cell_virtual void scheduleMessage(const std::chrono::system_clock::time_point& scheduledTime) = __cell_zero;

    /**
     * @brief Delete the scheduled message.
     */
    __cell_virtual void deleteScheduledMessage() = __cell_zero;

    /**
     * @brief Format the message with a specific formatting.
     * @param formatting The formatting to apply.
     */
    __cell_virtual void formatMessage(const std::string& formatting) = __cell_zero;

    /**
     * @brief Flag the message.
     */
    __cell_virtual void flagMessage() = __cell_zero;

    /**
     * @brief Mark the message as priority.
     */
    __cell_virtual void markAsPriority() = __cell_zero;

    /**
     * @brief Archive the message.
     */
    __cell_virtual void archiveMessage() = __cell_zero;

    /**
     * @brief Check if the message has an attachment.
     * @return True if the message has an attachment, false otherwise.
     */
    __cell_virtual bool hasAttachment() __cell_const = __cell_zero;

    /**
     * @brief Get the URL of the message's attachment.
     * @return The URL of the message's attachment.
     */
    __cell_virtual std::string getAttachmentURL() __cell_const = __cell_zero;

    /**
     * @brief Set the URL of the message's attachment.
     * @param attachmentURL The URL of the attachment.
     */
    __cell_virtual void setAttachmentURL(const std::string& attachmentURL) = __cell_zero;
};

CELL_NAMESPACE_END

#endif  // CELL_MESSAGE_ABSTRACT_HPP
