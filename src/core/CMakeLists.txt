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
# Core module dependencies in CMakeLists.txt

add_library(axl_core_taxonomy STATIC src/core/taxonomy.c)
add_library(axl_core_token STATIC src/core/token.c)
add_library(axl_core_trie STATIC src/core/trie.c)
add_library(axl_core_dag STATIC src/core/dag.c)

# Enforce correct dependency order
add_dependencies(axl_core_dag axl_core_token axl_core_taxonomy)
add_dependencies(axl_core_trie axl_core_token axl_core_taxonomy)
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