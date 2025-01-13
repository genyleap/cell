# Package Info.
set(MYSQL_NAME "MySQL")
set(MYSQL_DESCRIPTION "")
# Pakcage option.
option(USE_DB_MYSQL ${MYSQL_DESCRIPTION} FALSE)
if (USE_DB_MYSQL)
    add_definitions(-DUSE_DB_MYSQL)
    # Package Info.
    # Package Info.
    list(APPEND LIB_TARGET_INCLUDE_DIRECTORIES
        /opt/homebrew/Cellar/mariadb-connector-c/3.3.8/include
        /opt/homebrew/Cellar/instantclient-sdk/19.8.0.0.0dbru/include
        /opt/homebrew/Cellar/unixodbc/2.3.12/include/
        /opt/homebrew/Cellar/postgresql@16/16.1_1/include
    )
endif()

# Package Info.
set(PSQL_NAME "PostgreSQL")
set(PSQL_DESCRIPTION "")
# Pakcage option.
option(USE_DB_PSQL ${PSQL_DESCRIPTION} FALSE)
if (USE_DB_PSQL)
    add_definitions(-DUSE_DB_PSQL)
    # Package Info.
    list(APPEND LIB_MODULES
        /opt/homebrew/Cellar/mariadb-connector-c/3.3.8/lib/mariadb/libmariadb.3.dylib
        /opt/homebrew/Cellar/instantclient-basic/19.8.0.0.0dbru/lib/libclntsh.dylib
        /opt/homebrew/Cellar/unixodbc/2.3.12/lib/libodbc.2.dylib
        /opt/homebrew/Cellar/postgresql@16/16.1_1/lib/libpq.dylib
    )
endif()

# Package Info.
set(MSSQL_NAME "MSSql")
set(MSSQL_DESCRIPTION "")
# Pakcage option.
option(USE_DB_MSSQL ${MSSQL_DESCRIPTION} FALSE)
if (USE_DB_MSSQL)
    add_definitions(-DUSE_DB_MSSQL)
endif()

# Package Info.
set(ORACLE_NAME "Sqlite")
set(ORACLE_DESCRIPTION "")
# Pakcage option.
option(USE_DB_ORACLE ${ORACLE_DESCRIPTION} FALSE)
if (USE_DB_ORACLE)
    add_definitions(-DUSE_DB_ORACLE)
endif()

# Package Info.
set(SQLITE_NAME "Oracle")
set(SQLITE_DESCRIPTION "")
# Pakcage option.
option(USE_DB_SQLITE ${SQLITE_DESCRIPTION} FALSE)
if (USE_DB_SQLITE)
    add_definitions(-DUSE_DB_SQLITE)
endif()

# find_package(ODBC REQUIRED)
# find_package(PostgreSQL REQUIRED)
