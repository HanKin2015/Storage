/**
* 文 件 名: rm_but_used_memory.c
* 文件描述: 使用rm删除文件成功后依然占用内存
* 作    者: HanKin
* 创建日期: 2023.08.16
* 修改日期：2023.08.16
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
    
    const char *data = "hello world\n";
    for (int i = 0; i < 1000; i++) {
        write(fd, data, strlen(data));
    }
    sleep(600);
    close(fd);  // 使用gcc open_example.c -fsanitize=address无法检测出内存泄露
    return 0;
}