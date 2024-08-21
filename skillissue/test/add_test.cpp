#include <gtest/gtest.h>
#include "add.hpp"

// Test for the add function
TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(3, 4), 7);  // 3 + 4 = 7
}

TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(add(-3, -4), -7);  // -3 + -4 = -7
}

TEST(AdditionTest, MixedNumbers) {
    EXPECT_EQ(add(-3, 4), 1);  // -3 + 4 = 1
}

TEST(AdditionTest, ZeroNumbers) {
    EXPECT_EQ(add(0, 0), 0);  // 0 + 0 = 0
}
