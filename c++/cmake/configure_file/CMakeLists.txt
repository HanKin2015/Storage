cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 定义版本号
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

# 使用 configure_file 生成 config.h
configure_file(config.h.in config.h @ONLY)

