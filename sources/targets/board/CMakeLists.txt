# CMake version string
cmake_minimum_required(VERSION 2.8.12)

# Project
set(PROJECT board)
project(${PROJECT})

# CMake modules
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/RecurseSubdirs.cmake)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core)

# Libs
set(LIBRARIES
# Qt5
    Qt5::Core
)

# Include directories
HEADER_DIRECTORIES(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES})

# Sources
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Executable target
add_executable(${PROJECT} ${SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
