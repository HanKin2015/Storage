/**
* 文 件 名: attribute_example.c
* 文件描述: attribute学习
* 作    者: HanKin
* 创建日期: 2023.08.15
* 修改日期：2023.08.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>

static void
#if defined __GNUC__
__attribute__((format(printf, 3, 4)))
#endif
va_log(int *host, int level, const char *fmt, ...)
{
    printf("%d\n", level);
    return;
}

static void
#if defined __GNUC__
__attribute__((format(printf, 3, 4)))
#endif
va_log_(int n, int *host, int level, const char *fmt, ...)
{
    printf("%d\n", level);
    return;
}

int main()
{
    printf("%s\n", get_abstime_us_str());

    va_log(NULL, 1, "%d", 32);
    va_log_(1, NULL, 1, "%d", 32);
    return 0;
}
/*

[root@ubuntu0006:~/cmake] #gcc attribute_example.c
attribute_example.c:36:1: error: format string argument is not a string type
 {
 ^
[root@ubuntu0006:~/cmake] #vi attribute_example.c
[root@ubuntu0006:~/cmake] #gcc attribute_example.c
attribute_example.c:36:1: error: format string argument follows the args to be formatted
 {
 ^
[root@ubuntu0006:~/cmake] #
*/
