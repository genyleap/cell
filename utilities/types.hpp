/*!
 *
 * Copyright (c) 2024 Kambiz Asadzadeh (compez.eth)
 * Copyright (c) 2024 Genyleap
 */

#ifndef PROJECT_TYPES_HPP
#define PROJECT_TYPES_HPP

#if __has_include(<precompiled/pch.hpp>)
#   include <precompiled/pch.hpp>
#else
#   include <precompiled/pch.hpp>
#endif

#if __has_include(<cstdint>)
#   include <cstdint>
#endif

#if defined(USE_JSON) && !defined(USE_BOOST)
#   include <json/json.h>
using JSonValue = Json::Value;
using JSonArray = JSonValue;
using JSonObject = JSonValue;
#   elif defined(USE_BOOST)
#   include <boost/json.hpp>
using JSonValue = boost::json::value;
using JSonObject = boost::json::object;
using JSonArray = boost::json::array;
#   elif !defined(USE_JSON) && !defined(USE_BOOST)
#if __cpp_lib_json
#   include <json>
#else
#error There is no any json library!
#endif
#endif
#if __has_include(<openssl/aes.h>)
#   include <openssl/opensslv.h>
#   include <openssl/core_names.h>
#   include <openssl/aes.h>
#   include <openssl/des.h>
#   include <openssl/bio.h>
#   include <openssl/evp.h>
#   include <openssl/rsa.h>
#   include <openssl/pem.h>
#   include <openssl/ssl.h>
#   include <openssl/err.h>
#define ENABLE_OPENSSL 1
#endif


#ifdef __cpp_lib_format
#   include <format>
#define USE_STL_FORMAT
#else
#ifdef USE_FMT
#   include <fmt/format.h>
#define USE_FMT_FORMAT
#elif defined(USE_BOOST) && !defined(USE_FMT)
#   include <boost/format.hpp>
#define USE_BOOST_FORMAT
#endif
#endif

#ifdef USE_ZLIB
#ifdef __has_include
# if __has_include("zlib.h")
#   include "zlib.h"
#else
#   error "Cell's "zlib.h" was not found!"
# endif
#endif
#else
#error There is no any zlib library!
#endif

#include <variant>

#ifdef USE_MYSQL_MARIADB
#include "mariadb/mysql.h"
using MySqlConnectPtr = MYSQL*;
using MySqlPtr = MYSQL*;
#endif

#ifdef USE_POSTGRESQL
#include <libpq-fe.h>
using PsqlConnectPtr = PGconn*;
using PostgreSqlPtr = PGconn*;
#endif

#ifdef USE_SQLITE
#include <sqlite3.h>
using SqliteConnectPtr = sqlite3*;
using SqlitePtr = sqlite3*;
#endif

#ifdef USE_MSSQL
#include <sql.h>
#include <sqlext.h>
using MssqlConnectPtr = SQLHANDLE;
using SqlServerPtr = SQLHANDLE;
#endif

#ifdef USE_ORACLE
#include <occi.h>
using OraclePtr = oracle::occi::Connection*;
using OracleConnectPtr = oracle::occi::Connection*;
#endif


