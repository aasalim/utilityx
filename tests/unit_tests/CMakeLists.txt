
add_executable(TestConstrain testConstrain.cpp)

target_link_libraries(TestConstrain
    PUBLIC
    GTest::gtest_main
    GTest::gmock
    xTemplate
)
gtest_discover_tests(TestConstrain)
