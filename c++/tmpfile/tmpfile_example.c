/**
* 文 件 名: tmpfile_example.c
* 文件描述: 学习tmpfile函数
* 作    者: HanKin
* 创建日期: 2024.09.24
* 修改日期：2024.09.24
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdio.h>

int main() {
    FILE *fp = tmpfile();
    if (fp == NULL) {
        perror("tmpfile");
        return 1;
    }
    fprintf(fp, "This is a temporary file.\n");
    rewind(fp);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }
    fclose(fp);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
This is a temporary file.
*/