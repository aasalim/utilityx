#include "UtilityX.h"
#include <gtest/gtest.h>

/**
 * MaxParameterizedFixture
 *
 * Parameterized Variables:
 *      1) value
 *      2) compare
 *      3) result  (Expected)
 */
class MaxParameterizedFixture
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<int, int, int>> {
public:
    int value;
    int compare;
    int result;
    int expectedResult;
};
INSTANTIATE_TEST_SUITE_P(MaxTests, MaxParameterizedFixture,
    ::testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 1),
        std::make_tuple(-1, 0, 0),
        std::make_tuple(-1, 1, 1)));

TEST_P(MaxParameterizedFixture, Test_Max)
{
    /* Arrange */
    value = std::get<0>(GetParam());
    compare = std::get<1>(GetParam());
    expectedResult = std::get<2>(GetParam());
    /* Act */
    result = max(value, compare);
    /* Assert */
    EXPECT_EQ(result, expectedResult);
}
