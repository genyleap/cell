# Package Info.
set(CPPZMQ_NAME "ZeroCppMQ")
set(CPPZMQ_DESCRIPTION "C++ binding for ZeroMQ")
# Package option.
option(USE_CPPZMQ ${CPPZMQ_DESCRIPTION} FALSE)
if (USE_CPPZMQ)
    add_definitions(-DUSE_CPPZMQ)
    # Define the repository URL and tag for the cppzmq library
    set(CPPZMQ_URL "https://github.com/zeromq/cppzmq.git")
    set(CPPZMQ_TAG "master")
    set(CPPZMQ_LIB_LIST "cppzmq" CACHE STRING "List of modules (separated by a semicolon)")
endif()

# Package data repository.
if(USE_CPPZMQ)
    set(FETCHCONTENT_QUIET off)
    get_filename_component(CPPZMQ_BASE "${CMAKE_CURRENT_SOURCE_DIR}/${THIRD_PARTY}/${CPPZMQ_NAME}"
        REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
    set(FETCHCONTENT_BASE_DIR ${CPPZMQ_BASE})
    # Declare the cppzmq library using FetchContent_Declare
    include(FetchContent)
    FetchContent_Declare(
        ${CPPZMQ_NAME}
        GIT_REPOSITORY ${CPPZMQ_URL}
        GIT_TAG ${CPPZMQ_TAG}
        GIT_PROGRESS   TRUE
        USES_TERMINAL_DOWNLOAD TRUE
    )
    # Check if population has already been performed
    FetchContent_GetProperties(${CPPZMQ_NAME})
    string(TOLOWER "${CPPZMQ_NAME}" lcName)
    if(NOT ${lcName}_POPULATED)
        FetchContent_Populate(${lcName})
        include_directories(${${lcName}_SOURCE_DIR})
        add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
    FetchContent_MakeAvailable(${lcName})
    foreach(module IN LISTS CPPZMQ_LIB_LIST)
        list(APPEND LIB_MODULES ${module})
    endforeach()
endif()

if(NOT USE_CPPZMQ)
    return()
endif()
