/*!
 * @file        storage.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System processor information.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_DISKSTORAGE_HPP
#define CELL_DISKSTORAGE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE fs = std::filesystem;

CELL_USING DiskList = std::vector<std::string>;

CELL_USING DeviceList = std::optional<std::vector<std::string>>;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

#ifdef PLATFORM_MACOS
constexpr std::string_view kDiskMountPath = "/Volumes";
#elif defined(PLATFORM_LINUX)
constexpr std::string_view kDiskMountPath = "/proc/mounts";
#elif defined(PLATFORM_WINDOWS)
constexpr std::string_view kDiskMountPath = "";
#else
#error "Unsupported platform"
#endif

/**
 * @brief The DiskStorage struct contains information about the storage devices.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export DiskStorage {
public:
    DiskStorage();
    ~DiskStorage();

    /**
     * @brief The Specification struct contains detailed DiskStorage.
     */
    struct Specification final
    {
        Types::OptionalString name          {};  //!< Name of the disk.
        Types::OptionalString fileSystem    {};  //!< Disk format (e.g., NTFS, ext4, apfs).
        Types::u64 totalSpace               {};  //!< Total space in bytes.
        Types::u64 freeSpace                {};  //!< Free space in bytes.
        Types::u64 availableSpace           {};  //!< Available space in bytes.

        bool isWritable                     {};  //!< Indicates if the disk is writable.
        bool isReadable                     {};  //!< Indicates if the disk is readable.
    };

    /**
     * @brief Retrieve a list of available disk devices.
     * @return A vector of strings containing disk device names.
     */
    __cell_no_discard DiskList getDisks();

    /**
     * @brief Retrieve detailed information about a specific disk.
     * @param diskName The name of the disk.
     * @return An optional Specification struct with detailed disk information.
     */
    __cell_no_discard std::optional<Specification> getDiskDetails(const std::string& diskName);

    /**
     * @brief Determines the file system type of a disk path.
     *      * This function attempts to determine the file system type of the specified disk path.
     * @param diskPath The path to the disk.
     * @return An optional string representing the file system type if successful, std::nullopt otherwise.
     */
    __cell_no_discard Types::OptionalString determineFileSystemType(const fs::path& diskPath);

    /**
     * @brief Checks if a file is writable.
     *      * This function checks whether the specified file is writable.
     *      * @param filePath The path to the file.
     * @return true if the file is writable, false otherwise.
     */
    __cell_no_discard bool isFileWritable(const std::filesystem::path& filePath);

    /**
     * @brief Checks if a file is readable.
     *      * This function checks whether the specified file is readable.
     * @param filePath The path to the file.
     * @return true if the file is readable, false otherwise.
     */
    __cell_no_discard bool isFileReadable(const std::filesystem::path& filePath);

    /**
     * @brief Get the list of disk devices.
     * @return An optional vector of strings containing disk device names.
     */
    __cell_no_discard DeviceList getDiskDevices() const;

    /**
     * @brief Print detailed information about a specific disk.
     * @param diskName The name of the disk.
     */
    void printDetailedDiskInfo(const std::string& diskName);

    /**
     * @brief Check the health status of a specific disk.
     * @param diskName The name of the disk.
     */
    void checkDiskHealth(const std::string& diskName);

    /**
     * @brief Clean up unnecessary files on a specific disk.
     * @param diskName The name of the disk.
     */
    void cleanupDisk(const std::string& diskName);

private:
    /**
     * @brief Get the path to the disk.
     * @param diskName The name of the disk.
     * @return The path to the disk.
     */
    fs::path getDiskPath(const std::string& diskName) const;

    /**
     * @brief Handle disk access errors.
     * @param e The filesystem error.
     */
    void handleDiskAccessError(const fs::filesystem_error& e) const;

};

CELL_NAMESPACE_END

#endif // CELL_DISKSTORAGE_HPP
