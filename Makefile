# Makefile wrapper for CMake build

# Default build directory
BUILD_DIR = build

# Default build type
BUILD_TYPE ?= Debug

# CMake generation flags
CMAKE_FLAGS ?= -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

# Determine the number of CPU cores for parallel builds
NPROCS = $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)

.PHONY: all clean test install configure reconfigure

all: configure
	@echo "Building AXL compiler..."
	@cmake --build $(BUILD_DIR) -j$(NPROCS)

configure:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		echo "Configuring CMake build..."; \
		mkdir -p $(BUILD_DIR); \
		cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS) ..; \
	fi

reconfigure:
	@echo "Reconfiguring CMake build..."
	@rm -rf $(BUILD_DIR)/CMakeCache.txt
	@cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS) ..

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

test: all
	@echo "Running tests..."
	@cd $(BUILD_DIR) && ctest --output-on-failure

install: all
	@echo "Installing AXL compiler..."
	@cd $(BUILD_DIR) && cmake --install .

# Target for sanitizer builds
sanitize:
	@$(MAKE) reconfigure CMAKE_FLAGS="$(CMAKE_FLAGS) -DAXL_ENABLE_SANITIZERS=ON"
	@$(MAKE) all

# Target for dry run (just configure and show what would be built)
dry-run: configure
	@echo "Dry run complete. Build files generated in $(BUILD_DIR)"
	@echo "To build, run: make"
