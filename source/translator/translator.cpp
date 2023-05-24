#if __has_include("translator.hpp")
#   include "translator.hpp"
#else
#   error "Cell's "translator.hpp" was not found!"
#endif

#if __has_include("core/json.hpp")
#   include "core/json.hpp"
#else
#   error "Cell's "core/json.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("core/config.hpp")
#   include "core/config.hpp"
#else
#   error "Cell's "core/config.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

#if __has_include("core/filesystem.hpp")
#   include "core/filesystem.hpp"
#else
#   error "Cell's "core/filesystem.hpp" was not found!"
#endif

#include <stdio.h>
#ifdef PLATFORM_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::JSon;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn::Settings;

CELL_NAMESPACE_BEGIN(Cell::Translation)

Translator::Translator()
{
    m_default_language = basic_lang;
}

Translator::~Translator()
{
}

//!TODO for better init by external devices.
bool Translator::initExternal(const std::vector<std::string>& file) __cell_noexcept
{
    bool res = false;
    try {
        for(const auto& f : file) {
            //! TODO...
        }
        m_hasError = false;
        res = true;
    } catch (std::exception& e) {
        DeveloperMode::IsEnable ? Log("Error Message " + std::string(e.what()), LoggerType::Critical) : DO_NOTHING;
        m_hasError = true;
        m_errorMessage = std::string(e.what());
        res = false;
    }
    return res;
}

bool Translator::init() __cell_noexcept
{
    bool res = false;
    auto fp = fileManager.getExecutablePath();
    for(const auto& f : getFile())
    {
        std::string file{};
        try {
            file = { std::string(fp) + translations + "/" + std::string(f) + ".json"};
            if(std::filesystem::exists(file))
            {
                //!Read from json files. [Multi based on language types].
                jsonParser.parse(file, InputType::File);
                jsonParser.setVectorJsonPtr(std::move(jsonParser.getData()));
                m_hasError = false;
                res = true;
            } else {
                DeveloperMode::IsEnable ? Log("The file [" + file + "] does not exist!", LoggerType::Critical) : DO_NOTHING;
            }
        } catch (std::exception& e) {
            Log("Error Message " + std::string(e.what()), LoggerType::Critical);
            m_hasError = true;
            m_errorMessage = std::string(e.what());
            res = false;
        }
    }
    return res;
}

bool Translator::existFile(const std::string& file) __cell_const_noexcept
{
    return std::filesystem::exists(file) ? true : false;
}

bool Translator::isMultiLanguage() __cell_const_noexcept
{
    bool ml = {false};
    if (m_multi_language)
    {
        ml = true;
    } else {
        ml = false;
    }
    return ml;
}

bool Translator::isValid() __cell_noexcept
{
    bool ret = {false};
    std::string filePath{};
    std::ifstream valid;
    valid.exceptions(std::ifstream::badbit);
    try {
#if !defined(PLATFORM_DESKTOP) && defined(PLATFORM_ANDROID)
        char buff[FILENAME_MAX];
        filePath = { std::string(GetCurrentDir(buff, FILENAME_MAX)) + translations + "/" + std::string(file)};
        std::string filePath = { "assets:/translations/" + std::string(file)};
#elif !defined(PLATFORM_DESKTOP) && defined(PLATFORM_IOS)
        //TODO...
        std::clog << "check real path for iOS from engine!\n";
        char buff[FILENAME_MAX];
        filePath = { std::string(GetCurrentDir(buff, FILENAME_MAX)) + translations + "/" + std::string(file)};
#elif defined(PLATFORM_DESKTOP)
        namespace fs = std::filesystem;
        filePath = { std::string(fs::current_path()) + translations + "/" + std::string(file)};
#else
#endif
        m_hasError = false;
        if (existFile(filePath)) {
            valid.open(filePath);
            if (!valid.is_open()) {
                m_hasError = true;
                m_errorMessage = "Could not open the file!\n";
                DeveloperMode::IsEnable ? Log("Could not open the file!", LoggerType::Failed) : DO_NOTHING;
            } else if (valid.bad()) {
                m_hasError = true;
                m_errorMessage = "Problem while reading file!\n";
                DeveloperMode::IsEnable ? Log("Problem while reading file!", LoggerType::Failed) : DO_NOTHING;
            }
        } else {
            m_hasError = true;
            m_errorMessage = "There is no file!\n";
            DeveloperMode::IsEnable ? Log("There is no file!", LoggerType::Failed) : DO_NOTHING;
        }
    } catch (const std::invalid_argument& e) {
        Log("Error " + std::string(e.what()), LoggerType::Critical);
        m_errorMessage = std::string(e.what());
        m_hasError = true;
    }
    return ret;
}

