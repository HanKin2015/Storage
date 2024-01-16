#!/bin/bash
#
# 文 件 名: complex_operation.sh
# 文件描述: 使用双括号 [[ 和 ]] 来进行复杂的条件判断
# 备    注: 使用双括号 [[ 和 ]] 来进行复杂的条件判断
# 作    者: HanKin
# 创建日期: 2024.01.15
# 修改日期：2024.01.15
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

X=1
Y=2
#if [ $X -ne 2 ] || [ $Y -ne 3 -a $X -eq 1 ]; then
#if [[ $X -ne 2 || ( $Y -ne 3 && $X -eq 1 ) ]]; then
if [ $X -ne 2 ] || [[ $Y -ne 3 && $X -eq 1 ]]; then
    echo "yes"
else
    echo "no"
fi
