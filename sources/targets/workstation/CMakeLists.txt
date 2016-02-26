# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT workstation)
project(${PROJECT})

# Enable Qt modules
find_package(Qt5 COMPONENTS Gui Quick Positioning Location REQUIRED)

# Libs
set(LIBRARIES
    ${LIBRARIES}
# Qt5
    Qt5::Gui
    Qt5::Quick
    Qt5::Positioning
    Qt5::Location
# Internal
    debug_node
)

# Includes
HEADER_DIRECTORIES(NODES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes)
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

set(INCLUDES
    ${INCLUDES}
    ${NODES_INCLUDES}
    ${INTERNAL_INCLUDES}
)
include_directories(${INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h" "*.qml")
set(SOURCES
    ${SOURCES}
    ${INTERNAL_SOURCES}
)

# Resources
file(GLOB QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES})

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Executable target
add_executable(${PROJECT} ${SOURCES} ${QRC_SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
