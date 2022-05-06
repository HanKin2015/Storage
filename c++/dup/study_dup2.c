#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int i_fd = open("hello_dup2.txt", O_CREAT|O_APPEND|O_RDWR, 0666);

    if(i_fd < 0)
    {
        printf("open error!\n");
        return 0;
    }

    if(write(i_fd, "hello i_fd\n", 11) != 11)
    {
        printf("write dup2 error\n");
    }

    // dup2调用成功则返回新的文件描述符，出错则返回-1
    // 第二个参数是负责给i_fd指定新的文件描述符值，因此成功的结果是返回值一定等于第二个参数
    int i_dup2_fd = dup2(i_fd, STDOUT_FILENO);
    printf("i_dup2_fd = %d, i_fd= %d, STDOUT_FILENO = %d\n", i_dup2_fd, i_fd, STDOUT_FILENO);
    if(i_dup2_fd != STDOUT_FILENO)
    {
        printf("error dup2!\n");
        return 0;
    }
    close(i_fd);

    char c_buf[1024] = {0};
    int i_read_n = 0;
    
    // 无限输入
    while((i_read_n = read(STDIN_FILENO, c_buf, 1024)) != 0)
    {
        // 再次输入
        i_read_n = read(STDIN_FILENO, c_buf + i_read_n, sizeof(c_buf) - 1 - i_read_n);

        if(i_read_n < 0)
        {
            printf("read error!\n");
            return 0;
        }

        // printf默认就是标准输出STDOUT_FILENO=1，现在打开的文件的文件描述符为1，因此会输出到hello_dup2.txt文件中
        printf("%s", c_buf);
        fflush(stdout);
        sleep(1);
        // 这步很重要，否则会出现乱码
        memset(c_buf, 0, sizeof(c_buf));
    }
    close(i_dup2_fd);
    return 0;
}