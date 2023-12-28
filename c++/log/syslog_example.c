/*******************************************************************************
* 文 件 名: syslog_example.c
* 文件描述: 学习syslog函数
* 备    注: 通常会将日志写入系统日志文件中，在大多数 Linux 系统 /var/log/syslog 或 /var/log/messages 文件中。而在 macOS 系统 /var/log/system.log 文件中
* 作    者: HanKin
* 创建日期: 2023.12.28
* 修改日期：2023.12.28
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

int main()
{
    printf("pid: %d\n", getpid());
    
    openlog("应用程序名称", LOG_ODELAY | LOG_PID, LOG_LOCAL0 | LOG_USER);
    syslog(LOG_INFO, "这是一条日志消息");
    closelog();
    return 0;
}
/*
[root@ubuntu0006:/var/log] #./a.out
pid: 28302
[root@ubuntu0006:/var/log] #tail -n 5 /var/log/syslog
Dec 28 16:16:35 ubuntu0006 systemd-timesyncd[343]: Timed out waiting for reply from [2620:2d:4000:1::40]:123 (ntp.ubuntu.com).
Dec 28 16:16:45 ubuntu0006 systemd-timesyncd[343]: Timed out waiting for reply from [2620:2d:4000:1::3f]:123 (ntp.ubuntu.com).
Dec 28 16:17:01 ubuntu0006 CRON[3460]: (root) CMD (   cd / && run-parts --report /etc/cron.hourly)
Dec 28 16:29:48 ubuntu0006 应用程序名称[19716]: 这是一条日志消息
Dec 28 16:35:09 ubuntu0006 应用程序名称[28302]: 这是一条日志消息
*/
