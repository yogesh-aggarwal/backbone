cmake_minimum_required(VERSION 3.20)

# Project Configuration
project(backbone VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/source)

# Add subdirectories
add_subdirectory(source)
add_subdirectory(cmd)
