/*!
 * @file        des.hpp
 * @brief       Cryptography Des for the Cell Engine.
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

#ifndef CELL_CRYPTOGRAPHY_DES_HPP
#define CELL_CRYPTOGRAPHY_DES_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef USE_OPENSSL
#if __has_include(<openssl/des.h>)
#   include <openssl/des.h>
#   include <openssl/evp.h>
#   include "openssl/rand.h"
#else
#   error "Cell's <openssl/des.h> was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

/**
 * @brief Provides DES encryption and decryption functionality.
 *
 * The Des class allows encryption and decryption of data using the DES (Data Encryption Standard) algorithm.
 * It supports key generation, encryption, decryption, key validation, and matching functionalities.
 */
class __cell_export Des {
public:
    /**
     * @brief Enumerates the supported key sizes for DES encryption.
     *
     * The KeySize enum class specifies the valid key sizes for DES encryption. It defines three options: DES_56, DES_112,
     * and DES_168, representing key sizes of 56 bits, 112 bits, and 168 bits, respectively.
     */
    enum class KeySize {
        DES_56 = 7,    //!< 56 bits.
        DES_112 = 14,  //!< 112 bits.
        DES_168 = 21   //!< 168 bits.
    };

    /**
     * @brief Encrypts the input plaintext using DES encryption with the specified key.
     * @param plaintext The plaintext to be encrypted.
     * @param key The DES key used for encryption.
     * @return The encrypted ciphertext as a string.
     */
    static std::string encrypt(const std::string& plaintext, const std::string& key);

    /**
     * @brief Decrypts the input ciphertext using DES decryption with the specified key.
     * @param ciphertext The ciphertext to be decrypted.
     * @param key The DES key used for decryption.
     * @return The decrypted plaintext as a string.
     */
    static std::string decrypt(const std::string& ciphertext, const std::string& key);

    /**
     * @brief Validates if the provided key is of the correct size for DES encryption.
     * @param key The key to validate.
     * @return True if the key is valid, false otherwise.
     */
    static bool validateKey(const std::string& key);

    /**
     * @brief Matches the given plaintext and ciphertext using DES encryption with the specified key.
     * @param plaintext The plaintext to be encrypted.
     * @param ciphertext The ciphertext to be matched against.
     * @param key The DES key used for encryption.
     * @return True if the ciphertext matches the encryption of the plaintext, false otherwise.
     */
    static bool match(const std::string& plaintext, const std::string& ciphertext, const std::string& key);

    /**
     * @brief Generates a random DES key with the specified key size.
     * @param keySize The desired size of the DES key.
     * @return The generated DES key as a string.
     */
    static std::string generateDESKey(KeySize keySize);
};

#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_DES_HPP

