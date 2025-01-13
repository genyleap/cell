cmake_minimum_required(VERSION 3.5)

project(Application LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")

get_filename_component(PARENT_DIR ../ ABSOLUTE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(ExternalProject)
include(FetchContent)


# ------ PACKAGES CONFIG ------
include(project-setting)
if(project-setting)
  return()
endif()
set(project-setting ON)

# ------ CROSS-COMPILE CONFIG ------
include(cross-compile)
if(cross-compile)
  return()
endif()
set(cross-compile ON)

# ------ PROJECT CONFIG ------
include(color-message)
if(color-message)
  return()
endif()
set(color-message ON)

# ------ COMPILER CONFIG ------
include(compiler-options)
if(compiler-options)
  return()
endif()
set(compiler-options ON)

# ------ PACKAGES CONFIG ------
include(packages)
if(packages)
  return()
endif()
set(packages ON)

set(PREFIX_HPPHEADER *.hpp)
set(PREFIX_SOURCE *.cpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB SOURCESFILE
    ${PREFIX_HPPHEADER}
    ${PREFIX_SOURCE}
)

file(GLOB UTILS
     utilities/${SUFFIX_HPPHEADER}
     utilities/${SUFFIX_SOURCE}
)

# ------ PROJECT DIRECTORIES ------
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${dir}/final CACHE PATH "Build directory" FORCE)
message(STATUS "Executable output path: ${EXECUTABLE_OUTPUT_PATH}")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(${PROJECT_SOURCE_DIR}/../source)
include_directories(${PROJECT_SOURCE_DIR}/../include)

add_executable(${PROJECT_NAME} ${SOURCESFILE} ${UTILS})


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source PRIVATE source ${LIB_TARGET_INCLUDE_DIRECTORIES})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source ${LIB_TARGET_LINK_DIRECTORIES})
target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../../../build/final ${LIB_TARGET_LINK_DIRECTORIES}) #CoreInterface


target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../build/final)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreInterface ${LIB_MODULES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIB_TARGET_COMPILER_DEFINATION})
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source PRIVATE source
    ${LIB_TARGET_INCLUDE_DIRECTORIES}
)


# Ignore unused files for packaging
list(APPEND CPACK_SOURCE_IGNORE_FILES /.git/ /build/ .gitignore .DS_Store)

# Copy files after build
if(EXISTS "${PROJECT_SOURCE_DIR}/../build/final")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${PROJECT_SOURCE_DIR}/../build/final"
                "${CMAKE_CURRENT_BINARY_DIR}/final"
    )
else()
    message(WARNING "Directory ${PROJECT_SOURCE_DIR}/../build/final does not exist")
endif()

# Define PLATFORM_FOLDER if not already defined
if(NOT DEFINED PLATFORM_FOLDER)
    set(PLATFORM_FOLDER "platform")  # Default value, adjust as needed
endif()

get_filename_component(PARENT_DIR ../ ABSOLUTE)

#Copy from Core Interface.
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${PROJECT_SOURCE_DIR}/../build/final"
                "${CMAKE_CURRENT_BINARY_DIR}/final"
            )


    if(EXISTS "${PROJECT_SOURCE_DIR}/build/${PLATFORM_FOLDER}/${PROJECT_NAME}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    "${PROJECT_SOURCE_DIR}/build/${PLATFORM_FOLDER}/${PROJECT_NAME}"
                    "${PARENT_DIR}/application/build/final"
        )
    else()
        message(WARNING "File ${PROJECT_SOURCE_DIR}/build/${PLATFORM_FOLDER}/${PROJECT_NAME} does not exist")
    endif()

    # Install target
    install(TARGETS ${PROJECT_NAME} DESTINATION build/final)
