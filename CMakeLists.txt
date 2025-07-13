cmake_minimum_required(VERSION 3.14)
project(axl VERSION 0.1.0 LANGUAGES C)

# Configuration paths for OBINexus modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/std")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/core")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cli")

# Include standard configuration modules
include(CompilerOptions)
include(Sanitizers)
include(Testing)

# Core library configuration
add_subdirectory(src/core)

# CLI application configuration
add_subdirectory(src/cli)

# Documentation explicitly states test requirements
enable_testing()
