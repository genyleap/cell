# Package Info.
set(POPPLER_NAME "Poppler")
set(POPPLER_DESCRIPTION "Poppler is a PDF rendering library based on the xpdf-3.0 code base.")

# Pakcage option.
option(USE_POPPLER ${POPPLER_DESCRIPTION} TRUE)
if (USE_POPPLER)
#    add_definitions(-DUSE_POPPLER)
    # Define the repository URL and tag for the POPPLER libraries
#    set(POPPLER_URL "https://anongit.freedesktop.org/git/poppler/poppler.git")
endif()

# Package Info.
list(APPEND LIB_TARGET_INCLUDE_DIRECTORIES
    /Users/compez/Documents/GitHub/cell/third-party/Poppler/poppler-src/cpp/
)

list(APPEND LIB_MODULES
    /Users/compez/Documents/GitHub/cell/third-party/Poppler/poppler-src/build/cpp/libpoppler-cpp.dylib
)


#find_package(PkgConfig QUIET)
#pkg_search_module(${POPPLER_NAME} POPPLER)
## Package data repository.
#if(USE_POPPLER)
#    set(FETCHCONTENT_QUIET off)
#    get_filename_component(POPPLER_base "${CMAKE_CURRENT_SOURCE_DIR}/${THIRD_PARTY}/${PLATFORM_FOLDER_NAME}/${POPPLER_NAME}"
#        REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
#    set(FETCHCONTENT_BASE_DIR ${POPPLER_base})
#    FetchContent_Declare(
#        POPPLER
#        GIT_REPOSITORY     ${POPPLER_URL}
#        GIT_PROGRESS   TRUE
#        )
#    # Check if population has already been performed
#    FetchContent_GetProperties(POPPLER)
#    string(TOLOWER "${POPPLER_NAME}" lcName)
#    if(NOT ${lcName}_POPULATED)
#        FetchContent_Populate(${lcName})
#        add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR} EXCLUDE_FROM_ALL)
#    endif()
#    FetchContent_MakeAvailable(POPPLER)
#    list(APPEND LIB_MODULES POPPLER)
#    list(APPEND LIB_TARGET_INCLUDE_DIRECTORIES ${POPPLER_INCLUDE_DIRS})
#    list(APPEND LIB_TARGET_LIBRARY_DIRECTORIES ${POPPLER_LIBRARY_DIRS})
#    list(APPEND LIB_TARGET_LINK_DIRECTORIES ${POPPLER_LIBRARY_DIRS})
#endif()
#if(NOT POPPLER_FOUND)
#    return()
#endif()
