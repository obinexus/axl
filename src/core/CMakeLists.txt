# Core library - header-only approach initially
add_library(axl_core SHARED
    dag.c
    trie.c
)

# Define include paths
target_include_directories(axl_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)
# src/core/CMakeLists.txt - Add integration directory
target_sources(axl_core PRIVATE
    integration/trie_dag.c
)