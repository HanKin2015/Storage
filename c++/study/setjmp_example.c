/*******************************************************************************
* 文 件 名: setjmp_example.c
* 文件描述: setjmp 和 longjmp 是 C 语言中的一对函数，用于实现非局部跳转（non-local jump）。
* 备    注: 它们通常用于错误处理、状态恢复或在复杂的控制流中返回到某个特定的执行点。
* 作    者: HanKin
* 创建日期: 2025.04.16
* 修改日期：2025.04.16
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void throw_error(int code)
{
    printf("In throw_error, about to longjmp.\n");
    longjmp(env, code); // 跳回到 setjmp 的位置
}

int main()
{
    // setjmp 用于保存当前的执行环境（包括栈指针、程序计数器等），并将其存储在 jmp_buf 类型的变量中
    if (setjmp(env) == 0) {
        // 第一次调用 setjmp，它返回 0，如果是通过 longjmp 返回，它返回 longjmp 中的第二个参数
        printf("Calling throw_error.\n");
        throw_error(1); // 模拟抛出异常
    } else {
        // 这里是从 longjmp 返回的地方，错误处理代码
        printf("Returned to main from longjmp.\n");
    }
    return 0;
}
/*
[root@ubuntu0006:/media/sangfor/vdb] #./a.out 
Calling throw_error.
In throw_error, about to longjmp.
Returned to main from longjmp.
*/