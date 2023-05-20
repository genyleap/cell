/*!
 * @file        setting.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System setting structure.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
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

class SettingInterface
{
public:
    SettingInterface(const Types::OptionalString& title,
                     const Types::OptionalString& descr,
                     const Types::OptionalString& value,
                     const Types::OptionalString& json,
                     const Types::OptionalString& defaultVal,
                     const Types::OptionalString& extra);
    SettingInterface();
    ~SettingInterface();

    /*!
     * \brief title is subject of setting option.
     * \returns string.
     */
    Types::OptionalString title();

    /*!
     * \brief descr is description of setting option.
     * \returns string.
     */
    Types::OptionalString descr();

    /*!
     * \brief value is content of option value.
     * \returns string.
     */
    Types::OptionalString value();

    /*!
     * \brief json is content based on json format.
     * \returns string.
     */
    Types::OptionalString json();

    /*!
     * \brief defaultVal will gets default value for option.
     * \returns string.
     */
    Types::OptionalString defaultVal();

    /*!
     * \brief extra will gets extra data from option.
     * \returns string.
     */
    Types::OptionalString extra();

    void setTitle(const std::string& val);
    void setDescr(const std::string& val);
    void setValue(const std::string& val);
    void setJson(const std::string& val);
    void setDefaultVal(const std::string& val);
    void setExtra(const std::string& val);

private:
    InterfaceData* m_interfaceData;
};

struct SettingData final
{
    Scope<System::Engine>   engine   {};
    Types::VectorString     option           {};
    Types::SettingType      type     {};
    std::string             language {};
};

class Setting
{
public:
    Setting();
    ~Setting();

    std::string getOption(const std::string& var);

    /*!
     * \brief getList function will returns list of setting items.
     * \returns list
     */
    __cell_no_discard Types::SettingType getList() __cell_const_noexcept;

    /*!
     * \brief option function gets item as option.
     * \returns list of options.
     */
    Types::VectorString option() const;

    /*!
     * \brief setOption function will sets value into option.
     * \param val as list of string.
     */
    void setOption(const Types::VectorString& val);

    /*!
     * \brief saveList function will sets all data inside the list of setting. Any website changes effects on the list data.
     */
    void saveList() __cell_const_noexcept;

private:
    SettingData* m_settingData;
};

CELL_NAMESPACE_END

#endif  // CELL_SETTING_HPP
