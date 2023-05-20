#ifdef _WIN32
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
//!libs
#pragma comment(lib, "Ws2_32.lib")
#elif __APPLE__
#include <unistd.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#else
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#endif

#ifdef __has_include
# if __has_include("sysinfo.hpp")
#   include "sysinfo.hpp"
#else
#   error "Cell's "sysinfo.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif


CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Hardware)

SystemInformation::SystemInformation()
{
}

SystemInformation::~SystemInformation()
{
}

OptionalString SystemInformation::getOsName()
{
    return OptionalString();
}

//!Dedicated for Win32 WMI System.
#ifdef PLATFORM_WINDOWS
std::string getFromWmi(const std::string_view query, const std::string_view key)
{
    std::string resutl;

    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        return resutl;
    }

    hr = CoInitializeSecurity(
        nullptr,
        -1,
        nullptr,
        nullptr,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE,
        nullptr);
    if (FAILED(hr)) {
        CoUninitialize();
        return resutl;
    }

    IWbemLocator* pLoc = nullptr;
    hr = CoCreateInstance(
        CLSID_WbemLocator,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        reinterpret_cast<LPVOID*>(&pLoc));
    if (FAILED(hr)) {
        CoUninitialize();
        return resutl;
    }

    IWbemServices* pSvc = nullptr;
    hr = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        nullptr,
        nullptr,
        0,
        0,
        0,
        0,
        &pSvc);
    if (FAILED(hr)) {
        pLoc->Release();
        CoUninitialize();
        return resutl;
    }

    hr = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        nullptr,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE);
    if (FAILED(hr)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return resutl;
    }

    IEnumWbemClassObject* pEnumerator = nullptr;
    bstr_t bstr(query.data());
    hr = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM " + bstr),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr,
        &pEnumerator);
    if (FAILED(hr)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return resutl;
    }

    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;
    hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
    if (FAILED(hr)) {
        pEnumerator->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return resutl;
    }

    VARIANT vtProp;
    bstr_t kstr(key.data());
    hr = pclsObj->Get(kstr, 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr)) {
        resutl = std::string(_bstr_t(vtProp));
        VariantClear(&vtProp);
    }

    pclsObj->Release();
    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return resutl;
}
#endif

OptionalString SystemInformation::getHostName()
{
#ifdef PLATFORM_WINDOWS
    WSADATA wsa_data;
    int error = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (error != 0) {
        (DeveloperMode::IsEnable) ? Log("Failed to initialize Windows Sockets!", LoggerType::Critical) : DO_NOTHING;
        informationData.hostName = "Unknown";
    }

    char hostname[NI_MAXHOST];
    if (gethostname(hostname, NI_MAXHOST) == 0) {
        informationData.hostName = hostname;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get hostname!", LoggerType::Critical) : DO_NOTHING;
        informationData.hostName = "Unknown";
    }

    WSACleanup();
#else
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        informationData.hostName = hostname;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get hostname!", LoggerType::Critical) : DO_NOTHING;
        informationData.hostName = "Unknown";
    }
#endif

    return informationData.hostName;
}

OptionalString SystemInformation::getUserName()
{
#ifdef PLATFORM_WINDOWS
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserNameA(username, &username_len)) {
        std::cout << "Username: " << username << std::endl;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get username!", LoggerType::Critical) : DO_NOTHING;
        informationData.userName = "Unknown";
    }
#else
    char *username = getlogin();
    if (username != NULL) {
        informationData.userName = username;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get username!", LoggerType::Critical) : DO_NOTHING;
        informationData.userName = "Unknown";
    }
#endif
    return informationData.userName;
}

OptionalString SystemInformation::getKernelName()
{
#ifdef PLATFORM_WINDOWS
    OSVERSIONINFOEX info;
    info.dwOSVersionInfoSize = sizeof(info);
    if (GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&info))) {
        informationData.kernelName = "Windows NT";
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel name", LoggerType::Critical) : DO_NOTHING;
        informationData.kernelName = "Unknown";
    }
#elif defined(PLATFORM_MAC)
    int name[] = {CTL_KERN, KERN_OSTYPE};
    char kernel_name[128];
    size_t length = sizeof(kernel_name);
    if (sysctl(name, 2, kernel_name, &length, NULL, 0) == 0) {
        informationData.kernelName = kernel_name;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel name", LoggerType::Critical) : DO_NOTHING;
        informationData.kernelName = "Unknown";
    }
