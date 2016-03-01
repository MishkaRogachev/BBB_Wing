# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_sns_node)
project(${PROJECT})

# Libraries
set(LIBRARIES
    ${LIBRARIES}
# Gpsd
    gps
)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    sensor_sns_node.h
    sensor_sns_node.cpp
)

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES sensor_sns_node.h)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
