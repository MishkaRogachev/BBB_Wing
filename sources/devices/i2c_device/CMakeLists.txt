# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Includes
set(INCLUDES
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
PARENT_SCOPE)

# Sources
set(SOURCES 
    ${SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/i2c_device.h
    ${CMAKE_CURRENT_SOURCE_DIR}/i2c_device.cpp
PARENT_SCOPE)