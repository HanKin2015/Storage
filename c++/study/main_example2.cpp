/*******************************************************************************
* 文 件 名: main_example2.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.06
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
void my_main()
{
    // 直接用系统调用写终端（不依赖标准库）
    const char* msg = "Hello from my_main!\n";
    // 调用write系统调用（x86_64汇编）
    asm volatile (
        "mov $1, %%rax\n"   // sys_write
        "mov $1, %%rdi\n"   // fd=1（stdout）
        "mov %0, %%rsi\n"   // 字符串地址
        "mov %1, %%rdx\n"   // 长度
        "syscall"
        : : "r"(msg), "r"(21) : "rax", "rdi", "rsi", "rdx"
    );
    // 调用exit系统调用退出
    asm volatile (
        "mov $60, %%rax\n"  // sys_exit
        "mov $0, %%rdi\n"   // status=0
        "syscall"
    );
}