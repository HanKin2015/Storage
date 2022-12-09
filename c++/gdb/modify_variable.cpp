/**
* 文 件 名: modify_variable.cpp
* 文件描述: 修改变量
* 作    者: HanKin
* 创建日期: 2022.12.07
* 修改日期：2022.12.07
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <cassert>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
using namespace std;

#define LOG_TIGGER "./debug"

/*
fopen函数用来打开一个文件，其调用的一般形式为：文件指针名=fopen(文件名,使用文件方式);其中，“文件指针名”必须是被说明为FILE 类型的指针变量；“文件名”是被打开文件的文件名；“使用文件方式”是指文件的类型和操作要求。“文件名”是字符串常量或字符串数组。文件使用方式 意义“rt” 只读打开一个文本文件，只允许读数据“wt” 只写打开或建立一个文本文件，只允许写数据“at” 追加打开一个文本文件，并在文件末尾写数据“rb” 只读打开一个二进制文件，只允许读数据“wb” 只写打开或建立一个二进制文件，只允许写数据“ab” 追加打开一个二进制文件，并在文件末尾写数据“rt+” 读写打开一个文本文件，允许读和写“wt+” 读写打开或建立一个文本文件，允许读写“at+” 读写打开一个文本文件，允许读，或在文件末追加数据“rb+” 读写打开一个二进制文件，允许读和写“wb+” 读写打开或建立一个二进制文件，允许读和写“ab+” 读写打开一个二进制文件，允许读，或在文件末追加数据
*/

static FILE *g_log_fp = NULL;
#define LOG_TIME_BUF 128
#define LOG_TIME_FMT "%F %T"
void camera_log(const char *fmt, ...)
{

    char buf[LOG_TIME_BUF] = {0,};
    time_t cur;
    
    va_list ap;
    va_start(ap, fmt);

    time(&cur);
    
    strftime(buf, LOG_TIME_BUF, LOG_TIME_FMT, localtime(&cur));
    
    fprintf(g_log_fp, "%s ", buf);
    vfprintf(g_log_fp, fmt, ap);
    va_end(ap);
    
    fflush(g_log_fp);
    return;
};

int main(int argc, char *argv[])
{
    // 每次程序打开其标准流的值都不相同，并不需要这样手动打印，只需要在gdb中打印即可print stderr
    printf("stdin %p, stdout %p, stderr %p\n", stdin, stdout, stderr);
    const char *log_file_path = "./hj.log";
    if (0 == access(LOG_TIGGER, F_OK)) {
        printf("LOG_TIGGER file is exist!\n");
        g_log_fp = fopen(log_file_path, "w+t");
        assert(g_log_fp);
    } else {
        printf("LOG_TIGGER file is not exist!\n");
    }
    
    int index = 0;
    while (true) {
        if (g_log_fp) {
            camera_log("index = %d\n", index++);
        } else {
            printf("g_log_fp is NULL, index = %d\n", index);
        }
        sleep(2);
    }
    return 0;
}
