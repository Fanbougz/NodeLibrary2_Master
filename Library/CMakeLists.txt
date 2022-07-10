cmake_minimum_required(VERSION 3.21)
project(Library CXX)

add_definitions(
        /DNodeLibrary2_EXPORTS
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VS_PLATFORM_NAME "x64")


# remove default flags provided with CMake for MSVC
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CXX_FLAGS "/EHsc")

########################################################################################################################
# External dependencies.
########################################################################################################################

find_package(Boost 1.77.0 REQUIRED python39 filesystem)
find_package(Python 3.9.7 REQUIRED Development)


add_definitions(
        /DNodeLibrary2_IMPORTS
)


########################################################################################################################
# Defined Nodelibrary variables.
########################################################################################################################

if (NOT DEFINED NODELIBRARY_LINK_DIR)
        if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
                set(NODELIBRARY_LINK_DIR ../NodeLibrary2/cmake-build-debug)
        else()
                set(NODELIBRARY_LINK_DIR ../NodeLibrary2/cmake-build-release)
        endif()
endif()

if (NOT DEFINED NODELIBRARY_INCLUDE_DIR)
        set(NODELIBRARY_INCLUDE_DIR ../NodeLibrary2)
endif()

########################################################################################################################


add_library(Library
        SHARED
        "mathLibrary.h"
        "main.cpp"
        "mayaLibrary.h"
        "stringLibrary.h"
        "files.h")


target_include_directories(
        Library
        PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${NODELIBRARY_INCLUDE_DIR}
        ${Python_INCLUDE_DIRS}
)

target_link_directories(Library
        PUBLIC
        ${Boost_LIBRARY_DIRS}
        ${NODELIBRARY_LINK_DIR}
        ${Python_LIBRARY_DIRS}
        )


target_link_libraries(
        Library
        PUBLIC
        Boost::python39
        Boost::filesystem
        NodeLibrary2.lib
        Python::Python
        Python::Module
)


#add_custom_command(
#        TARGET
#        Library
#        PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${NODELIBRARY_DLL_PATH}
#        ${CMAKE_CURRENT_BINARY_DIR}/NodeLibrary2.dll)


#add_custom_command(
#        TARGET
#        Library
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_CURRENT_BINARY_DIR}/NodeLibrary2.dll
#)