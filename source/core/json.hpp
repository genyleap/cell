/*!
 * @file        json.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Json system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
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
    /**
     * Constructor that initializes the JsonDocument with a boost::json::value object.
     * @param value The boost::json::value object to initialize the JsonDocument.
     */
    JsonDocument() = default;

    /**
     * Constructor that initializes the JsonDocument with a Json::Value object.
     * @param value The Json::Value object to initialize the JsonDocument.
     */
    JsonDocument(const JSonValue& value);

    /**
     * Parse a JSON data from a given input and populate root node of the JSON object.
     * @param data Input data in JSonType format.
     * @param inputType The InputType for selecting the type of input data (file or raw string).
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
     * Convert the JSON object to a string representation.
     * @return The JSON object as a string.
     */
    std::string toString() const;

    /**
     * Check if a key exists in the JSON object.
     * @param key The key to check.
     * @return true if the key exists, false otherwise.
     */
    bool hasKey(const std::string& key) const;

    /**
     * Get the integer value associated with the specified key.
     * @param key The key to retrieve the integer value.
     * @return The integer value.
     */
    int getInt(const std::string& key) const;

    /**
     * Get the JSON value associated with the specified key.
     * @return The JSON value.
     */
    Types::JSonValue getJson() const;

    /**
     * Get the string value associated with the specified key.
     * @param key The key to retrieve the string value.
     * @return The string value.
     */
    std::string getString(const std::string& key) const;

    /**
     * Check if the specified key represents an array in the JSON object.
     * @param key The key to check.
     * @return true if the key represents an array, false otherwise.
     */
    bool hasArray(const std::string& key) const;

    /**
     * Get the size of the array associated with the specified key.
     * @param key The key to retrieve the array size.
     * @return The size of the array.
     */
    size_t getArraySize(const std::string& key) const;

    /**
     * Get a nested JSON object associated with the specified key.
     * @param key The key to retrieve the nested JSON object.
     * @return The nested JSON object as a JsonDocument.
     */
    JsonDocument getObject(const std::string& key) const;

    /**
     * Get a specific type of object from the given JSON value.
     * @tparam T The type of the object to retrieve.
     * @tparam Args The types of arguments used to access the nested value.
     * @param jsonValue The JSON value to retrieve the object from.
     * @param args The arguments used to access the nested value.
     * @return The retrieved object of type T.
     * @throws std::runtime_error if the type conversion is unsupported.
     */
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

    /**
     * Get an array of values associated with the specified key.
     * @tparam T The type of the values in the array.
     * @param key The key to retrieve the array.
     * @return The array of values.
     * @throws std::runtime_error if the key does not exist or is not an array.
     */
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

    /**
     * Retrieves multiple values of type T from nested JSON arrays based on the provided keys.
     *
     * @tparam T The type of values to retrieve.
     * @tparam Keys The keys used to navigate through the JSON structure.
     * @param key The first key to access the nested JSON array.
     * @param keys The remaining keys to access further nested JSON arrays (optional).
     * @return A vector containing the retrieved values.
     * @throws std::runtime_error if the keys do not exist or the value is not an array.
     */
    template<typename T, typename... Keys>
    std::vector<T> getMultipleArray(const std::string& key, const Keys&... keys) const
    {
        std::vector<T> result;
#ifdef USE_BOOST
        if (m_root.is_object()) {
            auto obj = m_root.as_object();
            if (obj.contains(key)) {
                auto jsonValue = obj.at(key);
                // Recursive call to getMultipleArray for further nested arrays.
                if constexpr (sizeof...(Keys) > 0) {
                    JsonDocument nestedWrapper(jsonValue);
                    return nestedWrapper.getMultipleArray<T>(keys...);
                } else {
                    if (jsonValue.is_array()) {
                        auto jsonArray = jsonValue.get_array();
                        for (const auto& element : jsonArray) {
                            T value;
                            if constexpr (std::is_same<T, JsonDocument>::value)
                            {
                                // Handle nested JsonDocument objects
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
        }
#else
        if (m_root.isObject() && m_root.isMember(key)) {
            const Json::Value& jsonValue = m_root[key];
            if constexpr (sizeof...(Keys) > 0) {
                JsonDocument nestedWrapper(jsonValue);
                // Recursive call to getMultipleArray for further nested arrays.
                return nestedWrapper.getMultipleArray<T>(keys...);
            } else {
                if (jsonValue.isArray()) {
                    const Json::Value& jsonArray = jsonValue;
                    for (unsigned int i = 0; i < jsonArray.size(); ++i)
                    {
                        T value;
                        if constexpr (std::is_same<T, JsonDocument>::value)
                        {
                            // Handle nested JsonDocument objects
                            JsonDocument nestedWrapper(jsonArray[i]);
                            value = nestedWrapper;
                        } else {
                            value = jsonArray[i].as<T>();
                        }
                        result.push_back(value);
                    }
                    return result;
                }
            }
        }
#endif
        throw std::runtime_error("Keys do not exist or the value is not an array.");
    }

    /**
     * Get all the keys in the JSON object.
     * @return A vector of keys.
     */
    std::vector<std::string> getKeys() const;

    /**
     * Check if the JSON object represents an array.
     * @return true if the JSON object is an array, false otherwise.
     */
    bool isArray() const;

    /**
     * Get the JSON values as a vector of pointers.
     * @return A vector of JSON value pointers.
     */
    std::vector<Types::JSonValue> getVectorJsonPtr();

    /**
     * Get the JSON object as a JsonDocument.
     * @return The JSON object as a JsonDocument.
     */
    JsonDocument getObject() const;

    /**
     * Set the JSON values as a vector of pointers.
     * @param data The JSON value to set.
     */
    void setVectorJsonPtr(const JSonValue& data);

private:
    Types::JSonValue m_root{}; //!< Root node of the JSON object
    std::vector<Types::JSonValue> vectorJsonPtr;
    Cell::FileSystem::FileManager fileManager{};
};


CELL_NAMESPACE_END

#endif  // CELL_JSON_HPP