#else
    std::string kernel_name;
    struct utsname uts;
    if(uname(&uts) == -1) {
        return 1;
    }
    kernel_name = uts.sysname;
    informationData.kernelName = kernel_name;
#endif
    return informationData.kernelName;
}

OptionalString SystemInformation::getKernelVersion()
{
#ifdef PLATFORM_WINDOWS
    OSVERSIONINFOEX info;
    info.dwOSVersionInfoSize = sizeof(info);
    if (GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&info))) {
        informationData.kernelName = "Windows NT";
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel name", LoggerType::Critical) : DO_NOTHING;
        informationData.kernelName = "Unknown";
    }
#elif defined(PLATFORM_MAC)
    int name[] = {CTL_KERN, KERN_OSRELEASE};
    char version[128];
    size_t length = sizeof(version);
    if (sysctl(name, 2, version, &length, NULL, 0) == 0) {
        informationData.kernelVersion = version;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel version", LoggerType::Critical) : DO_NOTHING;
        informationData.kernelVersion = "Unknown";
    }
#else
    std::string kernel_ver;
    std::ifstream infile("/proc/version");
    if (infile.is_open()) {
        getline(infile, kernel_ver, ' ');
        getline(infile, kernel_ver, ' ');
        getline(infile, kernel_ver, ' ');
        infile.close();
    }
    informationData.kernelVersion = kernel_ver;
#endif
    return informationData.kernelVersion;
}

CpuInfo SystemInformation::getCpuInfo()
{
#ifdef PLATFORM_WINDOWS
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    informationData.processorInfo.count = sysinfo.dwNumberOfProcessors;
#pragma intrinsic(__cpuid) // For inline CPUID call
    int reg[4];
    char brand[13*4+1] = {0};
    __cpuid(reg, 0x80000002);
    std::memcpy(brand, reg, sizeof(reg));
    __cpuid(reg, 0x80000003);
    std::memcpy(brand+16, reg, sizeof(reg));
    __cpuid(reg, 0x80000004);
    std::memcpy(brand+32, reg, sizeof(reg));
    informationData.processorInfo.brandString = brand;
#elif defined(PLATFORM_MAC)
    long nproc = sysconf(_SC_NPROCESSORS_ONLN);
    informationData.processorInfo.count = nproc;
    size_t size;
    sysctlbyname("machdep.cpu.brand_string", nullptr, &size, nullptr, 0);
    char* brand = new char[size];
    sysctlbyname("machdep.cpu.brand_string", brand, &size, nullptr, 0);
    informationData.processorInfo.brandString = brand;
    delete[] brand;
#else
    long nproc = sysconf(_SC_NPROCESSORS_ONLN);
    informationData.processorInfo.count = nproc;
    std::string cpu_brand;
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.substr(0, 10) == "model name") {
            cpu_brand = line.substr(13);
            break;
        }
    }
    cpuinfo.close();
    informationData.processorInfo.brandString = cpu_brand;
#endif
    return informationData.processorInfo;
}


MemoryInfo SystemInformation::getMemoryInfo()
{
#ifdef PLATFORM_WINDOWS
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    informationData.memoryInfo.freeMemory  = memInfo.ullAvailPhys;
    informationData.memoryInfo.usedMemory  = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
    informationData.memoryInfo.totalMemory = memInfo.ullTotalPhys;
#elif defined(PLATFORM_MAC)
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    long total_mem = pages * page_size;
    informationData.memoryInfo.totalMemory = total_mem;

    mach_port_t host_port = mach_host_self();
    mach_msg_type_number_t host_size = sizeof(vm_statistics64_data_t) / sizeof(integer_t);
    vm_size_t pagesize;
    host_page_size(host_port, &pagesize);
    vm_statistics64_data_t vm_stats;
    if (host_statistics64(host_port, HOST_VM_INFO64, (host_info64_t)&vm_stats, &host_size) != KERN_SUCCESS) {
        informationData.memoryInfo.usedMemory = 0;
    }
    natural_t used_memory = (vm_stats.active_count + vm_stats.inactive_count + vm_stats.wire_count) * pagesize;
    informationData.memoryInfo.usedMemory = used_memory;

    int mib[] = { CTL_HW, HW_MEMSIZE };
    uint64_t totalMemory;
    size_t len = sizeof(totalMemory);
    if (sysctl(mib, 2, &totalMemory, &len, NULL, 0) < 0) {
        (DeveloperMode::IsEnable) ? Log("Failed to get total memory!", LoggerType::Critical) : DO_NOTHING;
        informationData.memoryInfo.freeMemory = 0;
    }
    vm_statistics_data_t vmStats;
    mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
    kern_return_t status = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmStats, &infoCount);
    if (status != KERN_SUCCESS) {
        (DeveloperMode::IsEnable) ? Log("Failed to get VM statistics!", LoggerType::Critical) : DO_NOTHING;
        informationData.memoryInfo.freeMemory = 0;
    }
    uint64_t freeMemory = vm_page_size * (vmStats.free_count + vmStats.inactive_count);
    informationData.memoryInfo.freeMemory = freeMemory;
