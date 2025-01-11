#ifdef _WIN32
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
//!libs
#pragma comment(lib, "Ws2_32.lib")
#elif __APPLE__
#include <unistd.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <mach/mach.h>
#else
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/statfs.h>
#include <sys/utsname.h>
#endif

#if __has_include("storage.hpp")
#   include "storage.hpp"
#else
#   error "Cell's "storage.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

DiskStorage::DiskStorage() {}

DiskStorage::~DiskStorage() {}

DiskList DiskStorage::getDisks()
{
    std::vector<std::string> disks;
#ifdef PLATFORM_WINDOWS
    for (const auto& drive : fs::directory_iterator(kDiskMountPath)) {
        disks.push_back(drive.path().root_name());
    }
#elif PLATFORM_MACOS
    for (const auto& entry : fs::directory_iterator(kDiskMountPath)) {
        disks.push_back(entry.path().filename());
    }
#else
    for (const auto& entry : fs::directory_iterator(kDiskMountPath)) {
        if (fs::is_block_file(entry.status())) {
            disks.push_back(entry.path().filename());
        }
    }
#endif
    return disks;
}

std::optional<DiskStorage::Specification> DiskStorage::getDiskDetails(const std::string& diskName)
{
    try {
        fs::path diskPath = getDiskPath(diskName);
        fs::space_info spaceInfo = fs::space(diskPath);

        Specification spec;
        spec.name = diskName;
        spec.totalSpace = spaceInfo.capacity;
        spec.freeSpace = spaceInfo.free;
        spec.availableSpace = spaceInfo.available;

        // Determine disk format (File system type)
        spec.fileSystem = determineFileSystemType(diskPath);

        // Check if the disk is writable and readable
        {
            spec.isWritable = isFileWritable(diskPath);
            spec.isReadable = isFileReadable(diskPath);
        }
        return spec;
    } catch (const fs::filesystem_error& e) {
        handleDiskAccessError(e);
        return std::nullopt;
    }
}

bool DiskStorage::isFileWritable(const fs::path& filePath)
{
    return (fs::status(filePath).permissions() & fs::perms::owner_write) != fs::perms::none;
}

bool DiskStorage::isFileReadable(const fs::path& filePath)
{
    return (fs::status(filePath).permissions() & fs::perms::owner_read) != fs::perms::none;
}

Types::OptionalString DiskStorage::determineFileSystemType(const fs::path& diskPath)
{
    try {
#if defined(_WIN32)
        WCHAR volumeName[MAX_PATH + 1];
        if (GetVolumeInformationW(diskPath.root_path().c_str(), volumeName, MAX_PATH + 1, nullptr, nullptr, nullptr, nullptr, 0)) {
            return volumeName;
        }
#elif defined(__APPLE__)
        struct statfs fsInfo;
        if (statfs(diskPath.root_path().c_str(), &fsInfo) == 0) {
            return fsInfo.f_fstypename;
        }
        return std::nullopt;
#else
        struct statfs fsInfo;
        if (statfs(diskPath.root_path().c_str(), &fsInfo) == 0) {
            return fsInfo.f_fstypename;
        }
#endif
    } catch (const fs::filesystem_error& e) {
        handleDiskAccessError(e);
        return std::nullopt;
    }
    return std::nullopt;
}

DeviceList DiskStorage::getDiskDevices() const
{
    try {
        std::vector<std::string> disks;
        for (const auto& entry : fs::directory_iterator(kDiskMountPath)) {
            if (entry.is_directory()) {
                disks.push_back(entry.path().filename().string());
            }
        }
        return disks;
    } catch (const fs::filesystem_error& e) {
        handleDiskAccessError(e);
        return std::nullopt;
    }
}

void DiskStorage::printDetailedDiskInfo(const std::string& diskName)
{
    if (auto details = getDiskDetails(diskName))
    {
        std::cout << "Detailed Disk Information for drive " << diskName << ":" << std::endl;
        std::cout << "   Total space: " << details->totalSpace << " bytes" << std::endl;
        std::cout << "   Free space: " << details->freeSpace << " bytes" << std::endl;
        std::cout << "   Available space: " << details->availableSpace << " bytes" << std::endl;
    }
}

void DiskStorage::checkDiskHealth(const std::string& diskName)
{
  // Implement disk health check logic here.
}

void DiskStorage::cleanupDisk(const std::string& diskName)
{
  // Implement disk cleanup logic here.
}

fs::path DiskStorage::getDiskPath(const std::string& diskName) const
{
    std::string d = kDiskMountPath.data();
    return d.append("/") + diskName;
}

void DiskStorage::handleDiskAccessError(const fs::filesystem_error& e) const
{
    (DeveloperMode::IsEnable) ? Log("Error accessing disk: " + FROM_CELL_STRING(e.what()), LoggerType::Critical) : DO_NOTHING;
}


CELL_NAMESPACE_END
