/**
* 文 件 名: mkstemp_example.c
* 文件描述: 学习mkstemp函数
* 作    者: HanKin
* 创建日期: 2024.09.24
* 修改日期：2024.09.24
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    char template[] = "/tmp/tempfileXXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        perror("mkstemp");
        return 1;
    }
    printf("Temporary file created: %s\n", template);
    close(fd);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Temporary file created: /tmp/tempfile2JbhDO
[root@ubuntu0006:~/cmake] #ls /tmp/
config-err-c3fBP5     qt-trayicon-T13822.png                                                             Temp-21a7ca2e-b6ef-426f-a972-0b1d5ab2374c
fcitx-qimpanel:0.pid  ssh-XA5eJ6v8u1Q9                                                                   Temp-55a6104d-faea-4eb2-9e2a-f8192e9f0b51
fcitx-socket-:0       systemd-private-2932f61ff9704c809a179e819ea66c9b-rtkit-daemon.service-iCWl4g       tempfile2JbhDO
heartalive.lock       systemd-private-2932f61ff9704c809a179e819ea66c9b-systemd-timesyncd.service-eUbtyS  vdprogressbar.log
*/
