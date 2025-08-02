cmake_minimum_required(VERSION 3.28)

project(TestParam VERSION 0.1 LANGUAGES CXX)

add_executable(test_param test_compare_strings.cpp)
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(test_param PRIVATE ${GTEST_BOTH_LIBRARIES})

gtest_discover_tests(test_param)

