# -------------------- PROJECT TEMPLATE INFO ---------------------------------------------
#   Title   :                       Cell Engine
#   Version :                       0.9.550
#   Author  :                       Kambiz Asadzadeh (compez.eth)
#   Url     :                       https://github.com/genyleap/cell
#   Organization  :                 The Genyleap
# ----------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.27)
# Set CMP0042 policy to NEW
# cmake_policy(SET CMP0042 NEW)
# cmake_policy(SET CMP0048 NEW)

# Add include path for cmake modules
# ------ PROJECT EXTRA CMAKE ------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(ExternalProject)
include(FetchContent)

# ------ PROJECT INFO ------
# Options
set(PROJECT_NAME "CoreInterface" CACHE STRING "Project Name.") #You can change "ProjectTemplate" with your project name.
set(PROJECT_TARGET ${PROJECT_NAME} CACHE STRING "Project Target Name.")
set(PROJECT_REAL_NAME "Cell" CACHE STRING "Project Real Name.")

set(PROJECT_VERSION 0.8.550)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 8)
set(PROJECT_VERSION_PATCH 550)

# ---- Project settings ----
set_property(GLOBAL APPEND PROPERTY USE_FOLDERS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

set(PROJECT_CREATOR "Kambiz Asadzadeh" CACHE STRING "Creator of your project.") #Your project creator.

set(PROJECT_ORGANIZATION "The Genyleap" CACHE STRING "Organization name.") #Your project creator.

set(PROJECT_LICENSE_TYPE "Gen3" CACHE STRING "Project License Type.") #Your project license type.

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
  execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VERSION_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

endif()
if(NOT PROJECT_VERSION_TAG)
  set(PROJECT_VERSION_TAG 00000000)
endif()
set(PROJECT_VERSION_TAG_HEX 0x${PROJECT_VERSION_TAG})
set(PROJECT_VERSION_TYPE "final" CACHE STRING "Version type.")
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set(PROJECT_VERSION_STRING ${PROJECT_VERSION}-${PROJECT_VERSION_TYPE})

# Supported languages include C, CXX (i.e. C++), CUDA, OBJC (i.e. Objective-C), OBJCXX, Fortran, HIP, ISPC, and ASM. By default C and CXX are enabled if no language options are given.
# Specify language NONE, or use the LANGUAGES keyword and list no languages, to skip enabling any languages.
set(PROJECT_LANGUAGES CXX)

#Use these keys [application, library]
set(PROJECT_USAGE_TYPE "library" CACHE STRING "Usage Type.")

#Use these keys [stl, qt, qtwidget, qtquick]
set(PROJECT_MAIN_TYPE "stl" CACHE STRING "Library System.")

set(DEVELOPER_BUNDLE_IDENTIFIER com.genyleap.app.${PROJECT_NAME} CACHE STRING "Developer Bundle Identifier.")

#You can replace your project description with this string.
set(PROJECT_DESCRIPTION "Cell Engine is a new and exclusive cross-platform computer application engine based on modern C++." CACHE STRING "Project Description")

#Your project website address.
set(PROJECT_HOMEPAGE_URL "https://github.com/genyleap/cell" CACHE STRING "Project URL.")

#Project pre-configuration system.
configure_file(
  ${PROJECT_SOURCE_DIR}config.hpp.in
  ${PROJECT_SOURCE_DIR}config.hpp
)

project(
    ${PROJECT_NAME}
    LANGUAGES ${PROJECT_LANGUAGES}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
    VERSION ${PROJECT_VERSION}
    )

# ------ PROJECT CONFIG ------
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

if(NOT PROJECT_MAIN_TYPE STREQUAL "stl")
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
endif()

set(SUFFIX_EXTRA *.in)
set(SUFFIX_HPPHEADER *.hpp)
set(SUFFIX_IPPHEADER *.ipp)
set(SUFFIX_INLHEADER *.inl)
set(SUFFIX_SOURCE *.cpp)
set(SUFFIX_CONFIG *.json)
set(SUFFIX_TRANSLATIONS *.json)

if(PROJECT_MAIN_TYPE STREQUAL "qtwidget")
     set(SUFFIX_WIDGET *.ui)
     set(SUFFIX_TRANSLATIONS *.json)
elseif(PROJECT_MAIN_TYPE STREQUAL "qtquick")
     set(SUFFIX_QML *.qml)
     set(SUFFIX_QRC *.qrc)
     set(SUFFIX_TRANSLATIONS *.json)
else()
    set(SUFFIX_TRANSLATIONS *.json)
endif()

file(GLOB HEADERS source/${SUFFIX_HPPHEADER})
file(GLOB SOURCES source/${SUFFIX_SOURCE})

#include cell's file.
include_directories(${PROJECT_SOURCE_DIR}/include/cell/)

file(
    GLOB HEADERS
    source/${SUFFIX_HPPHEADER}
    source/core/${SUFFIX_HPPHEADER}
    source/core/datetime/${SUFFIX_HPPHEADER}
    source/core/convertor/${SUFFIX_HPPHEADER}
    source/core/convertor/currencies/${SUFFIX_HPPHEADER}
    source/core/convertor/text/${SUFFIX_HPPHEADER}
    source/core/convertor/color/${SUFFIX_HPPHEADER}
    source/classes/${SUFFIX_HPPHEADER}
    source/modules/network/http/${SUFFIX_HPPHEADER}
    source/modules/network/webserver/${SUFFIX_HPPHEADER}
    source/modules/database/psql/${SUFFIX_HPPHEADER}
    source/modules/hardware/system/${SUFFIX_HPPHEADER}
    source/modules/cryptography/${SUFFIX_HPPHEADER}
    source/modules/settings/${SUFFIX_HPPHEADER}
    source/modules/utility/${SUFFIX_HPPHEADER}
    source/modules/ai/${SUFFIX_HPPHEADER}
    source/modules/blockchain/${SUFFIX_HPPHEADER}
    source/modules/web/${SUFFIX_HPPHEADER}
    source/modules/gui/${SUFFIX_HPPHEADER}
    source/modules/multimedia/${SUFFIX_HPPHEADER}
    source/modules/compression/${SUFFIX_HPPHEADER}
    source/modules/iot/${SUFFIX_HPPHEADER}
    source/modules/protocol/${SUFFIX_HPPHEADER}
    source/modules/protocol/farcaster/${SUFFIX_HPPHEADER}
    source/translator/${SUFFIX_HPPHEADER}
    source/abstracts/${SUFFIX_HPPHEADER}
    source/abstracts/apis/${SUFFIX_HPPHEADER}
    source/abstracts/account/${SUFFIX_HPPHEADER}
    source/abstracts/blockchain/${SUFFIX_HPPHEADER}
    source/abstracts/calendar/${SUFFIX_HPPHEADER}
    source/abstracts/database/${SUFFIX_HPPHEADER}
    source/modules/database/${SUFFIX_HPPHEADER}
    source/abstracts/account/${SUFFIX_HPPHEADER}
    source/abstracts/dynamics/${SUFFIX_HPPHEADER}
    source/abstracts/modules/webserver/${SUFFIX_HPPHEADER}
    source/classes/dynamics/${SUFFIX_HPPHEADER}
    source/metagen/core/${SUFFIX_HPPHEADER}
)
file(
    GLOB SOURCES
    source/${SUFFIX_SOURCE}
    source/core/${SUFFIX_SOURCE}
    source/core/datetime/${SUFFIX_SOURCE}
    source/core/convertor/${SUFFIX_SOURCE}
    source/core/convertor/currencies/${SUFFIX_SOURCE}
    source/core/convertor/text/${SUFFIX_SOURCE}
    source/core/convertor/color/${SUFFIX_SOURCE}
    source/classes/${SUFFIX_SOURCE}
    source/modules/network/http/${SUFFIX_SOURCE}
    source/modules/network/webserver/${SUFFIX_SOURCE}
    source/modules/database/psql/${SUFFIX_SOURCE}
    source/modules/hardware/system/${SUFFIX_SOURCE}
    source/modules/settings/${SUFFIX_SOURCE}
    source/modules/utility/${SUFFIX_SOURCE}
    source/modules/ai/${SUFFIX_SOURCE}
    source/modules/blockchain/${SUFFIX_SOURCE}
    source/modules/web/${SUFFIX_SOURCE}
    source/modules/gui/${SUFFIX_SOURCE}
    source/modules/multimedia/${SUFFIX_SOURCE}
    source/modules/compression/${SUFFIX_SOURCE}
    source/modules/iot/${SUFFIX_SOURCE}
    source/modules/cryptography/${SUFFIX_SOURCE}
    source/modules/protocol/${SUFFIX_SOURCE}
    source/modules/protocol/farcaster/${SUFFIX_SOURCE}
    source/translator/${SUFFIX_SOURCE}
    source/abstracts/${SUFFIX_SOURCE}
    source/abstracts/apis/${SUFFIX_SOURCE}
    source/abstracts/account/${SUFFIX_SOURCE}
    source/abstracts/blockchain/${SUFFIX_SOURCE}
    source/abstracts/calendar/${SUFFIX_SOURCE}
    source/abstracts/database/${SUFFIX_SOURCE}
    source/modules/database/${SUFFIX_SOURCE}
    source/abstracts/account/${SUFFIX_SOURCE}
    source/abstracts/dynamics/${SUFFIX_SOURCE}
    source/abstracts/modules/webserver/${SUFFIX_SOURCE}
    source/classes/dynamics/${SUFFIX_SOURCE}

)

file(GLOB PRECOMPILED
    precompiled/pch.hpp
    precompiled/unix/pch.hpp
    precompiled/linux/pch.hpp
    precompiled/win32/pch.hpp
)

# file(GLOB EXAMPLES
#      source/examples/${SUFFIX_HPPHEADER}
#      source/examples/${SUFFIX_SOURCE}
# )

file(GLOB UTILS
     utilities/${SUFFIX_HPPHEADER}
     utilities/${SUFFIX_SOURCE}
)

file(GLOB TRANSLATIONS
    translations/${SUFFIX_TRANSLATIONS}
)

if(${PROJECT_MAIN_TYPE} STREQUAL "stl")
    set(HAS_USER_INTERFACE false)
    file(GLOB MAIN_ENTRY_POINT
         source/entrypoint/stl/${SUFFIX_HPPHEADER}
         source/entrypoint/stl/${SUFFIX_SOURCE}
    )
elseif(${PROJECT_MAIN_TYPE} STREQUAL "qt")
    file(GLOB MAIN_ENTRY_POINT
         source/entrypoint/qt/nogui/${SUFFIX_HPPHEADER}
         source/entrypoint/qt/nogui/${SUFFIX_SOURCE}
    )
elseif(${PROJECT_MAIN_TYPE} STREQUAL "qtwidget")
    file(GLOB MAIN_ENTRY_POINT
        source/entrypoint/qt/qtwidget/${SUFFIX_HPPHEADER}
        source/entrypoint/qt/qtwidget/${SUFFIX_SOURCE}
        ui/widgets/${SUFFIX_HPPHEADER}
        ui/widgets/${SUFFIX_SOURCE}
    )
elseif(${PROJECT_MAIN_TYPE} STREQUAL "qtquick")
    file(GLOB MAIN_ENTRY_POINT
         source/entrypoint/qt/qtquick/${SUFFIX_HPPHEADER}
         source/entrypoint/qt/qtquick/${SUFFIX_SOURCE}
    )
endif()
if(${PROJECT_MAIN_TYPE} STREQUAL "qtwidget")
   file(GLOB UI_SOURCE ui/widgets/${SUFFIX_WIDGET})
endif()
if(${PROJECT_MAIN_TYPE} STREQUAL "qtquick")
   file(GLOB UI_SOURCE ui/qtquick/${SUFFIX_QRC})
   file(GLOB UI_QML_SOURCE ui/qtquick/${SUFFIX_QML})
endif()

file(GLOB_RECURSE src_files ui/qtquick/${SUFFIX_QML})

FOREACH(LETTER ${src_files})
  string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" fileList "${LETTER}")
  message(${fileList})
  list(APPEND UI_QML_FILES ${fileList})
ENDFOREACH()

file(GLOB CONFIGFILE config/${SUFFIX_CONFIG})

file(GLOB SOURCESFILE
    #---C++---
    ${MAIN_ENTRY_POINT}
    ${HEADERS}
    ${SOURCES}
    ${UI_SOURCE}
    ${UI_QML_SOURCE}
    ${UTILS}
    ${CONFIGFILE}
    ${TRANSLATIONS}
    ${PRECOMPILED}
    ${EXAMPLES}
    )


# ------ PROJECT DIRECTORIES ------

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${dir}/final CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir}/final CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir}/final)
SET(LIBRARY_OUTPUT_PATH ${dir}/final)
SET(CMAKE_CACHEFILE_DIR ${dir})

