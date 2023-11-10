cmake_minimum_required(VERSION 3.18)

project(keycycler VERSION 1.0 LANGUAGES CXX)

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

add_subdirectory(src)

target_include_directories(
  keycycler
  PRIVATE include
)

target_link_libraries(keycycler)
