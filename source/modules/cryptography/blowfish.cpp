#if __has_include("blowfish.hpp")
#   include "blowfish.hpp"
#else
#   error "Cell's blowfish was not found!"
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

std::vector<unsigned char> BlowFish::encrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& data)
{
    std::vector<unsigned char> encryptedData(data.size());
    BF_KEY bfKey;
    BF_set_key(&bfKey, key.size(), key.data()); // Set the encryption key

    unsigned char iv[BF_BLOCK];
    RAND_bytes(iv, BF_BLOCK); // Generate random initialization vector

    BF_cbc_encrypt(data.data(), encryptedData.data(), data.size(), &bfKey, iv, BF_ENCRYPT); // Perform encryption

    // Append the initialization vector to the encrypted data
    encryptedData.insert(encryptedData.begin(), iv, iv + BF_BLOCK);

    return encryptedData;
}

std::vector<unsigned char> BlowFish::decrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& encryptedData)
{
    std::vector<unsigned char> decryptedData(encryptedData.size() - BF_BLOCK);
    BF_KEY bfKey;
    BF_set_key(&bfKey, key.size(), key.data()); // Set the encryption key

    // Extract the initialization vector from the encrypted data
    unsigned char iv[BF_BLOCK];
    std::copy(encryptedData.begin(), encryptedData.begin() + BF_BLOCK, iv);

    BF_cbc_encrypt(encryptedData.data() + BF_BLOCK, decryptedData.data(), encryptedData.size() - BF_BLOCK, &bfKey, iv, BF_DECRYPT); // Perform decryption

    return decryptedData;
}

bool BlowFish::validateKey(const std::vector<unsigned char>& key)
{
    size_t keySize = key.size();
    return (keySize == static_cast<size_t>(KeySize::BLOWFISH_128) ||
            keySize == static_cast<size_t>(KeySize::BLOWFISH_192) ||
            keySize == static_cast<size_t>(KeySize::BLOWFISH_256));
}

bool BlowFish::match(const std::string& plaintext, const std::string& ciphertext, const std::vector<unsigned char>& key)
{
    std::vector<unsigned char> encryptedData = encrypt(key, std::vector<unsigned char>(plaintext.begin(), plaintext.end()));
    std::vector<unsigned char> decryptedData = decrypt(key, std::vector<unsigned char>(ciphertext.begin(), ciphertext.end()));
    std::string decryptedText(decryptedData.begin(), decryptedData.end());
    return (decryptedText == plaintext);
}

std::vector<unsigned char> BlowFish::generateBlowfishKey(KeySize keySize)
{
    std::vector<unsigned char> key(static_cast<size_t>(keySize));
    RAND_bytes(key.data(), static_cast<int>(keySize));
    return key;
}

CELL_NAMESPACE_END
