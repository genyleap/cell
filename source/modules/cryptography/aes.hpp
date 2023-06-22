/*!
 * @file        aes.hpp
 * @brief       Cryptography Aes for the Cell Engine.
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

#ifndef CELL_CRYPTOGRAPHY_AES_HPP
#define CELL_CRYPTOGRAPHY_AES_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef USE_OPENSSL
#if __has_include(<openssl/aes.h>)
#   include <openssl/aes.h>
#   include "openssl/rand.h"
#else
#   error "Cell's <openssl/aes.h> was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

/**
 * @brief Provides AES encryption and decryption functionality.
 *
 * The Aes class allows encryption and decryption of data using the AES (Advanced Encryption Standard) algorithm.
 * It supports key generation, encryption, decryption, key validation, and matching functionalities.
 */
class __cell_export Aes {
public:

    /**
 * @brief Enumerates the supported key sizes for AES encryption.
 *
 * The KeySize enum class specifies the valid key sizes for AES encryption. It defines three options: AES_128, AES_192,
 * and AES_256, representing key sizes of 128 bits, 192 bits, and 256 bits, respectively.
 */
    enum class KeySize {
        AES_128 = 16,   //!< 128 bits.
        AES_192 = 24,   //!< 192 bits.
        AES_256 = 32    //!< 256 bits.
    };

    /**
     * @brief Encrypts the input plaintext using AES encryption with the specified key.
     * @param plaintext The plaintext to be encrypted.
     * @param key The AES key used for encryption.
     * @return The encrypted ciphertext as a string.
     */
    static std::string encrypt(const std::string& plaintext, const std::string& key);

    /**
     * @brief Decrypts the input ciphertext using AES decryption with the specified key.
     * @param ciphertext The ciphertext to be decrypted.
     * @param key The AES key used for decryption.
     * @return The decrypted plaintext as a string.
     */
    static std::string decrypt(const std::string& ciphertext, const std::string& key);

    /**
     * @brief Validates if the provided key is of the correct size for AES encryption.
     * @param key The key to validate.
     * @return True if the key is valid, false otherwise.
     */
    static bool validateKey(const std::string& key);

    /**
     * @brief Matches the given plaintext and ciphertext using AES encryption with the specified key.
     * @param plaintext The plaintext to be encrypted.
     * @param ciphertext The ciphertext to be matched against.
     * @param key The AES key used for encryption.
     * @return True if the ciphertext matches the encryption of the plaintext, false otherwise.
     */
    static bool match(const std::string& plaintext, const std::string& ciphertext, const std::string& key);

    /**
     * @brief Generates a random AES key with the specified key size.
     * @param keySize The desired size of the AES key.
     * @return The generated AES key as a string.
     */
    static std::string generateAESKey(KeySize keySize);
};

#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_AES_HPP

