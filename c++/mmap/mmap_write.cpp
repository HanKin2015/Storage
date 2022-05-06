/*
mmap()系统调用使得进程之间通过映射同一个普通文件实现共享内存。普通文件被映射到进程地址空间后，进程可以像访问普通内存一样对文件进行访问，不必再调用read()，write（）等操作。
注：实际上，mmap()系统调用并不是完全为了用于共享内存而设计的。它本身提供了不同于一般对普通文件的访问方式，进程可以像读写内存一样对普通文件的操作。而Posix或System V的共享内存IPC则纯粹用于共享目的，当然mmap()实现共享内存也是其主要应用之一。

给出两个进程通过映射普通文件实现共享内存通信，包含两个子程序：mmap_write.cpp及mmap_read.cpp。编译两个程序，可执行文件分别为 mmap_write及mmap_read。两个程序通过命令行参数指定同一个文件来实现共享内存方式的进程间通信。

本文件试图打开命令行参数指定的一个普通文件，把该文件映射到进程的地址空间，并对映射后的地址空间进行写操作。
*/

#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>

typedef struct {
    char name[4];
    int age;
} people;

int main(int argc, char **argv)
{
    int fd, i;
    people *p_map;
    char temp;
    
    // 1.打开一个普通文件，不存在则创建
    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 00777);
    
    // 2.把文件的长度设置为5个people结构大小
    lseek(fd, sizeof(people) * 5 - 1, SEEK_SET);
    write(fd, "", 1);

    // 3.map a normal file as shared mem
    p_map = (people *)mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p_map == (void *) -1) {
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        return -1;
    }
    close(fd);
    
    // 4.写入10条数据
    temp = 'a';
    for(i = 0; i < 10; i++) {
        temp += 1;
        (*(p_map + i)).name[1] = '\0';
        memcpy((*(p_map + i)).name, &temp, 1);
        (*(p_map + i)).age = 20 + i;
    }
    printf("initializeover\n");
    
    // 5.这里睡眠时间是有意义的，mmap_read.cpp在睡眠时间结束前能读取10条数据，结束后只能读取5条
    sleep(12);
    
    // 6.释放
    munmap(p_map, sizeof(people) * 10);
    printf("umapok\n");
    return 0;
}