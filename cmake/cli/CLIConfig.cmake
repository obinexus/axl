# CLI library configuration

# Create CLI library
add_library(axl_cli
    # Add CLI source files as they're created
    # src/cli/axl_compiler.c is not included here as it's the main entry point
)

# Define include directories
target_include_directories(axl_cli
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cli
)

# Link dependencies
target_link_libraries(axl_cli
    PUBLIC axl_core
)

# Set compiler features and options
target_compile_features(axl_cli PRIVATE c_std_11)
apply_compiler_options(axl_cli)

if(AXL_ENABLE_SANITIZERS)
    add_sanitizers(axl_cli)
endif()

# Installation rules
install(TARGETS axl_cli
    EXPORT axl_cli-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
