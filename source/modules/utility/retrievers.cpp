#if __has_include("retrievers.hpp")
#   include "retrievers.hpp"
#else
#   error "Cell's "retrievers.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Utility)

std::vector<Library> LibraryManager::getInstalledLibraries()
{
    std::vector<Library> libraries;

#ifdef CELL_PLATFORM_WINDOWS
    libraries = getInstalledLibrariesWindows();
#elif defined(CELL_PLATFORM_LINUX)
    libraries = getInstalledLibrariesLinux();
#elif defined(CELL_PLATFORM_MAC)
    libraries = getInstalledLibrariesMacOS();
#endif

    return libraries;
}

bool LibraryManager::isLibraryAvailable(const std::string& libraryName)
{
    std::vector<Library> libraries = getInstalledLibraries();
    for (const auto& library : libraries) {
        if (library.name == libraryName)
            return true;
    }
    return false;
}

#ifdef CELL_PLATFORM_WINDOWS
std::vector<Library> LibraryManager::getInstalledLibrariesWindows()
{
    std::vector<Library> libraries;
    char sysDir[MAX_PATH];
    GetSystemDirectoryA(sysDir, MAX_PATH);

    DWORD len = GetFileVersionInfoSizeA(sysDir, nullptr);
    if (len != 0) {
        std::vector<BYTE> versionInfo(len);
        if (GetFileVersionInfoA(sysDir, 0, len, versionInfo.data())) {
            VS_FIXEDFILEINFO* fileInfo = nullptr;
            UINT fileInfoLen = 0;
            if (VerQueryValueA(versionInfo.data(), "\\", reinterpret_cast<LPVOID*>(&fileInfo), &fileInfoLen) && fileInfo)
            {
                libraries.push_back({ "Windows System Directory", getWindowsVersionString(sysDir) });
            }
        }
    }

    return libraries;
}

std::string LibraryManager::getWindowsVersionString(const std::string& filePath)
{
    DWORD versionHandle;
    DWORD versionSize = GetFileVersionInfoSizeA(filePath.c_str(), &versionHandle);
    if (versionSize != 0) {
        std::vector<char> versionBuffer(versionSize);
        if (GetFileVersionInfoA(filePath.c_str(), versionHandle, versionSize, versionBuffer.data())) {
            LPVOID versionInfo = nullptr;
            UINT versionInfoSize = 0;
            if (VerQueryValueA(versionBuffer.data(), "\\", &versionInfo, &versionInfoSize) && versionInfo) {
                VS_FIXEDFILEINFO* fileInfo = reinterpret_cast<VS_FIXEDFILEINFO*>(versionInfo);
                std::ostringstream oss;
                oss << (fileInfo->dwFileVersionMS >> 16) << "." << (fileInfo->dwFileVersionMS & 0xFFFF) << "."
                    << (fileInfo->dwFileVersionLS >> 16) << "." << (fileInfo->dwFileVersionLS & 0xFFFF);
                return oss.str();
            }
        }
    }

    return "Unknown";
}

#elif defined(CELL_PLATFORM_LINUX)
std::vector<Library> LibraryManager::getInstalledLibrariesLinux()
{
    std::vector<Library> libraries;
    std::ifstream maps_file("/proc/self/maps");
    std::string line;
    while (std::getline(maps_file, line)) {
        if (line.find(".so") != std::string::npos) {
            std::string libraryPath = line.substr(0, line.find_first_of(' '));
            libraries.push_back({ libraryPath, getLinuxLibraryVersion(libraryPath) });
        }
    }
    return libraries;
}

std::string LibraryManager::getLinuxLibraryVersion(const std::string& libraryPath)
{
    std::ifstream file(libraryPath);
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find("Version:");
        if (pos != std::string::npos) {
            return line.substr(pos + 8);
        }
    }
    return "Unknown";
}

#elif defined(CELL_PLATFORM_MAC)

