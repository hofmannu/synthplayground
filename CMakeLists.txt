cmake_minimum_required(VERSION 3.0.0...3.28.0)

project(synthplayground 
    VERSION 0.1
    LANGUAGES CXX)

option(BUILD_TESTS "Build tests" ON)

# add municode to compile options
set(CMAKE_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the build type if not already set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set the default install prefix to the build directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "..." FORCE)
endif()

# add subdirectory /cmake/modules to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

find_package(miniaudio REQUIRED)

# defining the backbone of the application that is used by all wrappers 
# does the actual work, everything else is just a wrapper around this
add_library(synthengine STATIC "")

target_include_directories(synthengine PUBLIC
    ${miniaudio_INCLUDE_DIR}
)

add_subdirectory(src/)

# unit testing if requested
if (BUILD_TESTS)
    add_subdirectory(tests/)
endif()