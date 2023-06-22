#if __has_include("rsa.hpp")
#   include "rsa.hpp"
#else
#   error "Cell's rsa was not found!"
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

RSA* Rsa::generateKeyPair(int keySize)
{
    RSA* rsaKeyPair = RSA_new();
    BIGNUM* bn = BN_new();
    if (BN_set_word(bn, RSA_F4) != 1) {
        throw std::runtime_error("Failed to set RSA exponent");
    }

    if (RSA_generate_key_ex(rsaKeyPair, keySize, bn, nullptr) != 1) {
        throw std::runtime_error("Failed to generate RSA key pair");
    }

    BN_free(bn);
    return rsaKeyPair;
}

std::string Rsa::encrypt(const std::string& plaintext, RSA* publicKey)
{
    std::vector<uchar> ciphertext(RSA_size(publicKey));

    int encryptLen = RSA_public_encrypt(plaintext.size(), reinterpret_cast<const uchar*>(plaintext.c_str()),
                                        ciphertext.data(), publicKey, RSA_PKCS1_PADDING);
    if (encryptLen == -1) {
        throw std::runtime_error("Failed to encrypt using RSA");
    }

    return std::string(reinterpret_cast<char*>(ciphertext.data()), encryptLen);
}

std::string Rsa::decrypt(const std::string& ciphertext, RSA* privateKey)
{
    std::vector<uchar> decryptedText(RSA_size(privateKey));

    int decryptLen = RSA_private_decrypt(ciphertext.size(), reinterpret_cast<const uchar*>(ciphertext.c_str()),
                                         decryptedText.data(), privateKey, RSA_PKCS1_PADDING);
    if (decryptLen == -1) {
        throw std::runtime_error("Failed to decrypt using RSA");
    }

    return std::string(reinterpret_cast<char*>(decryptedText.data()), decryptLen);
}

std::string Rsa::sign(const std::string& message, RSA* privateKey)
{
    unsigned int signatureLen;
    std::vector<uchar> signature(RSA_size(privateKey));

    if (RSA_sign(NID_sha256, reinterpret_cast<const uchar*>(message.c_str()), message.size(),
                 signature.data(), &signatureLen, privateKey) != 1) {
        throw std::runtime_error("Failed to sign message using RSA");
    }

    return std::string(reinterpret_cast<char*>(signature.data()), signatureLen);
}

bool Rsa::verify(const std::string& message, const std::string& signature, RSA* publicKey)
{
    return RSA_verify(NID_sha256, reinterpret_cast<const uchar*>(message.c_str()), message.size(),
                      reinterpret_cast<const uchar*>(signature.c_str()), signature.size(), publicKey) == 1;
}

RsaKeyGenerator::RsaKeyGenerator(KeySize keySize)
    : m_rsaKeyPair(nullptr), m_keySize(keySize) {}

RsaKeyGenerator::~RsaKeyGenerator() {
    if (m_rsaKeyPair != nullptr)
        RSA_free(m_rsaKeyPair);
}

bool RsaKeyGenerator::generateKeys(const std::string& privateKeyFile, const std::string& publicKeyFile)
{
    m_rsaKeyPair = RSA_new();
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return false;
    }

    BIGNUM* bne = BN_new();
    if (bne == nullptr) {
        RSA_free(m_rsaKeyPair);
        // Error handling
        return false;
    }

    if (BN_set_word(bne, RSA_F4) != 1) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        // Error handling
        return false;
    }

    if (RSA_generate_key_ex(m_rsaKeyPair, m_keySize, bne, nullptr) != 1) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        // Error handling
        return false;
    }

    FILE* privateKeyFilePtr = fopen(privateKeyFile.c_str(), "w");
    if (privateKeyFilePtr == nullptr) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        // Error handling
        return false;
    }

    if (PEM_write_RSAPrivateKey(privateKeyFilePtr, m_rsaKeyPair, nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        fclose(privateKeyFilePtr);
        // Error handling
        return false;
    }

    fclose(privateKeyFilePtr);

    FILE* publicKeyFilePtr = fopen(publicKeyFile.c_str(), "w");
    if (publicKeyFilePtr == nullptr) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        // Error handling
        return false;
    }

    if (PEM_write_RSAPublicKey(publicKeyFilePtr, m_rsaKeyPair) != 1) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        fclose(publicKeyFilePtr);
        // Error handling
        return false;
    }

    fclose(publicKeyFilePtr);
    BN_free(bne);

    return true;
}

RSA* RsaKeyGenerator::generateKeyPair() {
    m_rsaKeyPair = RSA_new();
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return nullptr;
    }

    BIGNUM* bne = BN_new();
    if (bne == nullptr) {
        RSA_free(m_rsaKeyPair);
        // Error handling
        return nullptr;
    }

    if (BN_set_word(bne, RSA_F4) != 1) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        // Error handling
        return nullptr;
    }

    if (RSA_generate_key_ex(m_rsaKeyPair, m_keySize, bne, nullptr) != 1) {
        RSA_free(m_rsaKeyPair);
        BN_free(bne);
        // Error handling
        return nullptr;
    }

    BN_free(bne);
    return m_rsaKeyPair;
}

