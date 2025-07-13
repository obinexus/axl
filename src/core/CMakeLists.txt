# Core library build configuration
add_library(axl_core SHARED
    trie.c
    dag.c
)

target_include_directories(axl_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Apply compiler options
apply_compiler_options(axl_core)

# Set output properties for consistent naming
set_target_properties(axl_core PROPERTIES
    OUTPUT_NAME "axl"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Also create static library variant
add_library(axl_static STATIC
    trie.c
    dag.c
)

target_include_directories(axl_static
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

apply_compiler_options(axl_static)

set_target_properties(axl_static PROPERTIES
    OUTPUT_NAME "axl"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