message("CMAKE_BUILD_FILES_DIRECTORY: " ${CMAKE_BUILD_FILES_DIRECTORY})

# ------ OUTPUTS CONFIG ------
if(PLATFORM_OS STREQUAL "macOS")
    if(OS_ARCHITECTURES STREQUAL "")
      set(OS_ARCHITECTURES ${CMAKE_OSX_ARCHITECTURES})
    endif()
else()
    if(PROCESSOR_ARCHITECTURE STREQUAL "")
      set(OS_ARCHITECTURES ${PROCESSOR_ARCHITECTURE})
    endif()
endif()

# source_group("PrecompiledHeaders"  FILES ${PRECOMPILED})
# source_group("Utilities"  FILES ${UTILS})
# source_group("Entry Point (Main)"   FILES ${MAIN_ENTRY_POINT})
# source_group("Base"   FILES ${HEADERS} ${SOURCES})
# source_group("UI"     FILES ${UI_SOURCE})
# source_group("UI/QML"     FILES ${UI_QML_SOURCE})
# source_group("Translations"     FILES ${TRANSLATIONS})
# source_group("Config" FILES ${CONFIGFILE})
# source_group("Examples"  FILES ${EXAMPLES})

# ------ OUTPUTS CONFIG ------
message(STATUS "${BoldRed}------ ${PROJECT_TARGET} Tools Configuration ------${ColourReset}")
message(STATUS "${Bold}Language Standard${ColourReset}	    : C++[${CMAKE_CXX_STANDARD}]")
message(STATUS "${Bold}Compiler${ColourReset}		    : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "${Bold}Compiler Version${ColourReset}	    : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "${Bold}OS Target${ColourReset}		    : ${CMAKE_HOST_SYSTEM}")
message(STATUS "${Bold}OS Version${ColourReset}             : ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "${Bold}System Architecture${ColourReset}    : ${OS_ARCHITECTURES}")
message(STATUS "${Bold}Project License${ColourReset}	    : ${PROJECT_LICENSE_TYPE}")
message(STATUS "${BoldBlue}------ ${PROJECT_TARGET} Framework Info ------${ColourReset}")
message(STATUS "${Bold}Name${ColourReset}			    : ${CMAKE_PROJECT_NAME}")
message(STATUS "${Bold}Description${ColourReset}		    : ${CMAKE_PROJECT_DESCRIPTION}")
message(STATUS "${Bold}Version${ColourReset}		    : ${PROJECT_VERSION}")
message(STATUS "${Bold}Full Version${ColourReset}	    : ${PROJECT_VERSION_STRING}")
message(STATUS "${Bold}Creator${ColourReset}		    : ${PROJECT_CREATOR}")
message(STATUS "${BoldBlue}------ ${PROJECT_TARGET} Project Configuration ------${ColourReset}")
message(STATUS "${Bold}DEVELOPER${ColourReset}		    : ${PROJECT_CREATOR}")
message(STATUS "${Bold}PROJECT_PROJECT${ColourReset}	    : ${PROJECT_NAME}")
message(STATUS "${Bold}PROJECT_TARGET${ColourReset}	    : ${PROJECT_TARGET}")
message(STATUS "${Bold}PROJECT_VERSION${ColourReset}	    : ${PROJECT_VERSION}")
message(STATUS "${Bold}PROJECT_VERSION_TYPE${ColourReset}	    : ${Underscore}${PROJECT_VERSION_TYPE}${ColourReset}")
message(STATUS "${BoldBlue}------ ${PROJECT_TARGET} Building Configuration ------${ColourReset}")
message(STATUS "${Bold}PROJECT_BUILD_SHARED${ColourReset}	: ${PROJECT_BUILD_SHARED}")
message(STATUS "${Bold}PROJECT_VERSION_TAG_HEX${ColourReset}	: ${PROJECT_VERSION_TAG_HEX}")
message(STATUS "${Bold}PROJECT_FOLDER_SUFFIX${ColourReset}	: ${PROJECT_FOLDER_SUFFIX}")
message(STATUS "${Bold}LIBRARY_OUTPUT_PATH${ColourReset}		: ${LIBRARY_OUTPUT_PATH}")
message(STATUS "${Bold}CMAKE_CURRENT_SOURCE_DIR${ColourReset}	: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "${BoldBlue}------ ${PROJECT_TARGET} End Configuration ------${ColourReset}")

if(GUI_APPLICATION AND PROJECT_MAIN_TYPE STREQUAL "qt" OR PROJECT_MAIN_TYPE STREQUAL "qtwidget" OR PROJECT_MAIN_TYPE STREQUAL "qtquick")

    if(USE_QT5_FEATURES)
        if(${PROJECT_MAIN_TYPE} STREQUAL "qt")
            list(APPEND QT_MODULES Core Core5Compat)
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Core5Compat
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Core5Compat)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Core5Compat)
        elseif(${PROJECT_MAIN_TYPE} STREQUAL "qtwidget")
            list(APPEND QT_MODULES Core Widgets Core5Compat)
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Widgets
                Qt${QT_VERSION_MAJOR}::Core5Compat
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Core5Compat)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Core5Compat)
        elseif(${PROJECT_MAIN_TYPE} STREQUAL "qtquick")
            list(APPEND QT_MODULES Core Quick Core5Compat)
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Quick
                Qt${QT_VERSION_MAJOR}::Core5Compat
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Core5Compat)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Core5Compat)
        else()
            list(APPEND QT_MODULES Core Core5Compat)
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Core5Compat
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Core5Compat)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Core5Compat)
        endif()
    else()
        if(${PROJECT_MAIN_TYPE} STREQUAL "qt")
            list(APPEND QT_MODULES Core)
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
        elseif(${PROJECT_MAIN_TYPE} STREQUAL "qtwidget")
            list(APPEND QT_MODULES Core Widgets)
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Widgets
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
        elseif(${PROJECT_MAIN_TYPE} STREQUAL "qtquick")
            list(APPEND QT_MODULES Core${SPACE_ARG})
            list(APPEND QT_MODULES Quick${SPACE_ARG})
            list(APPEND QT_MODULES_LINK
                Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
                )
            find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
            find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
        endif()
    endif()
    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        if(PROJECT_USAGE_TYPE STREQUAL "library")
            qt_add_library(${PROJECT_NAME}
                MANUAL_FINALIZATION
                ${SOURCESFILE}
            )
        else()
            qt_add_resources(SOURCESFILE ui/qtquick/qml.qrc)
            qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${SOURCESFILE})
            if(${PROJECT_MAIN_TYPE} STREQUAL "qtquick")
                if(USE_QT_QUICK_COMPILER)
                qt_add_qml_module(${PROJECT_NAME}
                    URI ${PROJECT_NAME}
                    VERSION 1.0
                    RESOURCE_PREFIX /app.genyleap.com/import
                    OUTPUT_DIRECTORY ""
                    QML_FILES ${UI_QML_FILES}
                )
                endif()
            endif()
        endif()
    else()
        if(ANDROID)
            add_library(${PROJECT_NAME} SHARED
                ${SOURCESFILE}
            )
        else()
            if(PROJECT_USAGE_TYPE STREQUAL "library")
                add_library(${PROJECT_NAME}
                  ${SOURCESFILE}
                )
            else()
                add_executable(${PROJECT_NAME}
                  ${SOURCESFILE}
                )
            endif()
        endif()
    endif()

    #Extra Targets & Modules
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${LIB_STL_MODULES_LINKER}
            ${LIB_MODULES}
            ${QT_MODULES_LINK}
            ${OS_LIBS}
        )

    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source PRIVATE source ${LIB_TARGET_INCLUDE_DIRECTORIES})
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source ${LIB_TARGET_LINK_DIRECTORIES})

    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER ${DEVELOPER_BUNDLE_IDENTIFIER}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/properties/${PLATFORM_FOLDER}/Info.plist.in"
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

