# CLI application build configuration
add_executable(axl_cli
    main.c
)

# Rename the output binary to simply "axl"
set_target_properties(axl_cli PROPERTIES
    OUTPUT_NAME "axl"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link against the core library
target_link_libraries(axl_cli
    PRIVATE
        axl_core
)

target_include_directories(axl_cli
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# Apply compiler options
apply_compiler_options(axl_cli)
