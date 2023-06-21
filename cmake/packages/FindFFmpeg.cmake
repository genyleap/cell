## Package Info.
#set(FFMPEG_NAME "FFmpeg")
#set(FFMPEG_DESCRIPTION "FFmpeg is a collection of libraries and tools to process multimedia content such as audio, video, subtitles, and related metadata.")

## Package option.
#option(USE_FFMPEG ${FFMPEG_DESCRIPTION} FALSE)
#if (USE_FFMPEG)
#    add_definitions(-DUSE_FFMPEG)
#    # Define the repository URL and tag for the FFmpeg libraries
#    set(FFMPEG_URL "https://github.com/FFmpeg/FFmpeg.git")
#    if(FORCE_UPGRADED_LIBS)
#        set(FFMPEG_TAG "master")
#    else()
#        set(FFMPEG_TAG "n4.2.9")
#    endif()
#    set(FFMPEG_LIB_LIST "avformat;avutil;avcodec;swscale;" CACHE STRING "List of modules (separated by a semicolon)")
#endif()

#if(USE_FFMPEG)
#    set(FETCHCONTENT_QUIET off)
#    FetchContent_Declare(
#        ffmpeg
#        GIT_REPOSITORY      ${FFMPEG_URL}
#        GIT_TAG             ${FFMPEG_TAG}
#        GIT_PROGRESS        TRUE
#    )
#    FetchContent_GetProperties(ffmpeg)
#    if(NOT ffmpeg_POPULATED)
#        FetchContent_Populate(ffmpeg)
#        add_subdirectory(${ffmpeg_SOURCE_DIR} ${ffmpeg_BINARY_DIR} EXCLUDE_FROM_ALL)
#    endif()
#endif()
#if(NOT FFMPEG_FOUND)
#    return()
#endif()

#foreach(module IN LISTS FFMPEG_LIB_LIST)
#    list(APPEND LIB_MODULES ${module})
#endforeach()

## Path to the FFmpeg source directory
#set(FFMPEG_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${THIRD_PARTY}/${PLATFORM_FOLDER_NAME}/${FFMPEG_NAME}/ffmpeg-src")

## Path to the build directory for FFmpeg
#set(FFMPEG_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${THIRD_PARTY}/${PLATFORM_FOLDER_NAME}/${FFMPEG_NAME}/ffmpeg-build")

## Run the FFmpeg configure script
#execute_process(
#    COMMAND "${FFMPEG_SOURCE_DIR}/configure"
#    WORKING_DIRECTORY "${FFMPEG_BINARY_DIR}"
#    RESULT_VARIABLE FFMPEG_CONFIGURE_RESULT
#    OUTPUT_VARIABLE FFMPEG_CONFIGURE_OUTPUT
#)

## Print the output of the configure script
#message("FFmpeg configuration output:\n${FFMPEG_CONFIGURE_OUTPUT}")

## Check the result of the configure script
#if(FFMPEG_CONFIGURE_RESULT EQUAL 0)
#    message("FFmpeg configuration completed successfully")
#else()
#    message(FATAL_ERROR "FFmpeg configuration failed: ${FFMPEG_CONFIGURE_RESULT}")
#endif()

#set(FFMPEG_LIB_LIST
#    avcodec
#    avformat
#    avutil
#    # Add more FFmpeg module names here if needed
#)

#set(FETCHCONTENT_QUIET off)

## Function to customize the build and configure commands
#function(customize_build_configuration target)
#    set_target_properties(${target} PROPERTIES
#        EXCLUDE_FROM_ALL TRUE
#        EXCLUDE_FROM_DEFAULT_BUILD TRUE
#        PREFIX ""
#    )
#    target_compile_options(${target} PRIVATE
#        -Wno-error
#        -Wno-unused-parameter
#        -Wno-unused-variable
#    )
#    target_compile_definitions(${target} PRIVATE
#        -D__STDC_CONSTANT_MACROS
#        -D__STDC_FORMAT_MACROS
#        -D__STDC_LIMIT_MACROS
#    )
#endfunction()

#foreach(module IN LISTS FFMPEG_LIB_LIST)
#    FetchContent_Declare(
#        ${module}
#        GIT_REPOSITORY https://github.com/FFmpeg/FFmpeg.git
#        GIT_TAG master
#        GIT_PROGRESS        TRUE
#    )
#    FetchContent_GetProperties(${module})
#    if(NOT ${module}_POPULATED)
#        FetchContent_Populate(${module})
#        set(FFMPEG_SOURCE_DIR "${${module}_SOURCE_DIR}")

#        # Run configure command
#        execute_process(
#            COMMAND ${FFMPEG_SOURCE_DIR}/configure
#            WORKING_DIRECTORY ${FFMPEG_SOURCE_DIR}
#            RESULT_VARIABLE FFMPEG_CONFIGURE_RESULT
#            OUTPUT_VARIABLE FFMPEG_CONFIGURE_OUTPUT
#        )
#        if(NOT FFMPEG_CONFIGURE_RESULT EQUAL 0)
#            message(FATAL_ERROR "Failed to configure FFmpeg module ${module}. Error: ${FFMPEG_CONFIGURE_OUTPUT}")
#        endif()

#        # Run make command
#        execute_process(
#            COMMAND make
#            WORKING_DIRECTORY ${FFMPEG_SOURCE_DIR}
#            RESULT_VARIABLE FFMPEG_MAKE_RESULT
#            OUTPUT_VARIABLE FFMPEG_MAKE_OUTPUT
#        )
#        if(NOT FFMPEG_MAKE_RESULT EQUAL 0)
#            message(FATAL_ERROR "Failed to build FFmpeg module ${module}. Error: ${FFMPEG_MAKE_OUTPUT}")
#        endif()
#    endif()

#    add_library(${module} SHARED IMPORTED)
#        set_target_properties(${module} PROPERTIES
#            IMPORTED_LOCATION "${FFMPEG_SOURCE_DIR}/lib${module}.so"
#            INTERFACE_INCLUDE_DIRECTORIES ${FFMPEG_SOURCE_DIR}
#        )
#        customize_build_configuration(${module})
#        list(APPEND LIB_MODULES ${module})
#    endforeach()

#message(STATUS "FFmpeg library modules: ${LIB_MODULES}")

#include(FetchContent)

## Define the FFmpeg library module names
#set(FFMPEG_LIB_LIST
#    avcodec
#    avformat
#    avutil
#    # Add more FFmpeg module names here if needed
#)

## Set up FFmpeg using FetchContent_Declare
#foreach(module IN LISTS FFMPEG_LIB_LIST)
#    FetchContent_Declare(
#        ${module}
#        GIT_REPOSITORY https://github.com/FFmpeg/FFmpeg.git
#        GIT_TAG master
#        CONFIGURE_COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${module}-build ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/${module}-install ../${module}
#        BUILD_COMMAND ${CMAKE_COMMAND} --build .
#        INSTALL_COMMAND ${CMAKE_COMMAND} --install .
#    )

#    FetchContent_GetProperties(${module})
#    if(NOT ${module}_POPULATED)
#        FetchContent_Populate(${module})
#    endif()

#    # Add the library module to LIB_MODULES
#    list(APPEND LIB_MODULES ${${module}_SOURCE_DIR})

#    # Add library path to CMAKE_PREFIX_PATH for find_package
#    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/${module}-install)
#endforeach()

## Add targets and link against FFmpeg libraries
#foreach(module IN LISTS FFMPEG_LIB_LIST)
#    add_executable(${module}_example ${module}_example.cpp)
#    target_link_libraries(${module}_example PRIVATE ${LIB_MODULES})
#endforeach()

