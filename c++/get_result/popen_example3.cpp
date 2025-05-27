/*******************************************************************************
* 文 件 名: popen_example3.cpp
* 文件描述: popen函数
* 备    注: bug就是只能读取一行
* 作    者: HanKin
* 创建日期: 2025.05.21
* 修改日期：2025.05.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>

void sys_popen(const char *cmd, char *result, size_t result_len)
{
    int try_n = 0;
    const int TRY_MAXN = 10;
    FILE *read_fp = nullptr;
    // 使用 "2>&1" 将标准错误重定向到标准输出
    std::string full_cmd = std::string(cmd) + " 2>&1";

    if (cmd == nullptr) {
        printf("cmd is nullptr\n");
        goto END;
    }

    read_fp = popen(cmd, "r");
    //read_fp = popen(full_cmd.c_str(), "r");
    if (read_fp == nullptr) {
        printf("popen fail, errno=%d, strerror=%s, cmd=%s\n", errno, strerror(errno), cmd);
        goto END;
    }

    // 说明只需要执行命令，不关注执行结果
    if (result == nullptr || result_len == 0) {
        goto END;
    }

    memset(result, 0, result_len);
    while (fgets(result, result_len, read_fp) == nullptr) {
        if (errno != EINTR || try_n++ >= TRY_MAXN) {
            printf("fgets fail, errno=%d, strerror=%s, cmd=%s\n", errno, strerror(errno), cmd);
            goto END;
        }
    };

END:
    if (read_fp && pclose(read_fp) < 0) {
       printf("pclose fail, errno=%d, strerror=%s, cmd=%s\n", errno, strerror(errno), cmd);
    }
}

int main()
{
    printf("%d\n", BUFSIZ);

    char result[BUFSIZ] = { 0 };
    sys_popen("ls -l", result, BUFSIZ);
    std::cout << "Command result:\n" << result << std::endl;

    sys_popen("cat /hj", result, BUFSIZ);
    std::cout << "Command result:\n" << result << std::endl;

    sys_popen("cat /var/log/syslog", result, BUFSIZ);
    std::cout << "Command result:\n" << result << std::endl;

    char usb_path_list[BUFSIZ] = { 0 };
    sys_popen("getsn info 9", usb_path_list, BUFSIZ);
    if (strlen(usb_path_list)) {
        printf("usb_path_list:%s", usb_path_list);
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
8192
Command result:
总用量 48

cat: /hj: 没有那个文件或目录
fgets fail, errno=0, strerror=Success, cmd=cat /hj
Command result:

Command result:
Aug 13 15:21:42 ubuntu0006 rsyslogd: [origin software="rsyslogd" swVersion="8.16.0" x-pid="720" x-info="http://www.rsyslog.com"] rsyslogd was HUPed

cat: /sys/class/net/eth0/address: 没有那个文件或目录
/usr/bin/getsn: 第 10 行: printf: 0x: 无效的十六进制数
fgets fail, errno=0, strerror=Success, cmd=getsn info 9


[root@ubuntu0006:~/cmake] #./a.out
8192
Command result:
总用量 52

Command result:
cat: /hj: 没有那个文件或目录

Command result:
Aug 13 15:21:42 ubuntu0006 rsyslogd: [origin software="rsyslogd" swVersion="8.16.0" x-pid="720" x-info="http://www.rsyslog.com"] rsyslogd was HUPed

usb_path_list:cat: /sys/class/net/eth0/address: 没有那个文件或目录
*/