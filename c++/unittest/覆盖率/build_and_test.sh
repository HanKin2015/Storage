#!/bin/bash
set -e

# 创建并进入构建目录
mkdir -p build
cd build

# 配置CMake
cmake ..

# 构建项目
make

# 运行测试
ctest --output-on-failure