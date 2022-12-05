#!/bin/bash
#
# 文 件 名: calc_files_and_dirs_copy_speed.sh
# 文件描述: 计算文件和文件夹拷贝速度
# 作    者: HanKin
# 创建日期: 2022.11.30
# 修改日期：2022.11.30
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

start=$(date +%s)
ls -l;
pwd;
echo this is a test.
top;
end=$(date +%s)
difference=$(( end - start))
echo Time taken to execute commands is $difference seconds.

date; cp -r /home/admin/1GB.txt .; date