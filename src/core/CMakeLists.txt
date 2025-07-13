# Core library build configuration
add_library(axl_core
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