std::vector<Library> LibraryManager::getInstalledLibrariesMacOS()
{
    std::vector<Library> libraries;
    // Check the location of Homebrew
    std::string brewPath = System::execute("/bin/sh -c 'which brew'");
    if (brewPath.empty()) {
        std::cout << "Homebrew is not installed or cannot be found." << std::endl;
        return libraries;
    }
    std::string command = brewPath + __cell_space + "list --versions";
    std::string libraryInfo = System::execute(command.c_str());
    std::istringstream iss(libraryInfo);
    std::string line;
    while (std::getline(iss, line)) {
        size_t delimiterPos = line.find(' ');
        if (delimiterPos != std::string::npos) {
            std::string name = line.substr(0, delimiterPos);
            std::string version = line.substr(delimiterPos + 1);
            libraries.push_back({ name, version });
        }
    }
    return libraries;
}
#endif

ApplicationRetriever::ApplicationRetriever()
{
}

ApplicationRetriever::~ApplicationRetriever()
{
}

std::vector<std::pair<std::string, std::string>> ApplicationRetriever::getInstalledApplications()
{
    std::vector<std::pair<std::string, std::string>> appNames;

#ifdef CELL_PLATFORM_WINDOWS
    appNames = getInstalledApplicationsWindows();
#elif defined(CELL_PLATFORM_MAC)
    appNames = getInstalledApplicationsMac();
#elif defined(CELL_PLATFORM_ANDROID)
    appNames = getInstalledApplicationsAndroid();
#elif defined(CELL_PLATFORM_IOS)
    appNames = getInstalledApplicationsiOS();
#elif defined(CELL_PLATFORM_LINUX)
    appNames = getInstalledApplicationsLinux();
#endif

    return appNames;
}

#ifdef CELL_PLATFORM_WINDOWS
std::vector<std::pair<std::string, std::string>> ApplicationRetriever::getInstalledApplicationsWindows()
{
    std::vector<std::pair<std::string, std::string>> appNames;

    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_32KEY, &hKey) == ERROR_SUCCESS)
    {
        DWORD numSubKeys;
        if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &numSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            char subKeyName[255];
            for (DWORD i = 0; i < numSubKeys; ++i)
            {
                DWORD subKeyNameSize = sizeof(subKeyName);
                if (RegEnumKeyEx(hKey, i, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
                {
                    HKEY appKey;
                    std::string appKeyPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + std::string(subKeyName);
                    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, appKeyPath.c_str(), 0, KEY_READ | KEY_WOW64_32KEY, &appKey) == ERROR_SUCCESS)
                    {
                        char appName[255];
                        char appVersion[255];
                        DWORD appNameSize = sizeof(appName);
                        DWORD appVersionSize = sizeof(appVersion);
                        if (RegQueryValueEx(appKey, "DisplayName", NULL, NULL, reinterpret_cast<LPBYTE>(appName), &appNameSize) == ERROR_SUCCESS &&
                            RegQueryValueEx(appKey, "DisplayVersion", NULL, NULL, reinterpret_cast<LPBYTE>(appVersion), &appVersionSize) == ERROR_SUCCESS)
                        {
                            appNames.push_back(std::make_pair(appName, appVersion));
                        }
                        RegCloseKey(appKey);
                    }
                }
            }
        }
        RegCloseKey(hKey);
    }

    return appNames;
}
#endif

