/*!
 * @file        setting.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System setting structure.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SETTING_HPP
#define CELL_SETTING_HPP

#include "common.hpp"
#include "core/core.hpp"

CELL_NAMESPACE_BEGIN(Cell::Interface)

/*!
 * \brief The SettingData class
 */
struct InterfaceData final
{
    Types::OptionalString title      {};
    Types::OptionalString descr      {};
    Types::OptionalString value      {};
    Types::OptionalString json       {};
    Types::OptionalString defaultVal {};
    Types::OptionalString extra      {};
};

class __cell_export SettingInterface
{
public:
    /**
     * @brief Constructs a SettingInterface object with the given parameters.
     * @param title The optional title for the interface.
     * @param descr The optional description for the interface.
     * @param value The optional value for the interface.
     * @param json The optional JSON data for the interface.
     * @param defaultVal The optional default value for the interface.
     * @param extra The optional extra information for the interface.
     */
    SettingInterface(const Types::OptionalString& title,
                     const Types::OptionalString& descr,
                     const Types::OptionalString& value,
                     const Types::OptionalString& json,
                     const Types::OptionalString& defaultVal,
                     const Types::OptionalString& extra);

    /**
     * @brief Constructs a default SettingInterface object.
     */
    SettingInterface();

    /**
     * @brief Destructor for the SettingInterface object.
     */
    ~SettingInterface();

    /**
     * @brief Retrieves the optional title for the interface.
     * @return The optional title.
     */
    Types::OptionalString title();

    /**
     * @brief Retrieves the optional description for the interface.
     * @return The optional description.
     */
    Types::OptionalString descr();

    /**
     * @brief Retrieves the optional value for the interface.
     * @return The optional value.
     */
    Types::OptionalString value();

    /**
     * @brief Retrieves the optional JSON data for the interface.
     * @return The optional JSON data.
     */
    Types::OptionalString json();

    /**
     * @brief Retrieves the optional default value for the interface.
     * @return The optional default value.
     */
    Types::OptionalString defaultVal();

    /**
     * @brief Retrieves the optional extra information for the interface.
     * @return The optional extra information.
     */
    Types::OptionalString extra();

    /**
     * @brief Sets the title for the interface.
     * @param val The title value to set.
     */
    void setTitle(const std::string& val);

    /**
     * @brief Sets the description for the interface.
     * @param val The description value to set.
     */
    void setDescr(const std::string& val);

    /**
     * @brief Sets the value for the interface.
     * @param val The value to set.
     */
    void setValue(const std::string& val);

    /**
     * @brief Sets the JSON data for the interface.
     * @param val The JSON data to set.
     */
    void setJson(const std::string& val);

    /**
     * @brief Sets the default value for the interface.
     * @param val The default value to set.
     */
    void setDefaultVal(const std::string& val);

    /**
     * @brief Sets the extra information for the interface.
     * @param val The extra information to set.
     */
    void setExtra(const std::string& val);

private:
    InterfaceData* m_interfaceData;
};

struct SettingData final
{
    Types::VectorString     option   {};
    Types::SettingType      type     {};
    std::string             language {};
};

class __cell_export Setting
{
public:
    /**
     * @brief Constructs a Setting object.
     */
    Setting();

    /**
     * @brief Destructor for the Setting object.
     */
    ~Setting();

    /**
     * @brief Retrieves the option for the specified variable.
     * @param var The variable to retrieve the option for.
     * @return The option for the variable.
     */
    std::string getOption(const std::string& var);

    /**
     * @brief Retrieves the list of settings.
     * @return The setting type list.
     */
    __cell_no_discard Types::SettingType getList() __cell_const_noexcept;

    /**
     * @brief Retrieves the vector of options for the setting.
     * @return The vector of options.
     */
    Types::VectorString option() const;

    /**
     * @brief Sets the vector of options for the setting.
     * @param val The vector of options to set.
     */
    void setOption(const Types::VectorString& val);

    /**
     * @brief Saves the list of settings.
     * saveList function will sets all data inside the list of setting. Any website changes effects on the list data.
     */
    void saveList() __cell_const_noexcept;

private:
    SettingData* m_settingData;
};

CELL_NAMESPACE_END

#endif  // CELL_SETTING_HPP
