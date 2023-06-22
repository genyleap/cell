#if __has_include("des.hpp")
#   include "des.hpp"
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

std::string Des::encrypt(const std::string& plaintext, const std::string& key)
{
    // Prepare the DES key
    DES_cblock desKey;
    DES_key_schedule desKeySchedule;
    std::string encryptedText;

    memset(&desKey, 0, sizeof(desKey));
    memcpy(&desKey, key.c_str(), std::min(key.size(), sizeof(desKey)));

    DES_set_key_unchecked(&desKey, &desKeySchedule);

    // Prepare the input and output buffers
    const size_t blockSize = 8;
    unsigned char input[blockSize];
    unsigned char output[blockSize];

    size_t textLength = plaintext.size();
    size_t encryptedLength = 0;

    while (textLength > 0) {
        memset(input, 0, blockSize);
        memset(output, 0, blockSize);

        size_t currentBlockSize = std::min(textLength, blockSize);
        memcpy(input, plaintext.c_str() + encryptedLength, currentBlockSize);

        DES_ecb_encrypt(reinterpret_cast<DES_cblock*>(input),
                        reinterpret_cast<DES_cblock*>(output),
                        &desKeySchedule,
                        DES_ENCRYPT);

        encryptedText.append(reinterpret_cast<char*>(output), blockSize);

        textLength -= currentBlockSize;
        encryptedLength += currentBlockSize;
    }

    return encryptedText;
}


std::string Des::decrypt(const std::string& ciphertext, const std::string& key)
{
    // Prepare the DES key
    DES_cblock desKey;
    DES_key_schedule desKeySchedule;
    std::string decryptedText;

    memset(&desKey, 0, sizeof(desKey));
    memcpy(&desKey, key.c_str(), std::min(key.size(), sizeof(desKey)));

    DES_set_key_unchecked(&desKey, &desKeySchedule);

    // Prepare the input and output buffers
    const size_t blockSize = 8;
    unsigned char input[blockSize];
    unsigned char output[blockSize];

    size_t textLength = ciphertext.size();
    size_t decryptedLength = 0;

    while (textLength > 0) {
        memset(input, 0, blockSize);
        memset(output, 0, blockSize);

        size_t currentBlockSize = std::min(textLength, blockSize);
        memcpy(input, ciphertext.c_str() + decryptedLength, currentBlockSize);

        DES_ecb_encrypt((DES_cblock*)input, (DES_cblock*)output, &desKeySchedule, DES_DECRYPT);

        decryptedText.append(reinterpret_cast<char*>(output), blockSize);

        textLength -= currentBlockSize;
        decryptedLength += currentBlockSize;
    }

    return decryptedText;
}

bool Des::validateKey(const std::string &key)
{
    return (key.size() == static_cast<size_t>(KeySize::DES_56) ||
            key.size() == static_cast<size_t>(KeySize::DES_112) ||
            key.size() == static_cast<size_t>(KeySize::DES_168));
}

bool Des::match(const std::string &plaintext, const std::string &ciphertext, const std::string &key)
{
    std::string encryptedText = encrypt(plaintext, key);
    return (encryptedText == ciphertext);
}

std::string Des::generateDESKey(KeySize keySize)
{
    const int keyLength = static_cast<int>(keySize);
    std::vector<unsigned char> key(keyLength);
    if (RAND_bytes(key.data(), keyLength) != 1) {
        Log("Failed to generate DES key", LoggerType::Critical);
        throw std::runtime_error("Failed to generate DES key");
    }
    return std::string(reinterpret_cast<const char*>(key.data()), key.size());
}


CELL_NAMESPACE_END
