/**
* 文 件 名: ##_example.c
* 文件描述: ##运算符的学习
* 作    者: HanKin
* 创建日期: 2023.08.15
* 修改日期：2023.08.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdarg.h>

static void
#if defined __GNUC__
__attribute__((format(printf, 3, 4)))
#endif
va_log(void *host, int level, const char *fmt, ...)
{
    char buf[1024];
    va_list ap;
    int n;

    if (level > 5) {
        return;
    }

    n = sprintf(buf, "usbredirhost: ");
    va_start(ap, fmt);
    vsnprintf(buf + n, sizeof(buf) - n, fmt, ap);
    va_end(ap);
    printf("%s\n", buf);
    return;
}

#ifdef ERROR /* defined on WIN32 */
#undef ERROR
#endif

#define ERROR2(...)   va_log(NULL, 3, __VA_ARGS__)

/*
在这段代码中，## 是 C 预处理器中的一个运算符，用于在宏定义中处理可变参数列表。具体来说，## 运算符用于将可变参数列表中的参数与前面的标记连接起来，从而避免在可变参数列表为空时出现语法错误。

在这里，## 运算符用于处理 ERROR 宏的可变参数列表。当可变参数列表为空时，## 运算符会将前面的标记（即 __VA_ARGS__）删除，从而避免在调用 ERROR 宏时出现语法错误。例如，当调用 ERROR("error message") 时，## 运算符会将 __VA_ARGS__ 删除，从而将 ERROR 宏展开为 ERROR2("%s(%d)-%s " "error message", __FILE__, __LINE__, __FUNCTION__)，即将格式化字符串和固定参数连接起来，从而输出错误信息。

因此，## 运算符可以用于在宏定义中处理可变参数列表，从而实现更加灵活的代码生成。
*/
//#define ERROR(fmt, ...) ERROR2("%s(%d)-%s "fmt, __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)

/*
[root@ubuntu0006:~/cmake] #gcc l.c
l.c: In function ‘main’:
l.c:41:50: error: expected expression before ‘)’ token
 #define ERROR2(...)   va_log(NULL, 3, __VA_ARGS__)
                                                  ^
l.c:43:25: note: in expansion of macro ‘ERROR2’
 #define ERROR(fmt, ...) ERROR2("%s(%d)-%s "fmt, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
                         ^
l.c:49:5: note: in expansion of macro ‘ERROR’
     ERROR("hello world");
     ^
[root@ubuntu0006:~/cmake] #v
*/
#define ERROR(fmt, ...) ERROR2("%s(%d)-%s "fmt, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

int main()
{
    int age = 29;
    ERROR("my age is %d", age);
    ERROR("hello world");
    return 0;
}
/*

*/
