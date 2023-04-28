/*!
 * @file        backup.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Backup manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_BACKUP_HPP
#define CELL_BACKUP_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Maintenance)

using StateFunction = std::function<void(int)>;
using FutureState   = std::future<bool>;

/**
 * @brief The BackupStruct class
 */
struct BackupStruct final
{
    Types::OptionalString fileName              {}; ///<! Filename
    std::function<void(int)> progressCallback   {}; ///<! Progress callback.
};

/**
 * @brief The FileBackup class
 */
class __cell_export FileBackup {
public:
    FileBackup(const std::string& fileName);
    ~FileBackup();

    void setProgressCallback(const StateFunction& callback);

    __cell_no_discard FutureState backupAsync() __cell_noexcept;

    __cell_no_discard bool backupSync() __cell_noexcept;

private:
    BackupStruct backupStruct {};
};


CELL_NAMESPACE_END


#endif // CELL_BACKUP_HPP
