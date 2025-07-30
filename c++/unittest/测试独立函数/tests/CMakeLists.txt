# 查找Google Test框架
find_package(GTest REQUIRED)
include(GoogleTest)

# 添加测试可执行文件
add_executable(my_library_tests
  test_math_functions.cpp
)
target_link_libraries(my_library_tests
  PRIVATE
    my_library
    GTest::gtest
    GTest::gtest_main
)

# 自动发现测试用例
gtest_discover_tests(my_library_tests)