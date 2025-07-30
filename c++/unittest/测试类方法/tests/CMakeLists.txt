cmake_minimum_required(VERSION 3.28)

project(TestCalculator VERSION 0.1 LANGUAGES CXX)

# 添加GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 添加二进制文件
add_executable(test_calculator test_calculator.cpp)
# GTEST_LIBRARIES和GTEST_MAIN_LIBRARIES
target_link_libraries(test_calculator PRIVATE calculator ${GTEST_BOTH_LIBRARIES} pthread)

# 自动发现测试用例
gtest_discover_tests(test_calculator)

message(STATUS "GTEST_INCLUDE_DIRS=" ${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_FOUND=" ${GTEST_FOUND})
message(STATUS "GTEST_LIBRARIES=" ${GTEST_LIBRARIES})
message(STATUS "GTEST_MAIN_LIBRARIES=" ${GTEST_MAIN_LIBRARIES})
message(STATUS "GTEST_BOTH_LIBRARIES=" ${GTEST_BOTH_LIBRARIES})