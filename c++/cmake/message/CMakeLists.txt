#######################################################
# 文 件 名: CMakeLists.txt
# 文件描述: message打印日志和大小写不敏感
# 备    注: 
# 作    者: HanKin
# 创建日期: 2025.08.13
# 修改日期：2025.08.13
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#######################################################
cmake_minimum_required(VERSION 3.16)
project(message)

set(MY_VAR "hello world")
message(STATUS "VALUE1=" ${MY_VAR}) # 可能被解析为多个参数，输出异常
message(STATUS "VALUE2=${MY_VAR}")  # 正确输出 "VALUE=hello world"
MESSage(STATUS "VALUE3=${MY_VAR}")  # 对大小写不敏感