/**
* 文 件 名: snprintf_example.cpp
* 文件描述: 返回值判断
* 作    者: HanKin
* 创建日期: 2022.06.30
* 修改日期：2022.06.30
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>

void test()
{
    char a[16];
    size_t i;

    i = snprintf(a, 13, "%012d", 12345);  // 第 1 种情况
    printf("i = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 000000012345

    i = snprintf(a, 9, "%012d", 12345);   // 第 2 种情况
    printf("i = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 00000001
    return;
}

int main(int argc, char *argv[])
{
    // (1)如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，并给其后添加一个字符串结束符('\0')
    // (2) 如果格式化后的字符串长度 >= size，则只将其中的(size-1)个字符复制到str中，并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度
    const int BUFF_SIZE = 5;
    char json[BUFF_SIZE] = { 0 };
    char str[] = "12345678";
    int ret = snprintf(json, BUFF_SIZE, "%s", str);
    printf("ret: %d, json: %s\n", ret, json);
    
    test();
    return 0;
}