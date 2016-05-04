# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT sensor_ins_node)
project(${PROJECT})

# Config
ADD_JSON_CONFIG(${CMAKE_CURRENT_SOURCE_DIR}/config.json)

# External dirs
add_subdirectory(../../devices/i2c_device ${CMAKE_CURRENT_BINARY_DIR}/devices/i2c_device)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
set(INTERNAL_SOURCES
    sensor_ins_node.h
    sensor_ins_node.cpp
    imus/i_imu.h
    imus/lsm9ds1/lsm9ds1.h
    imus/lsm9ds1/lsm9ds1_registers.h
    imus/lsm9ds1/lsm9ds1_gyro_accel.h
    imus/lsm9ds1/lsm9ds1_mag.h
    imus/lsm9ds1/lsm9ds1_gyro_accel.cpp
    imus/lsm9ds1/lsm9ds1_mag.cpp
    imus/lsm9ds1/lsm9ds1.cpp
)

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES sensor_ins_node.h)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
