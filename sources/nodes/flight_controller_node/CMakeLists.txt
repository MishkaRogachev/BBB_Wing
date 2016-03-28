# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT flight_controller_node)
project(${PROJECT})

# Config
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/config.conf LOCAL_CONFIG)
set(CONFIG ${CONFIG} "\n" ${LOCAL_CONFIG} PARENT_SCOPE)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h")

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES flight_controller_node.h)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
