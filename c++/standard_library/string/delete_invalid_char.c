/**
* 文 件 名: delete_invalid_char.c
* 文件描述: 在原字符串上删除非法字符
* 作    者: HanKin
* 备    注: 
* 创建日期: 2024.08.23
* 修改日期：2024.08.23
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 尝试修改了一个指向字符串常量的指针。在C语言中，字符串常量是不可变的，尝试修改它们会导致未定义的行为，通常会导致段错误。
static void segmentation_fault()
{
    char *name = "\"hejian\"";
    printf("my name is %s\n", name);
    size_t name_len = strlen(name);
    printf("name_len = %ld\n", name_len);
    for (int i = 0; i < name_len; i++) {
        if (name[i] == '\"') {
            name[i] = ' ';
        }
    }
    printf("my name is %s\n", name);
    return;
}

// 可以通过移动字符的方式来实现。
static void test()
{
    char name[] = "\"hejian\"";
    printf("my name is %s\n", name);
    size_t name_len = strlen(name);
    printf("name_len = %ld\n", name_len);
    int shift = 0;  // 用于记录移动的位移
    for (int i = 0; i < name_len; i++) {
        if (name[i] == '"') {
            shift++;  // 每找到一个双引号，需要向前移动的位移加一
        } else {
            name[i - shift] = name[i];  // 移动字符
        }
    }
    name[name_len - shift] = '\0';  // 在最后加上字符串结束符
    printf("my name is %s\n", name);
    return;
}

// 单引号之间没有包含任何字符，这会导致编译错误。
int main(int argc, char *argv[])
{
    char name[] = "\"hejian\"";
    printf("my name is %s\n", name);
    size_t name_len = strlen(name);
    printf("name_len = %ld\n", name_len);
    for (int i = 0; i < name_len; i++) {
        // 两种写法都是对的
        //if (name[i] == '\"') {
        if (name[i] == '"') {
            name[i] = ' ';
        }
    }
    printf("my name is %s\n", name);

    test();
    return 0;
}
