/*!
 * @file        translator.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Translator core.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_TRANSLATOR_HPP
#define CELL_TRANSLATOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core/json.hpp")
#   include "core/json.hpp"
#else
#   error "Cell's "core/json.hpp" was not found!"
#endif

#if __has_include("dictionary.hpp")
#   include "dictionary.hpp"
#else
#   error "Cell's "dictionary.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Translation)

class LanguageTemplate;

using JSonPointer = std::unique_ptr<Cell::JSon::JsonManager>;

using LanguageList = std::vector<std::string>;

using LanguageFile = std::vector<std::string>;

using LSMap = Types::Map<std::string, Types::Map<std::string, LanguageTemplate>>;

using LanguageMap = Types::Map<std::string, LSMap>;

using MForLanguageTemplate = Types::Map<std::string, LanguageTemplate>;

using LanguageSheet = Types::Map<std::string, MForLanguageTemplate>;

using LanguagePair = Types::Pair<std::string, LanguageTemplate>;

using LanguageTemp = Types::Map<std::string, LanguageTemplate>;

/*!
 * \brief The TranslatorData class
 */
struct TranslatorData final
{
    LanguageFile      file             {};  //!< File.
    std::string       parseMessage     {};  //!< Message for parsing.
    LanguageList      language         {};  //!< Language.
    bool              isRtl            {};  //!< Is Right to left?
    std::string       symbol           {};  //!< Symbol.
    std::string       currency         {};  //!< Currency.
    std::string       callingCode      {};  //!< Calling code.
    std::string       callingCodeByUri {};  //!< Calling code by url.
    std::string       drivingSide      {};  //!< Driving side.
    std::string       iso3166Code      {};  //!< Iso3166 code.
    std::string       internetTld      {};  //!< Internal TLD.
};

/*!
 * \brief The Translator class
 */
class __cell_export Translator
{
public:
    Translator();
    ~Translator();

    /*!
     * \brief init
     * \return
     */
    __cell_no_discard bool init() __cell_noexcept;

    /*!
     * \brief initExternal
     * \param file
     * \return
     */
    __cell_no_discard bool initExternal(const std::vector<std::string>& file) __cell_noexcept;

    /*!
     * \brief translations
     */
    __cell_static_constexpr auto translations = "translations";

    /** @var string System Language */
    __cell_inline_static_constexpr std::string_view file = "en_US.json";

    __cell_inline_static std::string_view basic_lang = {"en_US"};

    /*!
     * \brief existFile checks file.
     * \param file
     * \returns true if file exists.
     */
    __cell_no_discard bool existFile(const std::string& file) __cell_const_noexcept;

    /*!
     * \brief isMultiLanguage
     * \returns true if system supports multi language.
     */
    __cell_no_discard bool isMultiLanguage() __cell_const_noexcept;
    /*!
     * \brief isValid checks json file!
     * \returns true if json format is valid.
     */
    __cell_no_discard bool isValid() __cell_noexcept;

    /*!
     * \brief hasError checks any error from json structure.
     * \returns true if error exists.
     */
    __cell_no_discard bool hasError() __cell_const_noexcept;

    /*!
     * \brief defaultLanguage
     * \return
     */
    std::string defaultLanguage() __cell_const_noexcept;

    /*!
     * \brief errorMessage
     * \return
     */
    __cell_no_discard std::string errorMessage() __cell_const_noexcept;

    /*!
     * \brief Language::hasString checks for the existence of [shee][lang][key].
     * \param sheet name of your selected sheet.
     * \param lang code of the language structure. e.g: en_US, or fa_IR.
     * \param key word_key of the `myword` structure. e.g: error, warning.
     * \returns true value if correct.
     */
    __cell_no_discard bool hasString(const std::string& lang,
                                     const std::string& sheet,
                                     const std::string& key) __cell_const_noexcept;
    /*!
     * \brief list gets all language name.
     * \returns list of language by name.
     */
    __cell_no_discard LanguageList list() __cell_noexcept;

    /*!
     * \brief listByCode
     * \return
     */
    __cell_no_discard LanguageList listByCode() __cell_noexcept;