bool Translator::hasError() __cell_const_noexcept
{
    return m_hasError;
}

std::string Translator::errorMessage() __cell_const_noexcept
{
    return m_errorMessage;
}

bool Translator::hasString(const std::string& lang, const std::string& sheet, const std::string& key) __cell_const_noexcept
{
    try {
        auto const l = wordMap.at(lang).at(sheet);
        return l.find(key) != std::cend(l);
    } catch (...) {
        return false;
    }
}

LanguageList Translator::list() noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        m_list.push_back(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "name"));
    }
    return m_list;
}

bool Translator::isRtl(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.isRtl = JSON_SETTING_SEQUENCE_BOOLEAN_GET(root, CELL_LANGUAGE_SPEC, "rtl");
        }
    }
    return m_translatorData.isRtl;
}

std::string Translator::symbol(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.symbol = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code");
        }
    }
    return m_translatorData.symbol;
}

std::string Translator::currency(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.currency = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "currency");
        }
    }
    return m_translatorData.currency;
}

std::string Translator::callingCode(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.callingCode = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "calling_code");
        }
    }
    return m_translatorData.callingCode;
}

std::string Translator::callingCodeByUri(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "uri") == code) {
            m_translatorData.callingCodeByUri = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code");
        }
    }
    return m_translatorData.callingCodeByUri;
}

std::string Translator::drivingSide(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.drivingSide = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "driving_side");
        }
    }
    return m_translatorData.drivingSide;
}

std::string Translator::iso3166Code(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.iso3166Code = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "iso_3166_code");
        }
    }
    return m_translatorData.iso3166Code;
}


std::string Translator::internetTld(const std::string& code) __cell_noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        if(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code") == code) {
            m_translatorData.internetTld = JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "internet_tld");
        }
    }
    return m_translatorData.internetTld;
}

LanguageList Translator::listByCode() noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        m_translatorData.language.push_back(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code"));
    }
    return m_translatorData.language;
}

LanguageList Translator::listByTitle() noexcept
{
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items) {
        m_list_title.push_back(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "native_name"));
    }
    return m_list_title;
}

LanguageFile Translator::getFile() __cell_const_noexcept
{
    return m_translatorData.file;
}

void Translator::setFile(const LanguageFile& file) __cell_noexcept
{
    m_translatorData.file = file;
}

