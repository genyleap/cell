# Package Info.
set(ZEROMQ_NAME "ZeroMQ")
set(ZEROMQ_DESCRIPTION "An open-source universal messaging library")
# Pakcage option.
option(USE_ZEROMQ ${ZEROMQ_DESCRIPTION} FALSE)
if (USE_ZEROMQ)
    add_definitions(-DUSE_ZEROMQ)
    # Define the repository URL and tag for the ZEROMQ libraries
    set(ZEROMQ_URL "https://github.com/zeromq/libzmq.git")
if(FORCE_UPGRADED_LIBS)
    set(ZEROMQ_TAG "master")
else()
    set(ZEROMQ_TAG "v4.3.4")
endif()
    set(ZEROMQ_LIB_LIST "zmq" CACHE STRING "List of modules (separated by a semicolon)")
endif()

find_package(PkgConfig QUIET)
pkg_search_module(ZEROMQ ZEROMQ)
# Package data repository.
if(USE_ZEROMQ)
    set(FETCHCONTENT_QUIET off)
    get_filename_component(ZEROMQ_base "${CMAKE_CURRENT_SOURCE_DIR}/${THIRD_PARTY}/${ZEROMQ_NAME}"
        REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
    set(FETCHCONTENT_BASE_DIR ${ZEROMQ_base})
    # Declare the ZEROMQ libraries with their submodules using FetchContent_Declare
    FetchContent_Declare(
        ZEROMQ
        GIT_REPOSITORY ${ZEROMQ_URL}
        GIT_TAG ${ZEROMQ_TAG}
        GIT_PROGRESS   TRUE
        USES_TERMINAL_DOWNLOAD TRUE
        )
    # Check if population has already been performed
    FetchContent_GetProperties(ZEROMQ)
    string(TOLOWER "${ZEROMQ_NAME}" lcName)
    if(NOT ${lcName}_POPULATED)
        FetchContent_Populate(${lcName})
        add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
    FetchContent_MakeAvailable(ZEROMQ)
    foreach(module IN LISTS ZEROMQ_LIB_LIST)
        list(APPEND LIB_MODULES ${module})
    endforeach()
endif()
if(NOT ZEROMQ_FOUND)
    return()
endif()
