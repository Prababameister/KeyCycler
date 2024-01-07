cmake_minimum_required(VERSION 3.18)

project(keycycler VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(PROJECT_HEAD ${PROJECT_SOURCE_DIR})
add_definitions( -DPROJECT_HEAD="${PROJECT_HEAD}" )

add_definitions( -DCONFIG_DIR="${CONFIG_DIR}" )

if(Qt6_DIR STREQUAL "Qt6_DIR-NOTFOUND")
  message(STATUS ${Qt6_DIR})
  if(DEFINED ENV{PREFERRED_QT_PATH})
    set(Qt6_DIR "$ENV{PREFERRED_QT_PATH}")
    message(STATUS "Using preferred your preferred Qt Path at: $ENV{PREFERRED_QT_PATH}")
  else()
    message(STATUS "Could not find this path :(")
  endif()
endif()

set(SOURCES
    ${PROJECT_HEAD}/src/keyboard.cc
    ${PROJECT_HEAD}/src/cycle_list.cc
    ${PROJECT_HEAD}/src/cycle.cc
    ${PROJECT_HEAD}/src/backend.cc
)

set(HEADERS
    ${PROJECT_HEAD}/include/keyboard.hh
    ${PROJECT_HEAD}/include/cycle_list.hh
    ${PROJECT_HEAD}/include/cycle.hh
    ${PROJECT_HEAD}/include/backend.hh
)

# Qt6 Library
find_package(Qt6 COMPONENTS Core Quick Gui REQUIRED)

# Jsoncpp for persistent storage
FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git 
    GIT_TAG        master
)

FetchContent_GetProperties(jsoncpp)
if (NOT jsoncpp_POPULATED)
    FetchContent_Populate(jsoncpp)
    add_subdirectory(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR})
endif ()

qt_standard_project_setup()

qt_add_executable(keycycler
    ${PROJECT_HEAD}/src/main.cc
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
  keycycler
  PRIVATE include
)

target_link_libraries(keycycler PRIVATE Qt6::Gui Qt6::Quick jsoncpp_lib)
