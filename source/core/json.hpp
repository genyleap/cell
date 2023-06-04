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

class JsonDocument {
public:
    JsonDocument() = default;


#ifdef USE_BOOST
    JsonDocument(const boost::json::value& value);
#else
    JsonDocument(const Json::Value& value);
#endif

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


    std::string toString() const;

    bool hasKey(const std::string& key) const;

    int getInt(const std::string& key) const;

    Types::JSonValue getJson() const;

    std::string getString(const std::string& key) const;

    bool hasArray(const std::string& key) const;

    size_t getArraySize(const std::string& key) const ;

    JsonDocument getObject(const std::string& key) const;

    template <typename T, typename... Args>
    T getJsonObject(const JSonValue& jsonValue, Args&&... args)
    {
        JSonValue object = jsonValue;
#ifdef USE_BOOST
        ((object = object.at(args)), ...);
        if constexpr (std::is_same_v<T, std::string>)
        {
            return object.as_string().c_str();
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return object.as_bool();
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            return object.as_int64();
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return object.as_double();
        }
        else if constexpr (std::is_same_v<T, decltype(object)>)
        {
            return object.as_object();
        }
        // Add more conditions for other specific type conversions as needed
        else
        {
            // Handle unsupported type conversion
            throw std::runtime_error("Unsupported type conversion");
            return T();
        }
#else
        ((object = object[args]), ...);
        if constexpr (std::is_same_v<T, std::string>)
        {
            return object.asString();
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return object.asBool();
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            return object.asInt();
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return object.asDouble();
        }
        else if constexpr (std::is_same_v<T, decltype(object)>)
        {
            return object;
        }
        else
        {
            // Handle unsupported type conversion
            throw std::runtime_error("Unsupported type conversion");
            return T();
        }
#endif
    }

    template<typename T>
    std::vector<T> getArray(const std::string& key) const {
        std::vector<T> result;
#ifdef USE_BOOST
        if (m_root.is_object()) {
            auto obj = m_root.as_object();
            if (obj.contains(key)) {
                auto jsonValue = obj.at(key);
                if (jsonValue.is_array()) {
                    auto jsonArray = jsonValue.get_array();
                    for (const auto& element : jsonArray) {
                        T value;
                        if constexpr (std::is_same<T, JsonDocument>::value) {
                            JsonDocument nestedWrapper(element);
                            value = nestedWrapper;
                        } else {
                            value = boost::json::value_to<T>(element);
                        }
                        result.push_back(value);
                    }
                    return result;
                }
            }
        }
#else
        if (m_root.isObject() && m_root.isMember(key) && m_root[key].isArray()) {
            const Json::Value& jsonArray = m_root[key];
            for (unsigned int i = 0; i < jsonArray.size(); ++i) {
                T value;
                if constexpr (std::is_same<T, JsonDocument>::value) {
                    JsonDocument nestedWrapper(jsonArray[i]);
                    value = nestedWrapper;
                } else {
                    value = jsonArray[i].as<T>();
                }
                result.push_back(value);
            }
            return result;
        }
#endif
        throw std::runtime_error("Key '" + key + "' does not exist or is not an array.");
    }

    std::vector<std::string> getKeys() const;

    bool isArray() const {
#ifdef USE_BOOST
        return m_root.is_array();
#else
        return m_root.isArray();
#endif
    }


    std::vector<Types::JSonValue> getVectorJsonPtr();

    JsonDocument getObject() const;

    void setVectorJsonPtr(const JSonValue& data);

private:
    Types::JSonValue m_root{}; //!< Root node of the JSON object
    std::vector<Types::JSonValue> vectorJsonPtr;
    Cell::FileSystem::FileManager fileManager{};
};


CELL_NAMESPACE_END

#endif  // CELL_JSON_HPP
