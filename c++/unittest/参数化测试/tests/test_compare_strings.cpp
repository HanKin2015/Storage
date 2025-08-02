// tests/test_compare_strings.cpp
#include <gtest/gtest.h>
#include "compare_strings.h"

class StringTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>> {};

TEST_P(StringTest, CompareStrings) {
    std::string a, b;
    bool expected;
    std::tie(a, b, expected) = GetParam();
    EXPECT_EQ(compare_strings(a, b), expected);
}

INSTANTIATE_TEST_SUITE_P(
    CompareTests,
    StringTest,
    ::testing::Values(
        std::make_tuple("hello", "hello", true),
        std::make_tuple("hello", "world", false),
        std::make_tuple("", "", true),
        std::make_tuple("abc", "abcd", false)
    )
);