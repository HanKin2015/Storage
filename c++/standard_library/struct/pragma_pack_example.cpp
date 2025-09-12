/*******************************************************************************
* 文 件 名: pragma_pack_example.cpp
* 文件描述: 
* 备    注: #pragma pack(n) 是 “上限约束” 而非 “强制值”，结构体大小由成员自然对齐值、成员顺序、pack 上限共同决定。
* 作    者: HanKin
* 创建日期: 2025.09.10
* 修改日期：2025.09.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

struct O { char c; int i; };  // 按 4 字节对齐

#pragma pack(16)          // 设置当前对齐值为 16（仅限制 “对齐值不能超过 16”，但不会强制成员按 16 字节对齐，除非成员自身的自然对齐值 ≥16）
struct OO { char c; int i; };  // 按 4 字节对齐

#pragma pack(2)          // 设置当前对齐值为 2（假设默认是 4）
struct A { char c; int i; };  // 按 2 字节对齐

#pragma pack(push)       // 将当前对齐值（2）压栈保存，当前对齐值仍为 2
#pragma pack(4)          // 修改当前对齐值为 4
struct B { char c; int i; };  // 按 4 字节对齐

#pragma pack(pop)        // 从栈中弹出之前保存的 2，恢复对齐值为 2
struct C { char c; int i; };  // 恢复按 2 字节对齐

#pragma pack(2)          // 设置当前对齐值为 2
struct AA { char c; int i; };

#pragma pack(push, 2)    // 保存当前对齐值（2）到栈，同时设置新对齐值为 2
struct BB { char c; int i; };  // 按 2 字节对齐

#pragma pack(pop)        // 弹出 2 并恢复，当前对齐值为 2
struct CC { char c; int i; };  // 按 2 字节对齐

// warning: ‘#pragma pack (pop)’ encountered without matching ‘#pragma pack (push)’ [-Wpragmas]
#pragma pack(pop)
struct CCC { char c; int i; };

// warning: malformed ‘#pragma pack(pop[, id])’ - ignored [-Wpragmas]
// 此语法GCC不支持，非标准用法
#pragma pack(pop, 4)
struct CCCC { char c; int i; };

int main()
{
    std::cout << sizeof(short) << ' ' << sizeof(int) << ' ' << sizeof(O) << ' ' << sizeof(OO) << std::endl;
    std::cout << sizeof(A) << ' ' << sizeof(B) << ' ' << sizeof(C) << std::endl;
    std::cout << sizeof(AA) << ' ' << sizeof(BB) << ' ' << sizeof(CC) << std::endl;
    // 多弹出一次有问题吗
    std::cout << sizeof(CCC) << ' ' << sizeof(CCCC) << std::endl;
    return 0;
}