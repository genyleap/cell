/*!
 * @file        json.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Json system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_JSON_HPP
#define CELL_JSON_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core/filesystem.hpp")
#   include "core/filesystem.hpp"
#else
#   error "Cell's "core/filesystem.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::JSon)

/**
 * @brief The InputType enum
 */
enum class InputType { File, RawData };

/**
 * @brief The JsonManager class
 */
class __cell_export JsonManager {
public:
    JsonManager();
    ~JsonManager();

    /**
     * Parse a JSON data from a given input and populate root node of the JSON object.
     * @param data Input data in JSonType format.
     * @param inputType as InputType for select type of input data [file or raw string].
     * @return true if parsing is successful, false otherwise.
     */
    bool parse(const Types::JSonType& data, const InputType inputType) __cell_noexcept;

    /**
     * Parse a JSON data from a given input and populate root node of the JSON object.
     * @param data Input data in JSonType format.
     * @return true if parsing is successful, false otherwise.
     */
    bool parse(const Types::JSonType& data) __cell_noexcept;

    /**
     * Check if a given key is present in the JSON object.
     * @param key as string to be checked.
     * @return true if key is present in the JSON object, false otherwise.
     */
    bool contains(const std::string& key) __cell_noexcept;

    /**
     * Get the value associated with a given key in the JSON object.
     * @param key as stroing for which the value is to be retrieved.
     * @return Value associated with the key if found, else a null JSON value.
     */
    Types::JSonValue get(const std::string& key) __cell_noexcept;

    Types::JSonValue getData() __cell_noexcept;

    std::vector<Types::JSonValue> getVectorJsonPtr();

    void setVectorJsonPtr(const JSonValue& data);

private:
    Types::JSonValue m_root{}; //!< Root node of the JSON object
    std::vector<Types::JSonValue> vectorJsonPtr;
    Cell::FileSystem::FileManager fileManager{};
};

/**
 * @brief A class for finding and manipulating JSON values.
 * @tparam T The type of the JSON value.
 */
template <typename T>
class __cell_export JsonFind
{
public:
    /**
     * @brief Default constructor (deleted).
     */
    JsonFind() = delete;

    /**
     * @brief Constructs a JsonFind object with the specified JSON value and search object.
     *
     * @param jv The JSON value to search within.
     * @param obj The object to search for within the JSON value.
     */
    JsonFind(const JSonValue& jv, const T& obj)
    {
        JasonKeyValue jkv;

// Iterate through the JSON value to find the specified object
#ifdef USE_BOOST
        for(const auto& j : jv.as_object())
        {
            if(j.key() == obj)
            {
                // Set the keys and their corresponding values
                for(const auto& k : j.value().as_object())
                {
                    jkv.key = k.key();
                    jkv.value = k.value();
                    m_jKeyValue.push_back(jkv);
                }
            }
        }
#else
        for (JSonValue::const_iterator it = jv.begin(); it != jv.end(); ++it)
        {
            const std::string baseKey = it.key().asString();
            const Json::Value baseValue = *it;
            if(baseKey == obj) {
                std::vector<std::string> keys = baseValue.getMemberNames();
                // Set the keys and their corresponding values
                for (const std::string& key : keys) {
                    const Json::Value& value = baseValue[key];
                    jkv.key = key;
                    jkv.value = value;
                    m_jKeyValue.push_back(jkv);
                }
            }
        }
#endif
    }

    /**
     * @struct JasonKeyValue
     * @brief Structure representing a JSON key-value pair.
     */
    struct JasonKeyValue __cell_final
    {
        std::string key;     /**< The key of the JSON pair. */
        JSonValue value;     /**< The value of the JSON pair. */
    };

    /**
     * @brief Returns a JsonFind object representing the specified object within the JSON value.
     *
     * @param obj The object to search for within the JSON value.
     * @return A JsonFind object representing the specified object.
     */
    JsonFind getAsObject(const auto& obj) {
#ifdef USE_BOOST
        return JsonFind(m_jvalue.at(obj).as_object());
#else
        return JsonFind(m_jvalue[obj]);
#endif
    }

    /**
     * @brief Returns the JSON key-value pairs as an object.
     *
     * @return The JSON key-value pairs as an object.
     */
    std::vector<JasonKeyValue> getAsObject() {
#ifdef USE_BOOST
        return m_jKeyValue;
#else
        return m_jKeyValue;
#endif
    }

    /**
     * @brief Returns the specified JSON value as a string.
     *
     * @param jvalue The JSON value to convert.
     * @return The JSON value as a string.
     */
    auto getAsString(const JSonValue& jvalue)
    {
#ifdef USE_BOOST
        return jvalue.as_string().c_str();
#else
        return jvalue.asString();
#endif
    }

    /**
     * @brief Returns the stored JSON value.
     *
     * @return The stored JSON value.
     */
    auto getValue()
    {
#ifdef USE_BOOST
        return m_jvalue;
#else
        return m_jvalue;
#endif
    }

    /**
     * @brief Returns the specified JSON value as a map of key-value pairs.
     *
     * @param obj The JSON value to convert.
     * @return The JSON value as a map of key-value pairs.
     */
    std::map<std::string, JSonValue> getValue(const JSonValue& obj)
    {
        std::map<std::string, JSonValue> v;
#ifdef USE_BOOST
        for (const auto& [key, value] : obj.as_object()) {
            m_key = key;
            m_value = value;
            v.insert(std::make_pair(m_key.value(), m_value));
        }
#else
        for (JSonValue::const_iterator it = obj.begin(); it != obj.end(); ++it)
        {
            m_key = it.key().asString();
            m_value = *it;
            v.insert(std::make_pair(m_key.value(), m_value));
        }
#endif
        return v;
    }

    /**
     * @brief Returns the stored JSON value as an array.
     *
     * @return The stored JSON value as an array.
     */
    auto getAsArray() {
#ifdef USE_BOOST
        return m_jvalue.as_array();
#else
        return m_jvalue;
#endif
    }

    /**
     * @brief Returns the specified JSON value as an array.
     *
     * @param obj The JSON value to convert.
     * @return The JSON value as an array.
     */
    auto getAsArray(const JSonValue& obj) {
#ifdef USE_BOOST
        return obj.as_array();
#else
        return obj;
#endif
    }

private:
    Types::JSonValue            m_jvalue    {};   //!< The JSON value.
    Types::OptionalString       m_key       {};   //!< The JSON key.
    Types::JSonValue            m_value     {};   //!< The JSON value.
    std::vector<JasonKeyValue>  m_jKeyValue {};   //!< The JSON key-value pairs.
};

CELL_NAMESPACE_END

#endif  // CELL_JSON_HPP
