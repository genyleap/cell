/*!
 * @file        sms.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     SMS interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 202e
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SMS_ABSTRACT_HPP
#define CELL_SMS_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @brief The SmsStruct struct represents the internal structure of an SMS message.
 */
struct SmsStruct final
{
    Types::OptionalString from      {}; //!< The phone number or name of the sender.
    Types::OptionalString body      {}; //!< The message body.

    Types::Optional<Types::VectorString> to     {}; //!< The phone number or name of the message recipient(s).
    Types::Optional<Types::VectorString> cc     {}; //!< The phone number or name of the message recipient(s) who should be carbon-copied.
    Types::Optional<Types::VectorString> bcc    {}; //!< The phone number or name of the message recipient(s) who should be blind-carbon-copied.
};

/**
 * @brief The Sms class represents an SMS message.
 */
class __cell_export Sms final {
public:
    /**
     * @brief Constructs an SMS message with the specified properties.
     *
     * @param to The phone number or name of the message recipient(s).
     * @param cc The phone number or name of the message recipient(s) who should be carbon-copied.
     * @param bcc The phone number or name of the message recipient(s) who should be blind-carbon-copied.
     * @param from The phone number or name of the sender.
     * @param body The message body.
     */
    Sms(const Types::Optional<Types::VectorString>& to,
        const Types::Optional<Types::VectorString>& cc,
        const Types::Optional<Types::VectorString>& bcc,
        const Types::OptionalString& from,
        const Types::OptionalString& body);

    ~Sms();

    /**
     * @brief Returns the phone number or name of the message recipient(s).
     */
    const Types::Optional<Types::VectorString>& getTo() const;

    /**
     * @brief Returns the phone number or name of the message recipient(s) who should be carbon-copied.
     */
    const Types::Optional<Types::VectorString>& getCc() const;

    /**
     * @brief Returns the phone number or name of the message recipient(s) who should be blind-carbon-copied.
     */
    const Types::Optional<Types::VectorString>& getBcc() const;

    /**
     * @brief Returns the phone number or name of the sender.
     */
    const Types::OptionalString& getFrom() const;

    /**
     * @brief Returns the message body.
     */
    const Types::OptionalString& getBody() const;

private:
    SmsStruct smsStructure {}; //!< The internal structure of the SMS message.
};



CELL_NAMESPACE_END

#endif  // CELL_SMS_ABSTRACT_HPP
