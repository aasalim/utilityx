#include "UtilityX.h"
#include <gtest/gtest.h>

/**
 * ClampParameterizedFixture
 *
 * Parameterized Variables:
 *      1) value
 *      2) low
 *      3) high
 *      4) results  (Expected)
 */
class ClampParameterizedFixture
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<int, int, int, int>> {
public:
    int value;
    int low;
    int high;
    int result;
    int expectedResult;
};
INSTANTIATE_TEST_SUITE_P(ClampTests, ClampParameterizedFixture,
    ::testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(0, 1, 2, 1),
        std::make_tuple(3, 1, 2, 2)));

TEST_P(ClampParameterizedFixture, Test_Clamp)
{
    /* Arrange */
    value = std::get<0>(GetParam());
    low = std::get<1>(GetParam());
    high = std::get<2>(GetParam());
    expectedResult = std::get<3>(GetParam());
    /* Act */
    result = clamp(value, low, high);
    /* Assert */
    EXPECT_EQ(result, expectedResult);
}
