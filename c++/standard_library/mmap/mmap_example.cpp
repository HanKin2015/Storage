#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *mapped_mem;
    struct stat file_stat;

    // 1. 打开文件
    fd = open("test.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    // 2. 获取文件大小（若文件为空，需先扩展大小）
    if (fstat(fd, &file_stat) == -1) {
        perror("fstat failed");
        close(fd);
        exit(1);
    }
    if (file_stat.st_size == 0) {
        ftruncate(fd, 1024); // 扩展文件到1024字节
        file_stat.st_size = 1024;
    }

    // 3. 建立内存映射
    mapped_mem = mmap(
        NULL,               // 让系统自动分配映射地址
        file_stat.st_size,  // 映射长度（文件大小）
        PROT_READ | PROT_WRITE, // 读写权限
        MAP_SHARED,         // 共享映射（修改会同步到文件）
        fd,                 // 目标文件描述符
        0                   // 映射偏移量（从文件开头）
    );
    if (mapped_mem == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        exit(1);
    }

    // 4. 像操作内存一样读写文件
    sprintf(mapped_mem, "Hello, mmap!"); // 写入数据
    printf("Read from mapped memory: %s\n", mapped_mem);

    // 5. 主动同步（可选，确保数据写入磁盘）
    msync(mapped_mem, file_stat.st_size, MS_SYNC);

    // 6. 解除映射并关闭文件
    munmap(mapped_mem, file_stat.st_size);
    close(fd);

    return 0;
}