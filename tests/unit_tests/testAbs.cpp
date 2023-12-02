#include "UtilityX.h"
#include <gtest/gtest.h>

/**
 * AbsParameterizedFixture
 *
 * Parameterized Variables:
 *      1) value
 *      2) result  (Expected)
 */
class AbsParameterizedFixture
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<int, int>> {
public:
    int value;
    int compare;
    int result;
    int expectedResult;
};
INSTANTIATE_TEST_SUITE_P(AbsTests, AbsParameterizedFixture,
    ::testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(-1, 1)));

TEST_P(AbsParameterizedFixture, Test_Abs)
{
    /* Arrange */
    value = std::get<0>(GetParam());
    expectedResult = std::get<1>(GetParam());
    /* Act */
    result = X::abs(value);
    /* Assert */
    EXPECT_EQ(result, expectedResult);
}
