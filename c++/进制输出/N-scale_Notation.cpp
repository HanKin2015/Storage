/**
* 文 件 名: N-scale_Notation.cpp
* 文件描述: 二进制、八进制和十六进制表示
* 作    者: HanKin
* 创建日期: 2022.10.21
* 修改日期：2022.10.21
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <cstdio>

// 二进制

// 八进制由 0~7 八个数字组成，使用时必须以0开头（注意是数字 0，不是字母 o）
static void octal_number_system()
{
    // 合法的八进制数
    int a = 015;        // 换算成十进制为 13
    int b = -0101;      // 换算成十进制为 -65
    int c = 0177777;    // 换算成十进制为 65535
    printf("%d %d %d\n", a, b, c);

    // 非法的八进制
    int m = 256;    // 无前缀 0，相当于十进制
    int n = 03A2;   // A不是有效的八进制数字
    printf("%d %d\n", m, n);
    return;
}

// 十六进制由数字 0~9、字母 A~F 或 a~f（不区分大小写）组成，使用时必须以0x或0X（不区分大小写）开头


int main(int argc, char *argv[])
{
    octal_number_system()
    return 0;
}
