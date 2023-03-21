#!/bin/bash
#
# 文 件 名: b_calc_upan_rate.sh
# 文件描述: 使用dd命令计算U盘读写速率
# 备    注: 
# 作    者: HeJian
# 创建日期: 2021.09.14
# 修改日期：2021.09.14
# 
# Copyright (c) 2021 HeJian. All rights reserved.
#

upan_mount_path='/media/sangfor/VMP_5.4.5R1/'
file_name='test.zip'

# 检查参数合法性
if [ $? -eq 1 ]
then
    echo "check argument fail"
    exit 1
fi

# 执行开始时间
date

# 解析用户传递的参数
while getopts "rw" arg
do
    case $arg in
        r)
            dd if=${upan_mount_path}${file_name} of=/home/${file_name} oflag=direct
            exit 0
            ;;
        w)
            dd of=${upan_mount_path}${file_name} if=/home/${file_name} oflag=direct
            exit 0
            ;;
        ?)  #当有不认识的选项的时候arg为?
            echo "unkonw argument"
            exit 1
            ;;
    esac
done

