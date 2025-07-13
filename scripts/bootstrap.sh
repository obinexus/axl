#!/bin/bash

# AXL Compiler Bootstrap
# Usage: ./bootstrap.sh [--dry-run]

set -e

# Parse arguments
DRY_RUN=0
for arg in "$@"; do
  case $arg in
    --dry-run)
      DRY_RUN=1
      shift
      ;;
  esac
done

# Create build directory structure
mkdir -p build/core
mkdir -p build/cli

# Function to process .axl.in files
process_axl_files() {
  local src_dir=$1
  local build_dir=$2
  
  for file in $(find ${src_dir} -name "*.axl.in"); do
    rel_path=$(realpath --relative-to="${src_dir}" "${file}")
    target_file="${build_dir}/${rel_path%.in}"
    
    if [ $DRY_RUN -eq 1 ]; then
      echo "[DRY RUN] Would process ${file} -> ${target_file}"
    else
      echo "Processing ${file} -> ${target_file}"
      # Actual processing logic would go here
      cp "${file}" "${target_file}"
    fi
  done
}

# Compile source files
compile_sources() {
  if [ $DRY_RUN -eq 1 ]; then
    echo "[DRY RUN] Would compile src/core/*.c to build/core/*.o"
    echo "[DRY RUN] Would compile src/cli/*.c to build/cli/*.o"
  else
    echo "Compiling core components..."
    for src in src/core/*.c; do
      base=$(basename "$src" .c)
      gcc -c -I./include "$src" -o "build/core/${base}.o"
    done
    
    echo "Compiling CLI components..."
    for src in src/cli/*.c; do
      base=$(basename "$src" .c)
      gcc -c -I./include "$src" -o "build/cli/${base}.o"
    done
  fi
}

# Link final executable
link_executable() {
  if [ $DRY_RUN -eq 1 ]; then
    echo "[DRY RUN] Would link objects to build/axl"
  else
    echo "Linking executable..."
    gcc build/core/*.o build/cli/*.o -o build/axl
  fi
}

# Process input relation files
process_axl_files "src" "build"

# Compile and link
compile_sources
link_executable

if [ $DRY_RUN -eq 1 ]; then
  echo "[DRY RUN] Bootstrap completed successfully"
else
  echo "Bootstrap completed successfully"
  echo "Executable created at: $(pwd)/build/axl"
fi
