/*!
 * @file        ini.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     INI Setting Manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_INI_HPP
#define CELL_INI_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::Settings)

using IniData = std::map<std::string, std::map<std::string, std::string>>;
using IniComment = std::map<std::string, std::vector<std::string>>;

struct IniStructure final
{
    Types::OptionalString filename   {}; ///<! The filename of the Ini configuration file.
    Types::SettingData settingData   {}; ///<! The INI data stored in memory.
    IniComment comments              {}; ///<! The comments associated with each section.
};

/**
 * @brief A class for reading and writing INI files.
 */
class __cell_export IniSetting {
public:
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

#endif // CELL_INI_HPP
