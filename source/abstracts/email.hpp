/*!
 * @file        email.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Email structure and client interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_EMAIL_ABSTRACT_HPP
#define CELL_EMAIL_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @brief The EmailStruct class
 */
struct EmailStruct final
{
    Types::OptionalString from      {}; //!< An optional string indicating the sender of the email.
    Types::OptionalString subject   {}; //!< An optional string containing the subject of the email.
    Types::OptionalString body      {}; //!< An optional string containing the plain text body of the email.
    Types::OptionalString htmlBody  {}; //!< An optional string containing the HTML formatted body of the email.

    Types::Optional<Types::VectorString> to     {}; //!< An optional vector of strings containing the email addresses of the primary recipients of the email.
    Types::Optional<Types::VectorString> cc     {}; //!< An optional vector of strings containing the email addresses of the CC (Carbon Copy) recipients of the email.
    Types::Optional<Types::VectorString> bcc    {}; //!< An optional vector of strings containing the email addresses of the BCC (Blind Carbon Copy) recipients of the email.
};

class __cell_export Email final {
public:
    /**
     * @brief Constructs an Email object with the specified parameters.
     * @param to Recipient(s) of the email.
     * @param cc Carbon copy recipient(s) of the email.
     * @param bcc Blind carbon copy recipient(s) of the email.
     * @param from Sender of the email.
     * @param subject Subject of the email.
     * @param body Plain text body of the email.
     * @param attachments Vector of file paths of the attachments to the email.
     * @param htmlBody HTML body of the email.
     */
    Email(const Types::Optional<Types::VectorString>& to,
          const Types::Optional<Types::VectorString>& cc,
          const Types::Optional<Types::VectorString>& bcc,
          const Types::OptionalString& from,
          const Types::OptionalString& subject,
          const Types::OptionalString& body,
          const Types::Optional<Types::VectorString>& attachments = {},
          const Types::OptionalString& htmlBody = "");

    ~Email();

    /**
     * @brief Returns the recipient(s) of the email.
     * @return Recipient(s) of the email.
     */
    const Types::Optional<Types::VectorString>& getTo() const;

    /**
     * @brief Returns the carbon copy recipient(s) of the email.
     * @return Carbon copy recipient(s) of the email.
     */
    const Types::Optional<Types::VectorString>& getCc() const;

    /**
     * @brief Returns the blind carbon copy recipient(s) of the email.
     * @return Blind carbon copy recipient(s) of the email.
     */
    const Types::Optional<Types::VectorString>& getBcc() const;

    /**
     * @brief Returns the sender of the email.
     * @return Sender of the email.
     */
    const Types::OptionalString& getFrom() const;

    /**
     * @brief Returns the subject of the email.
     * @return Subject of the email.
     */
    const Types::OptionalString& getSubject() const;

    /**
     * @brief Returns the plain text body of the email.
     * @return Plain text body of the email.
     */
    const Types::OptionalString& getBody() const;

    /**
     * @brief Returns the vector of file paths of the attachments to the email.
     * @return Vector of file paths of the attachments to the email.
     */
    const Types::Optional<Types::VectorString>& getAttachments() const;

    /**
     * @brief Returns the HTML body of the email.
     * @return HTML body of the email.
     */
    const Types::OptionalString& getHtmlBody() const;

private:
    EmailStruct emailStructure {};
};

/**
 * @brief The EmailProtocol enum class defines the supported email protocols.
 */
enum class EmailProtocol { SMTP, POP3, IMAP };

/**
 * @brief The EmailClient class provides an interface for sending and receiving emails using different protocols.
 */
class __cell_export EmailClient {
public:

    /**
     * @brief connect establishes a connection with the email server.
     * @return true if connection is successful, false otherwise.
     */
    __cell_virtual bool connect() __cell_const = __cell_zero;

    /**
     * @brief login logs in to the email server with the given username and password.
     * @param username the username to use for logging in.
     * @param password the password to use for logging in.
     * @return true if login is successful, false otherwise.
     */
    __cell_virtual bool login(const std::string& username, const std::string& password) __cell_const = __cell_zero;

    /**
     * @brief sendEmail sends an email using the connected email server.
     * @param email the email to send.
     * @return true if sending is successful, false otherwise.
     */
    __cell_virtual bool sendEmail(const Email& email) __cell_const = __cell_zero;

    /**
     * @brief getUnreadEmails retrieves all unread emails from the email server.
     * @return a vector of all unread emails.
     */
    __cell_virtual std::vector<Email> getUnreadEmails() __cell_const = __cell_zero;

    /**
     * @brief markAsRead marks the given email as read on the email server.
     * @param email the email to mark as read.
     * @return true if marking as read is successful, false otherwise.
     */
    __cell_virtual bool markAsRead(const Email& email) __cell_const = __cell_zero;

    /**
     * @brief disconnect closes the connection to the email server.
     * @return true if disconnection is successful, false otherwise.
     */
    __cell_virtual bool disconnect() __cell_const = __cell_zero;

    /**
     * @brief setServer sets the email server to use for sending and receiving emails.
     * @param server the email server to use.
     */
    __cell_virtual void setServer(const std::string& server);

    /**
     * @brief setPort sets the port to use for the email server.
     * @param port the port to use.
     */
    __cell_virtual void setPort(int port);

    /**
     * @brief setEncryption sets whether to use encryption for the email server.
     * @param encryption true if encryption should be used, false otherwise.
     */
    __cell_virtual void setEncryption(bool encryption);

    /**
     * @brief setProtocol sets the email protocol to use for sending and receiving emails.
     * @param protocol the email protocol to use.
     */
    __cell_virtual void setProtocol(EmailProtocol protocol);
};


CELL_NAMESPACE_END

#endif  // CELL_EMAIL_ABSTRACT_HPP
