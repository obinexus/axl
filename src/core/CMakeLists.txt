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
