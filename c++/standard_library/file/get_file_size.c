/*******************************************************************************
* 文 件 名: get_file_size.c
* 文件描述: 获取文件大小
* 作    者: HanKin
* 备    注: https://www.python100.com/html/534ZMBM0V73H.html
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void stat_example()
{
    struct stat fileStat;
    stat("example.txt", &fileStat);
    printf("File Size: %ld bytes\n", fileStat.st_size);
    return;
}

int fstat_example()
{
    // 这种方式会有编译警告，但是结果没有问题
    //FILE* file = fopen("example.txt", "rb");
    //if (file == NULL) {
    //    printf("File not found.\n");
    //    return 1;
    //}
    int file = open("example.txt", O_RDONLY);
    if (file == -1) {
        printf("File open failed.\n");
        return 1;
    }
    
    struct stat fileStat;
    fstat(file, &fileStat);
    printf("File Size: %ld bytes\n", fileStat.st_size);
    return 0;
}

int ftell_example()
{
    FILE* file = fopen("example.txt", "rb");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);   // 将文件指针移动到文件尾部
    long fileSize = ftell(file);
    fclose(file);
    printf("File Size: %ld bytes\n", fileSize);
    return 0;
}

int getc_example()
{
    FILE* file = fopen("example.txt", "rb");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }
    int charCount = 0;
    while (getc(file) != EOF) {
        charCount++;
    }
    fclose(file);
    printf("File Size: %d bytes\n", charCount);
    return 0;
}

int fread_example()
{
    FILE* file = fopen("example.txt", "rb");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }
    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char buffer[fileSize];
    fread(buffer, sizeof(char), fileSize, file);
    fclose(file);
    printf("File Size: %ld bytes\n", fileSize);
    return 0;
}

int main(int argc, char *argv[])
{
    stat_example();
    fstat_example();
    ftell_example();
    getc_example();
    fread_example();
    // 最后使用Windows API获取文件大小GetFileSize()函数
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
File Size: 0 bytes
File not found.
File not found.
File not found.
File not found.

[root@ubuntu0006:~/cmake] #./a.out
File Size: 53 bytes
File Size: 53 bytes
File Size: 53 bytes
File Size: 53 bytes
File Size: 53 bytes
*/