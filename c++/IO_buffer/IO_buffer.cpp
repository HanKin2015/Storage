/**
* 文 件 名: IO_buffer.cpp
* 文件描述: 自定义IO缓冲区
* 备    注: 不是很理解代码的输出
* 作    者: HanKin
* 创建日期: 2022.12.01
* 修改日期：2022.12.01
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#inlcude <cstdlib>
using namespace std;

void setbuf(FILE *stream, char *buf);                   // 无缓冲区
void setbuffer(FILE *stream, char *buf, size_t size);   // 块缓冲区
void setlinebuf(FILE *stream);                          // 行缓冲区

/*兼容三种缓冲区
_IONBF // 无unbuffered
_IOLBF // 行line buffered
_IOFBF // 块fully buffered
*/
int setvbuf(FILE *stream, char *buf, int mode, size_t size);

int main(int argc, char *argv[])
{
    char buf[BUFSIZ];
    char buf2[BUFSIZ];
    printf("BUFSIZ is %d\n", BUFSIZ);
    setvbuf(stdout, buf, _IOFBF, BUFSIZ);   // 设置块缓冲

    printf("BUFSIZ after setvbuf is %d\n", BUFSIZ);
    setbuffer(stdout, buf2, 10240);         // 设置块缓冲
    printf("hello world\n");

    printf("buf:%s\n\n", buf);
    printf("buf2:%s\n", buf2);
    
    setvbuf(stdout, buf, _IONBF, BUFSIZ);   // 设置无缓冲
    printf("buf:%s\n\n", buf);
    return 0;
}
/*
BUFSIZ is 8192
BUFSIZ after setvbuf is 8192
hello world
buf:8192
Z after setvbuf is

buf2:buf:8192
Z after setvbuf is

buf2:
buf:8192
Z after setvbuf is

*/