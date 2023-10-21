/*******************************************************************************
* 文 件 名: stat_example.c
* 文件描述: struct stat结构体
* 备    注: 演示如何使用struct stat获取文件的状态信息
* 作    者: HanKin
* 创建日期: 2023.10.20
* 修改日期：2023.10.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat fileStat;
    char filePath[] = "example.txt";

    if (stat(filePath, &fileStat) == 0) {
        printf("File Size: %ld bytes\n", fileStat.st_size);
        printf("File Permissions: %o\n", fileStat.st_mode);
        printf("File Owner UID: %d\n", fileStat.st_uid);
        printf("File Group GID: %d\n", fileStat.st_gid);
        printf("File Last Accessed: %s", ctime(&fileStat.st_atime));
        printf("File Last Modified: %s", ctime(&fileStat.st_mtime));
        printf("File Last Status Change: %s", ctime(&fileStat.st_ctime));
    } else {
        printf("Failed to get file status.\n");
    }

    return 0;
}
