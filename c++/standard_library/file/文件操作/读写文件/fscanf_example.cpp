/**
* 文 件 名: fscanf_example.cpp
* 文件描述: 学习fscanf函数
* 作    者: HanKin
* 创建日期: 2022.08.11
* 修改日期：2022.08.11
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
a.txt:
1 2 3 0.4
2 3 4 0.5

output:
1 2 3 0.400000
2 3 4 0.500000
*/
static void test1(const char *file_path)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    
    FILE* fp = fopen(file_path, "r");
    int a, b, c;
    float d;
    while (fscanf(fp, "%d %d %d %f", &a, &b, &c, &d) == 4) {
        printf("%d %d %d %f\n", a, b, c, d);
    }
    return;
}

/*
b.txt:
张三,2022-3-12 12:00,睡觉
李四,2022-3-13:13:00,休息

output:
张三 2022-3-12 12:00 睡觉
李四 2022-3-13:13:00 休息

[^ ]表示匹配到的条件。例如
[^,]表示匹配到的逗号,前面的字符串
[^a-z]表示匹配到的a-z中的任意字符
*/
static void test2(const char *file_path)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    
    FILE *fp = fopen(file_path, "r");
    char name[20] = { 0 };
    char date_time[20] = { 0 };
    char action[20] = { 0 };
    while (fscanf(fp, "%19[^,],%19[^,],%s", name, date_time, action) == 3) {
        printf("%s %s %s", name, date_time, action);
    }
    return;
}

int main(int argc, char *argv[])
{
    const char *file_path1 = "./a.txt";
    const char *file_path2 = "./b.txt";
    
    test1(file_path1);
    test2(file_path2);
    return 0;
}
