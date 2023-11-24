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

if(NOT DEFINED Qt6_DIR)
  if(DEFINED ENV{PREFERRED_QT_PATH})
    set(Qt6_DIR "$ENV{PREFERRED_QT_PATH}")
    message(STATUS "Using preferred your preferred Qt Path at: $ENV{PREFERRED_QT_PATH}")
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
find_package(Qt6 6.2 COMPONENTS Core Quick Gui REQUIRED)
# Jsoncpp for persistent storage
find_package(jsoncpp REQUIRED)

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