void Translator::wordProcess() __cell_noexcept
{
    try {
        auto items = jsonParser.getVectorJsonPtr();
        std::string_view viewStr {};
        for (const auto& it : items) {
            LanguageSheet langSheet;
#ifdef USE_BOOST
            for (const auto& [key, value] : JSON_SETTING_OBJECT_GET(it, "data")) {
                //! key values are: exceptions, global, languages, ...
                LanguageTemp temp;
                for (const auto& i : value.as_array()) {
                    try {
                        LanguageTemplate words = {
                            JSON_SETTING_STRING_GET(i,"word_key"),
                            JSON_SETTING_STRING_GET(i,"module"),
                            JSON_SETTING_STRING_GET(i,"type"),
                            JSON_SETTING_STRING_GET(i,"default_value"),
                            JSON_SETTING_STRING_GET(i,"custom_value")
                        };
                        temp.insert(LanguagePair(JSON_SETTING_STRING_GET(i, "word_key"), words));
                    } catch (const std::exception& e) {
                        Log("Error on word process!:" + FROM_CELL_STRING(e.what()), LoggerType::Failed);
                    }
                }
                langSheet[key] = std::move(temp);
            }
#else
            JSonValue object = it["data"];
            //! key values are: exceptions, global, languages, ...
            for (JSonValue::const_iterator it = object.begin(); it != object.end(); ++it) {
                const std::string& key = it.key().asString();
                const JSonValue& value = *it;
                LanguageTemp temp;
                for (const auto& i : value) {
                    try {
                        LanguageTemplate words = {
                            JSON_SETTING_STRING_GET(i,"word_key"),
                            JSON_SETTING_STRING_GET(i,"module"),
                            JSON_SETTING_STRING_GET(i,"type"),
                            JSON_SETTING_STRING_GET(i,"default_value"),
                            JSON_SETTING_STRING_GET(i,"custom_value")
                        };
                        temp.insert(LanguagePair(JSON_SETTING_STRING_GET(i, "word_key"), words));
                    } catch (const std::exception& e) {
                        Log("Error on word process!:" + FROM_CELL_STRING(e.what()), LoggerType::Failed);
                    }
                }
                langSheet[key] = std::move(temp);
            }
#endif
            wordMap[JSON_SETTING_SEQUENCE_STRING_GET(it, CELL_LANGUAGE_SPEC, "code")] = langSheet;
        }

        m_hasError = false;

    } catch (const std::range_error& e) {
        Log("Error " + std::string(e.what()), LoggerType::Critical);
        m_errorMessage = std::string(e.what());
        m_hasError = true;
    }
}

bool Translator::parse()
{
    bool res = {false};
    if (init()) {
        wordProcess();
        res = true;
        m_translatorData.parseMessage = "Parsing initialized!";
        Log("Parsing initialized!", LoggerType::Success);
    } else {
        res = false;
        m_translatorData.parseMessage = "Parse error!";
        Log("Parse error!", LoggerType::Critical);
    }
    return res;
}

bool Translator::parseExternal(const std::vector<std::string> &data) __cell_noexcept
{
    bool res = {false};
    if (initExternal(data)) {
        wordProcess();
        res = true;
        m_translatorData.parseMessage = "Parsing initialized!";
        DeveloperMode::IsEnable ? Log("Parsing initialized!", LoggerType::Success) : DO_NOTHING;
    } else {
        res = false;
        m_translatorData.parseMessage = "Parse error!";
        DeveloperMode::IsEnable ? Log("Parse error!", LoggerType::Critical) : DO_NOTHING;
    }
    return res;
}

void Translator::parseMessage() noexcept
{
    Log(m_translatorData.parseMessage, LoggerType::Info);
}

std::string Translator::defaultLanguage() __cell_const_noexcept {
    if (m_default_language.empty()) {
        return basic_lang.data();
    } else {
        return m_default_language;
    }
}

LanguageTemplate Translator::translate(const std::string& lang, const std::string& sheet, const std::string& key)
{
    if (!isMultiLanguage()) {
        try {
            return wordMap.at(defaultLanguage()).at(sheet).at(key);
            m_hasError = false;
        } catch (const std::out_of_range& e) {
            DeveloperMode::IsEnable ? Log("Error Message: [" + key + "]\t" + std::string(e.what()), LoggerType::Warning) : DO_NOTHING;
            m_errorMessage = std::string(e.what());
            m_hasError = true;
            return m_template;
        }
    } else {
        try {
            return wordMap.at(lang).at(sheet).at(key);
            m_hasError = false;
        } catch (const std::out_of_range& e) {
            m_errorMessage = std::string(e.what());
            m_hasError = true;
            DeveloperMode::IsEnable ? Log("Error Message: [" + key + "]\t" + std::string(e.what()), LoggerType::Warning) : DO_NOTHING
                return m_template;
        }
    }
}

