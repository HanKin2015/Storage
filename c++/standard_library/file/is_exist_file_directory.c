/*******************************************************************************
* 文 件 名: is_exist_file_directory.c
* 文件描述: 判断目录或者文件是否存在
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.04.01
* 修改日期：2024.04.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int isDirectoryExists1(const char *path)
{
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1; // 目录存在
    } else {
        return 0; // 目录不存在
    }
}

int isDirectoryExists2(const char *path)
{
    struct stat info;
    if (stat(path, &info) != 0) {
        return 0; // 目录不存在
    } else if (info.st_mode & S_IFDIR) {
        return 1; // 目录存在
    } else {
        return 0; // 路径存在但不是目录
    }
}

// 判断文件或者目录推荐使用这个
int isDirectoryExists3(const char *path)
{
    if (access(path, F_OK) != -1) {
        return 1; // 目录存在
    } else {
        return 0; // 目录不存在
    }
}

int main()
{
    const char *path = "./test1/test2/test3";
    if (isDirectoryExists1(path)) {
        printf("目录存在\n");
    } else {
        printf("目录不存在\n");
    }
    
    if (isDirectoryExists2(path)) {
        printf("目录存在\n");
    } else {
        printf("目录不存在\n");
    }
    
    if (isDirectoryExists3(path)) {
        printf("目录存在\n");
    } else {
        printf("目录不存在\n");
    }
    return 0;
}

