#!/bin/bash -f
#
# 文 件 名: output_folder.sh
# 文件描述: 输出目录中的文件夹名字
# 备    注: 
# 作    者: HanKin
# 创建日期: 2025.04.25
# 修改日期：2025.04.25
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

# 方法一 
dir=$(ls -l /usr/ |awk '/^d/ {print $NF}')
for i in $dir
do
    echo $i
done

echo
# 方法二
for dir in $(ls /usr/)
do
    #cd /usr/ 
    [ -d /usr/$dir ] && echo $dir
done 

echo

# 方法三
ls -l /usr/ |awk '/^d/ {print $NF}' # 其实同方法一，直接就可以显示不用for循环