# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT ui_node)
project(${PROJECT})

# Enable required Qt modules
find_package(Qt5 COMPONENTS Gui Quick Positioning Location REQUIRED)

# Libraries
set(LIBRARIES
# Qt5
    Qt5::Gui
    Qt5::Quick
    Qt5::Positioning
    Qt5::Location
)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Sources and headrers
file(GLOB_RECURSE INTERNAL_HEADERS "*.h")
file(GLOB_RECURSE INTERNAL_SOURCES "*.cpp")
file(GLOB_RECURSE INTERNAL_QML "*.qml" "*.js")

# Resources
file(GLOB QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES})

# Qt5 wrap node's headers
qt5_wrap_cpp(MOC_SOURCES ${INTERNAL_HEADERS})

# Static Library target
add_library(${PROJECT} STATIC ${SOURCES} ${INTERNAL_SOURCES} ${INTERNAL_HEADERS}
            ${INTERNAL_QML} ${QRC_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})
