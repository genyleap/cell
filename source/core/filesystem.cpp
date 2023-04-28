#ifdef __has_include
# if __has_include("filesystem.hpp")
#   include "filesystem.hpp"
#define header_is_avaialble
#else
#   error "Cell's filesystem.hpp was not found!"
#undef header_is_avaialble
# endif
#endif

#ifdef header_is_avaialble

#ifdef __has_include
# if __has_include(<core>)
#   include <core>
#else
#   error "Cell's <core> was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::FileSystem)

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
    setState(false, true);
    m_data.clear();
}

std::string FileManager::read(const std::filesystem::path& filePath)
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        setState(false, true);
        throw std::runtime_error("Failed to open file for reading");
    }
    setState(true, false);
    std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();
    m_data = fileContents;
    return fileContents;
}

std::string FileManager::readRawData(const std::filesystem::path& filePath)
{
    // Open the file and read its contents as raw binary data
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile.is_open()) {
        setState(false, true);
        throw std::runtime_error("Failed to open file for reading raw data");
    }
    std::string rawData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    setState(true, false);
    inputFile.close();
    m_data = rawData;
    return rawData;
}

std::string FileManager::readData() const
{
    return m_data;
}

void FileManager::write(const std::filesystem::path& filePath, const std::string& data)
{
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        setState(false, true);
        throw std::runtime_error("Failed to open file for writing");
    }
    setState(true, false);
    outputFile << data;
    m_data = data;
    outputFile.close();
}

void FileManager::edit(const std::filesystem::path& filePath, const std::string& oldStr, const std::string& newStr)
{
    // Open the file and read its contents
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        setState(false, true);
        throw std::runtime_error("Failed to open file for editing");
    }
    std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    setState(true, false);
    inputFile.close();
    // Replace all occurrences of oldStr with newStr
    size_t pos = 0;
    while ((pos = fileContents.find(oldStr, pos)) != std::string::npos)
    {
        fileContents.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
    // Open the file for writing and write the modified contents
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
        setState(false, true);
    }
    setState(true, false);
    outputFile << fileContents;
    m_data = fileContents;
    outputFile.close();
}

bool FileManager::createFile(const std::filesystem::path& path)
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

bool FileManager::createDir(const std::filesystem::path& path)
{
    return fs::create_directory(path);
}

std::vector<std::string> FileManager::listDir(const std::filesystem::path& path)
{
    std::vector<std::string> result;
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (fs::is_directory(entry) && !entry.path().has_extension())
        {
            result.push_back(entry.path().filename().string());
        }
    }
    return result;
}

std::vector<std::string> FileManager::listFilesOfDir(const std::filesystem::path& path)
{
    std::vector<std::string> result;
    for (const auto& entry : fs::directory_iterator(path)) {
        result.push_back(entry.path().filename().string());
    }
    return result;
}

bool FileManager::deleteFile(const std::filesystem::path& path)
{
    return fs::remove(path);
}

bool FileManager::deleteDir(const std::filesystem::path& path)
{
    return fs::remove_all(path);
}

void FileManager::changePermissions(const std::filesystem::path& filePath, const std::filesystem::perms& permissions)
{
    try {
        std::filesystem::permissions(filePath, permissions);
        std::cout << "File permissions changed successfully.\n";
    } catch (const std::filesystem::filesystem_error& e) {
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

FileInfo::FileInfo(const std::filesystem::path& filePath)
{
    std::error_code ec;

    m_filePath = filePath;

    m_fileName = filePath.filename().string();

    m_fileSize = std::filesystem::file_size(filePath, ec);

    if (ec) { m_fileSize = -1; }

    auto writeTime = std::filesystem::last_write_time(filePath, ec);
    if (ec) {
        writeTime = decltype(writeTime)::clock::time_point::min();
    }
    m_lastWriteTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(writeTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());

    std::filesystem::file_time_type createTime = std::filesystem::last_write_time(filePath, ec);
    if (ec) {
        createTime = decltype(createTime)::clock::time_point::min();
    }
    m_creationTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(createTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());

}

FileInfo::~FileInfo()
{
}

std::string FileInfo::fileName() const
{
    return m_fileName;
}

long long FileInfo::fileSize() const
{
    return m_fileSize;
}

std::string FileInfo::lastWriteTime() const
{
    std::filesystem::file_time_type lastModifiedTime = std::filesystem::last_write_time(m_filePath);
    // Convert the file time type to a time point
    auto lastModifiedTimePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastModifiedTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    // Convert the time point to a time string
    std::time_t lastModifiedTimeT = std::chrono::system_clock::to_time_t(lastModifiedTimePoint);
    std::string lastModifiedTimeString = std::ctime(&lastModifiedTimeT);

    return lastModifiedTimeString;
}

std::string FileInfo::creationTime() const
{
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(m_creationTime));
    return std::asctime(std::localtime(&time));
}

FileTypeDetector::FileTypeDetector()
{
}

FileTypeDetector::~FileTypeDetector()
{
}

std::string FileTypeDetector::detectFileType(const std::filesystem::path& filePath)
{
    std::string extension = filePath.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });

    if (extension == ".txt") {
        return "Text File";
    } else if (extension == ".doc" || extension == ".docx") {
        return "Microsoft Word Document";
    } else if (extension == ".xls" || extension == ".xlsx") {
        return "Microsoft Excel Spreadsheet";
    } else if (extension == ".ppt" || extension == ".pptx") {
        return "Microsoft PowerPoint Presentation";
    } else if (extension == ".pdf") {
        return "PDF Document";
    } else if (extension == ".html" || extension == ".htm") {
        return "HTML Document";
    } else if (extension == ".xml") {
        return "XML Document";
    } else if (extension == ".json") {
        return "JSON Document";
    } else if (extension == ".cpp" || extension == ".hpp" || extension == ".h" || extension == ".cxx" || extension == ".hxx") {
        return "C++ Source Code";
    } else if (extension == ".java") {
        return "Java Source Code";
    } else if (extension == ".py") {
        return "Python Source Code";
    } else if (extension == ".rb") {
        return "Ruby Source Code";
    } else if (extension == ".php") {
        return "PHP Source Code";
    } else {
        return "Unknown File Type";
    }
}

CELL_NAMESPACE_END

#endif