    /*!
     * \brief isRtl
     * \return
     */
    __cell_no_discard bool isRtl(const std::string& code) __cell_noexcept;

    /*!
     * \brief symbol
     * \param code
     * \return
     */
    __cell_no_discard std::string symbol(const std::string& code) __cell_noexcept;

    /*!
     * \brief currency
     * \param code
     * \return
     */
    __cell_no_discard std::string currency(const std::string& code) __cell_noexcept;

    /*!
     * \brief callingCode
     * \param code
     * \return
     */
    __cell_no_discard std::string callingCode(const std::string& code) __cell_noexcept;

    /*!
     * \brief callingCodeByUri
     * \param code
     * \return
     */
    __cell_no_discard std::string callingCodeByUri(const std::string& code) __cell_noexcept;

    /*!
     * \brief drivingSide
     * \param code
     * \return
     */
    __cell_no_discard std::string drivingSide(const std::string& code) __cell_noexcept;

    /*!
     * \brief iso3166Code
     * \param code
     * \return
     */
    __cell_no_discard std::string iso3166Code(const std::string& code) __cell_noexcept;

    /*!
     * \brief internetTld
     * \param code
     * \return
     */
    __cell_no_discard std::string internetTld(const std::string& code) __cell_noexcept;

    /*!
     * \brief listByTitle gets all language by native name.
     * \returns title by native name as string.
     */
    __cell_no_discard LanguageList listByTitle() __cell_noexcept;

    /*!
     * \brief getFile function contains the filename and path.
     * \returns string for filename.
     */
    __cell_no_discard LanguageFile getFile() __cell_const_noexcept;

    /*!
     * \brief setFile function sets file to parsing.
     * \param file as string path and name.
     */
    void setFile(const LanguageFile& file) __cell_noexcept;

    /*!
     * \brief wordProcess function process the parsing of words inside json file
     * structure.
     */
    void wordProcess() noexcept;

    /*!
     * \brief parse function will parse the JSON file.
     */
    __cell_no_discard bool parse() __cell_noexcept;

    /*!
     * \brief parseExternal function is suitable for external device structure such as mobile android and ios storage.
     * \param data gets data list.
     * \return as bool.
     */
    __cell_no_discard bool parseExternal(const std::vector<std::string>& data) __cell_noexcept;

    /*!
     * \brief parseMessage function prints message of parsing status.
     */
    void parseMessage() noexcept;

    /*!
     * \brief translate function will translate data based on selected sheet, key and language.
     * \param lang is data based on language file.
     * \param sheet is sheet name.
     * \param key is sheet key.
     * \return as translated data.
     */
    __cell_no_discard LanguageTemplate translate(const std::string& lang, const std::string& sheet, const std::string& key);

    /*!
     * \brief data function will gets all language data from one sheet.
     * \param sheet is sheet name.
     * \return collection of one sheet.
     */
    __cell_no_discard DictonaryType data(const std::string& sheet) __cell_noexcept;

protected:
    JSon::JsonManager jsonParser            {};                 //!< JsonManager class.
    LanguageMap       wordMap               {};                 //!< Language map.

    LanguageList      m_list                {};                 //!< List of languages.
    LanguageList      m_list_title          {};                 //!< List of languages by their title.
    bool              m_multi_language =    {true};             //!< Multi language state.
    bool              m_hasError            {};                 //!< Error state.
    std::string       m_errorMessage =      {__cell_null_str};  //!< Error Message.
    DicType           m_data                {};                 //!< All data from language.
    LanguageTemplate  m_template            {};                 //!< Language template.
    std::string       m_default_language    {};                 //!< Default language.
    std::string       m_current_language    {};                 //!< Current language.

private:
    TranslatorData m_translatorData {};
    FileSystem::FileManager fileManager {};
};

__cell_no_discard_message("Pay attention! This version of the translator is safe and has a return value!")
    Types::Optional<Translator> safeTranslator() __cell_noexcept;

//! Function that creates and returns a unique_ptr to Translator.
Scope<Translator> createTranslatorObject();

CELL_NAMESPACE_END

#endif // CELL_TRANSLATOR_HPP
