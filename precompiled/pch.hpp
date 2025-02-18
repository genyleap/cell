/*!
 * Gen3 License
 *
 * Copyright (c) 2024 Kambiz Asadzadeh (compez.eth)
 * Copyright (c) 2024 Genyleap
 */

#ifndef PCH_HPP
#define PCH_HPP

/*!
 * Creating and using precompiled headers can do two major things for you:
 * Can reduce the compilation time of C++ files.
 * Can reduce the number of lines of code that the compiler must process (in some cases, by several orders of magnitude).
 */
#if __has_include(<utilities/preprocessor.hpp>)
#   include <utilities/preprocessor.hpp>
#else
#   include <utilities/preprocessor.hpp>
#endif

//!Header files for the C++ standard library and extensions, by category.

#ifdef CXX_STANDARD_98
#error "C++11 or better is required"
#endif

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

//!C++ Style
#include <stdexcept>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <string_view>
#include <stack>

//!Algorithms
#include <algorithm>
#include <cstdlib>
#include <numeric>

//!Added in the C++20 standard
#if defined(CXX_STANDARD_20)
#if __has_include(<concepts>)
#   include <concepts>
#endif
#endif

/*C++ Standard Library Containers*/

//!Sequence containers
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

//!Ordered associative containers
#include <map>
#include <set>

//! Unordered associative containers
#include <unordered_map>
#include <unordered_set>

//!Container adaptors
#include <queue>
#include <stack>

//!Container views
#if defined(CXX_STANDARD_20)
#if __has_include(<span>)
#   include <span>
#endif
#endif

//!Errors and exception handling
#include <cassert>
#include <exception>
#include <stdexcept>
#include <system_error>

//!General utilities
#include <any>

#include <bitset>
#include <cstdlib>

#if defined(CXX_STANDARD_20)
#if __has_include(<execution>)
#   include <execution>
#endif
#endif

#include <functional>
#include <memory>

#if defined(CXX_STANDARD_20)
#if __has_include(<memory_resource>)
#   include <memory_resource>
#endif
#endif

#include <optional>
#include <ratio>
#include <scoped_allocator>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <utility>
#include <variant>

//!Multithreading
#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <thread>

//!I/O and formatting
#include <cinttypes>
#include <cstdio>

#ifdef CXX_STANDARD_20
#if __has_include(<filesystem>)
#   include <filesystem>
#endif
#endif

#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <streambuf>

#if defined(CXX_STANDARD_20)
#if __has_include(<syncstream>)
#   include <syncstream>
#endif
#endif

//!Iterators
#include <iterator>

//!Language support
#include <cfloat>
#include <climits>
#include <codecvt>


#if defined(CXX_STANDARD_20)
#if __has_include(<compare>)
#   include <compare>
#endif
#endif

#if defined(CXX_STANDARD_20)
#if __has_include(<contract>)
#   include <contract>
#endif
#endif

#if defined(CXX_STANDARD_20)
#if __has_include(<coroutine>)
#   include <coroutine>
#endif
#endif

#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <limits>
#include <new>
#include <typeinfo>

#if defined(CXX_STANDARD_20)
#if __has_include(<version>)
#   include <version>
#endif
#endif

//!Ranges
#if defined(CXX_STANDARD_20)
#if __has_include(<ranges>)
#   include <ranges>
#endif
#endif

//!Regular expressions
#include <regex>

//!Strings and character data
#include <charconv>
#include <cctype>
#include <cstdlib>
#include <cstring>

#if defined(CXX_STANDARD_20)
#if __has_include(<cuchar>)
#   include <cuchar>
#endif
#endif

#include <cwchar>
#include <cwctype>
#include <regex>
#include <string>
#include <string_view>

//!Time
#include <chrono>
#include <ctime>

//!C-style Under C++
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

//!Localization
#include <clocale>
#include <codecvt>
#include <locale>

//!Math and numerics
#if defined(CXX_STANDARD_20)
#if __has_include(<bit>)
#   include <bit>
#endif
#endif
#include <cfenv>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <limits>
#include <numeric>
#include <random>
#include <ratio>
#include <valarray>
#include <ranges>

//!Memory management
#if __has_include(<allocators>)
#   include <allocators>
#endif
#include <memory>
#if __has_include(<memory_resource>)
#   include <memory_resource>
#endif
#include <new>
#include <scoped_allocator>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cpp_lib_json
#    include <json>
#else
#if __has_include(<boost/json.hpp>)
#    include <boost/json.hpp>
# elif __has_include(<json/json.h>)
#    include <json/json.h>
#endif
#endif

#if __cpp_lib_format
#    include <format>
#else
#if __has_include(<boost/format.hpp>)
#    include <boost/format.hpp>
# elif __has_include(<fmt/format.h>)
#    include <fmt/format.h>
#endif
#endif

#if defined(CELL_PLATFORM_MAC)
#   include "unix/pch.hpp"
#elif defined(CELL_PLATFORM_LINUX)
#   include "linux/pch.hpp"
#elif defined(CELL_PLATFORM_FREEBSD)
#   include "unix/pch.hpp"
#elif defined(CELL_PLATFORM_WINDOWS)
#   include "win32/pch.hpp"
#endif

#endif // PCH_HPP
