#ifndef CELL_DATABASEB_ABSTRACT_INCLUDES_HPP
#define CELL_DATABASEB_ABSTRACT_INCLUDES_HPP

#if __has_include("abstracts/database/connection.hpp")
#include "abstracts/database/connection.hpp"
#else
#error "Cell's abstracts/database/connection.hpp was not found!"
#endif

#if __has_include("abstracts/database/connectionpool.hpp")
#include "abstracts/database/connectionpool.hpp"
#else
#error "Cell's abstracts/database/connectionpool.hpp was not found!"
#endif

#if __has_include("abstracts/database/datamanipulator.hpp")
#include "abstracts/database/datamanipulator.hpp"
#else
#error "Cell's abstracts/database/datamanipulator.hpp was not found!"
#endif

#if __has_include("abstracts/database/maintenance.hpp")
#include "abstracts/database/maintenance.hpp"
#else
#error "Cell's abstracts/database/maintenance.hpp was not found!"
#endif

#if __has_include("abstracts/database/management.hpp")
#include "abstracts/database/management.hpp"
#else
#error "Cell's abstracts/database/management.hpp was not found!"
#endif

#if __has_include("abstracts/database/query.hpp")
#include "abstracts/database/query.hpp"
#else
#error "Cell's abstracts/database/query.hpp was not found!"
#endif

#if __has_include("abstracts/database/querybuilder.hpp")
#include "abstracts/database/querybuilder.hpp"
#else
#error "Cell's abstracts/database/querybuilder.hpp was not found!"
#endif

#if __has_include("abstracts/database/tableanalyzer.hpp")
#include "abstracts/database/tableanalyzer.hpp"
#else
#error "Cell's abstracts/database/tableanalyzer.hpp was not found!"
#endif

#if __has_include("abstracts/database/querybuilder.hpp")
#include "abstracts/database/querybuilder.hpp"
#else
#error "Cell's abstracts/database/querybuilder.hpp was not found!"
#endif

#if __has_include("abstracts/database/transaction.hpp")
#include "abstracts/database/transaction.hpp"
#else
#error "Cell's abstracts/database/transaction.hpp was not found!"
#endif

#if __has_include("abstracts/database/tablemanager.hpp")
#include "abstracts/database/tablemanager.hpp"
#else
#error "Cell's abstracts/database/tablemanager.hpp was not found!"
#endif

#endif // CELL_DATABASEB_ABSTRACT_INCLUDES_HPP
