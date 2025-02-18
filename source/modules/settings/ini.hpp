/*!
 * @file        ini.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     INI Setting Manager.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SETTING_INI_HPP
#define CELL_SETTING_INI_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

/**
 * @brief The structure holding the data of the XML setting.
 */
struct IniStructure final
{
    Types::OptionalString   filename    {}; //!< The filename of the Ini configuration file.
    Types::SettingComment   comments    {}; //!< The comments associated with each section.
    Types::SettingData      settingData {}; //!< The INI data stored in memory.
};

/**
 * @brief A class for reading and writing INI files.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export IniSetting {
public:
    /**
     * @brief Constructs a IniSetting object.
     */
    IniSetting();

    /**
     * @brief Destroys the IniSetting object.
     */
    ~IniSetting();

    /**
     * @brief Reads an INI file and stores the data in memory.
     *
     * @param filename The name of the file to read.
     * @return True if the file was successfully read, false otherwise.
     */
    bool read(const std::string& filename);

    /**
     * @brief Writes the INI data to a file.
     *
     * @return True if the file was successfully written, false otherwise.
     */
    bool save();

    /**
     * @brief Gets the value associated with a given section and key.
     *
     * @param section The name of the section.
     * @param key The name of the key.
     * @param value A reference to the string where the value will be stored.
     * @return True if the value was found, false otherwise.
     */
    bool getValue(const std::string& section, const std::string& key, std::string& value, const std::string& defaultValue = "") const;

    /**
     * @brief Sets the value associated with a given section and key.
     *
     * @param section The name of the section.
     * @param key The name of the key.
     * @param value The value to set.
     */
    void setValue(const std::string& section, const std::string& key, const std::string& value);

    /**
     * @brief Adds a comment to the given section.
     *
     * @param section The name of the section to add the comment to.
     * @param comment The comment to add.
     */
    void addComment(const std::string& section, const std::string& comment);

private:
    IniStructure iniStructure {};
};


CELL_NAMESPACE_END

#endif // CELL_SETTING_INI_HPP
