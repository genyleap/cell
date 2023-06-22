/*!
 * @file        sha.hpp
 * @brief       Cryptography Sha for the Cell Engine.
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

#ifndef CELL_CRYPTOGRAPHY_SHA_HPP
#define CELL_CRYPTOGRAPHY_SHA_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef USE_OPENSSL
#if __has_include(<openssl/sha.h>)
#   include <openssl/sha.h>
#else
#   error "Cell's <openssl/sha.h> was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

/**
 * @brief The SHA class provides functionality for hashing using various SHA algorithms.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Sha {
public:
    /**
     * @brief The Algorithm enum represents different SHA algorithms.
     */
    enum class Algorithm {
        SHA1,    //!< SHA-1 algorithm.
        SHA224,  //!< SHA-224 algorithm.
        SHA256,  //!< SHA-256 algorithm.
        SHA384,  //!< SHA-384 algorithm.
        SHA512   //!< SHA-512 algorithm.
    };

    /**
     * @brief Computes the hash value of the input string using the specified SHA algorithm.
     * @param input The input string to be hashed.
     * @param variant The SHA algorithm variant to use.
     * @return The computed hash value as a string.
     */
    static std::string hash(const std::string& input, Algorithm variant);

    /**
     * @brief Validates if a given hash matches the computed hash of the input string.
     * @param input The input string.
     * @param hashVal The hash value to validate against.
     * @param variant The SHA algorithm variant used to compute the hash.
     * @return True if the given hash matches the computed hash, false otherwise.
     */
    static bool validateHash(const std::string& input, const std::string& hashVal, Algorithm variant);

    /**
     * @brief Checks if the computed hash of the input string contains a given hash value.
     * @param input The input string.
     * @param hashVal The hash value to search for in the computed hash.
     * @param variant The SHA algorithm variant used to compute the hash.
     * @return True if the computed hash contains the given hash value, false otherwise.
     */
    static bool matchHash(const std::string& input, const std::string& hashVal, Algorithm variant);
};

#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_SHA_HPP

