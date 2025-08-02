cmake_minimum_required(VERSION 3.28)

project(ParamExample VERSION 0.1 LANGUAGES CXX)

include_directories(include)
add_executable(param_example src/main.cpp)

option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()