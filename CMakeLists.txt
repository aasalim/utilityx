#
# Main CMakelists for the UtilityX project.
#
# Project description
#
# Project specific options :
# - BP_USE_DOXYGEN
# - BP_BUILD_TESTS (requires BUILD_TESTING set to ON)
# Other options might be available through the cmake scripts including (not exhaustive):
# - ENABLE_WARNINGS_SETTINGS
#
cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

# Put the project early since modules might need to detect the compiler.
# More information https://cmake.org/cmake/help/latest/command/project.html
project(
    "UtilityX" # This will exposed as the variable PROJECT_NAME.
    VERSION 0.1.0 # Used for installation and defines variables PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, and PROJECT_VERSION_TWEAK.
    LANGUAGES C CXX # Used to determine the languages to use based on file extensions
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# ########################################################## MODULES AND SCRIPTS

# Standard CMake modules
include(CMakeDependentOption) # This is a really useful scripts that creates options that depends on other options. It can even be used with generator expressions !
include(GNUInstallDirs) # This will define the default values for installation directories (all platforms even if named GNU)
include(InstallRequiredSystemLibraries) # Tell CMake that the `install` target needs to install required system libraries (eg: Windows SDK)
include(CMakePackageConfigHelpers) # Helper to create relocatable packages

# Custom modules and scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake") # Make our cmake scripts available

include(Warnings)
include(CPM)
include(StaticAnalyzers)

# ###################################################################### OPTIONS

# You should try to give as much control over the project setup to the user.
# When modifying compile flags for example, if they are not mandatory, provide an option.
option(${PROJECT_NAME}_BUILD_TESTS "Enable ${PROJECT_NAME} project tests targets" OFF)
option(${PROJECT_NAME}_BUILD_EXAMPLES "Enable ${PROJECT_NAME} project example targets" OFF)
option(${PROJECT_NAME}_BUILD_COVERAGE "Enable ${PROJECT_NAME} project with coverage" OFF)
option(${PROJECT_NAME}_BUILD_CPPCHECK "Enable ${PROJECT_NAME} project with cppcheck" OFF)
option(${PROJECT_NAME}_BUILD_CCACHE "Enable ${PROJECT_NAME} project with ccache" OFF)
option(${PROJECT_NAME}_BUILD_DEV "Enable ${PROJECT_NAME} project development options" OFF)

if(NOT ${PROJECT_NAME}_BUILD_DEV)
    set(${PROJECT_NAME}_BUILD_TESTS OFF)
    set(${PROJECT_NAME}_BUILD_EXAMPLES OFF)
    set(${PROJECT_NAME}_BUILD_COVERAGE OFF)
    set(${PROJECT_NAME}_BUILD_CPPCHECK OFF)
    set(${PROJECT_NAME}_BUILD_CCACHE OFF)
else()
    # Verbose makefile
    set(CMAKE_VERBOSE_MAKEFILE ON)

    # Generate compile_commands.json
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Enable Compiler Cache tool
if(${PROJECT_NAME}_BUILD_CCACHE)
    include(Cache)
    check_enable_cache()
endif()

# Static Analyzer
# Enable Cppcheck
if(${PROJECT_NAME}_BUILD_CPPCHECK)
    tool_enable_cppcheck(ON "" # override cppcheck options
    )
endif()

# External dependencies
add_subdirectory(external EXCLUDE_FROM_ALL)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# When building a shared library, you do not want to export all symbols by default
# gcc (and hence clang) are wrong about this.
#
# For more information, see https://gcc.gnu.org/wiki/Visibility and https://www.youtube.com/embed/m0DwB4OvDXk
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# ###################################################################### PROJECT
# Project Dependencies
# CPMAddPackage("gh:aasalim/UtilityX#2676563bae7d79b3ccf1e64d61cda1e8ea97d111")

# ############################################################ UtilityX Library

# Always list the source files explicitly, including headers so that they are listed in the IDE
# If you need to use files based on a variable value, use target_sources
add_library(UtilityX src/UtilityX.cpp)

# Since we put the public interface headers in the include directory, we need to tell the compiler so that we can #include <file>.
target_include_directories(UtilityX
    PUBLIC # The folder must be used in the include path for any target using this library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> # Due to the way installation work, we only want this path set when building, not once installed
)

# The following properties are useful when you want to have an 'install' target
set_target_properties(UtilityX
    PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_LIST_DIR}/include/UtilityX.h # Headers listed here will automatically be copied when installing. Note that directories hierarchy is not preserved.
    DEBUG_POSTFIX d # We had a postfix so that we can install debug and release libraries side by side (Windows way)
)

# CMake scripts extensions
target_set_warnings(UtilityX ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Helper that can set default warning flags for you

# Give a 'namespaced' name to libraries targets, as it can't be mistaken with system libraries
# Use the same namespace as the one from the install command. This is only really needed if you want to support usage of your library through add_subdirectory.
add_library(${PROJECT_NAME}::xUtilityX ALIAS UtilityX)

# ############################################################ BUILD DEVELOPMENT
if(${PROJECT_NAME}_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(${PROJECT_NAME}_BUILD_COVERAGE)
    include(Coverage)
    include(CodeCoverage)
    set(GCOVR_ADDITIONAL_ARGS "--decisions" "-s" "--keep")
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE ctest
        DEPENDENCIES UtilityX
        BASE_DIRECTORY "${CMAKE_SOURCE_DIR}"
        EXCLUDE "tests" "examples/" "build/")

    set(${PROJECT_NAME}_BUILD_TESTS ON)
endif()

if(${PROJECT_NAME}_BUILD_TESTS)
    include(CTest) # Must be called before adding tests but after calling project(). This automatically calls enable_testing() and configures ctest targets when using Make/Ninja

    # Let the user add options to the test runner if needed
    set(TEST_RUNNER_PARAMS "--force-colors=true" CACHE STRING "Options to add to our test runners commands")

    add_subdirectory(tests)
endif()
