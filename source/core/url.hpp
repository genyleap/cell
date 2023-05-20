/*!
 * Gen3 License
 *
 * @file        url.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_URL_HPP
#define CELL_URL_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The UrlStructure class
 */
struct UrlStructure
{
    Types::OptionalString scheme       {}; //!< The scheme tells web servers which protocol to use when it accesses a page on your website.
    Types::OptionalString subdomain    {}; //!< A subdomain in a URL indicates which particular page of your website the web browser should serve up.
    Types::OptionalString secondLevel  {}; //!< Your second-level domain (SLD) is the name of your website.
    Types::OptionalString topLevel     {}; //!< The top-level domain (TLD) specifies what type of entity your organization registers as on the internet.
    Types::OptionalString subdirectory {}; //!< A subdirectory — also known as a subfolder — helps people as well as web crawlers understand which particular section of a webpage they’re on.
};

/**
 * @brief The Domain class
 * Represents a domain and provides methods for extracting its components.
 */
class __cell_export Domain {
public:
    Domain(const std::string& url);
    ~Domain();

    /**
     * @brief Returns the raw second-level domain (SLD) of the domain.
     * @return A string representing the raw SLD of the domain.
     */
    std::string getRawSLD() const;

    /**
     * @brief Returns the second-level domain (SLD) of the domain.
     * @return A string representing the SLD of the domain.
     */
    std::string getSLD() const;

    /**
     * @brief Returns the top-level domain (TLD) of the domain.
     * @return A string representing the TLD of the domain.
     */
    std::string getTLD() const;

    /**
     * @brief Returns a string of subdomain.
     * @return A string value.
     */
    std::string getSubdomain() const;

    /**
     * @brief Returns the protocol and domain of the URL.
     * @return A string representing the protocol and domain of the URL.
     */
    std::string getProtocolAndDomain() const;

    /**
     * @brief Returns the protocol of the URL.
     * @return A string representing the protocol of the URL.
     */
    std::string getProtocol();

private:
    UrlStructure urlStructure {};
};


/*!
 * \brief The LanguageUrl class
 */
struct LanguageUrl
{
    Types::OptionalString uri {};  //!< Uri for language [https://localhost/{language-uri}=en-us, fa-ir]
};

/*!
 * \brief The Url class
 */
class __cell_export Url
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Url)
    Url(const std::string& uri);
    /*!
     * \brief registerTag function will sets data in tag list.
     * \param urlStructure is a type of UrlStructure.
     */
    void registerUrl(const UrlStructure& urlStructure) __cell_const_noexcept;

    /*!
     * \brief getAsStructure will gets url by seprated sections.
     * \returns url as UrlStructure.
     */
    UrlStructure getAsStructure() __cell_const_noexcept;

    /*!
     * \brief getAsUrl function will gets url as full string.
     * \returns as string.
     */
    Types::OptionalString getAsUrl() __cell_const_noexcept;

    /*!
     * \brief setLanguageUri function will sets a string for language.
     * \param uri as string.
     */
    void setLanguageUri(const std::string& uri) __cell_const_noexcept;

    /*!
     * \brief getLanguageUri function will gets language based on url.
     * \returns as string.
     */
    Types::OptionalString getLanguageUri() __cell_const_noexcept;

protected:
    LanguageUrl* m_languageUrl{};

private:
    CELL_DISABLE_COPY(Url)
    UrlStructure* m_urlStructure{};
};

CELL_NAMESPACE_END

#endif  // CELL_URL_HPP
