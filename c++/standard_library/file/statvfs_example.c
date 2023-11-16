/*******************************************************************************
* 文 件 名: statfs_example.c
* 文件描述: 一个用来检查文件系统状态的函数
* 作    者: HanKin
* 备    注: https://www.python100.com/html/3L1O5B9OB16E.html
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[])
{
    struct statvfs vfs;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s /path/to/file/system\n", argv[0]);
        return 1;
    }

    if (statvfs(argv[1], &vfs) < 0) {
        perror("statvfs");
        return 1;
    }

    printf("Block size: %lu bytes\n", vfs.f_bsize);
    printf("Total blocks: %lu\n", vfs.f_blocks);
    printf("Free blocks: %lu\n", vfs.f_bfree);
    printf("Free blocks for non-root user: %lu\n", vfs.f_bavail);
    printf("File system ID: %lu\n", vfs.f_fsid);
    printf("Maximum file name length: %lu\n", vfs.f_namemax);

    unsigned long long uliFreeBytesAvailable = (unsigned long long)(vfs.f_bavail * vfs.f_bsize);
    printf("uliFreeBytesAvailable: %lld\n", uliFreeBytesAvailable);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #df
文件系统           1K-块     已用     可用 已用% 挂载点
udev             4065304        0  4065304    0% /dev
tmpfs             817500    81372   736128   10% /run
/dev/vda1       80373576 58160928 18106872   77% /
tmpfs            4087492      468  4087024    1% /dev/shm
tmpfs               5120        4     5116    1% /run/lock
tmpfs            4087492        0  4087492    0% /sys/fs/cgroup
/dev/vdb       103081248 94178916  3643068   97% /media/sangfor/vdb
tmpfs             817500       16   817484    1% /run/user/0
tmpfs             817500        4   817496    1% /run/user/108
tmpfs             817500       36   817464    1% /run/user/1001
[root@ubuntu0006:~/cmake] #./a.out /dev
Block size: 4096 bytes
Total blocks: 1016326
Free blocks: 1016326
Free blocks for non-root user: 1016326
File system ID: 0
Maximum file name length: 255
uliFreeBytesAvailable: 4162871296
[root@ubuntu0006:~/cmake] #./a.out /run
Block size: 4096 bytes
Total blocks: 204375
Free blocks: 184032
Free blocks for non-root user: 184032
File system ID: 0
Maximum file name length: 255
uliFreeBytesAvailable: 753795072
*/


