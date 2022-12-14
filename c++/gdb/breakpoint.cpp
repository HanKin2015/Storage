/**
* 文 件 名: breakpoint.cpp
* 文件描述: 下断点实战
* 作    者: HanKin
* 创建日期: 2022.12.09
* 修改日期：2022.12.09
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

int main(int argc, char *argv[])
{
    int index = 0;
    while (true) {
        char buf[BUFSIZ] = { 0 };
        time_t cur;
        time(&cur);
        strftime(buf, BUFSIZ, "%F %T", localtime(&cur));
        printf("%s: index = %d\n", buf, index++);
        sleep(2);
        if (index == 20) {
            printf("%s: index = %d, sorry, this is a breakpoint\n", buf, index++);
            index = 10;
        }
    }
    return 0;
}
