#if __has_include("compressor.hpp")
#   include "compressor.hpp"
#else
#   error "Cell's compressor was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core was not found!"
#endif

#if __has_include("core/filesystem.hpp")
#   include "core/filesystem.hpp"
#else
#   error "Cell's filesystem was not found!"
#endif


CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;

CELL_NAMESPACE_BEGIN(Cell::Globals)

void Compressor::compressFile(const std::string& filePath,
                              bool removeOriginal,
                              CompressionLevel compressionLevel,
                              ProgressCallBack progressCallback)
{

    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open the source file");
    }

    std::string compressedFilePath = getCompressedFilePath(filePath);
    gzFile outputFile = gzopen(compressedFilePath.c_str(), "wb");
    if (!outputFile) {
        inputFile.close();
        throw std::runtime_error("Failed to open the destination file");
    }

    int gzCompressionLevel = Z_DEFAULT_COMPRESSION;
    switch (compressionLevel) {
    case CompressionLevel::None:
        gzCompressionLevel = Z_NO_COMPRESSION;
        break;
    case CompressionLevel::Fastest:
        gzCompressionLevel = Z_BEST_SPEED;
        break;
    case CompressionLevel::Default:
        gzCompressionLevel = Z_DEFAULT_COMPRESSION;
        break;
    case CompressionLevel::Best:
        gzCompressionLevel = Z_BEST_COMPRESSION;
        break;
    }

    gzsetparams(outputFile, gzCompressionLevel, Z_DEFAULT_STRATEGY);

    const int bufferSize = CompressorConstants::GZIP_BUFFER_SIZE;
    char buffer[bufferSize];

    std::streamoff fileSize = std::filesystem::file_size(filePath);
    std::streamoff bytesReadTotal = 0;

    do {
        inputFile.read(buffer, bufferSize);
        std::streamsize bytesRead = inputFile.gcount();

        if (bytesRead > 0) {
            if (gzwrite(outputFile, buffer, bytesRead) <= 0) {
                inputFile.close();
                gzclose(outputFile);
                throw std::runtime_error("Failed to compress file data");
            }

            bytesReadTotal += bytesRead;
            calculateProgress(bytesReadTotal, fileSize, progressCallback);
        }
    } while (inputFile);

    inputFile.close();
    gzclose(outputFile);

    if (removeOriginal) {
        removeFile(filePath);
    }
}

void Compressor::decompressFile(const std::string& filePath,
                                bool removeOriginal,
                                ProgressCallBack progressCallback)
{
    gzFile inputFile = gzopen(filePath.c_str(), "rb");
    if (!inputFile) {
        throw std::runtime_error("Failed to open the source file");
    }

    std::string decompressedFilePath = getDecompressedFilePath(filePath);
    std::ofstream outputFile(decompressedFilePath, std::ios::binary);
    if (!outputFile) {
        gzclose(inputFile);
        throw std::runtime_error("Failed to open the destination file");
    }

    const int bufferSize = CompressorConstants::GZIP_BUFFER_SIZE;
    char buffer[bufferSize];
    int bytesRead = 0;

    std::streamoff fileSize = std::filesystem::file_size(filePath);
    std::streamoff bytesReadTotal = 0;

    while ((bytesRead = gzread(inputFile, buffer, bufferSize)) > 0) {
        outputFile.write(buffer, bytesRead);
        bytesReadTotal += bytesRead;
        calculateProgress(bytesReadTotal, fileSize, progressCallback);
    }

    gzclose(inputFile);
    outputFile.close();

    if (removeOriginal) {
        removeFile(filePath);
    }

    auto fileManager = FileSystem::FileManager();
    fileManager.changePermissions(decompressedFilePath, std::filesystem::perms::all);

}

void Compressor::compressDirectory(const std::string& directoryPath,
                                   bool recursive,
                                   bool removeOriginal,
                                   CompressionLevel compressionLevel,
                                   ProgressCallBack progressCallback)
{
    std::filesystem::directory_iterator endIterator;
    for (std::filesystem::directory_iterator it(directoryPath); it != endIterator; ++it)
    {
        if (std::filesystem::is_regular_file(it->path())) {
            compressFile(it->path().string(), removeOriginal, compressionLevel, progressCallback);
        } else if (recursive && std::filesystem::is_directory(it->path())) {
            compressDirectory(it->path().string(), recursive, removeOriginal, compressionLevel, progressCallback);
        }
    }
}

void Compressor::decompressDirectory(const std::string& directoryPath,
                                     bool recursive, bool removeOriginal,
                                     ProgressCallBack progressCallback)
{
    std::filesystem::directory_iterator endIterator;
    for (std::filesystem::directory_iterator it(directoryPath); it != endIterator; ++it)
    {
        if (std::filesystem::is_regular_file(it->path())) {
            decompressFile(it->path().string(), removeOriginal, progressCallback);
        } else if (recursive && std::filesystem::is_directory(it->path())) {
            decompressDirectory(it->path().string(), recursive, removeOriginal, progressCallback);
        }
    }
}

std::string Compressor::getCompressedFilePath(const std::string& filePath)
{
    std::filesystem::path path(filePath);
    return (path.parent_path() / (path.stem().string() + CompressorConstants::GZIP_SUFFIX.data())).string();
}

std::string Compressor::getDecompressedFilePath(const std::string& filePath)
{
    std::filesystem::path path(filePath);
    return (path.parent_path() / path.stem().string()).string();
}

void Compressor::removeFile(const std::string& filePath)
{
    if (std::filesystem::exists(filePath)) {
        std::filesystem::remove(filePath);
    }
}

bool Compressor::isDirectory(const std::string& path)
{
    std::error_code error;
    return std::filesystem::is_directory(path, error);
}

void Compressor::calculateProgress(std::streamoff current, std::streamoff total, ProgressCallBack progressCallback)
{
    if (progressCallback) {
        float progress = static_cast<float>(current) / total * 100.0f;
        progressCallback(progress);
    }
}

CELL_NAMESPACE_END
