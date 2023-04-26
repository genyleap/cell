#ifdef __has_include
# if __has_include("url.hpp")
#   include "url.hpp"
#else
#   error "Cell's "url.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_USING_NAMESPACE Cell::System;

CELL_NAMESPACE_BEGIN(Cell)

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

    if(!isset(m_languageUrl->uri.has_value()))
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
    if(!isset(m_languageUrl->uri.has_value()))
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
    if(!isset(m_languageUrl->uri.has_value()))
    {
        m_languageUrl->uri = uri;
    }
}

OptionalString Url::getLanguageUri() __cell_const_noexcept
{
    if (isset(m_languageUrl->uri.value())) {
        return m_languageUrl->uri.value();
    } else {
        return std::nullopt;
    }
}

CELL_NAMESPACE_END
