/*!
 * @file        rsa.hpp
 * @brief       Cryptography Rsa for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2025 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_CRYPTOGRAPHY_RSA_HPP
#define CELL_CRYPTOGRAPHY_RSA_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

#ifdef USE_OPENSSL
#if __has_include(<openssl/rsa.h>)
#   include <openssl/rsa.h>
#   include <openssl/x509.h>
#   include <openssl/pem.h>
#   include <openssl/err.h>
#else
#   error "Cell's <openssl/aes.h> was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

/**
 * @brief Class representing an RSA encryption algorithm.
 *
 * This class provides functionality for RSA encryption and decryption.
 * It can generate RSA key pairs and perform encryption and decryption operations
 * using the generated keys.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Rsa {
public:
    /**
     * @brief Generates a new RSA key pair with the specified key size.
     * @param keySize The size of the RSA key in bits.
     * @return The generated RSA key pair.
     */
    static RSA* generateKeyPair(int keySize);

    /**
     * @brief Encrypts the input plaintext using RSA encryption with the specified public key.
     * @param plaintext The plaintext to be encrypted.
     * @param publicKey The RSA public key used for encryption.
     * @return The encrypted ciphertext as a string.
     */
    static std::string encrypt(const std::string& plaintext, RSA* publicKey);

    /**
     * @brief Decrypts the input ciphertext using RSA decryption with the specified private key.
     * @param ciphertext The ciphertext to be decrypted.
     * @param privateKey The RSA private key used for decryption.
     * @return The decrypted plaintext as a string.
     */
    static std::string decrypt(const std::string& ciphertext, RSA* privateKey);

    /**
     * @brief Signs the input message using RSA signing with the specified private key.
     * @param message The message to be signed.
     * @param privateKey The RSA private key used for signing.
     * @return The signature as a string.
     */
    static std::string sign(const std::string& message, RSA* privateKey);

    /**
     * @brief Verifies the input message and signature using RSA verification with the specified public key.
     * @param message The message to be verified.
     * @param signature The signature to be verified.
     * @param publicKey The RSA public key used for verification.
     * @return True if the signature is valid, false otherwise.
     */
    static bool verify(const std::string& message, const std::string& signature, RSA* publicKey);

};

/**
 * @class RsaKeyGenerator
 * @brief Generates and manages RSA key pairs using OpenSSL.
 */
class __cell_export RsaKeyGenerator {
public:
    /**
     * @enum KeySize
     * @brief Enumeration of different RSA key sizes.
     */
    enum KeySize {
        Size_1024 = 1024, //!< 1024-bit RSA key size.
        Size_2048 = 2048, //!< 2048-bit RSA key size.
        Size_4096 = 4096  //!< 4096-bit RSA key size.
    };

    /**
     * @brief Constructs an RsaKeyGenerator object with the specified key size.
     * @param keySize The desired RSA key size.
     */
    RsaKeyGenerator(KeySize keySize);

    /**
     * @brief Destructor for the RsaKeyGenerator object.
     */
    ~RsaKeyGenerator();

    /**
     * @brief Generates an RSA key pair and saves them to files.
     * @param privateKeyFile The path to the private key file.
     * @param publicKeyFile The path to the public key file.
     * @return True if the key pair generation and file saving succeed, false otherwise.
     */
    bool generateKeys(const std::string& privateKeyFile, const std::string& publicKeyFile);

    /**
     * @brief Generates an RSA key pair.
     * @return A pointer to the generated RSA key pair.
     */
    RSA* generateKeyPair();

    /**
     * @brief Sets the key size.
     * @param keySize The desired RSA key size.
     */
    void setKeySize(KeySize keySize);

    /**
     * @brief Exports the RSA key pair to memory.
     * @param privateKey A string to store the exported private key.
     * @param publicKey A string to store the exported public key.
     * @return True if the export succeeds, false otherwise.
     */
    bool exportKeysToMemory(std::string& privateKey, std::string& publicKey);

