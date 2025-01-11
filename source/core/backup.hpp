/*!
 * @file        backup.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Backup manager.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_BACKUP_HPP
#define CELL_BACKUP_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Maintenance)

using StateFunction = std::function<void(int)>;
using FutureState   = std::future<bool>;

/**
 * @brief A class for performing file backup operations.
 */
struct BackupStruct final
{
    Types::OptionalString fileName              {}; //!< Filename
    std::function<void(int)> progressCallback   {}; //!< Progress callback.
};

/**
 * @brief The FileBackup class
 */
class __cell_export FileBackup {
public:
    /**
     * @brief Constructs a FileBackup object with the specified file name.
     * @param fileName The name of the file to be backed up.
     */
    FileBackup(const std::string& fileName);

    /**
     * @brief Destructor for the FileBackup class.
     */
    ~FileBackup();

    /**
     * @brief Sets a progress callback function to be called during backup operations.
     * @param callback The function to be called.
     */
    void setProgressCallback(const StateFunction& callback);

    /**
     * @brief Asynchronously performs the file backup operation.
     * @param A FutureState object representing the result of the backup operation.
     */
    __cell_no_discard FutureState backupAsync() __cell_noexcept;

    /**
     * @brief Synchronously performs the file backup operation.
     * @return True if the backup operation was successful, false otherwise.
     */
    __cell_no_discard bool backupSync() __cell_noexcept;

private:
    BackupStruct backupStruct {}; //!< An internal struct used for backup operations.
};

/**
 * @brief A class for performing file restore operations.
 */
struct RestoreStruct final
{
    Types::OptionalString backupFileName        {}; //!< Backup Filename
    Types::OptionalString restoreFileName       {}; //!< Restore Filename
    std::function<void(int)> progressCallback   {}; //!< Progress callback.
};

/**
 * @brief The FileRestore class
 */
class __cell_export DataRestore {
public:
    /**
     * @brief Constructs a DataRestore object with the specified file name.
     * @param fileName The name of the backup file.
     * @param restorefileName The name of the file to be restore.
     */
    DataRestore(const std::string& fileName, const std::string& restorefileName);

    /**
     * @brief Destructor for the FileBackup class.
     */
    ~DataRestore();

    /**
     * @brief Sets a progress callback function to be called during restore operations.
     * @param callback The function to be called.
     */
    void setProgressCallback(const StateFunction& callback);

    /**
     * @brief Asynchronously performs the file restore operation.
     * @param A FutureState object representing the result of the restore operation.
     */
    __cell_no_discard FutureState restoreAsync() __cell_noexcept;

    /**
     * @brief Synchronously performs the file restore operation.
     * @return True if the restore operation was successful, false otherwise.
     */
    __cell_no_discard bool restoreSync() __cell_noexcept;

private:
    RestoreStruct restoreStruct {}; //!< An internal struct used for restore operations.
};

CELL_NAMESPACE_END


#endif // CELL_BACKUP_HPP
