#ifdef __has_include
# if __has_include("config.hpp")
#   include "config.hpp"
#else
#   error "Cell's "config.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core.hpp")
#   include "core.hpp"
#else
#   error "Cell's "core.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("json.hpp")
#   include "json.hpp"
#else
#   error "Cell's "json.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Modules;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Abstracts;

CELL_NAMESPACE_BEGIN(Cell)

Configuration::Configuration(const ConfigType& configType)
{
    __cell_safe_instance(m_dataConfig, DataConfig)

    __cell_smart_instance(jsonSetting, Settings::JsonSetting);

    m_dataConfig->configType = configType;

    switch (configType) {
    case ConfigType::File:
        try {
            std::string cfile { __cell_null_str };
            cfile = CONFIG::SYSTEM_CONFIG_FILE.data();
            m_dataConfig->configFile = cfile;
            if(!jsonFile().empty()){
                //                if(m_dataConfig->json.parse(cfile))
                //                {
                //                    //ToDo...
                //                }
            }
        }
        catch (const Exception& e)
        {
            if(DeveloperMode::IsEnable) {
                eLogger::Log("Cannot open the file [" + m_dataConfig->configFile + "]", eLogger::LoggerType::Critical);
                eLogger::Log("Error details: " + FROM_CELL_STRING(e.what()), eLogger::LoggerType::Info);
            }
        }
        break;
    case ConfigType::Database:
        try {
            ///ToDo...
        }
        catch (const Exception& e)
        {
            if(DeveloperMode::IsEnable) {
                eLogger::Log("Configuration Error: " + FROM_CELL_STRING(e.what()), eLogger::LoggerType::Critical);
            }
        }
        break;
    default:
        break;
    }
}

Configuration::Configuration(const ConfigType& configType, const std::string& customFile)
{
    __cell_safe_instance(m_dataConfig, DataConfig)
    __cell_smart_instance(jsonSetting, Settings::JsonSetting);
    //!Todo...
}

Configuration::Configuration(const ConfigType& configType, const SectionType& sectionType)
{
    __cell_safe_instance(m_dataConfig, DataConfig)
    __cell_smart_instance(jsonSetting, Settings::JsonSetting);
    //!Todo...
}

Configuration::~Configuration()
{
    __cell_safe_delete(m_dataConfig);
}

bool Configuration::create(const FileType& fileType)
{
    ///ToDo...
    return false;
}

void Configuration::init(const SectionType sectionType)
{
    switch (sectionType) {
    case SectionType::SystemCore:
        break;
    case SectionType::Database:
        break;
    case SectionType::Translations:
        jsonSetting->read(CONFIG::SYSTEM_TRANSLATOR_CONFIG_FILE.data());
        break;
    case SectionType::Interface:
        break;
    case SectionType::Framework:
        break;
    case SectionType::Custom:
        break;
    default:
        break;
    }
}

void Configuration::registerFile(const VectorString& files)
{
    m_files = files;
}

bool Configuration::status()
{
    return false;
}

VectorString Configuration::files()
{
    return m_files;
}

std::optional<VariableType> Configuration::get()
{
    ///ToDo...
}

void Configuration::write(const KeyValueType& variable)
{
    ///ToDo...
}

template<class> inline constexpr bool always_false_v = false;

void Configuration::update(const KeyValueType& variable)
{
    ///ToDo...
}

void Configuration::remove(const KeyValueType &variable)
{
    ///ToDo...
}

bool Configuration::reset()
{
    ///ToDo...
}

bool Configuration::lock()
{
    ///ToDo...
}

std::string Configuration::getBaseUrl() __cell_noexcept
{
}

bool Configuration::isInstalled() __cell_noexcept
{
}

void Configuration::lockInstall() __cell_noexcept
{
}

std::string Configuration::jsonFile() __cell_noexcept
{
    std::string file { __cell_null_str };
    if(!m_dataConfig->configFile.empty())
    {
        file = m_dataConfig->configFile;
    } else {
        eLogger::Log("Please specify a config file and try again! ", eLogger::LoggerType::Critical);
    }
    return file;
}

void Configuration::system(const std::string &debug,
                           const std::string &cookiePrefix,
                           const std::string &tablePrefix,
                           const std::string &tableValueStruct,
                           const std::string &tableUnicode,
                           const std::string &defaultLanguage) __cell_noexcept
{

}

void Configuration::database(const std::string &rdbms,
                             const std::string &host,
                             const std::string &name,
                             const std::string &username,
                             const std::string &password,
                             const std::string &port) __cell_noexcept
{
}

void Configuration::feature(const std::string &dynamic,
                            const std::string &crossMode) __cell_noexcept
{
}

void Configuration::maintenance(const std::string &backupPath,
                                const std::string &experimentalUpdate,
                                const std::string &update,
                                const std::string &dbBackUpPath) __cell_noexcept
{
}

void Configuration::debug(const std::string& debug) __cell_noexcept
{
}

RdbmsTypeList Configuration::rdbms() __cell_noexcept
{
}

std::string Configuration::getPrefix() __cell_noexcept
{
}

std::string Configuration::currentRdbms()
{
}

std::string Configuration::getDefaultUri() __cell_noexcept
{
}

std::vector<std::string> Configuration::getLanguageUris() __cell_noexcept
{
}

void Configuration::programs(const std::string &pgDumpPath) __cell_noexcept
{
}

Modules::Settings::JsonSetting Configuration::Setting()
{
        switch (m_dataConfig->configType) {
    case ConfigType::File:
        jsonSetting->read(CONFIG::SYSTEM_TRANSLATOR_CONFIG_FILE.data());
        break;
    case ConfigType::Database:
        //ToDo...
        break;
    default:
        break;
    }
    return *jsonSetting;
}

CELL_NAMESPACE_END
