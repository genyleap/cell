#if __has_include("os-application.hpp")
#   include "os-application.hpp"
#else
#   error "Cell's "os-application.hpp" was not found!"
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

#ifdef __linux__
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

    for (const auto& app : appNames)
    {
        if (isAppInCategory(app.first, category))
        {
            filteredApps.push_back(app);
        }
    }

    return filteredApps;
}

void ApplicationRetriever::sortApplications(std::vector<std::pair<std::string, std::string>>& appNames, bool ascending)
{
    if (ascending)
    {
        std::sort(appNames.begin(), appNames.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    }
    else
    {
        std::sort(appNames.begin(), appNames.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });
    }
}

bool ApplicationRetriever::isAppInCategory(const std::string& appName, const std::string& category)
{
    // You can customize this method based on your specific requirements.
    // Here's an example implementation that checks if the category matches the last character of the app name.
    // For example, if the category is "Games", the app name must end with "G" to be considered in the category.

    if (appName.empty() || category.empty())
    {
        // If either the app name or category is empty, return false.
        return false;
    }

    char lastCharacter = appName.back();
    char categoryCharacter = category.back();

    return (lastCharacter == categoryCharacter);
}

CELL_NAMESPACE_END
