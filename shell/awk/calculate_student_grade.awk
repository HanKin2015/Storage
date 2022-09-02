#!/bin/bash -f
#
# 文 件 名: calculate_student_grade.awk
# 文件描述: 学习awk脚本 统计学生成绩
# 备    注: 还是和shell脚本有所区别
# 作    者: HanKin
# 创建日期: 2022.08.25
# 修改日期：2022.08.25
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

# 当前目录创建一个文件（学生成绩表score.txt）

# 运行前
BEGIN {
    math     = 0
    english  = 0
    computer = 0

    # 翻译过来就是姓名 学号 数学 英语 计算机 统计
    printf "NAME NO MATH ENGLISH COMPUTER TOTAL\n"
    printf "-----------------------------------\n"
}

# 运行中
{
    math     += $3
    english  += $4
    computer += $5
    printf "%-6s %-6s %4d %8d %8d %8d\n", $1, $2, $3, $4, $5, $3+$4+$5
}

# 运行后
END {
    printf "------------------------------------\n"
    printf " TOTAL:%10d %8d %8d \n", math, english, computer
    printf "AVERAGE:%10.2f %8.2f %8.2f\n", math/NR, english/NR, computer/NR
}