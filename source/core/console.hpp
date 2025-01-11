/*!
 * Gen3 License
 *
 * @file        console.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */


#ifndef CELL_CELL_CONSOLE_HPP
#define CELL_CELL_CONSOLE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#include <print>

CELL_NAMESPACE_BEGIN(Cell::Console)

class Output {
 public:
  Output();
  ~Output();
}; ///ToDo...

/*
 * The standard output stream is the default destination of characters
 * determined by the environment. This destination may be shared with more
 * standard objects (such as cerr or clog).
 */

#define cellPrint(x) printf(#x "\n")

#define paster(n) printf("token" #n " = %d", token##n)

static std::ostream print(std::cout.rdbuf());

/*
 * The standard input stream is a source of characters determined by the
 * environment. It is generally assumed to be input from an external source,
 * such as the keyboard or a file.
 */

static std::istream get(std::cin.rdbuf());

/*
 * The standard error stream is a destination of characters determined by the
 * environment. This destination may be shared by more than one standard object
 * (such as cout or clog).
 */

static std::ostream error(std::cerr.rdbuf());

/*
 * The standard logging stream is a destination of characters determined by the
 * environment. This destination may be shared by more than one standard object
 * (such as cout or cerr).
 */

static std::ostream log(std::clog.rdbuf());

/*
 * The standard input stream is a source of characters determined by the
 * environment. It is generally assumed to be input from an external source,
 * such as the keyboard or a file.
 */

static std::wistream get_wide(std::wcin.rdbuf());

/*
 * The standard input stream is a source of characters determined by the
 * environment. It is generally assumed to be input from an external source,
 * such as the keyboard or a file.
 */

static std::wostream print_wide(std::wcout.rdbuf());

/*
 * The standard error stream is a destination of characters determined by the
 * environment. This destination may be shared by more than one standard object
 * (such as wcout or wclog).
 */

static std::wostream error_wide(std::wcerr.rdbuf());

/*
 * The standard logging stream is a destination of characters determined by the
 * environment. This destination may be shared by more than one standard object
 * (such as wcout or wcerr).
 */

static std::wistream log_wide(std::wclog.rdbuf());

#define newline '\n'

CELL_NAMESPACE_END

#endif  // CELL_CELL_CONSOLE_HPP
