cmake_minimum_required(VERSION 3.14)
project(axl VERSION 0.1.0 LANGUAGES C)

# Configuration paths
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/std")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/core")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cli")

# Include standard configuration modules
include(CompilerOptions)
include(Sanitizers)
include(Testing)

# Ensure output directories exist
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Core library configuration
add_subdirectory(src/core)

# CLI application configuration
add_subdirectory(src/cli)

# Set up testing infrastructure
enable_testing()