#else
    struct sysinfo info;
    if(sysinfo(&info) != 0) {
        (DeveloperMode::IsEnable) ? Log("Failed to get system info", LoggerType::Critical) : DO_NOTHING;
        informationData.memoryInfo.usedMemory = 0;
        informationData.memoryInfo.freeMemory = 0
    }
    informationData.memoryInfo.usedMemory = (info.totalram - info.freeram);
    informationData.memoryInfo.freeMemory = info.freeram;
#endif
    return informationData.memoryInfo;
}

ProductInfo SystemInformation::getProductInfo()
{
#ifdef PLATFORM_WINDOWS
    // Name
    informationData.productInfo.productName = getFromWmi("Win32_OperatingSystem", "Caption");
    // Version
    informationData.productInfo.productVersion = getFromWmi("Win32_OperatingSystem", "Version");
    // Build
    informationData.productInfo.productBuildVersion = getFromWmi("Win32_OperatingSystem", "BuildNumber");
#elif defined(PLATFORM_MAC)
    size_t len = 0;
    // Name
    const char* cmd = "sw_vers -productName";
    std::string osName = execute(cmd);
    osName.erase(std::remove(osName.begin(), osName.end(), '\n'), osName.end());
    informationData.productInfo.productName = osName;
    // Version
    const char* name = "kern.osproductversion";
    sysctlbyname(name, NULL, &len, NULL, 0);
    char* version = new char[len];
    if (sysctlbyname(name, version, &len, NULL, 0) == 0) {
        version[len - 1] = '\0'; // explicitly add a null character
        informationData.productInfo.productVersion = version;
    }
    delete[] version;
    // Build
    std::string buildVersion;
    sysctlbyname("kern.osversion", NULL, &len, NULL, 0);
    if (len > 0) {
        char* buf = new char[len];
        if (sysctlbyname("kern.osversion", buf, &len, NULL, 0) == 0) {
            buildVersion = std::string(buf, len-1);
            informationData.productInfo.productBuildVersion = buildVersion;
        }
        delete[] buf;
    }
#else
    // Name
    std::string line;
    std::string name;
    std::ifstream file("/etc/os-release");
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (line.find("PRETTY_NAME") != std::string::npos)
            {
                auto start = line.find_first_of("\"") + 1;
                auto end = line.find_last_of("\"");
                name = line.substr(start, end - start);
                break;
            }
        }
        file.close();
    }
    informationData.productInfo.productName = name;
    // Version
    std::string command_ver = "lsb_release -ds";
    std::array<char, 128> buffer_ver;
    std::string version;
    std::shared_ptr<FILE> pipeVer(popen(command_ver.c_str(), "r"), pclose);
    if (!pipeVer) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer_ver.data(), buffer_ver.size(), pipeVer.get()) != nullptr) {
        version += buffer_ver.data();
    }
    informationData.productInfo.productVersion = version;
    // Build
    std::string command_build = "uname -r";
    std::array<char, 128> buffer_build;
    std::string build;
    std::shared_ptr<FILE> pipeBuild(popen(command_build.c_str(), "r"), pclose);
    if (!pipeBuild) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer_build.data(), buffer_build.size(), pipeBuild.get()) != nullptr) {
        build += buffer_build.data();
    }
    informationData.productInfo.productBuildVersion = build;

#endif
    return informationData.productInfo;
}

CELL_NAMESPACE_END
