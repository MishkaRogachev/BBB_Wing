# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_imu_node)
project(${PROJECT})

# CMake modules
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/RecurseSubdirs.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# External dirs
add_subdirectory(../../common ${CMAKE_CURRENT_BINARY_DIR}/common)
add_subdirectory(../../transport ${CMAKE_CURRENT_BINARY_DIR}/transport)
add_subdirectory(../../devices/lsm9ds1 ${CMAKE_CURRENT_BINARY_DIR}/devices/lsm9ds1)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core)

# Libraries
set(LIBRARIES
    ${LIBRARIES}
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
set(INTERNAL_SOURCES
    sensor_imu_node.h
    sensor_imu_node.cpp
)

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
