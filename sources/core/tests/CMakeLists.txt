# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT core_tests)
project(${PROJECT})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core Test)

# Libs
set(LIBRARIES
    ${LIBRARIES}
# Qt5
    Qt5::Core
    Qt5::Test
# ZeroMQ
    zmq
)

# Includes
HEADER_DIRECTORIES(TEST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${TEST_INCLUDES})

# Test sources
file(GLOB_RECURSE TEST_SOURCES "../*.h" "../*.cpp")

# Add compiler flags
add_definitions(-std=c++11 -Wall)

# Executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Tests
add_test (NAME ${PROJECT} COMMAND ${PROJECT})
