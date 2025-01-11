/*!
 * @file        xml.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     XML Setting Manager.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SETTING_XML_HPP
#define CELL_SETTING_XML_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

/**
 * @brief The structure holding the data of the XML setting.
 */
struct XmlStructure final
{
    Types::OptionalString filename      {}; //!< the filename of the XML configuration file
    Types::SettingComment comments      {}; //!< a map of vectors of strings containing comments for each section
    Types::SettingData    settingData   {}; //!< a map of maps containing configuration data for each section
};

constexpr const std::string_view settingBegin  = { "<settings>" };
constexpr const std::string_view settingEnd    = { "</settings>"};

/**
 * @brief A class for reading and writing settings in Xml format.
 * The XmlSetting class provides methods for reading and writing settings stored in Xml format.
 * It can read settings from a file and save settings to a file.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export XmlSetting {
public:
    /**
     * @brief Constructs a XmlSetting object.
     */
    XmlSetting();

    /**
     * @brief Constructs a XmlSetting object.
     */
    ~XmlSetting();

    /**
     * @brief Sets the value of a key in a section.
     * @param section The section of the setting.
     * @param key The key of the setting.
     * @param value The value of the setting.
     */
    void setValue(const std::string& section, const std::string& key, const std::string& value);

    /**
     * @brief Gets the value of a key in a section.
     * @param section The section of the setting.
     * @param key The key of the setting.
     * @param value The reference to the value of the setting.
     * @return True if the key is found and the value is retrieved successfully; false otherwise.
     */
    bool getValue(const std::string& section, const std::string& key, std::string& value) const;

    /**
     * @brief Saves the current setting to the XML file.
     *
     * @return True if the setting is saved successfully; false otherwise.
     */
    bool save();

    /**
     * @brief Loads the setting from the XML file.
     * @return True if the setting is loaded successfully; false otherwise.
     */
    bool read(const std::string& filename);

    /**
     * @brief Adds a comment to a section.
     * @param section The section of the setting.
     * @param comment The comment to add.
     */
    void addComment(const std::string& section, const std::string& comment);

private:
    XmlStructure xmlStructure {};
};

CELL_NAMESPACE_END

#endif // CELL_SETTING_XML_HPP
