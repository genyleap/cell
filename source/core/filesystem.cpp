#if __has_include("filesystem.hpp")
#   include "filesystem.hpp"
#define header_is_avaialble
#else
#   error "Cell's filesystem.hpp was not found!"
#undef header_is_avaialble
#endif

#ifdef header_is_avaialble

#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's <core> was not found!"
#endif

#if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::FileSystem)

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
    setState(false, true);
}

std::string FileManager::read(const FilePath& filePath)
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        setState(false, true);
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for reading", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file for reading");
    }
    setState(true, false);
    std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();
    m_data = fileContents;
    return fileContents;
}

std::ifstream FileManager::readRawData(const FilePath& filePath)
{
    // Open the file and read its contents as raw binary data
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile.is_open()) {
        setState(false, true);
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for reading raw data", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file for reading raw data");
    }
    setState(true, false);
    inputFile.close();
    return inputFile;
}

std::string FileManager::readData() const
{
    return m_data;
}

void FileManager::write(const FilePath& filePath, const std::string& data)
{
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        setState(false, true);
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for writing", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file for writing");
    }
    setState(true, false);
    outputFile << data;
    m_data = data;
    outputFile.close();
}

std::ofstream FileManager::stream(const FilePath& filename)
{
    std::ofstream file(filename);
    if (!file) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for write!", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file");
    }
    return file;
}

std::ifstream FileManager::get(const FilePath& filename)
{
    std::ifstream file(filename);
    if (!file) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for read!", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file");
    }
    return file;
}

void FileManager::edit(const FilePath& filePath, const std::string& oldStr, const std::string& newStr)
{
    // Open the file and read its contents
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        setState(false, true);
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for editing", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file for editing");
    }
    std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    setState(true, false);
    inputFile.close();
    // Replace all occurrences of oldStr with newStr
    size_t pos = __cell_zero;
    while ((pos = fileContents.find(oldStr, pos)) != std::string::npos)
    {
        fileContents.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
    // Open the file for writing and write the modified contents
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file for writing", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to open file for writing");
        setState(false, true);
    }
    setState(true, false);
    outputFile << fileContents;
    m_data = fileContents;
    outputFile.close();
}

bool FileManager::createFile(const FilePath& path)
{
    std::ofstream file(path);
    if(file.is_open())
    {
        setState(true, false);
    } else {
        setState(false, true);
    }
    return file.good();
}

bool FileManager::createDir(const FilePath& path)
{
    return Fs::create_directory(path);
}

std::vector<std::string> FileManager::listDir(const FilePath& path)
{
    std::vector<std::string> result;
    for (const auto& entry : Fs::directory_iterator(path))
    {
        if (Fs::is_directory(entry) && !entry.path().has_extension())
        {
            result.push_back(entry.path().filename().string());
        }
    }
    return result;
}

std::vector<std::string> FileManager::listFilesOfDir(const FilePath& path)
{
    std::vector<std::string> result;
    for (const auto& entry : Fs::directory_iterator(path))
    {
        result.push_back(entry.path().filename().string());
    }
    return result;
}

bool FileManager::deleteFile(const FilePath& path)
{
    return Fs::remove(path);
}

bool FileManager::deleteFiles(const FilePath& path)
{
    std::string folderAndFile {};
    bool status {false};
    for (const auto& file : listFilesOfDir(path))
    {
        folderAndFile = path.string() + file;
        status = deleteFile(folderAndFile);
    }
    return status;
}

bool FileManager::deleteSelectedFiles(ListOfFiles& files)
{
    if (files.empty())
    {
        if(DeveloperMode::IsEnable)
        {
            Log("Error: no files provided for deletion.", LoggerType::Critical);
        }
        return false;
    }
    bool allFilesDeleted = true;
    std::string folderAndFile {};
    for (const auto& [key, value] : files)
    {
        folderAndFile = key + value;
        // Check if the file exists before attempting to delete it.
        if (!Types::Fs::exists(folderAndFile)) {
            if(DeveloperMode::IsEnable)
            {
                Log("Warning: file " + folderAndFile + " does not exist.", LoggerType::Warning);
            }
            allFilesDeleted = false;
            continue;
        }

        // Attempt to delete the file.
        bool status = deleteFile(folderAndFile);

        // Log or handle any errors that occur during deletion.
        if (!status) {
            if(DeveloperMode::IsEnable)
            {
                Log("Error: could not delete file " + folderAndFile, LoggerType::Critical);
            }
            allFilesDeleted = false;
        }
    }
    return allFilesDeleted;
}

