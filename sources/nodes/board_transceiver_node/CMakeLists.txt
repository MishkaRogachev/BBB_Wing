# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT board_transceiver_node)
project(${PROJECT})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

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
    board_transceiver_node.h
    board_transceiver_node.cpp
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
target_link_libraries(${PROJECT} ${LIBRARIES})