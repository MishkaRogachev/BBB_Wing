# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
project(BBB_Wing)

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Tagret type. Avalible values: all, workstation, board
if (NOT TARGET_TYPE)
    set(TARGET_TYPE "all")
endif (NOT TARGET_TYPE)
message("Tagret type: " ${TARGET_TYPE})

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Common & framework-specific tagrets
add_subdirectory(sources/common)
add_subdirectory(sources/transport)

# Nodes targets
if (TARGET_TYPE STREQUAL "board" OR TARGET_TYPE STREQUAL "all")
    add_subdirectory(sources/nodes/debug_node)
    add_subdirectory(sources/nodes/sensor_altimeter_node)
    add_subdirectory(sources/nodes/sensor_ins_node)
    add_subdirectory(sources/nodes/sensor_sns_node)
    add_subdirectory(sources/nodes/flight_recorder_node)

    add_subdirectory(sources/targets/board)
endif()

if (TARGET_TYPE STREQUAL "workstation" OR TARGET_TYPE STREQUAL "all")
    if (NOT TARGET debug_node)
        add_subdirectory(sources/nodes/debug_node)
    endif()
    add_subdirectory(sources/targets/workstation)
endif()
