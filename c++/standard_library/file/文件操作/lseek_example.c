/*******************************************************************************
* 文 件 名: lseek_example.c
* 文件描述: 设置文件读写位置的偏移量
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.17
* 修改日期：2025.07.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    const char *file_path = "./char.c";
    int fd = open(file_path, O_RDWR);
    if (fd == -1) {
        perror("open failed\n");
        return -1;
    }
    
    // 将文件指针移动到文件末尾前 10 字节处
    off_t new_pos = lseek(fd, -10, SEEK_END);
    if (new_pos == -1) {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    printf("New position: %ld\n", (long)new_pos);
    close(fd);
    return 0;
}