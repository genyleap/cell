#if __has_include("md5.hpp")
#   include "md5.hpp"
#else
#   error "Cell's md5 was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Cryptography)

std::string Md5::hash(const std::string& input)
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);

    char md5string[MD5_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&md5string[i * 2], "%02x", static_cast<unsigned int>(digest[i]));
    }

    return std::string(md5string);
}

bool Md5::validateHash(const std::string& hashval)
{
    std::regex pattern("^[a-fA-F0-9]{32}$");
    return std::regex_search(hashval, pattern);
}

bool Md5::matchHash(const std::string& input, const std::string& hashval)
{
    std::string computedHash = hash(input);
    return (computedHash == hashval);
}

CELL_NAMESPACE_END
