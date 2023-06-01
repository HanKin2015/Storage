# CMake 最低版本要求
cmake_minimum_required(VERSION 3.5.1)

# 项目名称
project(CMakeStudy)

# 宏定义开关选项，布尔类型变量OFF或ON
option(ENABLE_LIBUVC_BACKEND "enable libuvc backend for uvc device operation [default=ON]" ON)
option(BUILD_TESTING "enable test building" ON)
option(BUILD_COVERAGE_REPORT "enable coverage report generation" OFF)

# 定义一个普通类型的变量
set(SRC_FILES main.cpp foo.cpp bar.cpp)

# 用于查找和加载外部依赖库，REQUIRED 表示如果找不到依赖库则停止 CMake 构建过程
find_package(Threads REQUIRED)

# 认识一些变量
message(STATUS "[variable]")
message(STATUS "CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})
message(STATUS "PROJECT_SOURCE_DIR=" ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_NAME=" ${PROJECT_NAME})
message(STATUS "PROCESSOR_COUNT=" ${PROCESSOR_COUNT})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR=" ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CMAKE_BINARY_DIR=" ${CMAKE_BINARY_DIR})
message(STATUS "PROJECT_BINARY_DIR=" ${PROJECT_BINARY_DIR})
message(STATUS "CMAKE_INSTALL_PREFIX=" ${CMAKE_INSTALL_PREFIX})


