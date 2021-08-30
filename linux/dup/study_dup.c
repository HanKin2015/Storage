#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    // 追加写
    int i_fd = open("hello_dup.txt", O_CREAT|O_APPEND|O_RDWR, 0666);

    if(i_fd < 0)
    {
        printf("open error!\n");
        return 0;
    }

    if(write(i_fd, "hello fd\n", 9) != 9)
    {
        printf("write fd error\n");

    }

    int i_dup_fd = dup(i_fd);
    if(i_dup_fd < 0)
    {
        printf("dup error!\n");
        return 0;
    }

    // 返回描述符的最小值，一般来说i_fd=3，i_dup_fd=4
    printf("i_dup_fd = %d \t i_fd = %d\n", i_dup_fd, i_fd);
    close(i_fd);

    char c_buffer[100];
    int n = 0;
    
    // 无限输入
    if((n = read(STDIN_FILENO, c_buffer, 1000)) != 0)
    {
        // 写入文件描述符
        if(write(i_dup_fd, c_buffer, n) != n)
        {
            printf("write dup fd error!\n");
            return 0;
        }
    }
    return 0;
}