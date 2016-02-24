# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Includes
set(INCLUDES
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes
    ${CMAKE_CURRENT_SOURCE_DIR}/transceivers
    ${CMAKE_CURRENT_SOURCE_DIR}/packets
PARENT_SCOPE)
    
# Sources
set(SOURCES 
    ${SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes/abstract_node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes/abstract_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes/abstract_node_frequency.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes/abstract_node_frequency.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes/scheduler_node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nodes/scheduler_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/transceivers/abstract_transceiver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/transceivers/abstract_transceiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/packets/base_packet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/packets/base_packet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/packets/board_packet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/packets/board_packet.cpp
PARENT_SCOPE)

# Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
