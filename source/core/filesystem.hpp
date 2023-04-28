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

/**
 * @brief The FileState class
 */
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

static const std::map<std::string, std::string> fileTypes = {
    { ".txt", "Text File" },
    { ".doc", "Microsoft Word Document" },
    { ".docx", "Microsoft Word Document" },
    { ".xls", "Microsoft Excel Spreadsheet" },
    { ".xlsx", "Microsoft Excel Spreadsheet" },
    { ".ppt", "Microsoft PowerPoint Presentation" },
    { ".pptx", "Microsoft PowerPoint Presentation" },
    { ".pdf", "PDF Document" },
    { ".html", "HTML Document" },
    { ".htm", "HTML Document" },
    { ".xml", "XML Document" },
    { ".json", "JSON Document" },
    { ".cpp", "C++ Source Code" },
    { ".cuh", "C++ Cuda Header Code" },
    { ".c++", "C++ Source Code" },
    { ".cxx", "C++ Source Code" },
    { ".hpp", "C++ Modern Header Code" },
    { ".ixx", "C++ Module File" },
    { ".mxx", "C++ Module File" },
    { ".cppm", "C++ Module File" },
    { ".ccm", "C++ Module File" },
    { ".cxxm", "C++ Module File" },
    { ".c++m", "C++ Module File" },
    { ".h", "C Header Code" },
    { ".c", "C Source Code" },
    { ".java", "Java Source Code" },
    { ".py", "Python Source Code" },
    { ".rb", "Ruby Source Code" },
    { ".php", "PHP Source Code" },
    { ".rs", "Rust Source Code" },
    { ".js", "JavaScript Source Code" },
    { ".css", "Cascading Style Sheet" },
    { ".scss", "Sass CSS File" },
    { ".less", "Less CSS File" },
    { ".jsx", "React JSX File" },
    { ".tsx", "TypeScript JSX File" },
    { ".ts", "TypeScript Source Code" },
    { ".go", "Go Source Code" },
    { ".swift", "Swift Source Code" },
    { ".kt", "Kotlin Source Code" }
};

/**
 * @brief Structure for holding file information.
 * This structure holds file information that is retrieved from the operating system.
 */
struct InfoStruct final
{
    std::string filePath;   ///<! Path of file.
    std::string fileName;   ///<! Name of file.
    std::chrono::system_clock::time_point lastWriteTime;    ///<! Latest write time on the file.
    std::chrono::system_clock::time_point creationTime;     ///<! File creation time.
    Types::llong fileSize; ///<! Size of file.
};

/**
 * @brief A class for obtaining information about a file.
 * This class provides methods to obtain various information about a file,
 * including its name, last write time, creation time, and file size.
 */
class __cell_export FileInfo {
public:
    /**
     * @brief Construct a new FileInfo object for the specified file path.
     * @param filePath The path to the file for which information will be obtained.
     */
    FileInfo(const std::filesystem::path& filePath);

    /**
     * @brief Destroy the FileInfo object.
     */
    ~FileInfo();

    /**
     * @brief Get the name of the file.
     * @return The name of the file as a string.
     */
    std::string fileName() const;

    /**
     * @brief Get the last write time of the file.
     * @return The last write time of the file as a string.
     */
    std::string lastWriteTime() const;

    /**
     * @brief Get the creation time of the file.
     * @return The creation time of the file as a string.
     */
    std::string creationTime() const;

    /**
     * @brief Get the size of the file in bytes.
     * @return The size of the file in bytes.
     */
    Types::llong fileSize() const;

private:

    InfoStruct infoStruct {}; ///<! Structure for holding file information.
};

/**
 * @brief The FileTypeDetector class provides a static method to detect the type of a file based on its extension.
 */
class __cell_export FileTypeDetector {
public:
    FileTypeDetector();
    ~FileTypeDetector();

    /**
     * @brief Detects the type of a file based on its extension.
     * @param filePath The path to the file to detect the type of.
     * @return A string describing the file type.
     */
    static std::string detectFileType(const std::filesystem::path& filePath);
};

CELL_NAMESPACE_END


#endif // CELL_FILESYSTEM_HPP
