/*!
 * @file        compressor.hpp
 * @brief       Compressor manager for the Cell Engine.
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

#ifndef CELL_COMPRESSOR_HPP
#define CELL_COMPRESSOR_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Globals)

/**
 * @brief Compression levels for the Compressor class.
 */
enum class CompressionLevel : Types::s8
{
    None = Z_NO_COMPRESSION,            //!< No compression.
    Fastest = Z_BEST_SPEED,             //!< Fastest compression.
    Default = Z_DEFAULT_COMPRESSION,    //!< Default compression.
    Best = Z_BEST_COMPRESSION           //!< Best compression.
};

/** Type definition for the progress callback function. */
using ProgressCallBack = std::function<void(float)>;

/**
 * @brief Constants related to the Compressor class.
 */
struct CompressorConstants final
{
    static constexpr std::string_view GZIP_SUFFIX { ".gz" };        //!< GZIP file suffix.
    static constexpr std::size_t GZIP_BUFFER_SIZE { 1024 * 64 };    //!< GZIP buffer size.
};

/**
 * @brief Compressor class for file and directory compression/decompression.
 */
class Compressor
{
public:
    /**
     * @brief Compresses a file.
     *
     * @param filePath The path of the file to compress.
     * @param removeOriginal Flag indicating whether to remove the original file after compression (default: false).
     * @param compressionLevel The compression level to use (default: CompressionLevel::Default).
     * @param progressCallback Callback function to track the progress of compression (default: nullptr).
     */
    void compressFile(const std::string& filePath, bool removeOriginal = false,
                      CompressionLevel compressionLevel = CompressionLevel::Default,
                      ProgressCallBack progressCallback = nullptr);

    /**
     * @brief Decompresses a file.
     *
     * @param filePath The path of the file to decompress.
     * @param removeOriginal Flag indicating whether to remove the original file after decompression (default: false).
     * @param progressCallback Callback function to track the progress of decompression (default: nullptr).
     */
    void decompressFile(const std::string& filePath, bool removeOriginal = false,
                        ProgressCallBack progressCallback = nullptr);

    /**
     * @brief Compresses a directory.
     *
     * @param directoryPath The path of the directory to compress.
     * @param recursive Flag indicating whether to compress files in subdirectories recursively (default: false).
     * @param removeOriginal Flag indicating whether to remove the original files after compression (default: false).
     * @param compressionLevel The compression level to use (default: CompressionLevel::Default).
     * @param progressCallback Callback function to track the progress of compression (default: nullptr).
     */
    void compressDirectory(const std::string& directoryPath, bool recursive = false,
                           bool removeOriginal = false,
                           CompressionLevel compressionLevel = CompressionLevel::Default,
                           ProgressCallBack progressCallback = nullptr);

    /**
     * @brief Decompresses a directory.
     *
     * @param directoryPath The path of the directory to decompress.
     * @param recursive Flag indicating whether to decompress files in subdirectories recursively (default: false).
     * @param removeOriginal Flag indicating whether to remove the original files after decompression (default: false).
     * @param progressCallback Callback function to track the progress of decompression (default: nullptr).
     */
    void decompressDirectory(const std::string& directoryPath, bool recursive = false,
                             bool removeOriginal = false,
                             ProgressCallBack progressCallback = nullptr);

private:
    /**
     * @brief Gets the path of the compressed file.
     *
     * @param filePath The path of the original file.
     * @return The path of the compressed file.
     */
    std::string getCompressedFilePath(const std::string& filePath);

    /**
     * @brief Gets the path of the decompressed file.
     *
     * @param filePath The path of the compressed file.
     * @return The path of the decompressed file.
     */
    std::string getDecompressedFilePath(const std::string& filePath);

    /**
     * @brief Removes a file.
     *
     * @param filePath The path of the file to remove.
     */
    void removeFile(const std::string& filePath);

    /**
     * @brief Checks if a path is a directory.
     *
     * @param path The path to check.
     * @return True if the path is a directory, false otherwise.
     */
    bool isDirectory(const std::string& path);

    /**
     * @brief Calculates the progress of a compression or decompression operation.
     *
     * @param current The current progress value.
     * @param total The total progress value.
     * @param progressCallback The callback function to update the progress.
     */
    void calculateProgress(std::streamoff current, std::streamoff total, ProgressCallBack progressCallback);
};


CELL_NAMESPACE_END

#endif  // CELL_COMPRESSOR_HPP

