
add_executable(UnitTests testClamp.cpp
    testMax.cpp
    testMin.cpp
    testSign.cpp)

target_link_libraries(UnitTests
    PUBLIC
    GTest::gtest_main
    GTest::gmock
    UtilityX
)
gtest_discover_tests(UnitTests)
