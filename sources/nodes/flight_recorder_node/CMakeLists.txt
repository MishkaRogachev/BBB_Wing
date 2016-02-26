# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT flight_recorder_node)
project(${PROJECT})

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    flight_recorder_node.h
    flight_recorder_node.cpp
)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
