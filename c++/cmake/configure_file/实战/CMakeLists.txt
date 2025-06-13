cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 客户端类型识别 (同时配置客户端类型宏)
set(CLIENT_TYPE_LINUX FALSE)
set(CLIENT_TYPE_WIN FALSE)
set(CLIENT_TYPE_MAC FALSE)

if (UNIX AND NOT APPLE)
    message(STATUS "Detect Client Type <Linux>")
    set(CLIENT_TYPE_LINUX TRUE)
elseif (WIN32)
    message(STATUS "Detect Client Type <Windows>")
    set(CLIENT_TYPE_WIN TRUE)
elseif (APPLE)
    message(STATUS "Detect Client Type <Mac>")
    set(CLIENT_TYPE_MAC TRUE)
else ()
    message(FATAL_ERROR "unknown platform !!!")
endif()

# 被存储在 CMake 的缓存中。这使得它可以在命令行中通过 -D 选项进行设置，并且在 CMake GUI 中也可以看到和修改。
# 缓存变量的值在 CMake 配置过程中是持久的，允许你在不同的 CMake 运行之间保留设置
# 错误的用法 set(CLIENT_TYPE "")
set(CLIENT_TYPE "" CACHE STRING "Type of client")
if (CLIENT_TYPE STREQUAL "mac")
    message(STATUS "Client Type <Mac>")
    set(CLIENT_TYPE_MAC TRUE)
else ()
    message(FATAL_ERROR "unknown client type ${CLIENT_TYPE} !!!")
endif()

include(configure.cmake)

