#if __has_include("os.hpp")
#   include "os.hpp"
#else
#   error "Cell's "os.hpp" was not found!"
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

OsInfo::OsInfo()
{
}

OsInfo::~OsInfo()
{
}

//!Dedicated for Win32 WMI System.
#ifdef CELL_PLATFORM_WINDOWS
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

OptionalString OsInfo::getName()
{
#ifdef CELL_PLATFORM_WINDOWS
    m_productData.name = getFromWmi("Win32_OperatingSystem", "Caption");
#elif defined(CELL_PLATFORM_MAC)
    size_t len = 0;
    const char* cmd = "sw_vers -productName";
    std::string osName = execute(cmd);
    osName.erase(std::remove(osName.begin(), osName.end(), '\n'), osName.end());
    m_productData.name = osName;
#else
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
    m_productData.name = name;
#endif
    return m_productData.name;
}

OptionalString OsInfo::getVersion()
{
#ifdef CELL_PLATFORM_WINDOWS
    m_productData.version = getFromWmi("Win32_OperatingSystem", "Version");
#elif defined(CELL_PLATFORM_MAC)
    std::ostringstream command;
    command << "sw_vers -productVersion";
    m_productData.version = System::execute(command.str().c_str());
#else
    std::string command_ver = "lsb_release -ds";
    version = System::execute(command_ver.c_str());
    m_productData.version = version;
#endif
    return m_productData.version;
}

OptionalString OsInfo::getBuildNumber()
{
#ifdef CELL_PLATFORM_WINDOWS
    m_productData.build = getFromWmi("Win32_OperatingSystem", "BuildNumber");
#elif defined(CELL_PLATFORM_MAC)
    size_t len = 0;
    std::string buildVersion;
    sysctlbyname("kern.osversion", NULL, &len, NULL, 0);
    if (len > 0) {
        char* buf = new char[len];
        if (sysctlbyname("kern.osversion", buf, &len, NULL, 0) == 0) {
            buildVersion = std::string(buf, len-1);
            m_productData.build = buildVersion;
        }
        delete[] buf;
    }
#else
    std::string command_build = "uname -r";
    m_productData.build = System::execute(command_build.c_str());
#endif
    return m_productData.build;
}

OptionalString OsInfo::getHostName()
{
#ifdef CELL_PLATFORM_WINDOWS
    WSADATA wsa_data;
    int error = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (error != 0) {
        (DeveloperMode::IsEnable) ? Log("Failed to initialize Windows Sockets!", LoggerType::Critical) : DO_NOTHING;
        m_productData.hostname = "unknown";
    }
    char hostname[NI_MAXHOST];
    if (gethostname(hostname, NI_MAXHOST) == 0) {
        m_productData.hostname = hostname;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get hostname!", LoggerType::Critical) : DO_NOTHING;
        m_productData.hostname = "unknown";
    }
    WSACleanup();
#else
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        m_productData.hostname = hostname;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get hostname!", LoggerType::Critical) : DO_NOTHING;
        m_productData.hostname = "unknown";
    }
#endif
    return m_productData.hostname;
}

OptionalString OsInfo::getKernelName()
{
#ifdef CELL_PLATFORM_WINDOWS
    OSVERSIONINFOEX info;
    info.dwOSVersionInfoSize = sizeof(info);
    if (GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&info))) {
        m_productData.kernel = "Windows NT";
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel name", LoggerType::Critical) : DO_NOTHING;
        m_productData.kernel = "Unknown";
    }
#elif defined(CELL_PLATFORM_MAC)
    int name[] = {CTL_KERN, KERN_OSTYPE};
    char kernel_name[128];
    size_t length = sizeof(kernel_name);
    if (sysctl(name, 2, kernel_name, &length, NULL, 0) == 0) {
        m_productData.kernel = kernel_name;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel name", LoggerType::Critical) : DO_NOTHING;
        m_productData.kernel = "Unknown";
    }
#else
    std::string kernel_name;
    struct utsname uts;
    if(uname(&uts) == -1) {
        return 1;
    }
    kernel_name = uts.sysname;
    m_productData.kernel = kernel_name;
#endif
    return m_productData.kernel;
}

OptionalString OsInfo::getKernelVersion()
{
#ifdef CELL_PLATFORM_WINDOWS
    OSVERSIONINFOEX info;
    info.dwOSVersionInfoSize = sizeof(info);
    if (GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&info))) {
        // Extract the kernel version from the OS version information
        std::string kernelVersion = std::to_string(info.dwMajorVersion) + "." + std::to_string(info.dwMinorVersion);
        m_productData.kernelVer = kernelVersion;
    } else {
        // Handle the failure to retrieve the version information
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel version", LoggerType::Critical) : DO_NOTHING;
        m_productData.kernelVer = "Unknown";
    }
#elif defined(CELL_PLATFORM_MAC)
    int name[] = {CTL_KERN, KERN_OSRELEASE};
    char version[128];
    size_t length = sizeof(version);
    if (sysctl(name, 2, version, &length, NULL, 0) == 0) {
        m_productData.kernelVer = version;
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get kernel version", LoggerType::Critical) : DO_NOTHING;
        m_productData.kernelVer = "Unknown";
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
    m_productData.kernelVer = kernel_ver;
#endif
    return m_productData.kernelVer;
}

OptionalString OsInfo::getUserName()
{
#ifdef CELL_PLATFORM_WINDOWS
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserNameA(username, &username_len)) {
        m_productData.username.emplace(username);
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get username!", LoggerType::Critical) : DO_NOTHING;
        m_productData.username.emplace("unknown");
    }
#else
    char *username = getlogin();
    if (username != NULL) {
        m_productData.username.emplace(username);
    } else {
        (DeveloperMode::IsEnable) ? Log("Failed to get username!", LoggerType::Critical) : DO_NOTHING;
        m_productData.username.emplace("unknown");
    }
#endif
    return m_productData.username;

}

OptionalString OsInfo::getDeveloper()
{
    std::string registeredSymbol = CELL_PLATFORM_DEVELOPER;
    if (!registeredSymbol.empty()) {
        return std::make_optional(registeredSymbol);
    }
    return std::nullopt;
}

OptionalString OsInfo::getReleaseDate()
{
    // Todo...
    return std::nullopt;
}

OptionalString OsInfo::getArchitecture()
{
    std::string arch { CELL_ARCHITECTURE };
    if(!arch.empty()) {
        return arch;
    }
    return std::nullopt;
}


CELL_NAMESPACE_END
