# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT altitude_sensor_node)
project(${PROJECT})

# Root dir
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

# CMake modules
include(${ROOT_DIR}/cmake/RecurseSubdirs.cmake)

# Common
add_subdirectory(${ROOT_DIR}/common ${CMAKE_CURRENT_BINARY_DIR}/common)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core)

# Libs
set(LIBRARIES
# Qt5
    Qt5::Core
)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDES
    ${INCLUDES}
    ${INTERNAL_INCLUDES}
)
include_directories(${INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "sources/*.h" "sources/*.cpp")
set(SOURCES
    ${SOURCES}
    ${INTERNAL_SOURCES}
)

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Tests
# add_subdirectory(tests)
