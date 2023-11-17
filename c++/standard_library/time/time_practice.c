/*******************************************************************************
* 文 件 名: time_practice.c
* 文件描述: 练习实战
* 作    者: HanKin
* 创建日期: 2023.11.16
* 修改日期：2023.11.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
    time_t timestamp;
    time(&timestamp);
    printf("当前时间戳为：%ld\n", timestamp);

    char *timestr = ctime(&timestamp);
    printf("当前时间为：%s", timestr);
    
    time_t utc_time = time(NULL);
    printf("utc_time = %ld s\n", utc_time);
    
    timestamp = 1700123672;
    struct tm *local_tm = localtime(&timestamp);
    char time_str[BUFSIZ] = { 0 };
    (void)strftime(time_str, BUFSIZ, "%Y-%m-%d %H:%M:%S", local_tm); // 格式化时间字符串：年-月-日
    printf("time_str: %s\n", time_str);
    return 0;
}