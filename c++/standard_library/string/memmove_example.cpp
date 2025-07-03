/*******************************************************************************
* 文 件 名: memmove_example.cpp
* 文件描述: memmove 是 C 语言标准库中的一个函数，用于在内存中移动一块内存区域。
*           它的主要特点是能够处理重叠的内存区域，这使得它与 memcpy 函数有所不同，后者在处理重叠区域时可能会导致未定义行为。
* 备    注: 由于需要处理重叠情况，memmove 的性能通常比 memcpy 稍慢
* 作    者: HanKin
* 创建日期: 2025.06.24
* 修改日期：2025.06.24
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "Hello, World!";
    
    // 将 "World" 移动到 "Hello" 的位置
    memmove(str + 7, str + 5, 6); // 6 是要移动的字节数，包括空格和字符
    printf("%s\n", str); // 输出: "Hello, , Worl"

    memmove(str + 7, str + 5, 5); // 5 是要移动的字节数，包括空格和字符
    printf("%s\n", str); // 输出: "Hello, , Wor!"
    return 0;
}
