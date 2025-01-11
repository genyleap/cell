/*!
 * @file        user-concepts.hpp
 * @brief       This file is part of the Cell System.
 * @details     User concepts interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       13 Jan 2024
 * @copyright   Copyright (c) 2024 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_USER_CONCEPTS_ABSTRACT_HPP
#define CELL_USER_CONCEPTS_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Core (Core Only).
#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's requirements was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Concepts::User)

// Concept for valid hexadecimal characters
template <typename T>
concept IsHexChar = std::integral<T> && std::is_unsigned_v<T>;

// Concept for a string consisting of valid hexadecimal characters
template <typename T>
concept IsHexString = requires(T t) {
    { std::all_of(t.begin(), t.end(), [](char c) { return IsHexChar<unsigned char>; }) }
        ->std::same_as<bool>;
};

// Concept for valid crypto addresses (hex string)
template <typename T>
concept IsCryptoAddress = IsHexString<T>;

// Concept for valid email addresses
template <typename T>
concept IsEmail = std::is_convertible_v<T, std::string> && requires(T t) {
    // A simple check for email format (more sophisticated validation can be added)
    { t.find('@') != std::string::npos && t.find('.') != std::string::npos }
        ->std::same_as<bool>;
};

class UserCredentials {
public:
    // Constructor with concept constraints
    template <IsEmail E, IsCryptoAddress C>
    UserCredentials(E&& email, C&& cryptoAddress, const std::string& password)
        : email(std::forward<E>(email)), cryptoAddress(std::forward<C>(cryptoAddress)), password(password) {}

           // Getter functions
    std::string getEmail() const {
        return email;
    }

    std::string getCryptoAddress() const {
        return cryptoAddress;
    }

    std::string getPassword() const {
        return password;
    }

private:
    std::string email;
    std::string cryptoAddress;
    std::string password;
};

CELL_NAMESPACE_END

#endif // CELL_USER_CONCEPTS_ABSTRACT_HPP
