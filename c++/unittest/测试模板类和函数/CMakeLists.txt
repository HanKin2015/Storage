cmake_minimum_required(VERSION 3.28)

project(MaxExample VERSION 0.1 LANGUAGES CXX)

include_directories(include)
#add_library(max src/max_functions.h)
add_executable(max_example src/main.cpp)
#target_link_libraries(max_example max)

option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()