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

struct FileStruct final
{
    std::string filename {};    ///<! The name of the file.
    std::fstream content {};    ///<! The content of the file.
};

class __cell_export FileIO {
public:
    FileIO();
    ~FileIO();

    /**
     * @brief Opens a file.
     * @param fileName The file name.
     * @return bool Returns true if the file was opened successfully, false otherwise.
     */
    __cell_no_discard bool open(const std::string& fileName);

    /**
     * @brief Checks if the file is currently open.
     * @return bool Returns true if the file is open, false otherwise.
     */
    __cell_no_discard bool close();

    /**
     * @brief Checks if the file is currently open.
     * @return bool Returns true if the file is open, false otherwise.
     */
    __cell_no_discard bool isOpen() const;

    /**
     * @brief Writes data to the file.
     * @param data The data to write to the file.
     * @return bool Returns true if the write operation was successful, false otherwise.
     */
    __cell_no_discard bool write(const std::string& data);

    /**
     * @brief Reads all contents of the file as raw (ifstream).
     * @return std::ifstream Returns the contents of the file as a ifstream.
     */
    __cell_no_discard std::ifstream readRawAll() const;

    /**
     * @brief Reads all contents of the file.
     * @return std::string Returns the contents of the file as a string.
     */
    __cell_no_discard std::string readAll() const;


private:
    FileStruct fileStruct;
};

CELL_NAMESPACE_END

#endif // CELL_FILESYSTEM_HPP
