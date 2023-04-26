/*!
 * @file        setting.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Site setting interface.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SETTING_ABSTRACT_HPP
#define CELL_SETTING_ABSTRACT_HPP

#include "common.hpp"

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The ServiceType enum
 * \details Users and customers will have different options. For this purpose, it is necessary to have this structure.
 */
__cell_enum_class ServiceType : Types::u8
{
    Default       =   0x1,  ///< These types of options are available for all purposes and types of users.
    Customized    =   0x2,  ///< These types of options are only available for specific purposes or dedicated development.
    Premium       =   0x3   ///< These types of options are only available for premium users.
};

__cell_enum_class Status : Types::u8
{
    Disabled    =   0x0,  ///< Disabled.
    Hidden      =   0x1,  ///< Hidden.
    Active      =   0x2   ///< Active.
};

#if defined(ENABLE_SAFE_ONLY)
CELL_USING ValueType = std::variant<std::string, bool, s64, u64>;   ///<In this section we will cover data types for value of options.
#else
struct ValueType __cell_final
{
    std::string  AsString;           ///< String type.
    bool         AsBoolean;          ///< Boolean type.
    Types::s64   AsSignedInteger;    ///< Integer with signed.
    Types::u64   AsUnsignedInteger;  ///< Integer with unsigned.
};
#endif


/*!
 * \brief The SettingData class
 */
struct OptionData __cell_final
{
    Types::OptionalString      title      {};   ///< Title of setting option.
    Types::OptionalString      descr      {};   ///< Description of setting option.
    Types::Optional<ValueType> value      {};   ///< Value of setting option.
    Types::OptionalJsonVal     json       {};   ///< JSon of setting option.
    Types::OptionalString      defaultVal {};   ///< Default value of setting option.
    Types::OptionalString      extra      {};   ///< Extra value of setting option.
    Types::Optional<Status>    status     {};   ///< Status value of setting option.
    Types::OptionalNumeric     startGroup {};   ///< Group index value of option.
    ServiceType                service    {};   ///< Service type for option.
};

class __cell_export AbstractSetting
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractSetting)

    /*!
     * \brief title is subject of setting option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString title() __cell_const = __cell_zero;

    /*!
     * \brief descr is description of setting option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString descr() __cell_const = __cell_zero;

    /*!
     * \brief value is content of option value.
     * \returns as ValueType.
     */
    __cell_virtual Types::Optional<ValueType> value() __cell_const = __cell_zero;

    /*!
     * \brief json is content based on json format.
     * \returns string.
     */
    __cell_virtual Types::OptionalString json() __cell_const = __cell_zero;

    /*!
     * \brief defaultVal will gets default value for option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString defaultVal() __cell_const = __cell_zero;

    /*!
     * \brief extra will gets extra data from option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString extra() __cell_const = __cell_zero;

    /*!
     * \brief status will gets status value from option.
     * \returns one of the Status.
     */
    __cell_virtual Types::Optional<Status> status() __cell_const = __cell_zero;

    /*!
     * \brief startGroup will gets index of group id.
     * \returns id as integer.
     */
    __cell_virtual Types::OptionalNumeric startGroup() __cell_const = __cell_zero;

    /*!
     * \brief It is necessary to receive a list of all the options in the settings in a part of the system.
     * \returns string of items list.
     */
    __cell_virtual Types::VectorString getByList() __cell_const = __cell_zero;

    /*!
     * \brief SetTitle inserts data for the option's title.
     * \param title is a string type for inserting values into the function.
     */
    __cell_virtual void setTitle(const std::string& title) = __cell_zero;

    /*!
     * \brief setDescr inserts data for the option's description.
     * \param descr is a string type for inserting values into the function.
     */
    __cell_virtual void setDescr(const std::string& descr) = __cell_zero;

    /*!
     * \brief setValue inserts data for the option's value.
     * \param value is a ValueType for inserting values into the function.
     */
    __cell_virtual void setValue(const ValueType& value) = __cell_zero;

    /*!
     * \brief setJson inserts data for the option's json.
     * \param json is a json type for inserting values into the function.
     */
    __cell_virtual void setJson(const Types::JSonValue& json) = __cell_zero;

    /*!
     * \brief setDefaultValue inserts data for the option's default value.
     * \param deval is a string type for inserting values into the function.
     */
    __cell_virtual void setDefaultValue(const std::string& deval) = __cell_zero;

    /*!
     * \brief setStatus will change option's status.
     * \param status is a Status type for change the option status.
     */
    __cell_virtual void setStatus(const Types::Optional<Status> status) = __cell_zero;

    /*!
     * \brief setStartGroup will sets option's group index.
     * \param index is number of group id.
     */
    __cell_virtual void setStartGroup(const int index) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractSetting)
};

CELL_NAMESPACE_END

#endif  // CELL_SETTING_ABSTRACT_HPP
