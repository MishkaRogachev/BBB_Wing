# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_ins_node)
project(${PROJECT})

# External dirs
add_subdirectory(../../devices/lsm9ds1 ${CMAKE_CURRENT_BINARY_DIR}/devices/lsm9ds1)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    sensor_ins_node.h
    sensor_ins_node.cpp
)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
