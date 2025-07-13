# CLI application build configuration
add_executable(axl
    main.c
)

target_link_libraries(axl
    PRIVATE
        axl_core
)

target_include_directories(axl
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# Apply compiler options
apply_compiler_options(axl)

# Install the binary
install(TARGETS axl
    RUNTIME DESTINATION bin
)
