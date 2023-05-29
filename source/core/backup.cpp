#if __has_include("backup.hpp")
#   include "backup.hpp"
#else
#   error "Cell's "backup.hpp" was not found!"
#endif

#if __has_include("core.hpp")
#   include "core.hpp"
#else
#   error "Cell's "core.hpp" was not found!"
#endif

#if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Maintenance)

FileBackup::FileBackup(const std::string& fileName)
{
    backupStruct.fileName = fileName;
    backupStruct.progressCallback = nullptr;
}

FileBackup::~FileBackup()
{
}

void FileBackup::setProgressCallback(const StateFunction& callback)
{
    backupStruct.progressCallback = callback;
}

FutureState FileBackup::backupAsync() __cell_noexcept
{
    return std::async(std::launch::async, [this]() {
        return backupSync();
    });
}

bool FileBackup::backupSync() __cell_noexcept
{
    const auto fileName = backupStruct.fileName.value();

    // Check if the file exists
    if (!Fs::exists(fileName)) {
        if(DeveloperMode::IsEnable)
        {
            Log("Error: file does not exist.", LoggerType::Critical);
        }
        return false;
    }

    // Create a backup file name with a timestamp
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    auto backupFileName = fileName + "." + std::to_string(timestamp) + ".bak";

    // Check if the backup file already exists
    if (Fs::exists(backupFileName)) {
        // Prompt the user to confirm whether they want to overwrite the existing backup file
        if(DeveloperMode::IsEnable)
        {
            Log("A backup file with the name \"" + backupFileName + "\" already exists. Do you want to overwrite it? (y/n):", LoggerType::Warning);
        }
        std::string userInput;
        std::getline(std::cin, userInput);
        if (userInput != "y" && userInput != "Y")
        {
            if(DeveloperMode::IsEnable)
            {
                Log("Backup process cancelled.", LoggerType::Critical);
            }
            return false;
        }
    }

    // Get the file size for progress reporting
    auto fileSize = Fs::file_size(fileName);

    // Check if there is enough disk space available for the backup file
    auto spaceNeeded = Fs::file_size(fileName);
    if (spaceNeeded > Fs::space(Fs::path(".")).available)
    {
        if(DeveloperMode::IsEnable)
        {
            Log("Error: not enough disk space available to create backup file.", LoggerType::Critical);
        }
        return false;
    }

    // Input and output files with RAII objects.
    std::unique_ptr<std::ifstream> inFile;
    std::unique_ptr<std::ofstream> outFile;

    // Object to ensure exclusive access to the files.
    std::mutex fileMutex;
    bool success = false;

    try {
        // Lock the mutex to prevent concurrent access to the files
        std::lock_guard<std::mutex> lock(fileMutex);

        // Open the input and output file streams
        inFile = std::make_unique<std::ifstream>(fileName, std::ios::binary);
        outFile = std::make_unique<std::ofstream>(backupFileName, std::ios::binary);

        // Backup the file
        char buffer[4096];
        std::streamsize bytesRead = 0;
        int bytesCopied = 0;

        while (inFile->read(buffer, sizeof(buffer)), bytesRead = inFile->gcount())
        {
            outFile->write(buffer, bytesRead);
            bytesCopied += static_cast<int>(bytesRead);

            // Report progress
            if (backupStruct.progressCallback) {
                int progress = static_cast<int>((static_cast<double>(bytesCopied) / fileSize) * 100);
                backupStruct.progressCallback(progress);
            }
        }

        if(DeveloperMode::IsEnable)
        {
            Log("File backup created!", LoggerType::Success);
        }

        success = true;
    }
    catch (const Exception& e)
    {
        if(DeveloperMode::IsEnable)
        {
            Log(e.what(), LoggerType::Success);
        }
    }

    return success;
}

DataRestore::DataRestore(const std::string& fileName, const std::string& restorefileName)
{
    restoreStruct.backupFileName    = fileName;
    restoreStruct.restoreFileName   = restorefileName;
    restoreStruct.progressCallback  = nullptr;
}

DataRestore::~DataRestore()
{
}

void DataRestore::setProgressCallback(const StateFunction& callback)
{
    restoreStruct.progressCallback = callback;
}

FutureState DataRestore::restoreAsync() __cell_noexcept
{
    return std::async(std::launch::async, [this]() {
        return restoreSync();
    });
}

bool DataRestore::restoreSync() __cell_noexcept
{
    const auto fileName = restoreStruct.backupFileName.value();
    const auto restoreFileName = restoreStruct.restoreFileName.value();

    // Check if the backup file exists
    if (!Fs::exists(fileName)) {
        if(DeveloperMode::IsEnable)
        {
            Log("Error: backup file does not exist.", LoggerType::Critical);
        }
        return false;
    }

    // Check if the restore file already exists
    if (Fs::exists(restoreFileName)) {
        if(DeveloperMode::IsEnable)
        {
            Log("Error: restore file already exists.", LoggerType::Warning);
        }
        return false;
    }

    // Check if there is enough disk space for the restore file
    auto spaceNeeded = Fs::file_size(fileName);
    if (spaceNeeded > Fs::space(Fs::path(".")).available)
    {
        if(DeveloperMode::IsEnable)
        {
            Log("Error: not enough disk space to restore file.", LoggerType::Critical);
        }
        return false;
    }

    // Input and output files with RAII objects.
    std::unique_ptr<std::ifstream> inFile;
    std::unique_ptr<std::ofstream> outFile;

    // Object to ensure exclusive access to the files.
    std::mutex fileMutex;
    bool success = false;

    try {
        // Lock the mutex to prevent concurrent access to the files
        std::lock_guard<std::mutex> lock(fileMutex);

        // Open the input and output file streams
        inFile = std::make_unique<std::ifstream>(fileName, std::ios::binary);
        outFile = std::make_unique<std::ofstream>(restoreFileName, std::ios::binary);

        // Check if the files were opened successfully
        if (!inFile || !outFile) {
            if(DeveloperMode::IsEnable)
            {
                Log("Error: could not open files for restore.", LoggerType::Critical);
            }
            return false;
        }

        // Get the file size for progress reporting
        auto fileSize = Fs::file_size(fileName);

        // Restore the file
        char buffer[4096];
        std::streamsize bytesRead = 0;
        int bytesCopied = 0;
        while (inFile->read(buffer, sizeof(buffer)), bytesRead = inFile->gcount())
        {
            outFile->write(buffer, bytesRead);
            bytesCopied += static_cast<int>(bytesRead);

            // Report progress
            if (restoreStruct.progressCallback) {
                int progress = static_cast<int>((static_cast<double>(bytesCopied) / fileSize) * 100);
                restoreStruct.progressCallback(progress);
            }
        }

        success = true;
    }
    catch (const Exception& e)
    {
        // Ensure that the file streams are closed in case of an exception
        inFile.reset();
        outFile.reset();

        if(DeveloperMode::IsEnable)
        {
            Log(e.what(), LoggerType::Success);
        }
    }

    if(DeveloperMode::IsEnable)
    {
        Log("File restored: " + restoreFileName, LoggerType::Success);
    }

    return success;
}



CELL_NAMESPACE_END
