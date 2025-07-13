# Core library build configuration
add_library(axl_core SHARED
    trie.c
    dag.c
)

# Define taxonomy.h as a dependency for trie.h
set_source_files_properties(
    trie.c
    PROPERTIES
    OBJECT_DEPENDS "${CMAKE_SOURCE_DIR}/include/axl/core/taxonomy.h"
)

# Define include directories with proper scope
target_include_directories(axl_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Apply compiler options with warning suppressions where needed
target_compile_options(axl_core
    PRIVATE
        -Wall
        -Wextra
        -Werror
        -Wno-unused-parameter  # Only if you need to temporarily suppress warnings
)