DictonaryType Translator::data(const std::string& sheet, const ValueType valueType) __cell_noexcept
{
    DictonaryType d;
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items)
    {
#ifdef USE_BOOST
        for (const auto& [key, value] : JSON_SETTING_OBJECT_GET(root, "data"))
        {
            if(key==sheet)
            {
                switch (valueType) {
                case ValueType::Default:
                    for(const auto& arr : value.as_array())
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,"word_key"), JSON_SETTING_STRING_GET(arr ,"default_value"))));
                    }
                    break;
                case ValueType::Custom:
                    for(const auto& arr : value.as_array())
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,"word_key"), JSON_SETTING_STRING_GET(arr ,"custom_value"))));
                    }
                    break;
                }
            }
        }
#else
        JSonValue object = root["data"];
        for (JSonValue::const_iterator it = object.begin(); it != object.end(); ++it)
        {
            const std::string& key = it.key().asString();
            const JSonValue& value = *it;
            if(key==sheet)
            {
                switch (valueType) {
                case ValueType::Default:
                    for(const auto& arr : value)
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(object, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,"word_key"), JSON_SETTING_STRING_GET(arr ,"default_value"))));
                    }
                    break;
                case ValueType::Custom:
                    for(const auto& arr : value)
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(object, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,"word_key"), JSON_SETTING_STRING_GET(arr ,"custom_value"))));
                    }
                    break;
                }
            }
        }
#endif
    }
    return d;
}

DictonaryType Translator::data(const std::string& sheet, const std::string& byKey, const ValueType valueType) __cell_noexcept
{
    DictonaryType d;
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items)
    {
#ifdef USE_BOOST
        for (const auto& [key, value] : JSON_SETTING_OBJECT_GET(root, "data"))
        {
            if(key==sheet)
            {
                switch (valueType) {
                case ValueType::Default:
                    for(const auto& arr : value.as_array())
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,byKey), JSON_SETTING_STRING_GET(arr ,"default_value"))));
                    }
                    break;
                case ValueType::Custom:
                    for(const auto& arr : value.as_array())
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(root, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,byKey), JSON_SETTING_STRING_GET(arr ,"custom_value"))));
                    }
                    break;
                }
            }
        }
#else
        JSonValue object = root["data"];
        for (JSonValue::const_iterator it = object.begin(); it != object.end(); ++it)
        {
            const std::string& key = it.key().asString();
            const JSonValue& value = *it;
            if(key==sheet)
            {
                switch (valueType) {
                case ValueType::Default:
                    for(const auto& arr : value)
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(object, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,byKey), JSON_SETTING_STRING_GET(arr ,"default_value"))));
                    }
                    break;
                case ValueType::Custom:
                    for(const auto& arr : value)
                    {
                        d.insert(std::pair(JSON_SETTING_SEQUENCE_STRING_GET(object, CELL_LANGUAGE_SPEC, "code"),
                                           std::pair(JSON_SETTING_STRING_GET(arr ,byKey), JSON_SETTING_STRING_GET(arr ,"custom_value"))));
                    }
                    break;
                }
            }
        }
#endif
    }
    return d;
}

JSonValue Translator::getLanguageSpec(const std::string& code) __cell_noexcept
{
    JSonValue d;
    auto items = jsonParser.getVectorJsonPtr();
    for(const auto& root : items)
    {
#ifdef USE_BOOST

        for (const auto& [key, value] : JSON_SETTING_OBJECT_GET(root, CELL_LANGUAGE_SPEC))
        {
//            if(value.at("code").as_string() == code) {
//                if(value.at("name").as_string() == code)
//                    d = root;
//            }
        }


#else
        JSonValue object = root[CELL_LANGUAGE_SPEC];
        if(object["code"] == code)
            d = object;
#endif
    }
    return d;
}


// Definition of the createTranslatorObject function
Scope<Translator> createTranslatorObject()
{
    // Allocate memory for a Translator object using 'new'
    Translator* cellTranslatorPtr = new Translator;
    // Wrap the raw pointer in a unique_ptr and return it
    return std::unique_ptr<Translator>(cellTranslatorPtr);
}

Types::Optional<Translator> safeTranslator() __cell_noexcept
{
    return std::make_optional(Translator());
}

CELL_NAMESPACE_END
