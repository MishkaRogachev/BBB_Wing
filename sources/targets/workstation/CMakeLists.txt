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
    workstation_transceiver_node
)

# Includes
HEADER_DIRECTORIES(NODES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes)
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${NODES_INCLUDES} ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h" "*.qml")

# Resources
file(GLOB QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES})

# Executable target
add_executable(${PROJECT} ${SOURCES} ${INTERNAL_SOURCES} ${QRC_SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
