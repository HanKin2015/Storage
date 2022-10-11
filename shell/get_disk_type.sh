#!/bin/bash
#
# 文 件 名: get_disk_type.sh
# 文件描述: 获取磁盘类型，固态或机械
# 作    者: HanKin
# 创建日期: 2022.10.11
# 修改日期：2022.10.11
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

file_system=`df -h | head | awk '{if ($NF == "/") {print $1}}'` # /dev/sda3
disk_name=`echo ${file_system} | awk -F'/' '{print $NF}'`       # sda3
dir_name=`echo ${disk_name} | sed 's/[0-9]*$//'`                # sda
disk_type=`cat /sys/block/${dir_name}/queue/rotational`         # 0 or 1
echo ${disk_type}
if [ ${disk_type} -eq 0 ]; then
    echo '这是一个固态硬盘'
else
    echo '这是一个机械硬盘'
fi