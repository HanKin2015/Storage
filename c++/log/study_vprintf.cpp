#include<stdio.h>
//#include<stdlib.h>
#include<stdarg.h>//ANSI C可变参数的头文件

int print(char* format, ...) {
    va_list ap;
    int n;
    va_start(ap, format);
    n = vprintf(format, ap);
    va_end(ap);
    return 0;
}

// 打印到标准错误流
int error(char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    fputs("Error: ", stderr);
    result = vfprintf(stderr, fmt, args);
    va_end(args);
    return result;
}

// 保存到文件
int info(char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    FILE *fp = fopen("log.txt", "a");
    fputs("Error: ", fp);
    result = vfprintf(fp, fmt, args);
    fclose(fp);
    va_end(args);
    return result;
}

int main() {
    int ch1 = 10, ch2 = 20;
    print("%d\t%d\n", ch1, ch2);
    error("%d\t%d\n", ch1, ch2);
    info("%d\t%d\n", ch1, ch2);
    return 0;
}
