#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <iostream>

/*
 test.c:7:6: warning: conflicting types for built-in function 'log2'
 void log2(uint32_t line, const char* fmt, ...);

 gcc编译有函数重名警告，g++编译无
*/
void hj_log1(uint32_t line, const char* fmt, ...);
void hj_log2(uint32_t line, const char* fmt, ...);  // log2居然是内置函数

void hj_log1(uint32_t line, const char* fmt, ...)
{
    va_list va;
    char msg[512] = ""; // 这样初始化也很ok

    va_start(va, fmt);
    vsprintf(msg, fmt, va);
    va_end(va);

    printf("msg: %s\n", msg);

    hj_log2(line, msg); // 这里char转const char很ok
    return;
}

void hj_log2(uint32_t line, const char* fmt, ...)
{
    va_list va;
    char msg[512] = "";

    va_start(va, fmt);
    vsprintf(msg, fmt, va);
    va_end(va);

    printf("msg: %s\n", msg);
    return;
}

int main(void)
{
    std::string str = "";
    const char *msg = "hello world";
    str += (std::string)msg;
    hj_log1(130, "%s\n", str.c_str());
    return 0;
}