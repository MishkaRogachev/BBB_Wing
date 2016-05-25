# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT board_transceiver_node)
project(${PROJECT})

# Config
ADD_JSON_CONFIG(${CMAKE_CURRENT_SOURCE_DIR}/config.json)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h")

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES
    board_transceiver_node.h
    board_receiver/board_receiver.h
    board_transmitter/board_transmitter.h
)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
