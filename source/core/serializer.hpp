/*!
 * @file        serializer.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Serializer interface for data structure.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SERIALIZER_HPP
#define CELL_SERIALIZER_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::System::Serialization)

/**
 * @brief The DataSerializerStruct class
 */
struct DataSerializerStruct final {
#if defined(USE_BOOST)
///<! An alias JsonSerialize for the function pointer type std::string(*)(const boost::json::value&), which is the type of boost::json::serialize.
using JsonBoostSerialize = std::string(*)(const boost::json::value&);
JsonBoostSerialize builder = boost::json::serialize; ///<! builder is serialize variable using the alias [based on boost].
#else
    Json::StreamWriterBuilder builder;  ///<! builder is serialize variable using the alias. [based on jsoncpp].
#endif
};

class DataSerializer {
public:
/**
 * @brief Construct a new Data Serializer object
 *
 */
DataSerializer();

/**
 * @brief Destroy the Data Serializer object
 *
 */
~DataSerializer();

/**
 * @brief Serialize JSON data to string
 *
 * @param jsonValue JSON data to be serialized
 * @return std::string Serialized JSON string
 */
std::string serializeJson(const Types::JSonValue& jsonValue);

/**
 * @brief Serialize JSON data to file
 *
 * @param file File path to serialize JSON data to
 */
void serializeJsonByFile(const std::string& file);

private:
    DataSerializerStruct dataSerializerStruct {}; /**< Data Serializer structure */

};

CELL_NAMESPACE_END

#endif // CELL_SERIALIZER_HPP
