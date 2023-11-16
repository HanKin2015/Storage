/*******************************************************************************
* 文 件 名: statfs_example.c
* 文件描述: 获取文件系统状态的系统调用函数，通过该函数可以获取文件系统的状态信息
* 作    者: HanKin
* 备    注: https://www.python100.com/html/3XX0A8HF7S73.html
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

//1M字节数
#define ONE_MILLION_BYTES (1024*1024)
// 磁盘空闲字节阈值50M
#define WRITE_LOG_MIN_DISK_FREE_BYTES (50*ONE_MILLION_BYTES)

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <mountpoint>\n", argv[0]);
        exit(1);
    }

    struct statfs *stat;
    stat = (struct statfs *)malloc(sizeof(struct statfs) * 128);
    if (stat == NULL) {
        perror("malloc");
        exit(1);
    }

    int ret = statfs(argv[1], stat);
    if (ret == -1) {
        perror("statfs");
        exit(1);
    }

    printf("File system type: 0x%lx\n", stat->f_type);
    printf("Block size: %ld bytes\n", stat->f_bsize);
    printf("Total blocks: %ld\n", stat->f_blocks);
    printf("Free blocks: %ld\n", stat->f_bfree);
    printf("Available blocks: %ld\n", stat->f_bavail);
    printf("Total files: %ld\n", stat->f_files);
    printf("Free files: %ld\n", stat->f_ffree);
    printf("File system id: %d,%d\n", stat->f_fsid.__val[0], stat->f_fsid.__val[1]);

    unsigned long long uliFreeBytesAvailable = (unsigned long long)(stat->f_bavail * stat->f_bsize);
    printf("uliFreeBytesAvailable: %lld\n", uliFreeBytesAvailable);

    free(stat);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #df
文件系统           1K-块     已用     可用 已用% 挂载点
udev             4065304        0  4065304    0% /dev
tmpfs             817500    81372   736128   10% /run
/dev/vda1       80373576 58160920 18106880   77% /
tmpfs            4087492      468  4087024    1% /dev/shm
tmpfs               5120        4     5116    1% /run/lock
tmpfs            4087492        0  4087492    0% /sys/fs/cgroup
/dev/vdb       103081248 94178916  3643068   97% /media/sangfor/vdb
tmpfs             817500       16   817484    1% /run/user/0
tmpfs             817500        4   817496    1% /run/user/108
tmpfs             817500       36   817464    1% /run/user/1001
[root@ubuntu0006:~/cmake] #./a.out /dev
File system type: 0x1021994
Block size: 4096 bytes
Total blocks: 1016326
Free blocks: 1016326
Available blocks: 1016326
Total files: 1016326
Free files: 1015875
File system id: 0,0
uliFreeBytesAvailable: 4162871296
[root@ubuntu0006:~/cmake] #./a.out /run
File system type: 0x1021994
Block size: 4096 bytes
Total blocks: 204375
Free blocks: 184032
Available blocks: 184032
Total files: 1021873
Free files: 1021146
File system id: 0,0
uliFreeBytesAvailable: 753795072
*/