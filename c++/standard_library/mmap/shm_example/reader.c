/**
* 文 件 名: reader.c
* 文件描述: 打开内存共享文件读数据
* 作    者: HanKin
* 创建日期: 2022.10.21
* 修改日期：2022.10.21
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
#define MMAP_DATA_SIZE 1024
 
int main(int argc,char * argv[])
{
    char * data;
    int fd = shm_open("shm-file0001", O_RDWR, 0777);
    if(fd < 0) {
        printf("error open shm object\n");
        return -1;
    }
    
    data = (char*)mmap(NULL, MMAP_DATA_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (!data) {
        printf("mmap failed!\n");
        close(fd);
        return -1;
    }
    printf(data);

    munmap(data,MMAP_DATA_SIZE);
    close(fd);
    getchar();
    return 0;
}