#ifdef _WIN32
#include <Windows.h>
#include <VersionHelpers.h>
#include <winsock2.h>
#pragma comment(lib, "Version.lib")
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/event.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace Cell::Types {

using schar        = signed char;
using uchar        = unsigned char;
using ushort       = unsigned short;
using uint         = unsigned int;
using ulong        = unsigned long;
using ullong       = unsigned long long;
using ullongInt    = unsigned long long int;
using llong        = long long;

//! Fixed width integer types (since C++11)
//! Signed integer type
using s8  = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

#ifdef USE_BOOST
using s128 = __int128;
using u128 = unsigned __int128;
#else
using s128 = __int128;
using u128 = unsigned __int128;
#endif

//! Fastest signed integer type with width of at least 8, 16, 32 and 64 bits respectively.
using fs8  = std::int_fast8_t;
using fs16 = std::int_fast16_t;
using fs32 = std::int_fast32_t;
using fs64 = std::int_fast64_t;

//! Smallest signed integer type with width of at least 8, 16, 32 and 64 bits respectively.
using ss8  = std::int_least8_t;
using ss16 = std::int_least16_t;
using ss32 = std::int_least32_t;
using ss64 = std::int_least64_t;

using smax = std::intmax_t; //! Maximum-width signed integer type.
using sptr = std::intptr_t; //! Signed integer type capable of holding a pointer to void.

//! Unsigned integer type with width of exactly 8, 16, 32 and 64 bits respectively.
using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

//! Fastest unsigned integer type with width of at least 8, 16, 32 and 64 bits respectively.
using fu8  = std::uint_fast8_t;
using fu16 = std::uint_fast16_t;
using fu32 = std::uint_fast32_t;
using fu64 = std::uint_fast64_t;

//! Smallest unsigned integer type with width of at least 8, 16, 32 and 64 bits respectively.
using su8  = std::uint_least8_t;
using su16 = std::uint_least16_t;
using su32 = std::uint_least32_t;
using su64 = std::uint_least64_t;

using f32  = float;
using f64  = double;

using b8   = bool;

using size   = size_t;

using umax = std::uintmax_t; //! Maximum-width unsigned integer type
using uptr = std::uintptr_t; //! Unsigned integer type capable of holding a pointer to void.

using VariantTypes      = std::map<std::string, std::variant<std::string, std::string_view, int, double, bool>>;
using MapList           = std::pair<std::string, std::map<std::string, std::string>>;
using MapVector         = std::pair<std::string, std::vector<std::string>>;
using IteratorConfig    = std::map<std::string, std::string>::iterator;
using LanguageType      = std::map<std::string, std::string>;
using LanguageCodes     = std::vector<std::string>;
using MetaList          = std::map<std::string, std::string>;
using ResourceType      = std::map<std::string, std::string>;
using MapConfig         = std::map<std::string, std::string>;
using MapString         = std::map<std::string, std::string>;
using PairString        = std::pair<std::string, std::string>;
using SettingType       = std::map<int, std::string>;
using VectorString      = std::vector<std::string>;
using VectorSection     = std::vector<std::string>;
using OptionalString    = std::optional<std::string>;
using OptionalWString   = std::optional<std::wstring>;

using HttpQueryString   = std::unordered_map<std::string, std::string>;
using Headers           = std::unordered_map<std::string, std::string>;
using MimeTypes         = std::unordered_map<std::string, std::string>;
using StaticFiles       = std::unordered_map<std::string, std::string>;

using OptionalNumeric   = std::optional<int>;
using OptionalBool      = std::optional<bool>;

//! For Settings.
using SettingComment    = std::map<std::string, std::vector<std::string>>;
using SettingData       = std::map<std::string, std::map<std::string, std::string>>;

#if defined(USE_JSON) && !defined(USE_BOOST)
namespace JsonSpace        = Json;
using JSonValue            = Json::Value;
using JSonParser           = Json::Reader;
using OptionalJsonVal      = std::optional<Json::Value>;
using JSonException        = Json::Exception;
#   elif defined(USE_BOOST)
namespace JsonSpace        = boost::json;
using JSonValue            = boost::json::value;
using JSonParser           = boost::json::stream_parser;
using OptionalJsonVal      = std::optional<boost::json::value>;
#   elif !defined(USE_JSON) && !defined(USE_BOOST)
#if __cpp_lib_json
namespace JsonSpace      = std::json;
#endif
#endif

/**
 * @brief Represents a connection to a SQL database.
 * This type alias defines a C++ union type using `std::variant`, which allows for type-safe handling of multiple
 * possible database connection objects.
 * The `SqlConnection` typedef is a std::variant type that can hold a connection pointer to one of the following database types:
 * - Mariadb MySQL, PostgreSql, SqlServer, Oracle and Sqlite.
 *
 * The connection pointer returned by each database type should be of type `std::shared_ptr<DatabaseConnection>`.
 */

#if defined(USE_MYSQL_MARIADB) && defined(USE_POSTGRESQL) && defined(USE_SQLITE) && defined(USE_MSSQL) && defined(USE_ORACLE)
using SqlConnection         = std::variant<MySqlPtr, PostgreSqlPtr, SqlServerPtr, OraclePtr, SqlitePtr>;
using DbConnectionQueue     = std::deque<Types::SqlConnection>;
#endif

using BigNumberVariant = std::variant<uint, u64, u128>;

namespace Fs = std::filesystem;

using TableNames        = std::vector<std::string>;
using QueryType         = std::vector<std::string>;
using TranslateType     = std::string;

using JSonType = std::variant<std::string, std::ifstream>;

template<typename T1, typename T2> using UnorderedMap      = std::unordered_map<T1, T2>;
template<typename T1, typename T2> using Map      = std::map<T1, T2>;
template<typename T1, typename T2> using MultiMap = std::multimap<T1, T2>;
template<typename T1, typename T2> using UnorderedMultiMap = std::unordered_multimap<T1, T2>;
template<typename T1, typename T2> using Pair     = std::pair<T1, T2>;

template<typename T> using Vector        = std::vector<T>;
template<typename T> using Optional      = std::optional<T>;
template<typename T> using Variant       = std::variant<T>;

#ifdef USE_CURL
#include <curl/curl.h>
using CELL_CURL = CURL;
using CELL_CURLPTR = CURL*;
using SmartCurlPtr = std::unique_ptr<Types::CURL, decltype(&Types::curl_easy_cleanup)>;
using FunctionCurl = std::function<void(Types::CURL*)>;
#endif

#ifdef _WIN32
typedef SOCKET SocketType;
#else
typedef int SocketType;
#endif

using Function              = std::function<void(void)>;
using LockGuard             = std::lock_guard<std::mutex>;
using FutureStringObject    = std::future<std::string>;
using PromiseStringObject   = std::promise<std::string>;

using Mutex                 = std::mutex;
using PackagedTask          = std::packaged_task<void(void)>;
using MultiThreadVector     = std::vector<std::thread>;
using StringStream          = std::basic_stringstream<char>;
using String                = std::string;
using IfStreamer            = std::ifstream;
using StringStream          = std::stringstream;
using RuntimeError          = std::runtime_error;

using ConditionVariable     = std::condition_variable;
using QueryCache            = std::unordered_map<std::string, std::vector<std::vector<std::string>>>;

#define DO_NOTHING  void();

}

#endif // PROJECT_TYPES_HPP
