# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT flight_navigator_node)
project(${PROJECT})

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h")

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES
    flight_navigator_node.h
    navigation_states/abstract_navigation_state.h
    navigation_states/idle_navigation_state.h
    navigation_states/takeoff_navigation_state.h
)

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
