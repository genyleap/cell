/*!
 * @file        json.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Json Setting Manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SETTING_JSON_HPP
#define CELL_SETTING_JSON_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::Settings)

/**
 * @brief A class for reading and writing settings in JSON format.
 * The JsonSetting class provides methods for reading and writing settings stored in JSON format.
 * It can read settings from a file and save settings to a file.
 */

#include <boost/json.hpp>

template<typename T>
static auto JSON_SETTING_GET(const T& v) {
#ifdef USE_BOOST
    const JSonValue jvalue = v;
    return jvalue.as_string();
#else
    const JSonValue jvalue = v;
    return jvalue.asString();
#endif
}

struct JSonTypeStructure final
{
    std::string String;
    bool Boolean;
};

template <typename T>
static auto JSON_SETTING_GET(const JSonValue& jvalue, const T& obj) {
#ifdef USE_BOOST
    JSonTypeStructure jts;
    jts.String = jvalue.at(obj).as_string();
    jts.Boolean = jvalue.at(obj).as_bool();
    return jts;

#else
    return jvalue[obj].asString();
#endif
}

template <typename T>
static auto JSON_SETTING_OBJECT_GET(const JSonValue& jvalue, const T& obj) {
#ifdef USE_BOOST
    return jvalue.at(obj).as_object();
#else
    return jvalue[obj];
#endif
}

template <typename T>
static auto JSON_SETTING_STRING_GET(const JSonValue& jvalue, const T& obj) {
#ifdef USE_BOOST
    return jvalue.at(obj).as_string().c_str();
#else
    return jvalue[obj].asString();
#endif
}

template <typename T>
static auto JSON_SETTING_BOOLEAN_GET(const JSonValue& jvalue, const T& obj) {
#ifdef USE_BOOST
    return jvalue.at(obj).as_bool();
#else
    return jvalue[obj].asBool();
#endif
}

template <typename T1, typename T2>
static auto JSON_SETTING_SEQUENCE_STRING_GET(const JSonValue& jvalue, const T1& obj1, const T2& obj2) {
#ifdef USE_BOOST
    return jvalue.at(obj1).at(obj2).as_string().c_str();
#else
    return jvalue[obj1][obj2].asString();
#endif
}

template <typename T, typename T1, typename T2>
static auto JSON_SETTING_SEQUENCE_BOOLEAN_GET(const T& jvalue, const T1& obj1, const T2& obj2) {
#ifdef USE_BOOST
    return jvalue.at(obj1).at(obj2).as_bool();
#else
    return jvalue[obj1][obj2].asBool();
#endif
}

class JsonSetting {
public:
    /**
     * @brief JsonSetting constructor.
     */
    JsonSetting();

    /**
     * @brief JsonSetting destructor.
     */
    ~JsonSetting();

    /**
     * @brief Reads JSON data from a file.
     *
     * @param filename The name of the file to read from.
     *
     * @return True if the read was successful, false otherwise.
     */
    bool read(const std::string& filename);

    /**
     * @brief Saves the current JSON data to a file.
     *
     * @return True if the save was successful, false otherwise.
     */
    bool save();

    /**
     * @brief Gets the value associated with a given key and section.
     *
     * @param section The section to search in.
     * @param key The key to search for.
     * @param value The value to store the result in.
     * @param defaultValue The default value to use if no value is found.
     *
     * @return True if the value was found, false otherwise.
     */
    bool getValue(const std::string& key, JSonValue& value, const std::string& defaultValue = "") const;

    bool getValue(const std::string& section, const std::string& key, std::string& value, const std::string& defaultValue = "") const;

    bool getValueArray(const std::string& section, const std::string& key, std::vector<std::string>& value, const std::string& defaultValue = "") const;

    bool getValueMulti(const std::string& section, std::vector<JSonValue>& value, const std::string& defaultValue = "") const;

    /**
     * @brief Sets the value associated with a given key and section.
     *
     * @param section The section to set the value in.
     * @param key The key to set the value for.
     * @param value The value to set.
     */
    void setValue(const std::string& section, const std::string& key, const std::string& value);

    /**
     * @brief Sets the comment associated with a given key and section.
     *
     * @param section The section to set the comment in.
     * @param comment The comment to set.
     */
    void addComment(const std::string& section, const std::string& comment);

private:
    Types::JSonValue m_jsonValue        {}; //!< The JSON value representing the settings file. */
    Types::OptionalString m_filename    {}; //!< The filename of the Json configuration file
};

CELL_NAMESPACE_END

#endif // CELL_SETTING_JSON_HPP