void RsaKeyGenerator::setKeySize(KeySize keySize)
{
    m_keySize = keySize;
}

bool RsaKeyGenerator::exportKeysToMemory(std::string& privateKey, std::string& publicKey)
{
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return false;
    }

    BIO* privateKeyBio = BIO_new(BIO_s_mem());
    if (privateKeyBio == nullptr) {
        // Error handling
        return false;
    }

    if (PEM_write_bio_RSAPrivateKey(privateKeyBio, m_rsaKeyPair, nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        BIO_free(privateKeyBio);
        // Error handling
        return false;
    }

    char* privateKeyBuffer = nullptr;
    long privateKeyLength = BIO_get_mem_data(privateKeyBio, &privateKeyBuffer);
    if (privateKeyLength <= 0) {
        BIO_free(privateKeyBio);
        // Error handling
        return false;
    }

    privateKey.assign(privateKeyBuffer, privateKeyLength);

    BIO_free(privateKeyBio);

    BIO* publicKeyBio = BIO_new(BIO_s_mem());
    if (publicKeyBio == nullptr) {
        // Error handling
        return false;
    }

    if (PEM_write_bio_RSAPublicKey(publicKeyBio, m_rsaKeyPair) != 1) {
        BIO_free(publicKeyBio);
        // Error handling
        return false;
    }

    char* publicKeyBuffer = nullptr;
    long publicKeyLength = BIO_get_mem_data(publicKeyBio, &publicKeyBuffer);
    if (publicKeyLength <= 0) {
        BIO_free(publicKeyBio);
        // Error handling
        return false;
    }

    publicKey.assign(publicKeyBuffer, publicKeyLength);

    BIO_free(publicKeyBio);

    return true;
}

RSA* RsaKeyGenerator::getPublicKey()
{
    return m_rsaKeyPair;
}

RSA* RsaKeyGenerator::getPrivateKey()
{
    return m_rsaKeyPair;
}

std::string RsaKeyGenerator::encrypt(const std::string& plaintext)
{
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return "";
    }

    std::string ciphertext;
    int ciphertextLength = RSA_size(m_rsaKeyPair);
    uchar* ciphertextBuffer = new uchar[ciphertextLength];

    int encryptedLength = RSA_public_encrypt(plaintext.length(), reinterpret_cast<const uchar*>(plaintext.c_str()), ciphertextBuffer, m_rsaKeyPair, RSA_PKCS1_PADDING);
    if (encryptedLength == -1) {
        // Error handling
        delete[] ciphertextBuffer;
        return "";
    }

    ciphertext.assign(reinterpret_cast<const char*>(ciphertextBuffer), encryptedLength);
    delete[] ciphertextBuffer;

    return ciphertext;
}

std::string RsaKeyGenerator::decrypt(const std::string& ciphertext)
{
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return "";
    }

    std::string plaintext;
    int plaintextLength = RSA_size(m_rsaKeyPair);
    uchar* plaintextBuffer = new uchar[plaintextLength];

    int decryptedLength = RSA_private_decrypt(ciphertext.length(), reinterpret_cast<const uchar*>(ciphertext.c_str()), plaintextBuffer, m_rsaKeyPair, RSA_PKCS1_PADDING);
    if (decryptedLength == -1) {
        // Error handling
        delete[] plaintextBuffer;
        return "";
    }

    plaintext.assign(reinterpret_cast<const char*>(plaintextBuffer), decryptedLength);
    delete[] plaintextBuffer;

    return plaintext;
}

bool RsaKeyGenerator::exportPublicKey(const std::string& publicKeyFile) {
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return false;
    }

    FILE* publicKeyFilePtr = fopen(publicKeyFile.c_str(), "w");
    if (publicKeyFilePtr == nullptr) {
        // Error handling
        return false;
    }

    if (PEM_write_RSAPublicKey(publicKeyFilePtr, m_rsaKeyPair) != 1) {
        fclose(publicKeyFilePtr);
        // Error handling
        return false;
    }

    fclose(publicKeyFilePtr);
    return true;
}

bool RsaKeyGenerator::exportPrivateKey(const std::string& privateKeyFile)
{
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return false;
    }

    FILE* privateKeyFilePtr = fopen(privateKeyFile.c_str(), "w");
    if (privateKeyFilePtr == nullptr) {
        // Error handling
        return false;
    }

    if (PEM_write_RSAPrivateKey(privateKeyFilePtr, m_rsaKeyPair, nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        fclose(privateKeyFilePtr);
        // Error handling
        return false;
    }

    fclose(privateKeyFilePtr);
    return true;
}

bool RsaKeyGenerator::validateKeys() {
    if (m_rsaKeyPair == nullptr) {
        // Error handling
        return false;
    }

    return RSA_check_key(m_rsaKeyPair) == 1;
}

CSRGenerator::CSRGenerator() : m_privateKey(nullptr)
{
}

CSRGenerator::~CSRGenerator()
{
    if (m_privateKey)
        EVP_PKEY_free(m_privateKey);
}

