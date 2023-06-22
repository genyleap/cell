#if __has_include("sha.hpp")
#   include "sha.hpp"
#else
#   error "Cell's sha was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

std::string Sha::hash(const std::string &input, Algorithm variant)
{
    unsigned char digest[SHA512_DIGEST_LENGTH];
    unsigned int digestLength = 0;

    switch (variant) {
    case Algorithm::SHA1:
        SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
        digestLength = SHA_DIGEST_LENGTH;
        break;
    case Algorithm::SHA224:
        SHA224(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
        digestLength = SHA224_DIGEST_LENGTH;
        break;
    case Algorithm::SHA256:
        SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
        digestLength = SHA256_DIGEST_LENGTH;
        break;
    case Algorithm::SHA384:
        SHA384(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
        digestLength = SHA384_DIGEST_LENGTH;
        break;
    case Algorithm::SHA512:
        SHA512(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
        digestLength = SHA512_DIGEST_LENGTH;
        break;
    }

    std::stringstream ss;
    for (unsigned int i = 0; i < digestLength; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return ss.str();
}

bool Sha::validateHash(const std::string &input, const std::string &hashVal, Algorithm variant)
{
    std::string computedHash = hash(input, variant);
    return (computedHash == hashVal);
}

bool Sha::matchHash(const std::string &input, const std::string &hashVal, Algorithm variant)
{
    std::string computedHash = hash(input, variant);
    return (computedHash.find(hashVal) != std::string::npos);
}

CELL_NAMESPACE_END
