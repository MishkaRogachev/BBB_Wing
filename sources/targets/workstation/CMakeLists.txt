# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT workstation)
project(${PROJECT})

# Enable Qt modules
find_package(Qt5 COMPONENTS Gui REQUIRED)

# Libs
set(LIBRARIES
    ${LIBRARIES}
# Qt5
    Qt5::Gui
# Internal
    workstation_gateway_node
    ui_node
)

# Includes
HEADER_DIRECTORIES(NODES_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes)
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${NODES_INCLUDES} ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp" "*.h")

# Executable target
add_executable(${PROJECT} ${SOURCES} ${INTERNAL_SOURCES})
set_target_properties(${PROJECT} PROPERTIES AUTOMOC TRUE)

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