bool FileManager::deleteDir(const FilePath& path)
{
    return Types::Fs::remove_all(path);
}

void FileManager::changePermissions(const FilePath& filePath, const std::filesystem::perms& permissions)
{
    try {
        std::filesystem::permissions(filePath, permissions);
        if(DeveloperMode::IsEnable)
        {
            Log("File permissions changed successfully.", LoggerType::Success);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to change file permissions.", LoggerType::Critical);
        }
        throw std::runtime_error("Failed to change file permissions: " + std::string(e.what()));
    }
}

bool FileManager::isOpen()
{
    return fileState.open;
}

bool FileManager::isClose()
{
    return fileState.close;
}

void FileManager::setState(bool open, bool close)
{
    fileState.close = close;
    fileState.open = open;
}

std::string FileManager::getExecutablePath() {
    std::string expath{};
#if defined(CELL_PLATFORM_MOBILE) && defined(PLATFORM_ANDROID)
    expath = "assets:/";
#elif defined(CELL_PLATFORM_MOBILE) && defined(PLATFORM_IOS)
    std::string res = {"/"};
#elif defined(CELL_PLATFORM_MAC)
    expath = "/";
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::string v = path;
        expath = v.substr(0, v.find_last_of("\\/")) + "/";
    }
#elif defined(CELL_PLATFORM_LINUX)
    char buff[PATH_MAX];
    ssize_t len = ::readlink(expath.c_str(), buff, sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';
        return std::string(buff);
    }
#elif defined(CELL_PLATFORM_WINDOWS)
    expath = "/";
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    expath = std::string(buffer).substr(0, pos);
#elif defined(CELL_PLATFORM_FREEBSD)
    expath = "/";
    res = "FreeBSD does not support yet!"
#elif defined(CELL_PLATFORM_SOLARIS)
    expath = "/";
    res = "Solaris does not support yet!"
#endif
    return expath;
}


FileInfo::FileInfo(const FilePath& filePath)
{
    std::error_code ec;

    infoStruct.filePath = filePath;

    infoStruct.fileName = filePath.filename().string();

    infoStruct.fileSize = std::filesystem::file_size(filePath, ec);

    if (ec) { infoStruct.fileSize = -1; }

    auto writeTime = std::filesystem::last_write_time(filePath, ec);
    if (ec) {
        writeTime = decltype(writeTime)::clock::time_point::min();
    }
    infoStruct.lastWriteTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(writeTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());

    std::filesystem::file_time_type createTime = std::filesystem::last_write_time(filePath, ec);
    if (ec) {
        createTime = decltype(createTime)::clock::time_point::min();
    }
    infoStruct.creationTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(createTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
}

FileInfo::~FileInfo()
{
}

std::string FileInfo::fileName() const
{
    return infoStruct.fileName;
}

long long FileInfo::fileSize() const
{
    return infoStruct.fileSize;
}

std::string FileInfo::lastWriteTime() const
{
    std::filesystem::file_time_type lastModifiedTime = std::filesystem::last_write_time(infoStruct.filePath);
    // Convert the file time type to a time point
    auto lastModifiedTimePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastModifiedTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    // Convert the time point to a time string
    std::time_t lastModifiedTimeT = std::chrono::system_clock::to_time_t(lastModifiedTimePoint);
    std::string lastModifiedTimeString = std::ctime(&lastModifiedTimeT);
    return lastModifiedTimeString;
}

std::string FileInfo::creationTime() const
{
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(infoStruct.creationTime));
    return std::asctime(std::localtime(&time));
}

FileTypeDetector::FileTypeDetector()
{
}

FileTypeDetector::~FileTypeDetector()
{
}

std::string FileTypeDetector::detectFileType(const FilePath& filePath)
{
    std::string extension = filePath.extension().string();
    //! fileTypes
    //! fileTypes can extend from external data!?
    //!
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });
    auto iter = fileTypes.find(extension);
    if (iter != fileTypes.end()) {
        return iter->second;
    } else {
        if(DeveloperMode::IsEnable)
        {
            Log("Unknown File Type", LoggerType::Critical);
        }
        return "Unknown File Type";
    }
}

CELL_NAMESPACE_END

#endif
