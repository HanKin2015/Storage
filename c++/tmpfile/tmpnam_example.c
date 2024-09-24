/**
* 文 件 名: tmpnam_example.c
* 文件描述: 学习tmpnam函数
* 作    者: HanKin
* 创建日期: 2024.09.24
* 修改日期：2024.09.24
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdio.h>

int main()
{
    char tmpname[L_tmpnam];  // L_tmpnam 是一个宏，定义了临时文件名缓冲区的大小

    // 生成一个临时文件名
    if (tmpnam(tmpname) == NULL) {
        perror("tmpnam");
        return 1;
    }

    printf("Generated temporary file name: %s\n", tmpname);

    // 你可以使用这个文件名来创建一个文件
    FILE *fp = fopen(tmpname, "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    // 向临时文件写入一些数据
    fprintf(fp, "This is a temporary file.\n");
    fclose(fp);

    // 读取并显示临时文件的内容
    fp = fopen(tmpname, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }
    fclose(fp);

    // 删除临时文件
    if (remove(tmpname) != 0) {
        perror("remove");
        return 1;
    }

    printf("Temporary file deleted.\n");

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #gcc tmpnam_example.c
/tmp/cc8NMq2o.o：在函数‘main’中：
tmpnam_example.c:(.text+0x25): 警告： the use of `tmpnam' is dangerous, better use `mkstemp'
[root@ubuntu0006:~/cmake] #./a.out
Generated temporary file name: /tmp/filePQIDDt
This is a temporary file.
[root@ubuntu0006:~/cmake] #ls /tmp/
config-err-c3fBP5     qt-trayicon-T13822.png                                                             Temp-55a6104d-faea-4eb2-9e2a-f8192e9f0b51
fcitx-qimpanel:0.pid  ssh-XA5eJ6v8u1Q9                                                                   tempfile2JbhDO
fcitx-socket-:0       systemd-private-2932f61ff9704c809a179e819ea66c9b-rtkit-daemon.service-iCWl4g       vdprogressbar.log
filePQIDDt            systemd-private-2932f61ff9704c809a179e819ea66c9b-systemd-timesyncd.service-eUbtyS
heartalive.lock       Temp-21a7ca2e-b6ef-426f-a972-0b1d5ab2374c
[root@ubuntu0006:~/cmake] #cat /tmp/filePQIDDt
This is a temporary file.
*/