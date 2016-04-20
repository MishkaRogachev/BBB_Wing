# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT servo_control_node)
project(${PROJECT})

# Config
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/config.conf LOCAL_CONFIG)
set(CONFIG ${CONFIG} "\n" ${LOCAL_CONFIG} PARENT_SCOPE)

# External dirs
add_subdirectory(../../devices/pca9685 ${CMAKE_CURRENT_BINARY_DIR}/devices/pca9685)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    servo_control_node.h
    servo_control_node.cpp
)

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES servo_control_node.h)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
