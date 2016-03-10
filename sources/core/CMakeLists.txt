# CMake version string
cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(config)
add_subdirectory(nodes)
add_subdirectory(transport)
add_subdirectory(packets)

# Includes
set(INCLUDES
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
PARENT_SCOPE)

# Sources
set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/topics.h
PARENT_SCOPE)

# Libraries
set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)

# Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
