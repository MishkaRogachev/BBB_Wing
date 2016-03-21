# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
project(BBB_Wing)

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add globaly compiler flags
add_compile_options(-std=c++11 -Wall -fPIC)

# Enable globaly some Qt modules
find_package(Qt5 COMPONENTS Core Network SerialPort REQUIRED)

# Global libraries
set(LIBRARIES
# Qt5
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
)

# Core
add_subdirectory(sources/core)

# Tagret type. Avalible values: all, workstation, board
if (NOT TARGET_TYPE)
    set(TARGET_TYPE "all")
endif (NOT TARGET_TYPE)
message("Tagret type: " ${TARGET_TYPE})

# Nodes targets
if (TARGET_TYPE STREQUAL "board" OR TARGET_TYPE STREQUAL "all")
    add_subdirectory(sources/nodes/sensor_altimeter_node)
    add_subdirectory(sources/nodes/sensor_ins_node)
    add_subdirectory(sources/nodes/sensor_sns_node)
    add_subdirectory(sources/nodes/flight_recorder_node)
    add_subdirectory(sources/nodes/flight_controller_node)
    add_subdirectory(sources/nodes/board_transceiver_node)

    add_subdirectory(sources/targets/board)
endif()

if (TARGET_TYPE STREQUAL "workstation" OR TARGET_TYPE STREQUAL "all")
    add_subdirectory(sources/nodes/workstation_transceiver_node)
    add_subdirectory(sources/nodes/ui_node)

    add_subdirectory(sources/targets/workstation)
endif()

# Copy config
file(COPY ${CMAKE_SOURCE_DIR}/config/settings.ini
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
