# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT board)
project(${PROJECT})

# Libs
set(LIBRARIES
    ${LIBRARIES}
# Internal
    sensor_altimeter_node
    sensor_ins_node
    sensor_sns_node
    servo_drives_node
    flight_recorder_node
    flight_navigator_node
    flight_pilot_node
    flight_dynamics_node
    board_transceiver_node
)

# Includes
HEADER_DIRECTORIES(NODES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes)
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${NODES_INCLUDES} ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h")

# Executable target
add_executable(${PROJECT} ${SOURCES} ${INTERNAL_SOURCES})
set_target_properties(${PROJECT} PROPERTIES AUTOMOC TRUE)

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
