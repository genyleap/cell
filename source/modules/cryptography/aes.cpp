#if __has_include("aes.hpp")
#   include "aes.hpp"
#else
#   error "Cell's aes was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

std::string Aes::encrypt(const std::string &plaintext, const std::string &key)
{
    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);
    AES_KEY aesKey;

    if (AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), key.size() * 8, &aesKey) != 0) {
        Log("Failed to set AES encryption key", LoggerType::Critical);
        throw std::runtime_error("Failed to set AES encryption key");
    }

    AES_encrypt(reinterpret_cast<const unsigned char*>(plaintext.c_str()), ciphertext.data(), &aesKey);

    return std::string(reinterpret_cast<char*>(ciphertext.data()), ciphertext.size());
}

std::string Aes::decrypt(const std::string &ciphertext, const std::string &key)
{
    std::vector<unsigned char> decryptedText(ciphertext.size());
    AES_KEY aesKey;

    if (AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), key.size() * 8, &aesKey) != 0) {
        Log("Failed to set AES decryption key", LoggerType::Critical);
        throw std::runtime_error("Failed to set AES decryption key");
    }

    AES_decrypt(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), decryptedText.data(), &aesKey);

    return std::string(reinterpret_cast<char*>(decryptedText.data()), decryptedText.size());
}

bool Aes::validateKey(const std::string &key)
{
    return (key.size() == static_cast<size_t>(KeySize::AES_128) ||
            key.size() == static_cast<size_t>(KeySize::AES_192) ||
            key.size() == static_cast<size_t>(KeySize::AES_256));
}

bool Aes::match(const std::string &plaintext, const std::string &ciphertext, const std::string &key)
{
    std::string encryptedText = encrypt(plaintext, key);
    return (encryptedText == ciphertext);
}

std::string Aes::generateAESKey(KeySize keySize)
{
    const int keyLength = static_cast<int>(keySize);
    std::vector<unsigned char> key(keyLength);
    if (RAND_bytes(key.data(), keyLength) != 1) {
        Log("Failed to generate AES key", LoggerType::Critical);
        throw std::runtime_error("Failed to generate AES key");
    }
    return std::string(reinterpret_cast<char*>(key.data()), keyLength);
}

CELL_NAMESPACE_END
