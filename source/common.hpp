/*!
 * Gen3 License
 *
 * @file        common.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_COMMON_HPP
#define CELL_COMMON_HPP

/*!
 * C++20 introduces modules, a modern solution for componentization of C++ libraries and programs.
 * A module is a set of source code files that are compiled independently of the translation units that import them.
 * Modules eliminate or greatly reduce many of the problems associated with the use of header files, and also potentially reduce compilation times.
 * Macros, preprocessor directives, and non-exported names declared in a module are not visible and therefore have no effect on the compilation of the translation unit that imports the module.
 * You can import modules in any order without concern for macro redefinitions. Declarations in the importing translation unit do not participate in overload resolution or name lookup in the imported module.
 * After a module is compiled once, the results are stored in a binary file that describes all the exported types, functions and templates. That file can be processed much faster than a header file, and can be reused by the compiler every place where the module is imported in a project.
 *
!*/

#include "utilities/preprocessor.hpp"
#include "utilities/featuretest.hpp"
#include "utilities/types.hpp"
#include "defines.hpp"

#ifdef USE_LATEST_STANDARD
////TODO use module...
#else
///!
#endif

#if __cplusplus > 201703
#if __has_include("precompiled/pch.hpp")
#    include "precompiled/pch.hpp"
#else
#     pragma message("Your project is based on classic precompiled-header system.")
#endif
#else
# include "precompiled/pch.hpp"
#endif

namespace Cell {

#define CELL_LANGUAGE_SPEC "language-spec"
#define CELL_LANGS "langs"
#define CELL_DEFAULT_LANG "default_lang"

struct LANGUAGE_SHEET final {
  static constexpr auto GLOBAL      = "global";
  static constexpr auto EXCEPTION   = "exceptions";
};

struct CONFIG final {
  static constexpr std::string_view FRAMEWORK_CONFIG_FILE = "config.json";
  static constexpr std::string_view SYSTEM_CONFIG_FILE = "config/system-config.json";
  static constexpr std::string_view SYSTEM_TRANSLATOR_CONFIG_FILE = "config/globalization-config.json";
  static constexpr std::string_view SYSTEM_CUSTOM_FILE = "config/custom-setting.json";
  static constexpr std::string_view SYSTEM_DATABASE_FILE = "config/system-database.json";
  static constexpr std::string_view SYSTEM_INTERFACE_FILE = "config/system-interface.json";
  static constexpr std::string_view SYSTEM_MODULES_FOLDER = "modules/";
  static constexpr std::string_view SYSTEM_PLUGINS_FOLDER = "plugins/";
  static constexpr std::string_view SYSTEM_TABLES_PREFIX = "teg_";
  static constexpr std::string_view SYSTEM_TABLES_VALUE_STRUCT = "_l";
  static constexpr std::string_view SYSTEM_TABLES_TABLE_UNICODE = "utf-8";
  static constexpr std::string_view SYSTEM_TABLES_COOKIE_PREFIX = "cell_";
  static constexpr std::string_view TRANSLATION_FILE = "translations/contents.json";

  static constexpr std::string_view MODULE_FILE_SUFFIX = ".tegx";
  static constexpr std::string_view PLUGIN_FILE_SUFFIX = ".plugin";

  static constexpr std::string_view OFFICIAL_WEB_API_URL = "https://cell.genyleap.com";
  static constexpr std::string_view OFFICIAL_WEB = "http://genyleap.com";
  static constexpr std::string_view OFFICIAL_EMAIL = "info@genyleap.com";
};

struct STATICS final {

  //!INDEX
  static constexpr std::string_view INDEX_PATH        = "{}";
  static constexpr std::string_view INDEX_PATH_SCOPE  = "";

  //!ADMIN
  static constexpr std::string_view ADMIN_PATH        = "dashboard";
  static constexpr std::string_view ADMIN_PATH_SCOPE  = "dashboard/";

  //!INSTALLER
  static constexpr std::string_view INSTALL_PATH                = "install";
  static constexpr std::string_view INSTALL_PATH_SCOPE          = "install/";
  static constexpr std::string_view INSTALL_INIT_PATH           = "install/init";
  static constexpr std::string_view INSTALL_INIT_PATH_SCOPE     = "install/init/";
  static constexpr std::string_view INSTALL_DATABASE_PATH       = "install/database";
  static constexpr std::string_view INSTALL_DATABASE_PATH_SCOPE = "install/database/";
  static constexpr std::string_view INSTALL_FINALIZE_PATH       = "install/finalize";
  static constexpr std::string_view INSTALL_FINALIZE_PATH_SCOPE = "install/finalize/";
  static constexpr std::string_view INSTALL_COMPLETE_PATH       = "install/complete";
  static constexpr std::string_view INSTALL_COMPLETE_PATH_SCOPE = "install/complete/";
};

}

