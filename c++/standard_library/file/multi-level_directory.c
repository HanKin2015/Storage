/*******************************************************************************
* 文 件 名: multi-level_directory.c
* 文件描述: 创建多级目录
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.04.01
* 修改日期：2024.04.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int make_dir(const char *path)
{
    struct stat info;
    //if (strcmp(path, ".") == 0) {
    //    return 0;
    //}
    if (stat(path, &info) != 0) {
        // 目录不存在，创建目录
        if (mkdir(path, 0777) != 0) {
            return -1;
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        // 不是目录
        return -1;
    }
    return 0;
}

int make_dirs(const char *path)
{
    const char *sep = "/";
    char *token = strtok((char *)path, sep);
    char current_path[256] = "";
    strcat(current_path, token);
    while (token != NULL) {
        if (make_dir(current_path) != 0) {
            return -1;
        }
        token = strtok(NULL, sep);
        if (token != NULL) {
            strcat(current_path, sep);
            strcat(current_path, token);
        }
    }
    return 0;
}

int main()
{
    const char path[] = "./test1/test2/test3";
    if (make_dirs(path) == 0) {
        printf("目录创建成功\n");
    } else {
        printf("目录创建失败\n");
    }
    return 0;
}

