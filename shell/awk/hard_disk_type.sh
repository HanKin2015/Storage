#!/bin/bash -f
#
# 文 件 名: hard_disk_type.sh
# 文件描述: 硬盘类型判断
# 备    注: 
# 作    者: HanKin
# 创建日期: 2025.04.25
# 修改日期：2025.04.25
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

file_system=`df -h | head | awk '{if ($NF == "/") {print $1}}'`
disk_name=`echo ${file_system} | awk -F'/' '{print $NF}'`
dir_name=`echo ${disk_name} | sed 's/[0-9]*$//'`
disk_type=`cat /sys/block/${dir_name}/queue/rotational`
echo ${disk_type}
if [ ${disk_type} -eq 0 ]; then
    echo '这是一个固态硬盘'
else
    echo '这是一个机械硬盘'
fi