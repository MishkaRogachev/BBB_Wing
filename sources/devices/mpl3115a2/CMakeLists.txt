# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# External dirs
add_subdirectory(../interfaces ${CMAKE_CURRENT_BINARY_DIR}/interfaces)
add_subdirectory(../i2c_device ${CMAKE_CURRENT_BINARY_DIR}/i2c_device)

# Includes
set(INCLUDES
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
PARENT_SCOPE)

# Sources
set(SOURCES 
    ${SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/mpl3115a2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpl3115a2_registers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpl3115a2.cpp
PARENT_SCOPE)

# Tests
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
