/**
* 文 件 名: clang_example.c
* 文件描述: clang编译器学习
* 作    者: HanKin
* 创建日期: 2023.08.16
* 修改日期：2023.08.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>  // printf

int main(int argc, char *argv[])
{
    const char *file_path = "log.txt";
    FILE *fp = fopen(file_path, "a+");
    
    const char *data = "hello world";
    fprintf(fp, "%s\n", data);
    
    int *p = (int *)malloc(sizeof(int));
    *p = 5;
    printf("%p = %d\n", p, *p);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #scan-build -o memleak gcc k.c
scan-build: Using '/usr/lib/llvm-3.8/bin/clang' for static analysis
k.c:24:5: warning: Potential leak of memory pointed to by 'p'
    return 0;
    ^~~~~~~~
1 warning generated.
scan-build: 1 bug found.
scan-build: Run 'scan-view /root/cmake/memleak/2023-08-16-100332-16430-1' to examine bug reports.
[root@ubuntu0006:~/cmake] #clang --analyze k.c
k.c:24:5: warning: Potential leak of memory pointed to by 'p'
    return 0;
    ^~~~~~~~
1 warning generated.
*/