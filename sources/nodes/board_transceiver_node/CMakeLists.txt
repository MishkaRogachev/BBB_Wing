# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT board_transceiver_node)
project(${PROJECT})

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    board_transceiver_node.h
    board_transceiver_node.cpp
)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
