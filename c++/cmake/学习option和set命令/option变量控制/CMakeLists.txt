#Cmake 最低版本要求
cmake_minimum_required(VERSION 3.5.1)
 
#项目名称
project(CMakeExp)
 
message(STATUS "学习option和set命令") 
#set(TEST_OPTION OFF)
 
option(CLIENT_TYPE_MAC "client type is mac" OFF)

if (DEFINED CLIENT_TYPE_MAC)
    message(STATUS "CLIENT_TYPE_MAC defined: " ${CLIENT_TYPE_MAC})
else ()     
    message(STATUS "CLIENT_TYPE_MAC un-defined: " ${CLIENT_TYPE_MAC})
endif()

if (CLIENT_TYPE_MAC)
    message(STATUS "CLIENT_TYPE_MAC ON.")
    # 这样定义后c/cpp文件可以调用
    add_definitions(-DCLIENT_TYPE_UNIX)
else ()     
    message(STATUS "CLIENT_TYPE_MAC OFF.")
endif()


