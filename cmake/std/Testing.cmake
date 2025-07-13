# Test configuration for AXL project

# Function to add test executable
function(add_axl_test test_name sources)
    add_executable(${test_name} ${sources})
    target_link_libraries(${test_name} PRIVATE axl_core)
    
    # Apply compiler options and sanitizers
    apply_compiler_options(${test_name})
    if(AXL_ENABLE_SANITIZERS)
        add_sanitizers(${test_name})
    endif()
    
    # Add to CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()
