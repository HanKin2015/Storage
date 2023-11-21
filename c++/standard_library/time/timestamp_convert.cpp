/*******************************************************************************
* 文 件 名: timestamp_convert.cpp
* 文件描述: 时间戳转换成时间格式
* 备    注: https://www.zhihu.com/question/439751997/answer/3081238380
* 作    者: HanKin
* 创建日期: 2023.11.21
* 修改日期：2023.11.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>

int main()
{
    time_t timestamp;
    timestamp = 1700537679; // date +%s
    
    struct tm *timestamp_tm = localtime(&timestamp);
    char timestamp_str[BUFSIZ] = { 0 };
    (void)strftime(timestamp_str, BUFSIZ, "%Y-%m-%d %H:%M:%S", timestamp_tm);
    printf("timestamp_str: %s\n", timestamp_str);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
timestamp_str: 2023-11-21 11:34:39
*/