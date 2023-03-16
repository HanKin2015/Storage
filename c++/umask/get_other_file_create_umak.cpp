/**
* 文 件 名: get_other_file_create_umask.cpp
* 文件描述: 获取其他文件的文件创建掩码
* 作    者: HanKin
* 创建日期: 2023.06.30
* 修改日期：2023.06.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <sys/stat.h>
#include <stdio.h>

// 当前进程的文件创建掩码
int get_current_progress_file_create_umask()
{
    mode_t old_mask = umask(0); // 获取当前进程的文件创建掩码
    printf("umask: %o\n", old_mask); // 打印当前进程的文件创建掩码
    umask(old_mask); // 恢复之前的文件创建掩码
    return 0;
}

// 其他文件的文件创建掩码
int get_other_file_create_umask()
{
    struct stat st;
    if (stat("test.txt", &st) == -1) {
        perror("stat");
        return 1;
    }
    printf("file mode: %o\n", st.st_mode & 0777); // 打印文件权限信息
    printf("file umask: %o\n", ~st.st_mode & 0777); // 打印文件创建掩码
    return 0;
}

int main()
{
    get_current_progress_file_create_umask();
    get_other_file_create_umask();
    return 0;
}