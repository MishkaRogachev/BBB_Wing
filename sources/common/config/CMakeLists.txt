# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Includes
set(INCLUDES
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
PARENT_SCOPE)
    
# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.h" "*.cpp")
set(SOURCES 
    ${SOURCES} 
    ${INTERNAL_SOURCES}
PARENT_SCOPE)