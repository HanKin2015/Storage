cmake_minimum_required(VERSION 3.5)

# 添加 CTest 模块
include(CTest)

# 添加编译选项
add_compile_options(-g -O0 --coverage)

# 添加测试目标
add_executable(mytest test/test.cpp)
target_link_libraries(mytest gcov)

# 添加测试
add_test(NAME mytest COMMAND mytest)

# 生成代码覆盖率报告
add_custom_target(coverage
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o coverage.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report"
)
