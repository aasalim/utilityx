#include "UtilityX.h"
#include <gtest/gtest.h>

/**
 * MinParameterizedFixture
 *
 * Parameterized Variables:
 *      1) value
 *      2) compare
 *      3) result  (Expected)
 */
class MinParameterizedFixture
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<int, int, int>> {
public:
    int value;
    int compare;
    int result;
    int expectedResult;
};
INSTANTIATE_TEST_SUITE_P(MinTests, MinParameterizedFixture,
    ::testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 0),
        std::make_tuple(-1, 0, -1),
        std::make_tuple(-1, 1, -1)));

TEST_P(MinParameterizedFixture, Test_Min)
{
    /* Arrange */
    value = std::get<0>(GetParam());
    compare = std::get<1>(GetParam());
    expectedResult = std::get<2>(GetParam());
    /* Act */
    result = X::min(value, compare);
    /* Assert */
    EXPECT_EQ(result, expectedResult);
}
