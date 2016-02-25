# CMake version string
cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(config)
add_subdirectory(nodes)
add_subdirectory(transport)
add_subdirectory(packets)

# Parent scoping
set(INCLUDES ${INCLUDES} PARENT_SCOPE)
set(SOURCES ${SOURCES} PARENT_SCOPE)
set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)

# Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
