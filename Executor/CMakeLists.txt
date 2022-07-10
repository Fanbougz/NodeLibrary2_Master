cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)


project(NodeLibraryExecutor CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
# if(NOT CMAKE_VS_PLATFORM_NAME)
set(CMAKE_VS_PLATFORM_NAME "x64")
# endif()


add_definitions(
        /D_CRT_SECURE_NO_WARNINGS
        /DNodeLibrary2_EXPORTS
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

cmake_minimum_required(VERSION 3.21)
project(NodeLibraryExecutor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WARN_DEPRECATED FALSE)

########################################################################################################################
# Find external packages.
########################################################################################################################

find_package(Boost 1.77.0 REQUIRED python39 filesystem)
find_package(Python 3.9.7 REQUIRED Development)

include_directories(.)
include_directories(..)
include_directories(D:/Programmes/Python3.9/include)
include_directories(D:/Programmes/Python3.9/libs)
include_directories(D:/Programmes/Python3.9/lib)
include_directories(D:/BOOST/Binaries/boost_1_77_0)


add_executable(
        NodeLibraryExecutor
        main.cpp
)


set(PROJECT_NAME NodeLibraryExecutor)

set(ROOT_NAMESPACE NodeLibraryExecutor)


################################################################################
# Include directories
################################################################################
if (NOT DEFINED NODELIBRARY_LIBRARY_DIRS)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(NODELIBRARY_LIBRARY_DIRS ../NodeLibrary2/cmake-build-debug)
    else()
        set(NODELIBRARY_LIBRARY_DIRS ../NodeLibrary2/cmake-build-release)
    endif()
endif()


if (NOT DEFINED NODELIBRARY_INCLUDE_DIRS)
    set(NODELIBRARY_INCLUDE_DIRS ../NodeLibrary2)
endif()


target_include_directories(
        NodeLibraryExecutor
        PUBLIC
        ${Python_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${NODELIBRARY_INCLUDE_DIRS}
)


target_link_directories(NodeLibraryExecutor
        PUBLIC
        ${Python_LIBRARY_DIRS}
        ${Boost_LIBRARY_DIRS}
        ${NODELIBRARY_LIBRARY_DIRS}
        )




target_link_libraries(
        NodeLibraryExecutor
        NodeLibrary2.lib
        Boost::python39
        Boost::filesystem
        Python::Python
        Python::Module
)


add_custom_command(
        TARGET
        NodeLibraryExecutor
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${NODELIBRARY_LIBRARY_DIRS}/NodeLibrary2.dll
        ${CMAKE_CURRENT_BINARY_DIR}/NodeLibrary2.dll
)