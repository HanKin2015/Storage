#include <iostream>
#include <cstdio>
#include <stdarg.h>
#include <iconv.h>
#include <errno.h>
#include <string.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <map>
using namespace std;

void func(char **str, char *s)
{
    char *ch = "change";
    *str = ch;
    memcpy(s, ch, 6);
    cout << *str << ';' << s << endl;
    return;
}

int main()
{
    char *str = "origin";
    char s[105] = "origin";
    func(&str, s);
    cout << str << ';' << s << endl;

    const char *file_path = "./hankinTmp.txt";
    FILE *fp = nullptr;

    fp = fopen(file_path, "a");
    if (fp == nullptr) {
        printf("fopen error! err=%u, %s", errno, strerror(errno));
        return -1;
    }
    char c[100];
    strcpy(c, "¹þ¹þ,asd,d,d\n");
    fputs(c, fp);
    fclose(fp);
    return 0;
}