bool CSRGenerator::loadPrivateKey(const std::string& privateKeyPath)
{
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "r");
    if (!privateKeyFile) {
        perror("Error opening private key file");
        return false;
    }
    m_privateKey = PEM_read_PrivateKey(privateKeyFile, nullptr, nullptr, nullptr);
    fclose(privateKeyFile);
    if (!m_privateKey) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    return true;
}

bool CSRGenerator::generateCSR(const std::string& csrPath, const std::string& commonName,
                               const std::string& organization, const std::string& organizationalUnit,
                               const std::string& locality, const std::string& state,
                               const std::string& country, const std::string& emailAddress)
{
    if (!m_privateKey) {
        std::cerr << "No private key loaded" << std::endl;
        return false;
    }

    X509_REQ* req = X509_REQ_new();
    if (!req) {
        std::cerr << "Error creating X509 request" << std::endl;
        return false;
    }

    X509_REQ_set_version(req, 0L);

    X509_NAME* name = X509_REQ_get_subject_name(req);

    auto addEntry = [name](const std::string& fieldName, const std::string& fieldValue)
    {
        X509_NAME_add_entry_by_txt(name, fieldName.c_str(), MBSTRING_ASC,
                                   reinterpret_cast<const unsigned char*>(fieldValue.c_str()),
                                   -1, -1, 0);
    };

    addEntry("CN"   , commonName);
    addEntry("O"    , organization);
    addEntry("OU"   , organizationalUnit);
    addEntry("L"    , locality);
    addEntry("ST"   , state);
    addEntry("C"    , country);
    addEntry("emailAddress", emailAddress);

    X509_REQ_set_pubkey(req, m_privateKey);

    if (!X509_REQ_sign(req, m_privateKey, EVP_sha256())) {
        std::cerr << "Error signing X509 request" << std::endl;
        X509_REQ_free(req);
        return false;
    }

    FILE* csrFile = fopen(csrPath.c_str(), "wb");
    if (!csrFile) {
        std::cerr << "Error opening CSR file" << std::endl;
        X509_REQ_free(req);
        return false;
    }
    PEM_write_X509_REQ(csrFile, req);
    fclose(csrFile);

    X509_REQ_free(req);

    return true;
}

bool CSRGenerator::decodeCSR(const std::string& csrPath, CsrData& csrData)
{
    FILE* csrFile = fopen(csrPath.c_str(), "r");
    if (!csrFile) {
        perror("Error opening CSR file");
        return false;
    }

    X509_REQ* req = PEM_read_X509_REQ(csrFile, nullptr, nullptr, nullptr);
    fclose(csrFile);
    if (!req) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    X509_NAME* subject = X509_REQ_get_subject_name(req);
    if (!subject) {
        fprintf(stderr, "Error getting subject from CSR\n");
        X509_REQ_free(req);
        return false;
    }

    char value[256];

    // Extract common name (CN)
    int cnLength = X509_NAME_get_text_by_NID(subject, NID_commonName, value, sizeof(value));
    if (cnLength < 0) {
        fprintf(stderr, "Error extracting common name from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[cnLength] = __cell_null_character;
    csrData.commonName = value;

    // Extract organization (O)
    int orgLength = X509_NAME_get_text_by_NID(subject, NID_organizationName, value, sizeof(value));
    if (orgLength < 0) {
        fprintf(stderr, "Error extracting organization from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[orgLength] = __cell_null_character;
    csrData.organization = value;

    // Extract organizational unit (OU)
    int ouLength = X509_NAME_get_text_by_NID(subject, NID_organizationalUnitName, value, sizeof(value));
    if (ouLength < 0) {
        fprintf(stderr, "Error extracting organizational unit from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[ouLength] = __cell_null_character;
    csrData.organizationalUnit = value;

    // Extract locality (L)
    int localityLength = X509_NAME_get_text_by_NID(subject, NID_localityName, value, sizeof(value));
    if (localityLength < 0) {
        fprintf(stderr, "Error extracting locality from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[localityLength] = __cell_null_character;
    csrData.locality = value;

    // Extract state (ST)
    int stateLength = X509_NAME_get_text_by_NID(subject, NID_stateOrProvinceName, value, sizeof(value));
    if (stateLength < 0) {
        fprintf(stderr, "Error extracting state from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[stateLength] = __cell_null_character;
    csrData.state = value;

    // Extract country (C)
    int countryLength = X509_NAME_get_text_by_NID(subject, NID_countryName, value, sizeof(value));
    if (countryLength < 0) {
        fprintf(stderr, "Error extracting country from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[countryLength] = __cell_null_character;
    csrData.country = value;

    // Extract email address
    int emailLength = X509_NAME_get_text_by_NID(subject, NID_pkcs9_emailAddress, value, sizeof(value));
    if (emailLength < 0) {
        fprintf(stderr, "Error extracting email address from CSR\n");
        X509_REQ_free(req);
        return false;
    }
    value[emailLength] = __cell_null_character;
    csrData.emailAddress = value;

    X509_REQ_free(req);

    return true;
}

CELL_NAMESPACE_END
