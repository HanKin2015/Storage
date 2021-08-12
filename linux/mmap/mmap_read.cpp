/*
mmap()系统调用使得进程之间通过映射同一个普通文件实现共享内存。普通文件被映射到进程地址空间后，进程可以像访问普通内存一样对文件进行访问，不必再调用read()，write（）等操作。
注：实际上，mmap()系统调用并不是完全为了用于共享内存而设计的。它本身提供了不同于一般对普通文件的访问方式，进程可以像读写内存一样对普通文件的操作。而Posix或System V的共享内存IPC则纯粹用于共享目的，当然mmap()实现共享内存也是其主要应用之一。

给出两个进程通过映射普通文件实现共享内存通信，包含两个子程序：mmap_write.cpp及mmap_read.cpp。编译两个程序，可执行文件分别为 mmap_write及mmap_read。两个程序通过命令行参数指定同一个文件来实现共享内存方式的进程间通信。

把命令行参数指定的文件映射到进程地址空间，然后对映射后的地址空间执行读操作。

注意：需要传入一个参数为普通文件名
*/

#include<sys/mman.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>

typedef struct {
    char name[4];
    int age;
} people;

int main(int argc, char **argv) //map a normal file as shared mem:
{
    int fd, i;
    people *p_map;
    
    // 1.打开一个普通文件，不存在则创建
    fd = open(argv[1], O_CREAT | O_RDWR, 00777);
    
    // 2.内存映射，注意这里PROT_READ | PROT_WRITE需要和open函数里面参数一致
    p_map = (people *)mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p_map == (void *) -1) {
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        return -1;
    }
    close(fd);
    
    // 3.读取10个数据结果并输出
    for (i = 0; i < 10; i++) {
        printf("name:%s age%d;\n", (*(p_map + i)).name, (*(p_map + i)).age);
    }
    
    // 4.释放
    munmap(p_map, sizeof(people) * 10);
    return 0;
}

