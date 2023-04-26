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

CELL_USING_NAMESPACE Cell::System;

CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::FileSystem)

FileIO::FileIO()
{
}

FileIO::~FileIO()
{
    if(close())
    {
        if(DeveloperMode::IsEnable)
        {
            Log("File closed!", LoggerType::Critical);
        }
    }
}

bool FileIO::open(const std::string& fileName)
{
    if(close())
        if (fileName.empty()) {
            if(DeveloperMode::IsEnable)
            {
                Log("Empty file name provided!", LoggerType::Critical);
            }
            return false;
        }
    fileStruct.filename = fileName;
    fileStruct.content.open(fileName);
    if (!fileStruct.content.good()) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to open file " + fileName, LoggerType::Critical);
        }
        return false;
    }
    return true;
}

bool FileIO::close()
{
    bool ret {false};
    if (fileStruct.content.is_open())
    {
        fileStruct.content.flush();
        fileStruct.content.close();
        fileStruct.filename.clear();
        ret = true;
    }
    return ret;
}

bool FileIO::isOpen() const
{
    return fileStruct.content.is_open();
}

bool FileIO::write(const std::string& data)
{
    if (!fileStruct.content.is_open()) {
        if(DeveloperMode::IsEnable)
        {
            Log("File is not open", LoggerType::Critical);
        }
        return false;
    }
    fileStruct.content << data << "\n";
    if (!fileStruct.content.good()) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to write data to file " + fileStruct.filename, LoggerType::Critical);
        }
        return false;
    }
    return true;
}

std::ifstream FileIO::readRawAll() const
{
    if (!fileStruct.content.is_open()) {
        if(DeveloperMode::IsEnable)
        {
            Log("File is not open!" , LoggerType::Critical);
        }
    }
    std::stringstream ss;
    ss << fileStruct.content.rdbuf();
    std::string data { ss.str() };
    if (data.empty()) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to write data to file " + fileStruct.filename, LoggerType::Critical);
        }
    }
    std::ifstream iss;
    iss.open(fileStruct.filename);
    if(!iss.is_open()) {
        if(DeveloperMode::IsEnable)
        {
            Log("File is not open!" , LoggerType::Critical);
        }
    }
    return iss;
}

std::string FileIO::readAll() const
{
    if (!fileStruct.content.is_open()) {
        if(DeveloperMode::IsEnable)
        {
            Log("File is not open!" , LoggerType::Critical);
        }
        return "";
    }
    std::string data { std::istreambuf_iterator<char>(fileStruct.content.rdbuf()) , std::istreambuf_iterator<char>() };
    if (data.empty()) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to read data from file " + fileStruct.filename , LoggerType::Critical);
        }
    }
    return data;
}

CELL_NAMESPACE_END

#endif
