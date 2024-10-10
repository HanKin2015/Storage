#!/bin/bash
#
# 文 件 名: total_files_number.sh
# 文件描述: -exec sh -c '...' sh {}：对于每个找到的文件夹，执行一个子 shell 来统计该文件夹中的文件和子文件夹数量
# 备    注: find 命令的 -name 参数不支持使用管道符 | 进行多个模式的匹配。相反，你可以使用多个 -name 参数结合 -o（逻辑或）来实现
# 作    者: HanKin
# 创建日期: 2024.10.09
# 修改日期：2024.10.09
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

# 定义存储日期格式文件夹的父目录
PARENT_DIR="./"

# 使用 find 命令查找符合日期格式的文件夹，并统计其中的文件和文件夹数量
total_count=$(find "$PARENT_DIR" -type d \( -name '202404*' -o -name '202405*' -o -name '202406*' \) -exec sh -c '
  for dir do
    find "$dir" -mindepth 1 -maxdepth 1 | wc -l
  done
' sh {} + | awk '{s+=$1} END {print s}')

echo "Total number of files and directories: $total_count"
