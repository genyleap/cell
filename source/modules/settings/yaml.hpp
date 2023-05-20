/*!
 * @file        yaml.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Yaml Setting Manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SETTING_YAML_HPP
#define CELL_SETTING_YAML_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

/**
 * @brief The structure holding the data of the Yaml setting.
 */
struct YamlStructure final
{
    Types::OptionalString   filename        {}; //!< The filename of the Yaml configuration file
    Types::SettingComment   comments        {}; //!< The map of vectors of strings containing comments for each section
    Types::SettingData      settingData     {}; //!< The map of maps containing configuration data for each section
};

/**
 * @brief A class for reading and writing settings in Yaml format.
 * The YamlSetting class provides methods for reading and writing settings stored in Yaml format.
 * It can read settings from a file and save settings to a file.
 */
class __cell_export YamlSetting {
public:
    /**
     * @brief Constructs a YamlSetting object.
     */
    YamlSetting();

    /**
     * @brief Destroys the YamlSetting object.
     */
    ~YamlSetting();
    /**
     * @brief Reads configuration settings from a YAML file.
     *
     * @param filename The path to the YAML file to read.
     * @return true if the file was read successfully, false otherwise.
     */
    bool read(const std::string& filename);

    /**
     * @brief Saves configuration settings to a YAML file.
     *
     * @return true if the file was saved successfully, false otherwise.
     */
    bool save();

    /**
     * @brief Gets the value of a configuration setting.
     *
     * @param section The section of the configuration file containing the setting.
     * @param key The key of the setting.
     * @param value The value of the setting, if it exists.
     * @param defaultValue The default value to use if the setting does not exist.
     * @return true if the setting was found, false otherwise.
     */
    bool get(const std::string& section, const std::string& key, std::string& value, const std::string& defaultValue = "") const;

    /**
     * @brief Sets the value of a configuration setting.
     *
     * @param section The section of the configuration file containing the setting.
     * @param key The key of the setting.
     * @param value The value to set for the setting.
     */
    void setValue(const std::string& section, const std::string& key, const std::string& value);

    /**
     * @brief Adds a comment to a section of the configuration file.
     *
     * @param section The section of the configuration file to add the comment to.
     * @param comment The comment to add.
     */
    void addComment(const std::string& section, const std::string& comment);

private:
    YamlStructure yamlStructure {}; //!< The YAML data structure representing the configuration file.
};


CELL_NAMESPACE_END

#endif // CELL_SETTING_YAML_HPP
