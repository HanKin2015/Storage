// tests/test_math_functions.cpp
#include <gtest/gtest.h>
#include "math_functions.h"

TEST(AdditionTest, HandlesPositiveNumbers) {
    EXPECT_EQ(add(1, 2), 3);
}

TEST(AdditionTest, HandlesNegativeNumbers) {
    EXPECT_EQ(add(-1, -2), -3);
}

TEST(AdditionTest, HandlesMixedNumbers) {
    EXPECT_EQ(add(-1, 2), 1);
}