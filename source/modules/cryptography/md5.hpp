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

class __cell_export Md5
{
public:
    static std::string hash(const std::string& input);
    static bool validateHash(const std::string& hashval);
    static bool matchHash(const std::string& input, const std::string& hashval);
};

#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_MD5_HPP

