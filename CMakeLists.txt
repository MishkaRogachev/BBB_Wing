# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
project(BBB_Wing)

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Nodes targets
add_subdirectory(sources/nodes/debug_node)
add_subdirectory(sources/nodes/sensor_altimeter_node)
add_subdirectory(sources/nodes/sensor_sns_node)
add_subdirectory(sources/nodes/flight_recorder_node)

# Target subdirectories
add_subdirectory(sources/targets/board)

