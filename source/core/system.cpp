#include "system.hpp"

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;

CELL_NAMESPACE_BEGIN(Cell)

SystemInformation::SystemInformation()
{

}

SystemInformation::~SystemInformation()
{

}

std::string SystemInformation::getHostUserName()
{
#if defined(PLATFORM_MAC) || defined(PLATFORM_APPLE)
    return getenv("USER");
#elif defined(PLATFORM_LINUX)
    return getenv("USERNAME");
#elif defined(PLATFORM_WINDOWS)
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(username, &username_len);
    return username;
#endif
}

std::string SystemInformation::getHostName()
{
    std::string result{};
#ifdef PLATFORM_DESKTOP
#if defined(PLATFORM_MAC) || defined(PLATFORM_APPLE)
    result = command("scutil --get LocalHostName");
    return result;
#elif defined(PLATFORM_LINUX)
    result = command("hostnamectl");
    return result;
#elif defined(PLATFORM_WINDOWS)
    result = command("hostnamectl");
    return result;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS) || defined(PLATFORM_IOS_SIMULATOR)
    result = "Unknown";
#elif defined(PLATFORM_ANDROID)
    result = "Unknown";
#endif
#else
    result = "Unknown";
#endif
    return result;
}

std::string SystemInformation::getOsName()
{
    const std::string os{PLATFORM_OS};
    return os;
}

std::string SystemInformation::macAddressAsByteArray(unsigned char MACData[])
{
    std::string var {"unknown"};
    var = stringFormat("%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);
    return var;
}

std::string SystemInformation::getMacAddress()
{
    std::string result{};
#ifdef PLATFORM_DESKTOP
#if defined(PLATFORM_MAC) || defined(PLATFORM_APPLE)
    result = command("/sbin/ifconfig en0 | /usr/bin/grep 'ether' | /usr/bin/cut -d' ' -f 2");
    return result;
#elif defined(PLATFORM_LINUX)
    result = command("/sbin/ifconfig en0 | /usr/bin/grep 'ether' | /usr/bin/cut -d' ' -f 2");
    return result;
#elif defined(PLATFORM_WINDOWS)
    IP_ADAPTER_INFO AdapterInfo[16];			// Allocate information for up to 16 NICs
    DWORD dwBufLen = sizeof(AdapterInfo);		// Save the memory size of buffer
    [[maybe_unused]] DWORD dwStatus = GetAdaptersInfo( AdapterInfo,	&dwBufLen); // [in] size of receive data buffer
    assert(dwStatus == ERROR_SUCCESS);			// Verify return value is valid, no buffer overflow
    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;// Contains pointer to current adapter info
    m_macAddressList.push_front(macAddressAsByteArray(pAdapterInfo->Address));
    auto indexOfAddress = std::next(m_macAddressList.begin(), index);
    return *indexOfAddress;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS) || defined(PLATFORM_IOS_SIMULATOR)
    result = "Unknown";
#elif defined(PLATFORM_ANDROID)
    result = "Unknown";
#endif
#else
    result = command("/sbin/ifconfig en0 | /usr/bin/grep 'ether' | /usr/bin/cut -d' ' -f 2");
    result = "Unknown";
#endif
    return result;
}

std::string SystemInformation::getIpV4Address()
{
    std::string result = "Unknown";
#ifdef PLATFORM_DESKTOP
#if defined (PLATFORM_LINUX)
    return result;
#elif defined (PLATFORM_MAC) || defined(PLATFORM_APPLE)
    result = command("ipconfig getifaddr en0");
    if(result.empty()) {
        result = command("ipconfig getifaddr en1");
    }
    return result;
#elif defined (PLATFORM_WINDOWS)
    return result;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    return result;
#elif defined(PLATFORM_ANDROID)
    return result;
#endif
#else
    return result;
#endif
}

std::string SystemInformation::getIpV6Address()
{
    std::string result = "Unknown";
#ifdef PLATFORM_DESKTOP
#if defined (PLATFORM_LINUX)
    return result;
#elif defined (PLATFORM_MAC) || defined(PLATFORM_APPLE)
    result = command("system_profiler SPNetworkDataType | grep -e \"IPv4 Addresses\" | awk -F' *' '{print ""$4}'");
    return result;
#elif defined (PLATFORM_WINDOWS)
    return ls;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    return result;
#elif defined(PLATFORM_ANDROID)
    return result;
#endif
#else
    return result;
#endif
}

