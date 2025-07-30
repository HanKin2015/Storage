cmake_minimum_required(VERSION 3.28)

project(TestMax VERSION 0.1 LANGUAGES CXX)

add_executable(test_max test_max_functions.cpp)
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(test_max PRIVATE ${GTEST_BOTH_LIBRARIES})

gtest_discover_tests(test_max)

