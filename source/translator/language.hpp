/*!
 * @file        language.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Translator core.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_LANGUAGE_HPP
#define CELL_LANGUAGE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core/url.hpp")
#   include "core/url.hpp"
#else
#   error "Cell's "core/url.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Multilangual)

/*!
 * \brief The LanguageStruct class
 */
struct LanguageStruct final
{
    Types::LanguageType   get               {}; //!< LanguageType
    Types::LanguageCodes  languageSupport   {}; //!< Language support.
    Url                   url               {}; //!< Url{en-us, fa-ir}.
};

/*! Declaration of language support */
class Language {
public:
    Language();
    explicit Language(const std::string& uri);
    Language(Language const& rhs);
    ~Language();

    /*!
     * \brief set function will sets all data from translator adaptor inside the system.
     * \param data as a map [list].
     */
    void registerAll(const Types::LanguageType& data);

    /*!
     * \brief registerLanguage
     * \param code
     */
    void registerLanguage(const Types::LanguageCodes& code);

    /*!
     * \brief languageSupport
     * \returns
     */
    Types::LanguageCodes languageSupport() __cell_const_noexcept;

    /*!
     * \brief sections
     * \returns
     */
    Types::VectorSection sections() __cell_const_noexcept;

    /*!
     * \brief getLanguageCode
     * \returns
     */
    std::string getLanguageCode() __cell_const_noexcept;

    /*!
     * \brief getLanguage
     * \returns
     */
    std::string getLanguage() __cell_const_noexcept;

    /*!
     * \brief get function will returns all data.
     * \returns as map.
     */
    __cell_no_discard Types::LanguageType get() __cell_const_noexcept;

private:
    LanguageStruct* m_languageStruct;
};

CELL_NAMESPACE_END

#endif  // CELL_LANGUAGE_HPP
