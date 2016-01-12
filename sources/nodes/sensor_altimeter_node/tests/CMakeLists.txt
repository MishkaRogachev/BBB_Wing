# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_altimeter_test)
project(${PROJECT})

# Test executable output path
set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/tests)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core Test)

# Libs
set(LIBRARIES
# Qt5
    Qt5::Core
    Qt5::Test
# Internal
    sensor_altimeter_node
)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDES
    ${INCLUDES}
    ${INTERNAL_INCLUDES}
)
include_directories(${INCLUDES})

# Test sources
set(TEST_SOURCES
    sensor_altimeter_test.cpp
)

# Add compiler flags
add_definitions(-std=c++11 -Wall)

# Executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Tests
add_test (NAME ${PROJECT} COMMAND ${PROJECT})
