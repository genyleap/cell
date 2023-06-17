#if __has_include("url.hpp")
#   include "url.hpp"
#else
#   error "Cell's "url.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;

CELL_NAMESPACE_BEGIN(Cell)

Domain::Domain(const std::string& url)
{
    // Find the position of the scheme (i.e., "http", "https", etc.) in the URL.
    std::string::size_type pos = url.find("://");

    // If the scheme is found, extract it and update the position to after the "://" characters.
    if (pos != std::string::npos) {
        urlStructure.scheme = url.substr(__cell_zero, pos);
        pos += 3;
    } else { // Otherwise, the scheme is assumed to be empty and the position is set to the beginning of the URL.
        pos = __cell_zero;
    }

    // Find the next occurrence of the "/" character after the scheme (if any) to determine the domain.
    std::string::size_type next = url.find("/", pos);

    // If a slash is found, extract the domain.
    if (next != std::string::npos) {
        auto level = url.substr(pos, next - pos);
        urlStructure.subdomain      = level;
        urlStructure.secondLevel    = level;
        urlStructure.topLevel       = level;

    } else { // Otherwise, the domain is the remaining part of the URL after the scheme (if any).
        urlStructure.subdomain      = url.substr(pos);
        urlStructure.secondLevel    = url.substr(pos);
        urlStructure.topLevel       = url.substr(pos);
    }
}

std::string Domain::getRawSLD() const
{
    std::string::size_type last_dot = urlStructure.secondLevel.value().rfind(".");
    if (last_dot == std::string::npos) {
        return urlStructure.secondLevel.value();
    }
    std::string::size_type second_last_dot = urlStructure.secondLevel.value().rfind(".", last_dot - 1);
    if (second_last_dot == std::string::npos) {
        return urlStructure.secondLevel.value().substr(__cell_zero, last_dot);
    }
    return urlStructure.secondLevel.value().substr(second_last_dot + 1, last_dot - second_last_dot - 1);
}

std::string Domain::getSLD() const
{
    std::string::size_type pos = urlStructure.secondLevel.value().rfind(".");
    if (pos != std::string::npos && pos > __cell_zero) {
        std::string::size_type sld_pos = urlStructure.secondLevel.value().rfind(".", pos - 1);
        if (sld_pos != std::string::npos) {
            return urlStructure.secondLevel.value().substr(sld_pos + 1);
        }
    }
    return urlStructure.secondLevel.value();
}

std::string Domain::getSubdomain() const
{
    std::string subdomain;
    std::string::size_type pos = __cell_zero;
    std::string::size_type next = urlStructure.subdomain.value().find(".");
    if (next != std::string::npos && next > __cell_zero) {
        subdomain = urlStructure.subdomain.value().substr(pos, next - pos);
    }
    return subdomain;
}

std::string Domain::getTLD() const
{
    std::string::size_type pos = urlStructure.topLevel.value().find_last_of(".");
    if (pos != std::string::npos && pos > __cell_zero && pos < urlStructure.topLevel.value().size() - 1) {
        return urlStructure.topLevel.value().substr(pos + 1);
    }
    return "";
}

std::string Domain::getProtocolAndDomain() const
{
    return urlStructure.scheme.value() + "://" + urlStructure.secondLevel.value();
}

std::string Domain::getProtocol()
{
    return urlStructure.scheme.value();
}

Domain::~Domain()
{
}

/*!
 * \brief Constructs url class.
 */
Url::Url()
{
    __cell_safe_instance(m_urlStructure, UrlStructure);
    __cell_safe_instance(m_languageUrl, LanguageUrl);
}

Url::Url(const std::string& uri)
{
    __cell_safe_instance(m_urlStructure, UrlStructure);
    __cell_safe_instance(m_languageUrl, LanguageUrl);

    if(!m_languageUrl->uri.has_value())
    {
        m_languageUrl->uri = uri;
    }
}

/*!
 * \brief Destroys the url class.
 */
Url::~Url()
{
    __cell_safe_delete(m_urlStructure);
    __cell_safe_delete(m_languageUrl);
}

void Url::registerUrl(const UrlStructure& urlStructure) __cell_const_noexcept
{
    {
        m_urlStructure->scheme          =   urlStructure.scheme;
        m_urlStructure->subdomain       =   urlStructure.subdomain;
        m_urlStructure->secondLevel     =   urlStructure.secondLevel;
        m_urlStructure->topLevel        =   urlStructure.topLevel;
        m_urlStructure->subdirectory    =   urlStructure.subdirectory;
    }
}

UrlStructure Url::getAsStructure() __cell_const_noexcept
{
    return *m_urlStructure;
}

OptionalString Url::getAsUrl() __cell_const_noexcept
{
    std::string url {};
    if(!m_languageUrl->uri.has_value())
    {
        url.append(m_urlStructure->scheme.value());
        url.append(m_urlStructure->subdomain.value());
        url.append(m_urlStructure->secondLevel.value());
        url.append(m_urlStructure->topLevel.value());
        url.append(m_urlStructure->subdirectory.value());
    }
    return url;
}

void Url::setLanguageUri(const std::string& uri) __cell_const_noexcept
{
    if(!m_languageUrl->uri.has_value())
    {
        m_languageUrl->uri = uri;
    }
}

OptionalString Url::getLanguageUri() __cell_const_noexcept
{
    if (m_languageUrl->uri.has_value()) {
        return m_languageUrl->uri.value();
    } else {
        return std::nullopt;
    }
}

void Url::openURL(const std::string& url)
{
#ifdef PLATFORM_WINDOWS
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
#elif defined(PLATFORM_MAC)
    std::string openCommand = "open " + url;
    System::command(openCommand.c_str());
#elif defined(PLATFORM_LINUX)
    std::string openCommand = "xdg-open " + url;
    System::command(openCommand.c_str());
#else
    // Code for other platforms or error handling
#endif
}

bool Url::isBrowserAvailable()
{
#ifdef PLATFORM_WINDOWS
    HKEY hKey;
    LONG result = RegOpenKeyExA(HKEY_CLASSES_ROOT, "http\\shell\\open\\command", 0, KEY_QUERY_VALUE, &hKey);
    RegCloseKey(hKey);
    return (result == ERROR_SUCCESS);
#elif defined(PLATFORM_MAC)
    return System::command("which open");
#elif defined(PLATFORM_LINUX)
    return System::command("which xdg-open");
#else \
    // Code for other platforms or error handling
    return false;
#endif
}

CELL_NAMESPACE_END