#undef CELL_COPYRIGHT
#define CELL_COPYRIGHT "<!-- ]]></script> -->Copyright © 2022 <a class=\"nav-link d-inline-block p-0\" href=\"https://genyleap.com\" rel=\"noopener\" target=\"_blank\">Cell System</a> <!-- Cell System Team -->"

#define STLLIB_STANDARD             0x0
#define STLLIB_TECHNICAL_REPORT     0x1
#define STLLIB_EXPERIMENTAL         0x2
#define STLLIB_BOOST                0x3
#define STLLIB_NETWORKING_ERROR "We don't even have access to networking TS."
#define STLLIB_SYSTEM_ERROR "We don't even have access to system TS."
#define BOOST_ASIO_NO_DEPRECATED

//! Compiler Predefined Variables.

#define __cell_null_str ""
#define __cell_space " "
#define __cell_zero 0
#define __cell_exit 0
#define __cell_one 1
#define __cell_newline "\n"
#define __cell_compiler_counter __COUNTER__
#define __cell_compiler_line __LINE__
#define __cell_compiler_file __FILE__
#define __cell_compiler_function __FUNCTION__
#define __cell_compiler_pretty_function __PRETTY_FUNCTION__
#define __cell_compiled_date __DATE__
#define __cell_compiler_time __TIME__

#define __cell_has_include __has_include
#define __cell_charset "utf-8"
#define __cell_unknown "unknown"

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T>
constexpr Scope<T> CreateScope()
{
  return std::make_unique<T>();
}

template<typename T, typename ... Args>
constexpr Scope<T> CreateForwardScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

#define CELL_SCOPE_POINTER(Class, alias, param) std::unique_ptr<Class>alias(new Class(param));

template<typename T>
using Ref = std::shared_ptr<T>;

#define CELL_REF_SHARED_POINTER(Class, alias, param) std::shared_ptr<Class>alias(new Class(param));

template<typename T>
constexpr Ref<T> CreateRef()
{
    return std::make_shared<T>();
}

template<typename T, typename ... Args>
constexpr Ref<T> CreateForwardRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#define CELL_POINTER_TO_AN_OBJECT(object, name)\
typedef object* (*name)();

#define CELL_POINTER_TO_A_FUNCTION void(*)()

#define __cell_safe_instance(object, Class) \
object = new Class();\

#define __cell_safe_instance_rhs(object, Class, rhs) \
object = new Class(rhs);\

#define __cell_smart_instance(object, Class) \
object = CreateScope<Class>();\

#define __cell_smart_instance_rhs(object, Class, rhs) \
object = CreateScope<Class>(rhs);\

#define __cell_smart_forward_instance(object, Class) \
object = CreateForwardScope<Class>();\

#define __cell_smart_forward_instance_rhs(object, Class, rhs) \
    object = CreateForwardScope<Class>(rhs);\

#define DeclareSingletonSelf(Class) \
static Class& self();

#define CreateSingletonSelf(Class) \
Class& Class::self()\
{\
        static Class classObject;\
        return classObject;\
}

#define DeclareSingletonInstance(Class) \
static Class& instance();

#define CreateSingletonInstance(Class) \
Class& Class::instance()\
{\
    static Class classObject;\
    return classObject;\
}

#define __cell_safe_delete(object) \
if(object!=nullptr)                 \
{ delete object;}                   \
object = nullptr;                   \

#define __cell_null_optional std::nullopt

#define __cell_abort abort();

#define __cell_atexit(x) atexit(x); // C Style.

#define __cell_assert(x) assert(x);

#define CELL_BRACE_BEGIN {
#define CELL_BRACE_END }
#define CELL_USING_NAMESPACE using namespace
#define CELL_NAMESPACE_BEGIN(x) namespace x {
#define CELL_ANONYMOUS_NAMESPACE_BEGIN namespace {
#define CELL_NAMESPACE_END }
#define CELL_USING using
#define CELL_NAMESPACE namespace

/*
 * C++11 keywords and expressions
 */
#ifdef CELL_COMPILER_NULLPTR
# define __cell_nullptr         nullptr
#else
# define __cell_nullptr         NULL
#endif

# define __cell_override override
# define __cell_final final

# define __cell_const const
# define __cell_const_noexcept const noexcept
# define __cell_const_noexcept_override const noexcept override
# define __cell_noexcept_override noexcept override
# define __cell_noexcept noexcept
# define __cell_noexcept_expr(x) noexcept(x)
# define __cell_constexpr_virtual virtual constexpr
# define __cell_constexpr constexpr
# define __cell_static_constexpr static constexpr
# define __cell_static_const static const
# define __cell_static_const_constexpr static const constexpr
# define __cell_inline_static_constexpr inline static constexpr
# define __cell_inline_static_const inline static const
# define __cell_inline_static inline static

