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

using ListOfFiles = std::unordered_multimap<std::string, std::string>; ///<! Key [path], Value[name]
using FilePath = std::filesystem::path;

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
    __cell_no_discard bool createFile(const FilePath& path);

    /**
     * @brief Creates a new directory at the specified path.
     * @param path The path to the directory.
     * @return True if the directory was created successfully, false otherwise.
     */
    __cell_no_discard bool createDir(const FilePath& path);

    /**
     * @brief Deletes the file at the specified path.
     * @param path The path to the file.
     * @return True if the file was deleted successfully, false otherwise.
     */
    __cell_no_discard bool deleteFile(const FilePath& path);

    /**
     * @brief Deletes all file at the specified path.
     * @param path The path to the files.
     * @return True if the data was deleted successfully, false otherwise.
     */
    __cell_no_discard bool deleteFiles(const FilePath& path);

    /**
     * @brief Deletes all selected files at the specified path.
     * @param files is the list of file based on key[path] and value[name];
     * @return True if the data was deleted successfully, false otherwise.
     */
    __cell_no_discard bool deleteSelectedFiles(ListOfFiles& files);

    /**
     * @brief Deletes the directory at the specified path.
     * @param path The path to the directory.
     * @return True if the directory was deleted successfully, false otherwise.
     */
    __cell_no_discard bool deleteDir(const FilePath& path);

    /**
     * @brief Reads the contents of the file at the specified path.
     * @param filePath The path to the file.
     * @return The contents of the file as a string.
     */
    __cell_no_discard_message("This function has a return value as data string!")
        std::string read(const FilePath& filePath);

    /**
     * @brief Reads the raw binary data of the file at the specified path.
     * @param filePath The path to the file.
     * @return The raw binary data of the file as a string.
     */
    __cell_no_discard_message("This function has a return value as data raw string!")
        std::ifstream readRawData(const FilePath& filePath);

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
    void write(const FilePath& filePath, const std::string& data);

    /**
     * @brief Streams the specified data to the file at the specified path.
     * @param filePath The path to the file.
     */
    std::ofstream stream(const FilePath& filename);

    std::ifstream get(const FilePath& filename);

    /**
     * @brief Replaces all occurrences of oldStr with newStr in the file at the specified path.
     * @param filePath The path to the file.
     * @param oldStr The string to replace.
     * @param newStr The string to replace oldStr with.
     */
    void edit(const FilePath& filePath, const std::string& oldStr, const std::string& newStr);

    /**
     * @brief Changes the permissions of the file or directory at the specified path.
     * @param filePath The path to the file or directory.
     * @param permissions The new permissions to set.
     */
    void changePermissions(const FilePath& filePath, const std::filesystem::perms& permissions);

    /**
     * @brief Lists the files in the directory at the specified path.
     * @param path The path to the directory.
     * @return A vector of file names in the directory.
     */
    __cell_no_discard std::vector<std::string> listFilesOfDir(const FilePath& path);

    /**
     * @brief Lists the subdirectories in the directory at the specified path.
     * @param path The path to the directory.
     * @return A vector of subdirectory names in the directory.
     */
    __cell_no_discard std::vector<std::string> listDir(const FilePath& path);

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
    FileInfo(const FilePath& filePath);

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
    static std::string detectFileType(const FilePath& filePath);
};

CELL_NAMESPACE_END


#endif // CELL_FILESYSTEM_HPP