#ifdef CELL_PLATFORM_MAC
std::vector<std::pair<std::string, std::string>> ApplicationRetriever::getInstalledApplicationsMac()
{
    std::vector<std::pair<std::string, std::string>> applications;

    // Recursive function to traverse directories
    std::function<void(const std::string&)> traverseDirectory = [&](const std::string& directory) {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            try {
                if (entry.is_directory()) {
                    std::string path = entry.path();
                    std::string appName = path.substr(path.find_last_of("/\\") + 1);  // Extract the application name

                    // Check if the application bundle has a .app extension
                    if (std::filesystem::is_directory(entry) && appName.find(".app") != std::string::npos) {
                        // Remove the .app extension from the application name
                        appName = appName.substr(0, appName.find(".app"));

                        // Extract the application version from the Info.plist file
                        std::string plistPath = path + "/Contents/Info.plist";
                        std::ifstream plistFile(plistPath);
                        if (plistFile) {
                            std::string line;
                            std::string appVersion = "Unknown";  // Default version if not found

                            while (std::getline(plistFile, line)) {
                                // Look for the <key>CFBundleShortVersionString</key> line
                                if (line.find("<key>CFBundleShortVersionString</key>") != std::string::npos) {
                                    // Extract the version string from the next line
                                    std::getline(plistFile, line);
                                    size_t startPos = line.find("<string>") + 8;
                                    size_t endPos = line.find("</string>");
                                    appVersion = line.substr(startPos, endPos - startPos);
                                    break;
                                }
                            }
                            plistFile.close();

                            // Add the application name and version to the vector
                            applications.emplace_back(appName, appVersion);
                        }
                    }
                    else {
                        // If the entry is a directory, recursively traverse it
                        traverseDirectory(path);
                    }
                }
            } catch (const std::filesystem::filesystem_error& ex) {
                // Handle the permission error gracefully (e.g., print a message, log, or ignore)
                std::cout << "Skipping directory: " << entry.path().string() << " - Permission denied" << std::endl;
            }
        }
    };

    // Traverse the /Applications directory and its subdirectories
    traverseDirectory("/Applications");

    return applications;
}

#endif


#ifdef CELL_PLATFORM_ANDROID
#include <jni.h>
#include <android/log.h>
#include <android/content/pm/PackageManager.h>
#include <android/content/pm/ApplicationInfo.h>

