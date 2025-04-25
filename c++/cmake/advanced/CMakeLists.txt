# Cmake最低版本要求
cmake_minimum_required(VERSION 3.0.2)
 
# 项目名称（没有太大作用）
project(CMakeExp)

# 当前操作系统类型
message(STATUS "UNIX defined: " ${UNIX})
message(STATUS "APPLE defined: " ${APPLE})
message(STATUS "WIN32 defined: " ${WIN32})
message(STATUS "ANDROID defined: " ${ANDROID})

# 二进制文件名称为MyProject
add_executable(MyProject cmake_example.cpp)
