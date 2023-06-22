/*!
 * @file        blowfish.hpp
 * @brief       Cryptography Blowfish for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_CRYPTOGRAPHY_BLOWFISH_HPP
#define CELL_CRYPTOGRAPHY_BLOWFISH_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef USE_OPENSSL
#if __has_include(<openssl/blowfish.h>)
#   include <openssl/blowfish.h>
#   include <openssl/evp.h>
#   include "openssl/rand.h"
#else
#   error "Cell's <openssl/des.h> was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

/**
 * @class BlowFish
 * @brief Provides encryption and decryption using the Blowfish cipher.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export BlowFish {
public:
    /**
     * @enum KeySize
     * @brief Specifies the key sizes supported by Blowfish.
     */
    enum class KeySize {
        BLOWFISH_128 = 16, //!< 128-bit key size.
        BLOWFISH_192 = 24, //!< 192-bit key size.
        BLOWFISH_256 = 32  //!< 256-bit key size.
    };

    /**
     * @brief Encrypts the given data using the provided key.
     * @param key The encryption key as a vector of unsigned chars.
     * @param data The data to be encrypted as a vector of unsigned chars.
     * @return The encrypted data as a vector of unsigned chars.
     */
    static std::vector<unsigned char> encrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& data);

    /**
     * @brief Decrypts the given encrypted data using the provided key.
     * @param key The decryption key as a vector of unsigned chars.
     * @param encryptedData The encrypted data to be decrypted as a vector of unsigned chars.
     * @return The decrypted data as a vector of unsigned chars.
     */
    static std::vector<unsigned char> decrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& encryptedData);

    /**
     * @brief Validates the given encryption or decryption key.
     * @param key The key to be validated as a vector of unsigned chars.
     * @return True if the key is valid, false otherwise.
     */
    static bool validateKey(const std::vector<unsigned char>& key);

    /**
     * @brief Matches the given plaintext and ciphertext using the provided key.
     * @param plaintext The original plaintext as a string.
     * @param ciphertext The encrypted ciphertext as a string.
     * @param key The key used for encryption or decryption as a vector of unsigned chars.
     * @return True if the plaintext and ciphertext match using the given key, false otherwise.
     */
    static bool match(const std::string& plaintext, const std::string& ciphertext, const std::vector<unsigned char>& key);

    /**
     * @brief Generates a Blowfish key of the specified key size.
     * @param keySize The desired key size as a KeySize enum value.
     * @return The generated key as a vector of unsigned chars.
     */
    static std::vector<unsigned char> generateBlowfishKey(KeySize keySize);
};

#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_BLOWFISH_HPP

