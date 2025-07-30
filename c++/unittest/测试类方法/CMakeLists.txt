cmake_minimum_required(VERSION 3.28)

project(CalculatorExample VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定全局输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)

add_library(calculator STATIC src/calculator.cpp)
add_executable(calculator_example src/main.cpp)
target_link_libraries(calculator_example calculator)

# 添加测试子项目
option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

message(STATUS "PROJECT_BINARY_DIR=" ${PROJECT_BINARY_DIR})