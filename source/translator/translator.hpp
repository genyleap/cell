/*!
 * @file        translator.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Translator core.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
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

enum class ReadType
{
    FileOnDisk,
    Database,
    Memory
};

struct TRANSLATOR_CONSTANTS final
{
    __cell_static_const_constexpr std::string_view LANGUAGE_SPEC  {"language-spec"};
    __cell_static_const_constexpr std::string_view CODE           {"code"};
    __cell_static_const_constexpr std::string_view DATA_VIEW      {"data"};
    __cell_static_const_constexpr std::string_view DEFAULT_VALUE  {"default_value"};
    __cell_static_const_constexpr std::string_view COSTUM_VALUE   {"custom_value"};
    __cell_static_const_constexpr std::string_view WORD_KEY       {"word_key"};
    __cell_static_const_constexpr std::string_view TYPE           {"type"};
    __cell_static_const_constexpr std::string_view MODULE         {"module"};

    //! FILE SUFFIX
    __cell_static_const_constexpr std::string_view FILE_SUFFIX    {".json"};
};

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

/**
 * @brief The ValueType enum
 */
enum class ValueType : Types::u8
{
    Default, Custom
};

/*!
 * \brief The Translator class
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Translator
{
public:
    Translator();
    ~Translator();

    /**
     * @brief Initializes the Translator.
     * @return true if initialization is successful, false otherwise.
     */
    __cell_no_discard bool init(ReadType readType) __cell_noexcept;

    /**
     * @brief Initializes the Translator with external files.
     * @param files A vector of file paths.
     * @return true if initialization is successful, false otherwise.
     */
    __cell_no_discard bool initExternal(const std::vector<std::string>& files) __cell_noexcept;

    /**
     * @brief Constant variable for translations key.
     */
    __cell_static_constexpr auto translations = "translations";

    /** @var file
     *  @brief System Language.
     */
    __cell_inline_static_constexpr std::string_view file = "en_US.json";

    /**
     * @brief Basic language.
     */
    __cell_inline_static std::string_view basic_lang = {"en_US"};

    /**
     * @brief Checks if a file exists.
     * @param file The file to check.
     * @returns true if the file exists, false otherwise.
     */
    __cell_no_discard bool existFile(const std::string& file) __cell_const_noexcept;

    /**
     * @brief Checks if the system supports multi-language.
     * @returns true if the system supports multi-language, false otherwise.
     */
    __cell_no_discard bool isMultiLanguage() __cell_const_noexcept;

    /**
     * @brief Checks if the JSON format is valid.
     * @returns true if the JSON format is valid, false otherwise.
     */
    __cell_no_discard bool isValid() __cell_noexcept;

    /**
     * @brief Checks if there is any error from the JSON structure.
     * @returns true if there is an error, false otherwise.
     */
    __cell_no_discard bool hasError() __cell_const_noexcept;

    /**
     * @brief Gets the default language.
     * @return The default language.
     */
    std::string defaultLanguage() __cell_const_noexcept;

    /**
     * @brief Gets the error message.
     * @return The error message.
     */
    __cell_no_discard std::string errorMessage() __cell_const_noexcept;

    /**
     * @brief Checks if a language string exists in the specified sheet and key.
     * @param lang The language code.
     * @param sheet The sheet name.
     * @param key The key in the sheet.
     * @returns true if the string exists, false otherwise.
     */
    __cell_no_discard bool hasString(const std::string& lang,
                                     const std::string& sheet,
                                     const std::string& key) __cell_const_noexcept;

    /**
     * @brief Gets a list of all language names.
     * @return A list of language names.
     */
    __cell_no_discard LanguageList list() __cell_noexcept;

    /**
     * @brief Gets a list of all language names by their language code.
     * @return A list of language names.
     */
    __cell_no_discard LanguageList listByCode() __cell_noexcept;

    /**
     * @brief Checks if a language is written right-to-left.
     * @param code The language code.
     * @return true if the language is right-to-left, false otherwise.
     */
    __cell_no_discard bool isRtl(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the symbol for the specified code.
     * @param code The code.
     * @return The symbol.
     */
    __cell_no_discard std::string symbol(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the currency for the specified code.
     * @param code The code.
     * @return The currency.
     */
    __cell_no_discard std::string currency(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the calling code for the specified code.
     * @param code The code.
     * @return The calling code.
     */
    __cell_no_discard std::string callingCode(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the calling code for the specified code by URI.
     * @param code The code.
     * @return The calling code.
     */
    __cell_no_discard std::string callingCodeByUri(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the driving side for the specified code.
     * @param code The code.
     * @return The driving side.
     */
    __cell_no_discard std::string drivingSide(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the ISO 3166 code for the specified code.
     * @param code The code.
     * @return The ISO 3166 code.
     */
    __cell_no_discard std::string iso3166Code(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets the internet TLD (Top Level Domain) for the specified code.
     * @param code The code.
     * @return The internet TLD.
     */
    __cell_no_discard std::string internetTld(const std::string& code) __cell_noexcept;

    /**
     * @brief Gets a list of all language names by their native name.
     * @return A list of language names.
     */
    __cell_no_discard LanguageList listByTitle() __cell_noexcept;

    /**
     * @brief Gets the file information containing the filename and path.
     * @return The file information.
     */
    __cell_no_discard LanguageFile getFile() __cell_const_noexcept;

    /**
     * @brief Sets the file to be parsed.
     * @param file The file information.
     */
    void setFile(const LanguageFile& file) __cell_noexcept;

    /**
     * @brief Processes the parsing of words inside the JSON file structure.
     */
    void wordProcess() noexcept;

    /**
     * @brief Parses the JSON file.
     * @return true if parsing is successful, false otherwise.
     */
    __cell_no_discard bool parse();

    /**
     * @brief Parses the JSON file from external data.
     * @param data A vector of data strings.
     * @return true if parsing is successful, false otherwise.
     */
    __cell_no_discard bool parseExternal(const std::vector<std::string>& data) __cell_noexcept;

    /**
     * @brief Prints the message of the parsing status.
     */
    void parseMessage() noexcept;

    /**
     * @brief Translates data based on the selected sheet, key, and language.
     * @param lang The language code.
     * @param sheet The sheet name.
     * @param key The key in the sheet.
     * @return The translated data.
     */
    __cell_no_discard LanguageTemplate translate(const std::string& lang, const std::string& sheet, const std::string& key);

    /**
     * @brief Gets all language data from one sheet.
     * @param sheet The sheet name.
     * @param valueType The type of existing value.
     * @return The collection of data from the sheet.
     */
    __cell_no_discard DictonaryType data(const std::string& sheet, const ValueType valueType = ValueType::Default) __cell_noexcept;

    /**
     * @brief Gets all language data from one sheet by key.
     * @param sheet The sheet name.
     * @param byKey The key type of variable.
     * @param valueType The type of existing value.
     * @return The collection of data from the sheet.
     */
    __cell_no_discard DictonaryType data(const std::string& sheet, const std::string& byKey, const ValueType valueType = ValueType::Default) __cell_noexcept;

    /**
     * @brief Gets the language specification data from the language file.
     * @param code The language code.
     * @return The language specification data.
     */
    __cell_no_discard JSonValue getLanguageSpec(const std::string& code) __cell_noexcept;

protected:
    JSon::JsonDocument jsonParser                   {};                  //!< JsonManager class.
    LanguageMap wordMap                             {};                  //!< Language map.

    LanguageList m_list                             {};                  //!< List of languages.
    LanguageList m_list_title                       {};                  //!< List of languages by their title.
    bool m_multi_language =                         {true};              //!< Multi-language state.
    bool m_hasError                                 {};                  //!< Error state.
    std::string m_errorMessage =                    {__cell_null_str};   //!< Error message.
    DicType m_data                                  {};                  //!< All data from language.
    LanguageTemplate m_template                     {};                  //!< Language template.
    std::string m_default_language                  {};                  //!< Default language.
    std::string m_current_language                  {};                  //!< Current language.

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
