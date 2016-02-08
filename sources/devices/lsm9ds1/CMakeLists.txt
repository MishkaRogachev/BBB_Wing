# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# External dirs
add_subdirectory(../i2c_device ${CMAKE_CURRENT_BINARY_DIR}/i2c_device)

# Includes
set(INCLUDES
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
PARENT_SCOPE)

# Sources
set(SOURCES 
    ${SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1_registers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1_gyro_accel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1_mag.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1_gyro_accel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1_mag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm9ds1.cpp
PARENT_SCOPE)
