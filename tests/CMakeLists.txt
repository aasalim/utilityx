CPMAddPackage("gh:google/googletest@1.14.0")
enable_testing()
include(GoogleTest)

add_subdirectory(unit_tests)
