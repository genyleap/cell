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

#ifndef CELL_YAML_HPP
#define CELL_YAML_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::Settings)

/**
 * @brief The structure holding the data of the Yaml setting.
 */
struct YamlStructure
{
    Types::OptionalString filename  {}; ///<! the filename of the Yaml configuration file
    std::map<std::string, std::vector<std::string>> comments; ///<! a map of vectors of strings containing comments for each section
    std::map<std::string, std::map<std::string, std::string>> settingData; ///<! a map of maps containing configuration data for each section
};

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
     * @param filename The path to the YAML file to save.
     * @return true if the file was saved successfully, false otherwise.
     */
    bool save(const std::string& filename);

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
    YamlStructure yamlStructure {}; ///<! The YAML data structure representing the configuration file.
};


CELL_NAMESPACE_END

#endif // CELL_YAML_HPP
