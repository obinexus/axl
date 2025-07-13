# Root CMakeLists.txt for AXL Compiler
cmake_minimum_required(VERSION 3.14)
project(axl VERSION 0.1.0 LANGUAGES C)

# Add custom cmake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/std")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/core")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cli")

# Load standard modules
include(CompilerOptions)
include(Sanitizers)
include(Testing)

# Define build options
option(AXL_BUILD_TESTS "Build AXL test suite" ON)
option(AXL_ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
  message(STATUS "Setting build type to Debug as none was specified")
endif()

# Include core and CLI components
include(CoreConfig)
include(CLIConfig)

# Define the main executable target
add_executable(axl src/cli/axl_compiler.c)
target_link_libraries(axl PRIVATE axl_core axl_cli)

# Install configuration
install(TARGETS axl
        RUNTIME DESTINATION bin)

# Testing configuration
if(AXL_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