if(ANDROID)
    include(${ANDROID_SDK_ROOT}/android_openssl/CMakeLists.txt)
endif()

if(QT_VERSION_MAJOR GREATER_EQUAL 6.0) #From Qt.6.0
    if(${PROJECT_MAIN_TYPE} STREQUAL "qtquick")
        qt_import_qml_plugins(${PROJECT_NAME})
    endif()
    if(QT_VERSION GREATER_EQUAL 6.2) #From Qt6.2
        qt_finalize_target(${PROJECT_NAME})
    endif()
    if(WIN32)
        qt_disable_unicode_defines(${PROJECT_NAME})
        qt_allow_non_utf8_sources(${PROJECT_NAME})
    endif()
endif()

else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${SOURCESFILE}
        )
    else()
        if(PROJECT_USAGE_TYPE STREQUAL "library")
            add_library(${PROJECT_NAME}
              ${SOURCESFILE}
            )
        else()
            add_executable(${PROJECT_NAME}
              ${SOURCESFILE}
            )
        endif()
    endif()

    #Extra Targets & Modules
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${LIB_STL_MODULES_LINKER}
            ${LIB_MODULES}
            ${OS_LIBS}
        )
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source PRIVATE source
        ${LIB_TARGET_INCLUDE_DIRECTORIES}
        ${ODBC_INCLUDE_DIRS}
    )

    target_link_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${LIB_TARGET_LINK_DIRECTORIES}
        ${ODBC_LIBRARIES}
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER ${DEVELOPER_BUNDLE_IDENTIFIER}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/properties/${PLATFORM_FOLDER}/Info.plist.in"
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

