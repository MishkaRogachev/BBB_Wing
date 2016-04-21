# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_altimeter_node)
project(${PROJECT})

# Config
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/config.conf LOCAL_CONFIG)
set(CONFIG ${CONFIG} "\n" ${LOCAL_CONFIG} PARENT_SCOPE)

# External dirs
add_subdirectory(../../devices/i2c_device ${CMAKE_CURRENT_BINARY_DIR}/devices/i2c_device)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    sensor_altimeter_node.h
    sensor_altimeter_node.cpp
    altimeters/barometric_altimeter.h
    altimeters/mpl3115a2/mpl3115a2.h
    altimeters/mpl3115a2/mpl3115a2_registers.h
    altimeters/mpl3115a2/mpl3115a2.cpp
)

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES sensor_altimeter_node.h)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
