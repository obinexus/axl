#!/bin/bash

# QA Bootstrap for AXL Module
# Handles nested repositories and integration testing

set -e

# Configuration
MAIN_REPO="$(pwd)"
CORE_REPO="${MAIN_REPO}/submodules/core"
CLI_REPO="${MAIN_REPO}/submodules/cli"

# Ensure submodules are initialized
if [ ! -d "${CORE_REPO}" ] || [ ! -d "${CLI_REPO}" ]; then
  echo "Initializing submodules..."
  git submodule update --init --recursive
fi

# Synchronize header files to main include directory
sync_headers() {
  echo "Synchronizing header files..."
  mkdir -p "${MAIN_REPO}/include/axl"
  cp "${CORE_REPO}/include/axl/"*.h "${MAIN_REPO}/include/axl/"
  cp "${CLI_REPO}/include/axl/"*.h "${MAIN_REPO}/include/axl/"
}

# Link source files to main src directory
link_sources() {
  echo "Linking source files..."
  mkdir -p "${MAIN_REPO}/src/core"
  mkdir -p "${MAIN_REPO}/src/cli"
  
  # Use symbolic links to maintain reference to original repositories
  for file in "${CORE_REPO}/src/core/"*.c; do
    base=$(basename "$file")
    ln -sf "$file" "${MAIN_REPO}/src/core/${base}"
  done
  
  for file in "${CLI_REPO}/src/cli/"*.c; do
    base=$(basename "$file")
    ln -sf "$file" "${MAIN_REPO}/src/cli/${base}"
  done
}

# Run main bootstrap with the provided arguments
run_bootstrap() {
  echo "Running main bootstrap..."
  "${MAIN_REPO}/bootstrap.sh" "$@"
}

# Execute QA test suite
run_tests() {
  echo "Running test suite..."
  "${MAIN_REPO}/tests/run_tests.sh"
}

# Main execution flow
sync_headers
link_sources
run_bootstrap "$@"

if [[ ! "$*" == *"--dry-run"* ]]; then
  run_tests
fi

echo "QA bootstrap completed successfully"