endif()

#Ignore the warning/isable the warning
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wno-deprecated-declarations
    -Wdeprecated-non-prototype
    -Wstrict-prototypes
)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIB_TARGET_COMPILER_DEFINATION})

#This command generates installation rules for a project.
#Install rules specified by calls to the install() command within a source directory. are executed in order during installation.
#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${LIB_TARGET_PROPERTIES})
#This command generates installation rules for a project.
#Install rules specified by calls to the install() command within a source directory. are executed in order during installation.
# Ensure the final directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/final)

# Install the target executable/library to the final directory
install(TARGETS ${PROJECT_NAME} DESTINATION final)

# Copy additional files and directories
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config DESTINATION ${CMAKE_BINARY_DIR}/final)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/translations DESTINATION ${CMAKE_BINARY_DIR}/final)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/final/server-log)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/final)
install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/final/server-log)

# Copy the built executable/library to the final folder after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:${PROJECT_NAME}>
    ${CMAKE_BINARY_DIR}/final
)

#file(COPY "${PROJECT_SOURCE_DIR}/build/${PLATFORM_FOLDER}/lib" DESTINATION  "${PROJECT_SOURCE_DIR}/build/final")

#add_custom_command(
#        TARGET ${PROJECT_NAME}  POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#                "${PROJECT_SOURCE_DIR}/build/${PLATFORM_FOLDER}/lib"
#                 "${PROJECT_SOURCE_DIR}/build/final"
#             )

#Ignore unused files.
list(APPEND CPACK_SOURCE_IGNORE_FILES /.git/ /build/ .gitignore .DS_Store)