    /**
     * @brief Retrieves the public key.
     * @return A pointer to the RSA public key.
     */
    RSA* getPublicKey();

    /**
     * @brief Retrieves the private key.
     * @return A pointer to the RSA private key.
     */
    RSA* getPrivateKey();

    /**
     * @brief Encrypts a plaintext message using the RSA public key.
     * @param plaintext The plaintext message to encrypt.
     * @return The ciphertext as a string.
     */
    std::string encrypt(const std::string& plaintext);

    /**
     * @brief Decrypts a ciphertext message using the RSA private key.
     * @param ciphertext The ciphertext message to decrypt.
     * @return The decrypted plaintext as a string.
     */
    std::string decrypt(const std::string& ciphertext);

    /**
     * @brief Exports the RSA public key to a file.
     * @param publicKeyFile The path to the public key file.
     * @return True if the export succeeds, false otherwise.
     */
    bool exportPublicKey(const std::string& publicKeyFile);

    /**
     * @brief Exports the RSA private key to a file.
     * @param privateKeyFile The path to the private key file.
     * @return True if the export succeeds, false otherwise.
     */
    bool exportPrivateKey(const std::string& privateKeyFile);

    /**
     * @brief Validates the RSA key pair.
     * @return True if the key pair is valid, false otherwise.
     */
    bool validateKeys();

private:
    RSA* m_rsaKeyPair; //!< The RSA key pair.
    int m_keySize;     //!< The key size in bits.
};

/**
 * @brief The struct to store decoded CSR data.
 */
struct CsrData final
{
    Types::OptionalString commonName            {};    //!< The common name (CN) field.
    Types::OptionalString organization          {};    //!< The organization (O) field.
    Types::OptionalString organizationalUnit    {};    //!< The organizational unit (OU) field.
    Types::OptionalString locality              {};    //!< The locality (L) field.
    Types::OptionalString state                 {};    //!< The state/province (ST) field.
    Types::OptionalString country               {};    //!< The country (C) field.
    Types::OptionalString emailAddress          {};    //!< The email address field.
};

/**
 * @brief The class for generating CSR (Certificate Signing Request) using RSA OpenSSL.
 */
class __cell_export CSRGenerator
{
public:
    /**
     * @brief Constructor for CSRGenerator class.
     */
    CSRGenerator();

    /**
     * @brief Destructor for CSRGenerator class.
     */
    ~CSRGenerator();

    /**
     * @brief Loads the private key from the specified file.
     *
     * @param privateKeyPath The path to the private key file.
     * @return True if the private key was loaded successfully, false otherwise.
     */
    bool loadPrivateKey(const std::string& privateKeyPath);

    /**
     * @brief Generates a CSR with the specified information and saves it to the specified file.
     *
     * @param csrPath The path to save the generated CSR.
     * @param commonName The common name (CN) field.
     * @param organization The organization (O) field.
     * @param organizationalUnit The organizational unit (OU) field.
     * @param locality The locality (L) field.
     * @param state The state/province (ST) field.
     * @param country The country (C) field.
     * @param emailAddress The email address field.
     * @return True if the CSR was generated successfully, false otherwise.
     */
    bool generateCSR(const std::string& csrPath, const std::string& commonName,
                     const std::string& organization, const std::string& organizationalUnit,
                     const std::string& locality, const std::string& state,
                     const std::string& country, const std::string& emailAddress);

    /**
     * @brief Decodes the specified CSR file and stores the extracted data in the provided CsrData object.
     *
     * @param csrPath The path to the CSR file.
     * @param csrData The CsrData object to store the decoded data.
     * @return True if the CSR was decoded successfully, false otherwise.
     */
    bool decodeCSR(const std::string& csrPath, CsrData& csrData);

private:
    EVP_PKEY* m_privateKey; //!< The private key used for generating CSR.
};


#endif

CELL_NAMESPACE_END

#endif  // CELL_CRYPTOGRAPHY_RSA_HPP

