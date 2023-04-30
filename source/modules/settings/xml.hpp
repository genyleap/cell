/*!
 * @file        xml.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     XML Setting Manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_XML_HPP
#define CELL_XML_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::Settings)

/**
 * @brief The structure holding the data of the XML setting.
 */
struct XmlStructure
{
    Types::OptionalString filename  {}; ///<! the filename of the XML configuration file
    std::map<std::string, std::vector<std::string>> comments; ///<! a map of vectors of strings containing comments for each section
    std::map<std::string, std::map<std::string, std::string>> settingData; ///<! a map of maps containing configuration data for each section
};

constexpr const std::string_view settingBegin  = { "<settings>" };
constexpr const std::string_view settingEnd    = { "</settings>"};

class __cell_export XmlSetting {
public:
    /**
     * @brief Constructs an XmlSetting object with the given filename.
     * @param filename The filename of the XML setting file.
     */
    XmlSetting(const std::string& filename);

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
     * @return True if the setting is saved successfully; false otherwise.
     */
    bool save();

    /**
     * @brief Loads the setting from the XML file.
     * @return True if the setting is loaded successfully; false otherwise.
     */
    bool load();

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

#endif // CELL_XML_HPP