std::vector<std::pair<std::string, std::string>> ApplicationRetriever::getInstalledApplicationsAndroid()
{
    std::vector<std::pair<std::string, std::string>> appNames;

    // Get the Java environment and the application context
    JNIEnv* env = /* Obtain the JNIEnv */;
    jobject context = /* Obtain the application context */;

    // Get the PackageManager
    jclass contextClass = env->GetObjectClass(context);
    jmethodID getPackageManagerMethod = env->GetMethodID(contextClass, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject packageManager = env->CallObjectMethod(context, getPackageManagerMethod);

    // Get the list of installed applications
    jclass packageManagerClass = env->GetObjectClass(packageManager);
    jmethodID getInstalledApplicationsMethod = env->GetMethodID(packageManagerClass, "getInstalledApplications", "(I)Ljava/util/List;");
    jobject installedApplications = env->CallObjectMethod(packageManager, getInstalledApplicationsMethod, 0);

    // Get the size of the list
    jclass listClass = env->GetObjectClass(installedApplications);
    jmethodID sizeMethod = env->GetMethodID(listClass, "size", "()I");
    jint size = env->CallIntMethod(installedApplications, sizeMethod);

    // Iterate over the list of installed applications
    jclass applicationInfoClass = env->FindClass("android/content/pm/ApplicationInfo");
    jmethodID getPackageNameMethod = env->GetMethodID(applicationInfoClass, "packageName", "()Ljava/lang/String;");
    jmethodID getPackageVersionMethod = env->GetMethodID(applicationInfoClass, "versionName", "()Ljava/lang/String;");

    for (int i = 0; i < size; ++i)
    {
        // Get the ApplicationInfo object at the given index
        jobject applicationInfo = env->CallObjectMethod(installedApplications, env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;"), i);

        // Get the package name and version
        jstring packageName = static_cast<jstring>(env->CallObjectMethod(applicationInfo, getPackageNameMethod));
        jstring packageVersion = static_cast<jstring>(env->CallObjectMethod(applicationInfo, getPackageVersionMethod));

        // Convert the package name and version to C++ strings
        const char* packageNameStr = env->GetStringUTFChars(packageName, NULL);
        const char* packageVersionStr = env->GetStringUTFChars(packageVersion, NULL);

        // Store the package name and version in the appNames vector
        appNames.emplace_back(packageNameStr, packageVersionStr);

        // Release the JNI strings
        env->ReleaseStringUTFChars(packageName, packageNameStr);
        env->ReleaseStringUTFChars(packageVersion, packageVersionStr);

        // Delete the local references
        env->DeleteLocalRef(applicationInfo);
        env->DeleteLocalRef(packageName);
        env->DeleteLocalRef(packageVersion);
    }

    // Release the local references
    env->DeleteLocalRef(applicationInfoClass);
    env->DeleteLocalRef(listClass);
    env->DeleteLocalRef(packageManagerClass);
    env->DeleteLocalRef(installedApplications);
    env->DeleteLocalRef(packageManager);
    env->DeleteLocalRef(contextClass);

    return appNames;
}
#endif


#ifdef CELL_PLATFORM_IOS
#include <CoreFoundation/CoreFoundation.h>
#include <MobileCoreServices/MobileCoreServices.h>

std::vector<std::pair<std::string, std::string>> ApplicationRetriever::getInstalledApplicationsiOS()
{
    std::vector<std::pair<std::string, std::string>> appNames;

    CFArrayRef appArray = LSCopyAllInstalledApplications();
    CFIndex count = CFArrayGetCount(appArray);

    for (CFIndex i = 0; i < count; ++i)
    {
        CFDictionaryRef appDictionary = static_cast<CFDictionaryRef>(CFArrayGetValueAtIndex(appArray, i));
        CFStringRef bundleID = static_cast<CFStringRef>(CFDictionaryGetValue(appDictionary, kCFBundleIdentifierKey));
        CFStringRef bundleVersion = static_cast<CFStringRef>(CFDictionaryGetValue(appDictionary, kCFBundleVersionKey));

        char appName[255];
        char appVersion[255];

        CFStringGetCString(bundleID, appName, sizeof(appName), kCFStringEncodingUTF8);
        CFStringGetCString(bundleVersion, appVersion, sizeof(appVersion), kCFStringEncodingUTF8);

        appNames.emplace_back(appName, appVersion);
    }

    CFRelease(appArray);

    return appNames;
}
#endif

#ifdef CELL_PLATFORM_LINUX
std::vector<std::pair<std::string, std::string>> ApplicationRetriever::getInstalledApplicationsLinux()
{
    std::vector<std::pair<std::string, std::string>> appNames;

    std::ifstream dpkgStatus("/var/lib/dpkg/status");
    std::string line;

    std::string currentPackage;
    std::string currentVersion;

    while (std::getline(dpkgStatus, line))
    {
        if (line.empty())
        {
            if (!currentPackage.empty() && !currentVersion.empty())
            {
                appNames.emplace_back(currentPackage, currentVersion);
            }

            currentPackage.clear();
            currentVersion.clear();
        }
        else if (line.substr(0, 9) == "Package: ")
        {
            currentPackage = line.substr(9);
        }
        else if (line.substr(0, 9) == "Version: ")
        {
            currentVersion = line.substr(9);
        }
    }

    if (!currentPackage.empty() && !currentVersion.empty())
    {
        appNames.emplace_back(currentPackage, currentVersion);
    }

    dpkgStatus.close();

    return appNames;
}
#endif

std::vector<std::pair<std::string, std::string>> ApplicationRetriever::filterByCategory(const std::vector<std::pair<std::string, std::string>>& appNames, const std::string& category)
{
    std::vector<std::pair<std::string, std::string>> filteredApps;

    // Copy the elements from appNames vector to filteredApps vector based on the specified condition
    std::copy_if(appNames.begin(), appNames.end(), std::back_inserter(filteredApps), [&](const std::pair<std::string, std::string>& app) {
        // The lambda function defines the condition for filtering
        // Check if the current app's name is in the specified category
        return isAppInCategory(app.first, category);
    });

    // Return the filtered list of applications
    return filteredApps;
}


void ApplicationRetriever::sortApplications(std::vector<std::pair<std::string, std::string>>& appNames, bool ascending)
{
    if (ascending)
    {
        // Sort the appNames vector in ascending order based on the first element of each pair (app name)
        std::sort(appNames.begin(), appNames.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    }
    else
    {
        // Sort the appNames vector in descending order based on the first element of each pair (app name)
        std::sort(appNames.begin(), appNames.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });
    }
}


bool ApplicationRetriever::isAppInCategory(const std::string& appName, const std::string& category)
{
    if (appName.empty() || category.empty())
    {
        // If either the app name or category is empty, return false.
        return false;
    }

    return (appName.back() == category.back());
}

CELL_NAMESPACE_END
