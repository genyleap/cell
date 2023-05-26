/*!
 * @file        core-meta.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System meta core programming.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CORE_META_HPP
#define CELL_CORE_META_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core-concepts.hpp")
#   include "core-concepts.hpp"
#else
#   error "Cell's "core-concepts.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Concepts;

CELL_NAMESPACE_BEGIN(Cell::Meta)


class MetaEngine {
public:
    /**
     * @brief Applies fixed precision formatting to a value.
     *
     * If the value is a floating-point type, it formats the value using std::fixed and std::setprecision.
     * If the value can be converted to std::string, it converts the value to a string.
     *
     * @tparam T The type of the value.
     * @param value The value to format.
     * @param precision The number of decimal places to keep (default: 0).
     * @return The formatted value as a string.
     */
    template <typename T>
    std::string applyFixedPrecision(T value, int precision = 0)
    {
        if constexpr (FloatingPoint<T>) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(precision) << value;
            return oss.str();
        } else if constexpr (ConvertibleToString<T>) {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        } else {
            static_assert(FloatingPoint<T> || ConvertibleToString<T>, "Unsupported type");
        }
    }

    /**
     * @brief Returns the data pointer of a string-like object.
     *
     * This function takes a const reference to an object of a type satisfying the ConvertibleToStringView concept,
     * and returns the data pointer of the string.
     *
     * @param str The string-like object.
     * @return const char* Pointer to the underlying character data of the string.
     */
    template <ConvertibleToStringView T>
    const char* returnView(const T& str)
    {
        return str.data();
    }

    template <typename... Args>
    static auto returnJsonAsObj(const JSonValue& jvalue, const Args&... args) {
        const auto* result = &jvalue;
#ifdef USE_BOOST
        ((result = &(result->at(args))), ...);
        return result->as_object();
#else
        ((result = &(result[args])), ...);
        return result;
#endif
    }

    struct RetJsonKeyValue final {
        std::string key;    //!< As Key.
        JSonArray   value;  //!< As Array value.
    };

    std::map<std::string, RetJsonKeyValue> extractJsonKeyValues(const JSonValue& object)
    {
        std::map<std::string, RetJsonKeyValue> keyValues;
        RetJsonKeyValue rjkv;
#ifdef USE_BOOST
        for (const auto& kv : object.as_object())
        {
            const std::string key = kv.key();
            const JSonValue& value = kv.value();
            rjkv.key = key;
            rjkv.value = value.as_array();
            keyValues[key] = RetJsonKeyValue(rjkv);
        }
#else
        for (Json::Value::const_iterator it = object.begin(); it != object.end(); ++it)
        {
            const std::string key = it.key().asString();
            const JSonValue& value = *it;
            rjkv.key = key;
            rjkv.value = value;
            keyValues[key] = RetJsonKeyValue(rjkv);
        }
#endif
        return keyValues;
    }


    /**
     * @brief Structure representing a JSON value with various data types.
     */
    struct RetObjectStruct final {
        std::string                                       asString;   //!< String value
        bool                                              asBool;     //!< Boolean value
        double                                            asDouble;   //!< Double value
        int                                               asInt64;    //!< Int64 value
        std::vector<RetObjectStruct>                      asArray;    //!< Array value
        std::unordered_map<std::string, RetObjectStruct>  asObject;   //!< Object value
    };


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

    template <typename... Args>
    static auto returnJsonAsArr(const JSonValue& jvalue, const Args&... args) {
        const auto* result = &jvalue;
#ifdef USE_BOOST
        ((result = &(result->at(args))), ...);
        return result->as_array();
#else
        ((result = &(result[args])), ...);
        return result;
#endif
    }


    /**
     * @brief Structure representing a JSON value with various data types.
     */
    struct RetJsonStruct final {
        std::string                                     asString;   //!< String value
        bool                                            asBool;     //!< Boolean value
        double                                          asDouble;   //!< Double value
        int                                             asInt64;    //!< Int64 value
        std::vector<RetJsonStruct>                      asArray;    //!< Array value
        std::unordered_map<std::string, RetJsonStruct>  asObject;   //!< Object value
    };

    /**
     * @brief Retrieve JSON value at the specified path.
     *
     * This function retrieves the JSON value at the specified path within the given JSON value.
     * It supports traversing nested JSON structures and populates a RetJsonStruct object with the retrieved values.
     *
     * @param jvalue The JSON value to traverse.
     * @param args The path to the desired value.
     * @return RetJsonStruct The retrieved JSON value(s) as a RetJsonStruct object.
     */
    template <typename... Args>
    static RetJsonStruct returnJsonAt(const JSonValue& jvalue, const Args&... args)
    {
        auto result = &jvalue;
        RetJsonStruct retStruct;
#ifdef USE_BOOST
        ((result = &(result->at(args))), ...);
        if (result->is_string()) {
            retStruct.asString = result->as_string();
        } else if (result->is_bool()) {
            retStruct.asBool = result->as_bool();
        } else if (result->is_int64()) {
            retStruct.asInt64 = result->as_int64();
        } else if (result->is_double()) {
            retStruct.asDouble = result->as_double();
        } else if (result->is_array()) {
            for (const auto& value : result->as_array()) {
                retStruct.asArray.push_back(returnJsonAt(value));
            }
        } else if (result->is_object()) {
            for (const auto& keyValue : result->as_object()) {
                retStruct.asObject[keyValue.key()] = returnJsonAt(keyValue.value());
            }
        }
#else
        ((result = &(result->operator[](args))), ...);

        if (result->isString()) {
            retStruct.asString = result->asString();
        } else if (result->isBool()) {
            retStruct.asBool = result->asBool();
        } else if (result->isInt64()) {
            retStruct.asInt64 = result->asInt64();
        } else if (result->isDouble()) {
            retStruct.asDouble = result->asDouble();
        } else if (result->isArray()) {
            for (const auto& value : *result) {
                retStruct.asArray.push_back(returnJsonAt(value));
            }
        } else if (result->isObject()) {
            for (const auto& keyValue : result->getMemberNames()) {
                retStruct.asObject[keyValue] = returnJsonAt((*result)[keyValue]);
            }
        }
#endif
        return retStruct;
    }

};

CELL_NAMESPACE_END

#endif // CELL_CORE_META_HPP
