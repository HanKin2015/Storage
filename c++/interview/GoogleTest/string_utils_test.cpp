#include <gtest/gtest.h>
#include "string_utils.h"

using namespace StringUtils;

// 测试 StringUtils::split 函数
TEST(StringUtilsTest, SplitEmptyString) {
    std::string input = "";
    char delimiter = ',';
    auto result = split(input, delimiter);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "");
}

TEST(StringUtilsTest, SplitSingleToken) {
    std::string input = "hello";
    char delimiter = ',';
    auto result = split(input, delimiter);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "hello");
}

TEST(StringUtilsTest, SplitMultipleTokens) {
    std::string input = "apple,banana,orange";
    char delimiter = ',';
    auto result = split(input, delimiter);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "apple");
    EXPECT_EQ(result[1], "banana");
    EXPECT_EQ(result[2], "orange");
}

// 测试 StringUtils::trim 函数
TEST(StringUtilsTest, TrimNoSpaces) {
    std::string input = "hello";
    auto result = trim(input);
    
    EXPECT_EQ(result, "hello");
}

TEST(StringUtilsTest, TrimLeadingSpaces) {
    std::string input = "   world";
    auto result = trim(input);
    
    EXPECT_EQ(result, "world");
}

TEST(StringUtilsTest, TrimTrailingSpaces) {
    std::string input = "hello   ";
    auto result = trim(input);
    
    EXPECT_EQ(result, "hello");
}

TEST(StringUtilsTest, TrimBothEnds) {
    std::string input = "   hello world   ";
    auto result = trim(input);
    
    EXPECT_EQ(result, "hello world");
}

// 测试 StringUtils::reverse 函数
TEST(StringUtilsTest, ReverseEmptyString) {
    std::string input = "";
    auto result = reverse(input);
    
    EXPECT_EQ(result, "");
}

TEST(StringUtilsTest, ReverseSingleCharacter) {
    std::string input = "a";
    auto result = reverse(input);
    
    EXPECT_EQ(result, "a");
}

TEST(StringUtilsTest, ReverseNormalString) {
    std::string input = "hello";
    auto result = reverse(input);
    
    EXPECT_EQ(result, "olleh");
}

// 参数化测试示例
struct ReverseParamTest : public testing::TestWithParam<std::pair<std::string, std::string>> {
    // 可以添加共享的设置和清理代码
};

TEST_P(ReverseParamTest, ReverseWithParams) {
    auto params = GetParam();
    std::string input = params.first;
    std::string expected = params.second;
    
    EXPECT_EQ(reverse(input), expected);
}

INSTANTIATE_TEST_CASE_P(
    StringReverseTests,
    ReverseParamTest,
    testing::Values(
        std::make_pair("", ""),
        std::make_pair("a", "a"),
        std::make_pair("ab", "ba"),
        std::make_pair("abc", "cba"),
        std::make_pair("12345", "54321")
    )
);

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}    