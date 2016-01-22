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
    ${CMAKE_CURRENT_SOURCE_DIR}/base_transport.h
    ${CMAKE_CURRENT_SOURCE_DIR}/base_transport.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/publisher.h
    ${CMAKE_CURRENT_SOURCE_DIR}/publisher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/subscriber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/subscriber.cpp
PARENT_SCOPE)

# Libraries
set(LIBRARIES
    ${LIBRARIES}
# ZeroMQ
    zmq
PARENT_SCOPE
)

# Tests
if (NOT TARGET transport_tests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