std::string SystemInformation::getMachineUniqueId()
{
#ifdef PLATFORM_DESKTOP
#if defined(PLATFORM_MAC)
    char buf[512] = "";
    io_registry_entry_t ioRegistryRoot = IORegistryEntryFromPath(kIOMainPortDefault, "IOService:/");
    CFStringRef uuidCf = (CFStringRef) IORegistryEntryCreateCFProperty( ioRegistryRoot, CFSTR(kIOPlatformUUIDKey), kCFAllocatorDefault, 0);
    IOObjectRelease(ioRegistryRoot);
    CFStringGetCString(uuidCf, buf, sizeof(buf), kCFStringEncodingMacRoman);
    CFRelease(uuidCf);
    return buf;
#elif defined(PLATFORM_LINUX)
    return "Unknown";
#elif defined(PLATFORM_WINDOWS)
    return "Unknown";
#endif
#elif defined(PLATFORM_FREEBSD)
    return "Unknown";
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    std::string result = "Unknown";
    return result;
#elif defined(PLATFORM_ANDROID)
    std::string result = "Unknown";
    return result;
#endif
#else
    std::string result = "Unknown";
    return result;
#endif
}

std::string SystemInformation::getStorageDiskModel()
{
    std::string result = "Unknown";
#ifdef PLATFORM_DESKTOP
#if defined (PLATFORM_LINUX)
    return result;
#elif defined (PLATFORM_MAC)
    result = command("system_profiler SPSerialATADataType | grep -e \"Model\" | awk -F' *' '{print ""$3, ""$4, ""$5}'");
    return result;
#elif defined (PLATFORM_WINDOWS)
    return result;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    return result;
#elif defined(PLATFORM_ANDROID)
    return result;
#endif
#else
    return result;
#endif
}

std::string SystemInformation::getStorageDiskSerialNumber()
{
    std::string result = "Unknown";
#ifdef PLATFORM_DESKTOP
#if defined (PLATFORM_LINUX)
    return ls;
#elif defined (PLATFORM_MAC)
    result = command("system_profiler SPSerialATADataType | grep -e \"Serial Number\" | awk -F' *' '{print ""$4}'");
    return result;
#elif defined (PLATFORM_WINDOWS)
    return result;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    return result;
#elif defined(PLATFORM_ANDROID)
    return result;
#endif
#else
    return result;
#endif
}

std::string SystemInformation::getGpuModel()
{
    std::string result = "Unknown";
#ifdef PLATFORM_DESKTOP
#if defined (PLATFORM_LINUX)
    return result;
#elif defined (PLATFORM_MAC)
    return result;
#elif defined (PLATFORM_WINDOWS)
    return result;
#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    return result;
#elif defined(PLATFORM_ANDROID)
    return result;
#endif
#else
    return result;
#endif
}

std::string SystemInformation::getSerialNumber()
{
    std::string result{"unknown"};
#ifdef PLATFORM_DESKTOP
#if defined (PLATFORM_LINUX)
///
#elif defined (PLATFORM_MAC)
    CFStringRef serial;
    char buffer[32] = {0};
    io_service_t platformExpert = IOServiceGetMatchingService(kIOMainPortDefault, IOServiceMatching("IOPlatformExpertDevice"));
    if (platformExpert)
    {
        CFTypeRef serialNumberAsCFString = IORegistryEntryCreateCFProperty(platformExpert, CFSTR(kIOPlatformSerialNumberKey), kCFAllocatorDefault, 0);
        if (serialNumberAsCFString) {
            serial = (CFStringRef)serialNumberAsCFString;
        }
        if (CFStringGetCString(serial, buffer, 32, kCFStringEncodingUTF8)) {
            result = buffer;
        }
        IOObjectRelease(platformExpert);
    }
    //command("system_profiler SPHardwareDataType | awk '/Serial/ {print $4}' | sed 's/^.{7}//g'");
    return result;
#elif defined (PLATFORM_WINDOWS)

#endif
#elif defined(PLATFORM_MOBILE)
#if defined(PLATFORM_IOS)
    return result;
#elif defined(PLATFORM_ANDROID)
    return result;
#endif
#else
    return result;
#endif
}

CELL_NAMESPACE_END
