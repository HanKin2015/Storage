cmake_minimum_required(VERSION 3.10)
project(StringUtilsTest)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 添加GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# 对于Windows系统: 设置gtest_force_shared_crt为ON
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 添加可执行文件
add_executable(string_utils_test 
    string_utils.h 
    string_utils.cpp 
    string_utils_test.cpp
)

# 链接GoogleTest库
target_link_libraries(string_utils_test 
    gtest 
    gtest_main
)

# 添加测试
enable_testing()
add_test(NAME string_utils_test COMMAND string_utils_test)    