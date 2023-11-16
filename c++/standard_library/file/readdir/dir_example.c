/**
* 文 件 名: dir_example.c
* 文件描述: 学习目录相关函数
* 作    者: HanKin
* 备    注: 
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(void) 
{
    struct dirent *dir = NULL;
    DIR *dirp = NULL;
    int ret = 0;

    /* 打开目录 */
    dirp = opendir("./hj");
    if (NULL == dirp) {
        perror("opendir error");
        exit(-1);
    }

    /* 循环读取目录流中的所有目录条目 */
    errno = 0;
    while (NULL != (dir = readdir(dirp))) {
        // 注意linux下要排除.和..目录
        if (0 == strcmp(dir->d_name, ".")) {
            printf("filter %s %ld\n", dir->d_name, dir->d_ino);
            continue;
        }
        if (0 == strcmp(dir->d_name, "..")) {
            printf("filter %s %ld\n", dir->d_name, dir->d_ino);
            continue;
        }
        printf("%s %ld\n", dir->d_name, dir->d_ino);
    }
    if (0 != errno) {
        perror("readdir error");
        ret = -1;
        goto err;
    } else {
        printf("End of directory!\n");
    }

err:
    closedir(dirp);
    exit(ret);
}
/*
[root@ubuntu0006:~/cmake] #./a.out
main.cpp 2622024
filter .. 2621992
configure.ac 2622052
Makefile.am 2622043
autom4te.cache 2622027
filter . 2622016
aclocal.m4 2622032
End of directory!
*/