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
    ${CMAKE_CURRENT_SOURCE_DIR}/barometric_altimeter.h
PARENT_SCOPE)
