/*******************************************************************************
* 文 件 名: pragma_example2.cpp
* 文件描述: 预处理指令，用于向编译器提供特殊的编译选项或行为控制
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

#pragma warning(disable: 4996)  // 禁用特定警告（如Visual C++中的"函数不安全"警告）
#pragma GCC diagnostic ignored "-Wunused-variable"  // GCC中忽略未使用变量警告
#pragma optimize("O2", on)  // 开启特定优化级别（MSVC）
#pragma GCC push_options    // 保存当前GCC编译选项
#pragma GCC optimize("Ofast")  // 启用最快速度优化
// ... 代码 ...
#pragma GCC pop_options     // 恢复之前的编译选项
#pragma message("编译提示：这是一个自定义警告消息")  // 在编译时输出自定义消息
#pragma STDC FENV_ACCESS ON  // 启用浮点环境访问

int main()
{
    int x = 100;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp
root@hankin:~/opencv# ./a.out 
start main task...
start task...
[hankin] Code took 3000 ms.
*/