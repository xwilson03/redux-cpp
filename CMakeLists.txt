# Project Settings
cmake_minimum_required(VERSION 3.28)

# Compile Settings

set(CMAKE_CC_COMPILER        "clang")
set(CMAKE_CXX_COMPILER     "clang++")
set(CMAKE_CXX_STANDARD            20)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS         OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES    ON)

# Includes
include(GNUInstallDirs)

# Project
project(redux-cpp)
add_subdirectory(lib)

option(BUILD_EXAMPLES "Toggle building examples on/off." OFF)
if(${PROJECT_IS_TOP_LEVEL} AND ${BUILD_EXAMPLES})
  add_subdirectory(example)
endif()
