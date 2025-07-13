# Core library configuration

# Create core library
add_library(axl_core
    src/core/trie.c
    src/core/dag.c
    # Add other core source files as they're created
)

# Define include directories
target_include_directories(axl_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

# Set compiler features and options
target_compile_features(axl_core PRIVATE c_std_11)
apply_compiler_options(axl_core)

if(AXL_ENABLE_SANITIZERS)
    add_sanitizers(axl_core)
endif()

# Installation rules
install(TARGETS axl_core
    EXPORT axl_core-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/axl
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
