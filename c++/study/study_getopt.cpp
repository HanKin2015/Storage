/**
* 文 件 名: study_getopt.cpp
* 文件描述: 处理程序传入的参数选项
* 作    者: HanKin
* 创建日期: 2020.09.29
* 修改日期：2021.10.27
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int c, start = 0, len = 0;
    while ((c = getopt(argc, argv, "s:l:")) != -1) {
        switch (c) {
        case 's':
            start = atoi(optarg);
            break;
        case 'l':
            len = atoi(optarg);
            break;
        }
    }
 
    if (optind != argc - 1) {
        printf("usage:%s [-s <start>] [-l <len>] <pathname>\n", argv[0]);
        return 1;
    }
    printf("start = %d, len = %d, file_name = %s\n", start, len, argv[optind]);
    return 0;
}
