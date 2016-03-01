# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT core_tests)
project(${PROJECT})

# Enable Qt modules
find_package(Qt5 COMPONENTS Test)

# Libs
set(LIBRARIES
    ${LIBRARIES}
# Qt5
    Qt5::Test
# ZeroMQ
    zmq
)

# Includes
HEADER_DIRECTORIES(TEST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${TEST_INCLUDES})

# Test sources
file(GLOB_RECURSE TEST_SOURCES "../*.h" "../*.cpp")

# Executable
add_executable(${PROJECT} ${TEST_SOURCES})
set_target_properties(${PROJECT} PROPERTIES AUTOMOC TRUE)

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Tests
add_test (NAME ${PROJECT} COMMAND ${PROJECT})
