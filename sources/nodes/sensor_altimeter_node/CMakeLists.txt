# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_altimeter_node)
project(${PROJECT})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# External dirs
add_subdirectory(../../devices/mpl3115a2 ${CMAKE_CURRENT_BINARY_DIR}/devices/mpl3115a2)

# Enable Qt modules
find_package(Qt5 COMPONENTS Core)

# Libraries
set(LIBRARIES
    ${LIBRARIES}
# Qt5
    Qt5::Core
)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDES
    ${INCLUDES}
    ${INTERNAL_INCLUDES}
)
include_directories(${INCLUDES})

# Sources
set(INTERNAL_SOURCES
    sensor_altimeter_node.h
    sensor_altimeter_node.cpp
)

set(SOURCES
    ${SOURCES}
    ${INTERNAL_SOURCES}
)

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
