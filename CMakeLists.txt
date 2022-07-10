cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)


project(NodeLibrary2Complete CXX)

set(PROJECT_NAME NodeLibrary2Complete)


################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
# if(NOT CMAKE_VS_PLATFORM_NAME)
set(CMAKE_VS_PLATFORM_NAME "x64")


include_directories(./NodeLibrary2 ./NodeLibrary2_Python)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/NodeLibrary2)


set(BUILD_PACKAGE_SCRIPT_DIR ${CMAKE_SOURCE_DIR}/NodeLibrary2_Python)
set(BUILD_PACKAGE_DEPENDENCIES_DIRS ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/NodeLibrary2)

set(NODELIBRARY_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/NodeLibrary2)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(NODELIBRARY_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/NodeLibrary2/cmake-build-debug)
else()
    set(NODELIBRARY_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/NodeLibrary2/cmake-build-release)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/NodeLibrary2)

add_subdirectory(${CMAKE_SOURCE_DIR}/NodeLibrary2_Python)

add_subdirectory(${CMAKE_SOURCE_DIR}/Library)

add_subdirectory(${CMAKE_SOURCE_DIR}/Executor)