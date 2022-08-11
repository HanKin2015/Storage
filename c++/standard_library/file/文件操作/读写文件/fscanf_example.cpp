/**
* 文 件 名: fscanf_example.cpp
* 文件描述: 学习fscanf函数
* 作    者: HanKin
* 创建日期: 2022.08.11
* 修改日期：2022.08.11
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

/*
a.txt:
1 2 3 0.4
2 3 4 0.5
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void test1(const char *file_path)
{
    assert(file_path);
    
    FILE* fp = fopen(file_path, "r");
    int a, b, c;
    float d;
    while (fscanf(file, "%d %d %d %f", &a, &b, &c, &d) == 4) {
        printf("%d %d %d %f\n", a, b, c, d);
    }
    return;
}

int main(int argc, char *argv[])
{
    const char *file_path1 = "./a.txt";
    const char *file_path1 = "./a.txt";
    
    test1(file_path1);
    return 0;
}
/*
output:
1 2 3 0.400000
2 3 4 0.500000
*/