/*!
 * @file        md5.hpp
 * @brief       Cryptography md5 for the Cell Engine.
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

#ifndef CELL_CRYPTOGRAPHY_MD5_HPP
#define CELL_CRYPTOGRAPHY_MD5_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef USE_OPENSSL
#if __has_include(<openssl/md5.h>)
#   include <openssl/md5.h>
#else
#   error "Cell's <openssl/md5.h> was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

/**
 * @brief The Md5 class provides methods for computing and validating MD5 hashes.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Md5 {
public:
    /**
     * @brief Computes the MD5 hash of the given input string.
     * @param input The input string to compute the MD5 hash for.
     * @return The MD5 hash as a hexadecimal string.
     */
    static std::string hash(const std::string& input);

    /**
     * @brief Validates the given hash string.
     * @param hashval The hash string to validate.
     * @return True if the hash is valid, False otherwise.
     */
    static bool validateHash(const std::string& hashval);

    /**
     * @brief Matches the given input string with the provided hash.
     * @param input The input string to match.
     * @param hashval The hash string to match against.
     * @return True if the input matches the hash, False otherwise.
     */
    static bool matchHash(const std::string& input, const std::string& hashval);
};

#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_MD5_HPP

