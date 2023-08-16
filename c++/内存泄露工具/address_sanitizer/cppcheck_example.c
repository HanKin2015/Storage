/**
* 文 件 名: cppcheck_example.c
* 文件描述: cppcheck静态工具使用
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
#include <stdlib.h> // malloc

int main(int argc, char *argv[])
{
    const char *file_path = "log.txt";
    FILE *fp = fopen(file_path, "a+");
    const char *data = "hello world";
    fprintf(fp, "%s\n", data);
    //fclose(fp);
    
    int *p = (int *)malloc(sizeof(int));
    *p = 5;
    printf("%p = %d\n", p, *p);
    //free(p);
    
    int fd = open(file_path, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    printf("fd = %d\n", fd);
    fd = open(file_path, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    printf("fd = %d\n", fd);
    fd = open(file_path, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    printf("fd = %d\n", fd);
    write(fd, data, strlen(data));
    //close(fd);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #cppcheck k.c
Checking k.c...
[k.c:24]: (error) Resource leak: fp
[k.c:24]: (error) Memory leak: p

把代码修改正常后：
[root@ubuntu0006:~/cmake] #cppcheck k.c
Checking k.c...
[root@ubuntu0006:~/cmake] #

增加open函数后，还是无法检测：
[root@ubuntu0006:~/cmake] #cppcheck k.c
Checking k.c...
[k.c:24]: (error) Resource leak: fp
[k.c:24]: (error) Memory leak: p

使用动态工具valgrind也不行：
[root@ubuntu0006:~/cmake] #valgrind --leak-check=full --show-reachable=yes --trace-children=yes   ./a.out
==8109== Memcheck, a memory error detector
==8109== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==8109== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==8109== Command: ./a.out
==8109==
0x52052f0 = 5
==8109==
==8109== HEAP SUMMARY:
==8109==     in use at exit: 0 bytes in 0 blocks
==8109==   total heap usage: 4 allocs, 4 frees, 5,676 bytes allocated
==8109==
==8109== All heap blocks were freed -- no leaks are possible
==8109==
==8109== For counts of detected and suppressed errors, rerun with: -v
==8109== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
