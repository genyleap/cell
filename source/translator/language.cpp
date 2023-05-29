#if __has_include("language.hpp")
#   include "language.hpp"
#else
#   error "Cell's "language.hpp" was not found!"
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


CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Abstracts;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn::Settings;

CELL_NAMESPACE_BEGIN(Cell::Multilangual)

Language::Language(const Language& rhs) : m_languageStruct(rhs.m_languageStruct)
{
    Scope<Configuration> config(new Configuration(ConfigType::File));
    config->init(SectionType::Translations); //!System core for language.
    __cell_safe_instance(m_languageStruct, LanguageStruct);
    auto lcodes = LanguageCodes{}; //!Language codes.
    std::vector<JSonValue> v;
    std::string lstr {""};
    bool lstatus {false};
    if(config->Setting().getValueMulti(CELL_LANGS, v))
    {
        for(const auto& c : v)
        {
            lstatus = safeEngine()->get()->meta()->returnJsonAt(c,"status").asBool;
            if(lstatus == true) {
                lstr = safeEngine()->get()->meta()->returnJsonAt(c, std::string("l")).asString;
                lcodes.push_back(lstr.substr(0, 5));
            }
        }
    }
    //!Register language code.
    registerLanguage(lcodes); //!Language register method.
}

std::string_view getSubstring(const std::string_view str, int startIndex, int length) {
    return str.substr(startIndex, length);
}


Language::Language()
{
    Scope<Configuration> config(new Configuration(ConfigType::File));
    config->init(SectionType::Translations); //!System core for language.
    __cell_safe_instance(m_languageStruct, LanguageStruct);
    auto lcodes = LanguageCodes{}; //!Language codes.
    std::vector<JSonValue> v;
    std::string lstr {""};
    bool lstatus {false};
    if(config->Setting().getValueMulti(CELL_LANGS, v))
    {
        for(const auto& c : v)
        {
            lstatus = safeEngine()->get()->meta()->returnJsonAt(c,"status").asBool;
            if(lstatus == true) {
                lstr = safeEngine()->get()->meta()->returnJsonAt(c, std::string("l")).asString;
                lcodes.push_back(lstr.substr(0, 5));
            }
        }
    }
    //!Register language code.
    registerLanguage(lcodes); //!Language register method.
}

/*! Implementation of language support */
Language::Language(const std::string& uri)
{
    __cell_safe_instance(m_languageStruct, LanguageStruct);
    m_languageStruct->url.setLanguageUri(uri);
    Scope<Configuration> config(new Configuration(ConfigType::File));
    config->init(SectionType::Translations); //!System core for language.
    auto lcodes = LanguageCodes{}; //!Language codes.
    std::vector<JSonValue> v;
    std::string_view viewStr {};

    if(config->Setting().getValueMulti(CELL_LANGS, v))
    {
        for(const auto& c : v)
        {
            viewStr = safeEngine()->get()->meta()->returnJsonAt(c, "l").asString;
            lcodes.push_back(viewStr.substr(0, 5).data());
        }
    }
    //!Register language code.
    registerLanguage(lcodes); //!Language register method.
}

Language::~Language()
{
    __cell_safe_delete(m_languageStruct);
}


void Language::registerAll(const LanguageType& data)
{
    m_languageStruct->get = data;
}

LanguageType Language::get() __cell_const_noexcept
{
    return m_languageStruct->get;
}

void Language::registerLanguage(const Types::LanguageCodes& code)
{
    m_languageStruct->languageSupport = code;
}

LanguageCodes Language::languageSupport() __cell_const_noexcept
{
    return m_languageStruct->languageSupport;
}

std::string Language::getLanguageCode() __cell_const_noexcept
{
    Scope<Configuration> config(new Configuration(ConfigType::File));
    config->init(SectionType::Translations);
    String path = { m_languageStruct->url.getLanguageUri().value_or("en-us") }; //!->/{language}/uri/
    std::string lcode{};
    std::vector<JSonValue> v;
    JSonValue jvalue;
    std::string_view viewUri, viewCode, viewName {};
    bool viewStatus {false};
    std::string_view default_lang;
    if(config->Setting().getValue(CELL_DEFAULT_LANG, jvalue))
    {
        default_lang = safeEngine()->get()->meta()->returnJsonAt(jvalue).asString;
    }
    if(config->Setting().getValueMulti(CELL_LANGS, v))
    {
        for(const auto& c : v)
        {
            viewUri     =   safeEngine()->get()->meta()->returnJsonAt(c, "uri").asString;
            viewName    =   safeEngine()->get()->meta()->returnJsonAt(c, "code").asString;
            viewCode    =   safeEngine()->get()->meta()->returnJsonAt(c, "l").asString;
            viewStatus  =   safeEngine()->get()->meta()->returnJsonAt(c, "status").asBool; //! Status of language.

            if(viewStatus) // Return only enabled languages.
            {
                if(viewUri == path.substr(1, 5)) {
                    lcode = viewUri.substr(0,5);
                } else {
                    if(viewName == default_lang) { lcode = viewCode.substr(0,5);}
                }
            }
        }
    }
    return lcode;
}

std::string Language::getLanguage() __cell_const_noexcept
{
    Scope<Configuration> config(new Configuration(ConfigType::File));
    config->init(SectionType::Translations);
    String path = { m_languageStruct->url.getLanguageUri().value_or("en-us") }; //!->/{language}/uri/
    std::string lcode{};

    std::vector<JSonValue> v;
    JSonValue jvalue;
    std::string_view viewUri, viewCode, viewName {};
    std::string_view default_lang;
    if(config->Setting().getValue(CELL_DEFAULT_LANG, jvalue))
    {
        default_lang = safeEngine()->get()->meta()->returnJsonAt(jvalue).asString;
    }
    if(config->Setting().getValueMulti(CELL_LANGS, v))
    {
        for(const auto& c : v)
        {
            viewUri  = safeEngine()->get()->meta()->returnJsonAt(c, "uri").asString;
            viewName = safeEngine()->get()->meta()->returnJsonAt(c, "code").asString;
            viewCode = safeEngine()->get()->meta()->returnJsonAt(c, "l").asString;

            if(viewUri == path.substr(1, 5)) {
                lcode = viewUri.substr(0,5);
            } else {
                if(viewName == default_lang) { lcode = viewName;}
            }
        }
    }

    return lcode;
}

CELL_NAMESPACE_END