#define __cell_pure_const_noexcept const noexcept = 0

#define __cell_no_return [[noreturn]]

#define __cell_no_discard [[nodiscard]]
#define __cell_no_discard_virtual [[nodiscard]] virtual
#define __cell_no_discard_message(x) [[nodiscard(x)]]

#define __cell_maybe_unused [[maybe_unused]]

#define __cell_virtual virtual

#define FROM_CELL_STRING(x) std::string(x)
#define TO_CELL_STRING(x) std::to_string(x)

#define CELL_PAGE_URL_REGEN(x) regen_url(x, 2)

#define BOOLCOMBINER(v1, v2) v1[v2].asBool()
#define STRCOMBINER(v1, v2) v1[v2].asString()
#define INTCOMBINER(v1, v2) v1[v2].asInt()
#define DBLCOMBINER(v1, v2) v1[v2].asDouble()
#define FLTCOMBINER(v1, v2) v1[v2].asFloat()

//! EXPORTS & EXTRA
#if defined(__WINNT) || defined(__WINNT__) || defined(WIN32) || \
defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) ||    \
    defined(WIN64) || defined(_WIN64) || defined(__WIN64) ||    \
    defined(__WIN64__)
//! Microsoft Windows
#define __cell_export __declspec(dllexport)
#define __cell_import __declspec(dllimport)
#elif defined(__GNUC__)
//! Define for Unix base OS such as: Linux, macOS, FreeBSD, etc...
#define __cell_export __attribute__((visibility("default")))
#define __cell_import __attribute__((visibility("default")))
#define __cell_hidden __attribute__((visibility("hidden")))
#else
//  do nothing and hope for the best?
#define __cell_export
#define __cell_import
#pragma warning Unknown dynamic link import / export semantics.
#endif

#define PointerToFunction void(*)()
#define PointerToObject(object, name)\
typedef object* (*name)();

#define CELL_HAS_INCLUDE __has_include
#define CELL_ENABLE_SHARED_FROM(x) std::enable_shared_from_this<x>

#define CELL_MOVE(x) std::move(x)

#define eprintf(format, ...) fprintf (stderr, format, __VA_ARGS__)

#define SCOPE :
#define SCOPE_LEFT (
#define SCOPE_RIGHT )
#define SCOPE_ENDS {}

#define __cell_extern_c extern "C"

#define __cell_export_pointer(Class, object)\
__cell_extern_c __cell_export Class* object = __cell_nullptr;

#define CELL_QUERY(...) #__VA_ARGS__

#define CELL_DEFAULT_OCTORS_WITHOUT_IMPL(Class) \
    Class() = default;\
    ~Class() = default;

#define CELL_DEFAULT_INTERFACE_OCTORS_WITHOUT_IMPL(Class) \
Class() = default;\
    virtual ~Class() = default;

#define CELL_DEFAULT_OCTORS(Class) \
Class();\
    ~Class();

#define CELL_DEFAULT_OCTORS_IMPL(Class)\
Class::Class(){}\
    Class::~Class(){}\

#define CELL_DEFAULT_INTERFACE_OCTORS(Class) \
Class();\
    virtual ~Class();

#define CELL_DEFAULT_INTERFACE_OCTORS_IMPL(Class)\
Class::Class() {}\
    Class::~Class(){}\

#define __cell_enum enum
#define __cell_enum_class enum class

#define __cell_shared_ptr(Class) \
std::shared_ptr<Class>

#define __cell_classic_ptr(Class, object) \
Class* object;\

/*!
 * \brief This struct represents a non-copyable object.
 */
struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;
};

/*!
 * \brief This struct represents a non-movable object.
 */
struct NonMovable
{
    NonMovable() = default;
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};

/*!
 * \brief This struct represents a non-copyable or non-movable object.
 */
struct NonMovableOrCopyable : private NonCopyable, NonMovable
{
    NonMovableOrCopyable() = default;
};

//!Macro version of non-copyable.
#define CELL_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

//!Macro version of non-movable.

#define CELL_DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

//!Macro version of non-copyable and non-movable.
#define CELL_DISABLE_COPY_MOVE(Class) \
    CELL_DISABLE_COPY(Class) \
    CELL_DISABLE_MOVE(Class)

//! Cell's Prestructure.
#if __has_include("prestructure.hpp")
#   include "prestructure.hpp"
#else
#   error "Cell's prestructure was not found!"
#endif

#endif // CELL_COMMON_HPP
