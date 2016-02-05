# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT workstation)
project(${PROJECT})

# CMake modules
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/RecurseSubdirs.cmake)

# External dirs
add_subdirectory(../../common ${CMAKE_CURRENT_BINARY_DIR}/common)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core Gui Quick)

# Libs
set(LIBRARIES
# Qt5
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
# Internal
    debug_node
)

# Includes
HEADER_DIRECTORIES(NODES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes)
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

set(INCLUDES
    ${INCLUDES}
    ${NODES_INCLUDES}
    ${INTERNAL_INCLUDES}
)
include_directories(${INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h")

set(SOURCES
    ${SOURCES}
    ${INTERNAL_SOURCES}
)

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Executable target
add_executable(${PROJECT} ${SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
