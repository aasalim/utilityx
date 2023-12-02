BUILD_TESTS=1
BUILD_EXAMPLES=1
BUILD_COVERAGE=1
BUILD_CPPCHECK=1
BUILD_CCACHE=1
BUILD_DEV=1

BUILD_GENERATOR= "Ninja"

# Debug or Release Configuration depending on whether coverage is enabled
ifeq ($(BUILD_COVERAGE),1)
	BUILD_TYPE ?= Debug
else
	BUILD_TYPE ?= Release
endif

# Build Directory
BUILD_DIR ?= build

# Run all by building, running tests, and executable
all: build

# Configure CMake
configure:
	poetry install
	@cmake -G $(BUILD_GENERATOR) \
	-B $(BUILD_DIR)/$(BUILD_TYPE) \
	-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
	-DUtilityX_BUILD_TESTS=$(BUILD_TESTS) \
	-DUtilityX_BUILD_EXAMPLES=$(BUILD_EXAMPLES) \
	-DUtilityX_BUILD_COVERAGE=$(BUILD_COVERAGE) \
	-DUtilityX_BUILD_CPPCHECK=$(BUILD_CPPCHECK) \
	-DUtilityX_BUILD_CCACHE=$(BUILD_CCACHE) \
	-DUtilityX_BUILD_DEV=$(BUILD_DEV) 
# Build using Ninja with configuration type
.PHONY: build
build:configure
	cmake --build $(BUILD_DIR)/$(BUILD_TYPE) --config $(BUILD_TYPE)

# Run tests, depends on build
.PHONY: test
test: build
	cmake --build $(BUILD_DIR)/$(BUILD_TYPE)  --target test

# Run execuatable, depends on build
.PHONY: run
run: build
	./$(BUILD_DIR)/$(BUILD_TYPE)/examples/example1/Example1

# Run code coverage 
.PHONY: coverage
coverage: test
	cmake --build $(BUILD_DIR)/$(BUILD_TYPE) --target coverage

# Clean build directory
clean clear:
	@echo Cleaning build directory...
	@rm -rf $(BUILD_DIR)