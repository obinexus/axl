# CompilerOptions.cmake - Core compiler flags and optimization settings
cmake_minimum_required(VERSION 3.14)

# Define the compiler options function that will be applied to all targets
function(apply_compiler_options target)
  target_compile_options(${target} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    $<$<CONFIG:Debug>:-g3 -O0>
    $<$<CONFIG:Release>:-O3>
  )
endfunction()
