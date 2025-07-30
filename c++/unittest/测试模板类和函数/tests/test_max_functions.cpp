// tests/test_max_functions.cpp
#include <gtest/gtest.h>
#include "max_functions.h"

TEST(MaxValueTest, Integers) {
    EXPECT_EQ(max_value(1, 2), 2);
    EXPECT_EQ(max_value(5, 3), 5);
}

TEST(MaxValueTest, Doubles) {
    EXPECT_DOUBLE_EQ(max_value(1.5, 2.5), 2.5);
    EXPECT_DOUBLE_EQ(max_value(-1.0, -2.0), -1.0);
}

TEST(MaxValueTest, Strings) {
    EXPECT_EQ(max_value(std::string("apple"), std::string("banana")), "banana");
    EXPECT_EQ(max_value(std::string("cherry"), std::string("banana")), "cherry");
}