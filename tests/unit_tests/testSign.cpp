#include "UtilityX.h"
#include <gtest/gtest.h>

/**
 * SignParameterizedFixture
 *
 * Parameterized Variables:
 *      1) value
 *      2) result  (Expected)
 */
class SignParameterizedFixture
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<int, int>> {
public:
    int value;
    int compare;
    int result;
    int expectedResult;
};
INSTANTIATE_TEST_SUITE_P(SignTests, SignParameterizedFixture,
    ::testing::Values(
        std::make_tuple(0, 1),
        std::make_tuple(1, 1),
        std::make_tuple(-1, -1)));

TEST_P(SignParameterizedFixture, Test_Sign)
{
    /* Arrange */
    value = std::get<0>(GetParam());
    expectedResult = std::get<1>(GetParam());
    /* Act */
    result = sign(value);
    /* Assert */
    EXPECT_EQ(result, expectedResult);
}
