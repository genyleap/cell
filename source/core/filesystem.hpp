/*!
 * @file        filesystem.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Filesystem manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_FILESYSTEM_HPP
#define CELL_FILESYSTEM_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::FileSystem)

namespace fs = std::filesystem;


struct FileState final
{
    bool open;
    bool close;
};

/**
 @brief A class for managing files and directories.
*/
class __cell_export FileManager {
public:

    FileManager();
    ~FileManager();

    /**
     * @brief Creates a new file at the specified path.
     * @param path The path to the file.
     * @return True if the file was created successfully, false otherwise.
     */
    __cell_no_discard bool createFile(const std::filesystem::path& path);

    /**
     * @brief Creates a new directory at the specified path.
     * @param path The path to the directory.
     * @return True if the directory was created successfully, false otherwise.
     */
    __cell_no_discard bool createDir(const std::filesystem::path& path);

    /**
     * @brief Deletes the file at the specified path.
     * @param path The path to the file.
     * @return True if the file was deleted successfully, false otherwise.
     */
    __cell_no_discard bool deleteFile(const std::filesystem::path& path);

    /**
     * @brief Deletes the directory at the specified path.
     * @param path The path to the directory.
     * @return True if the directory was deleted successfully, false otherwise.
     */
    __cell_no_discard bool deleteDir(const std::filesystem::path& path);

    /**
     * @brief Reads the contents of the file at the specified path.
     * @param filePath The path to the file.
     * @return The contents of the file as a string.
     */
    __cell_no_discard_message("This function has a return value as data string!")
        std::string read(const std::filesystem::path& filePath);

    /**
     * @brief Reads the raw binary data of the file at the specified path.
     * @param filePath The path to the file.
     * @return The raw binary data of the file as a string.
     */
    __cell_no_discard_message("This function has a return value as data raw string!")
    std::string readRawData(const std::filesystem::path& filePath);

    /**
     * @brief Reads the contents of the file at the specified path.
     * @return The contents of the file as a string.
     */
    __cell_no_discard_message("This function has a return value as data!")
    std::string readData() const;

    /**
     * @brief Writes the specified data to the file at the specified path.
     * @param filePath The path to the file.
     * @param data The data to write to the file.
     */
    void write(const std::filesystem::path& filePath, const std::string& data);

    /**
     * @brief Replaces all occurrences of oldStr with newStr in the file at the specified path.
     * @param filePath The path to the file.
     * @param oldStr The string to replace.
     * @param newStr The string to replace oldStr with.
     */
    void edit(const std::filesystem::path& filePath, const std::string& oldStr, const std::string& newStr);

    /**
     * @brief Changes the permissions of the file or directory at the specified path.
     * @param filePath The path to the file or directory.
     * @param permissions The new permissions to set.
     */
    void changePermissions(const std::filesystem::path& filePath, const std::filesystem::perms& permissions);

    /**
     * @brief Lists the files in the directory at the specified path.
     * @param path The path to the directory.
     * @return A vector of file names in the directory.
     */
    __cell_no_discard std::vector<std::string> listFilesOfDir(const std::filesystem::path& path);

    /**
     * @brief Lists the subdirectories in the directory at the specified path.
     * @param path The path to the directory.
     * @return A vector of subdirectory names in the directory.
     */
    __cell_no_discard std::vector<std::string> listDir(const std::filesystem::path& path);

    /**
     * @brief isOpen function will gets state of file.
     * @return true if file was opened!
     */
    __cell_no_discard  bool isOpen();

    /**
     * @brief isOpen function will gets state of file.
     * @return false if file was closed!
     */
    __cell_no_discard bool isClose();

protected:
    void setState(bool open, bool close);

private:
    FileState fileState;
    std::string m_data{};
};

class __cell_export FileInfo {
public:
    FileInfo(const std::filesystem::path& filePath);
    ~FileInfo();

    std::string fileName() const;
    long long fileSize() const;
    std::string lastWriteTime() const;
    std::string creationTime() const;

private:
    std::string m_filePath;
    std::string m_fileName;
    long long m_fileSize;
    std::chrono::system_clock::time_point m_lastWriteTime;
    std::chrono::system_clock::time_point m_creationTime;
};

class __cell_export FileTypeDetector {
public:
    FileTypeDetector();
    ~FileTypeDetector();
    static std::string detectFileType(const std::filesystem::path& filePath);
};

struct FileStruct final
{
    std::string filename {};    ///<! The name of the file.
    std::fstream content {};    ///<! The content of the file.
};

CELL_NAMESPACE_END


#endif // CELL_FILESYSTEM_HPP
