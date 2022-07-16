/**
* 文 件 名: debug.c
* 文件描述: 简易的日志调试使用
* 作    者: HanKin
* 创建日期: 2022.06.18
* 修改日期：2022.06.18
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/
 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#define LOG(format, ...) printf_log(format, ## __VA_ARGS__)
void printf_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char logmsg[4096];
    vsnprintf(logmsg, sizeof(logmsg), format, args);

    FILE *fp = fopen("/home/debug.log", "a");
    if (!fp) {
        fprintf(stderr, "open log file</home/debug.log> failed, errno %s(%d)\n",
        strerror(errno), errno);
        return;
    }
    fprintf(fp, "%s\n", logmsg);
    fclose(fp);
    fp = NULL;

    va_end(args);
    return;
}

int main(int argc, char *argv[])
{
    const char *str = "hello world";
    int year = 2022;
    LOG("%s %d", str, year);
    return 0;
}