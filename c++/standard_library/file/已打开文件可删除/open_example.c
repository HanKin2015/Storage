/**
* 文 件 名: open_example.c
* 文件描述: open函数学习
* 作    者: HanKin
* 创建日期: 2023.08.15
* 修改日期：2023.08.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>  // printf
#include <string.h> // strlen
#include <fcntl.h>  // open
#include <unistd.h> // write close

int main(int argc, char *argv[])
{
    const char *file_path = "log.txt";
    int fd = open(file_path, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    
    const char *data = "hello world";
    write(fd, data, strlen(data));
    close(fd);  // 使用gcc open_example.c -fsanitize=address无法检测出内存泄露
    return 0;
}