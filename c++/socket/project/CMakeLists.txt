cmake_minimum_required(VERSION 3.10)
project(json_ipc_demo)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 检查操作系统
if(UNIX)
    # Linux需要链接pthread库
    set(EXTRA_LIBS pthread)
endif()

# 进程A
add_executable(process_a process_a.cpp)

# 进程B
add_executable(process_b process_b.cpp)

# 进程C
add_executable(process_c process_c.cpp)
