/*******************************************************************************
* 文 件 名: strchr_example.cpp
* 文件描述: 学习const
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.12
* 修改日期：2025.05.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <list>
#include <cstring>
#include <cstdio>

int main()
{
    // char* str = "1234:4567"; 这里 str 指向一个字符串字面量，字符串字面量在 C++ 中是不可修改的。
    // 尝试修改它（如 *split_ptr = '\0';）会导致未定义行为，通常会导致程序崩溃或其他错误
    char str[] = "1234:4567";
    char *split_ptr = strchr(str, ':');
    if(split_ptr != NULL) {
        *split_ptr = '\0';  // 因为这里替换了结束符
    } else {//illegal vid:pid
        printf("error\n");
    }
    printf("%s %s\n", str, split_ptr+1);
    return 0;
}