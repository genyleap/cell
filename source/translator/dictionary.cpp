#if __has_include("dictionary.hpp")
#   include "dictionary.hpp"
#else
#   error "Cell's "dictionary.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Translation)

LanguageTemplate::LanguageTemplate()
{
}

LanguageTemplate::LanguageTemplate(
        const std::string& word_key,
        const std::string& module,
        const std::string& type,
        const std::string& default_value,
        const std::string& custom_value
        )
    : m_wordKey(word_key),
      m_module(module),
      m_type(type),
      m_defaultValue(default_value),
      m_customValue(custom_value)
{
}

LanguageTemplate::~LanguageTemplate()
{
}

std::string LanguageTemplate::wordKey() __cell_const_noexcept
{
    if(!m_wordKey.empty()) {
        return m_wordKey;
    } else {
        return "unknown key";
    }
}

std::string LanguageTemplate::module() __cell_const_noexcept
{
    return m_module;
}

std::string LanguageTemplate::type() __cell_const_noexcept
{
    return m_type;
}

std::string LanguageTemplate::defaultValue() __cell_const_noexcept
{
    std::string ret {};
    if(!m_defaultValue.empty()) {
        return m_defaultValue;
    } else {
        ret = "Not defined key [" + wordKey() + "]";
        DeveloperMode::IsEnable ? Log("Not defined key [" + wordKey() + "]", LoggerType::Warning) : DO_NOTHING;
    }
    return ret;
}

std::string LanguageTemplate::customValue() __cell_const_noexcept
{
    std::string ret {};
    if(!m_customValue.empty()) {
        return m_customValue;
    } else {
        ret = "Not defined custom value [" + wordKey() + "]";
        DeveloperMode::IsEnable ? Log("Not defined custom value [" + wordKey() + "]", LoggerType::Warning) : DO_NOTHING;
    }
    return ret;
}

CELL_NAMESPACE_END
