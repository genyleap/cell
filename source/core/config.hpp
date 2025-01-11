/*!
 * Gen3 License
 *
 * @file        config.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_CONFIG_HPP
#define CELL_CONFIG_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#include "abstracts/configuration.hpp"
#include "modules/settings/json.hpp"

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The RdbmsInterface class
 */
struct RdbmsInterface final
{
    std::string codename    {};     //!< Code name for rdbms.
    std::string host        {};     //!< Host name.
    std::string name        {};     //!< Name of host.
    std::string username    {};     //!< Username.
    std::string password    {};     //!< Password.
    Types::u32  port        {};     //!< Port of host.
    bool        status      {};     //!< Status of rdbms.
};
/*!
 * \brief The DataSetting struct
 */
struct DataConfig final
{
    RdbmsInterface                      rdbmsInfo   {};   //!< Rdbms info.
    Abstracts::ConfigType               configType  {};   //!< Config type.
    Abstracts::SectionType              sectionType {};   //!< Section type.
//    Scope<System::Engine>               engine      {};   //!< Cell Engine
//    Scope<Interface::Setting>           setting     {};   //!< Cell Setting
    std::string                         configFile  {};   //!< Config file.
};

CELL_USING RdbmsTypeList = std::vector<std::optional<RdbmsInterface>>;

/*!
 * \brief The Configuration class
 */
class Configuration : public Abstracts::AbstractConfiguration
{
public:
    Configuration() = delete;
    Configuration(const Abstracts::ConfigType& configType);
    Configuration(const Abstracts::ConfigType& configType, const std::string& customFile);
    Configuration(const Abstracts::ConfigType& configType, const Abstracts::SectionType& sectionType);
    ~Configuration();

    /*!
     * \brief Checks and initializations are required from the abstract class before configuration.
     */
    void init(const Abstracts::SectionType sectionType) __cell_override;

    /*!
     * \brief Creating and implementing the content of a tree in configuration files requires this function.
     * \param fileType as types of configuration file.
     * \returns true if the creating and implementing was successful.
     */
    bool create(const Abstracts::FileType& fileType) __cell_override;

    /*!
     * \brief We need to register files inside the project to read and write.
     * \param files as a list string.
     */
    void registerFile(const Types::VectorString& files) __cell_override;

    /*!
     * \brief We need to get each file to check more details.
     * \returns list of files as string.
     */
    Types::VectorString files() __cell_override;

    /*!
     * \brief status of configuration system.
     * \returns true if there is no problem inside the config.
     */
    bool status() __cell_override;

    /*!
     * \brief get function will gets value based on variable types.
     * \returns value based on it's type.
     */
    std::optional<Abstracts::VariableType> get() __cell_override;

    /*!
     * \brief Writing in the configuration file requires sending information of variable type.
     * \param variable of multi types.
     */
    void write(const Abstracts::KeyValueType& variable) __cell_override;

    /*!
     * \brief Updating in the configuration file requires sending information of variable type.
     * \param variable of multi types.
     */
    void update(const Abstracts::KeyValueType& variable) __cell_override;

    /*!
     * \brief Removing in the configuration file requires sending information of variable type.
     * \param variable of multi types.
     */
    void remove(const Abstracts::KeyValueType& variable) __cell_override;

    /*!
     * \brief It is sometimes necessary to reset all configuration variables.
     * \returns true if file resets.
     */
    bool reset() __cell_override;

    /*!
     * \brief We may sometimes change the permission level of the file to prevent possible changes.
     * \returns true if permission changed.
     */
    bool lock() __cell_override;

    /*!
     * \brief isInstalled function gets system install status.
     * \returns true if the system is installed.
     */
    bool isInstalled() __cell_noexcept;

    /*!
     * \brief The installation process must be locked after successful installation. In this case, this function will be helpful.
     */
    void lockInstall() __cell_noexcept;

    /*!
     * \brief system function will sets system configuration variables.
     */
    void system(const std::string& debug,
                const std::string& cookiePrefix,
                const std::string& tablePrefix,
                const std::string& tableValueStruct,
                const std::string& tableUnicode,
                const std::string& defaultLanguage) __cell_noexcept;

    /*!
     * \brief database function will sets database configuration variables.
     */
    void database(const std::string& rdbms,
                  const std::string& host,
                  const std::string& name,
                  const std::string& username,
                  const std::string& password,
                  const std::string& port) __cell_noexcept;

    /*!
     * \brief feature function will sets feature configuration variables.
     */
    void feature(const std::string& dynamic, const std::string& crossMode) __cell_noexcept;

    /*!
     * \brief maintenance function will sets maintenance configuration variables.
     */
    void maintenance(const std::string& backupPath,
                     const std::string& experimentalUpdate,
                     const std::string& update,
                     const std::string& dbBackUpPath) __cell_noexcept;

    /*!
     * \brief debug function will sets debug configuration variables.
     */
    void debug(const std::string& debug) __cell_noexcept;

    /*!
     * \brief rdbms function will gets current used rdbms data from config.
     * \returns list of data member.
     */
    RdbmsTypeList rdbms() __cell_noexcept;

    /*!
     * \brief getPrefix function will returns prefix.
     * \returns string.
     */
    std::string getPrefix() __cell_noexcept;

    /*!
     * \brief getLanguageUris function will gets language uris.
     * \returns list of strings.
     */
    std::vector<std::string> getLanguageUris() __cell_noexcept;

    /*!
     * \brief currentRdbms function will gets current used rdbms name.
     * \return string name of rdbms.
     */
    std::string currentRdbms();
    /*!
     * \brief getDefaultUri
     * \returns string.
     */
    std::string getDefaultUri() __cell_noexcept;

    /*!
     * \brief getBaseUrl function will returns base domain address.
     * \returns string.
     */
    std::string getBaseUrl() __cell_noexcept;

    /*!
     * \brief programs function will sets programs configuration variables.
     */
    void programs(const std::string& pgDumpPath) __cell_noexcept;

    Modules::BuiltIn::Settings::JsonSetting Setting();

protected:
    __cell_no_discard std::string jsonFile() __cell_noexcept;

private:
    DataConfig*     m_dataConfig;
    Types::VectorString    m_files{};
    Scope<Modules::BuiltIn::Settings::JsonSetting> jsonSetting{};
};

CELL_NAMESPACE_END

#endif  // CELL_CONFIG_HPP
