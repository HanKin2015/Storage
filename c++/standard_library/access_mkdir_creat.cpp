#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void test()
{
    int ret = 0;
    const char *file_path = "/home/socket/debug.log";
    if (access(file_path, F_OK) == 0) {
        printf("file is exist\n");
    } else {
        printf("file is not exist, errno[%d]: %s\n", errno, strerror(errno));     
        ret = mkdir("/home/socket/", 0666);
        if (ret < 0) {
            printf("mkdir /home/socket failed , errno[%d]: %s\n", errno, strerror(errno));     
        }

        ret = creat(file_path, 00666);
        if (ret < 0) {
            printf("creat file failed, errno[%d]: %s\n", errno, strerror(errno));     
        } else if (ret > 0) {
            close(ret);     
        }
        // open(), openat(), and creat() return the new file descriptor, or -1 if an error occurred (in which case, errno is set appropriately).
        printf("ret: %d\n", ret);
    }
    return;
}

int main()
{
    test();
    return 0;
}

/*
hejian@ubuntu0006:/media/hankin/vdb/TransferStation$ g++ access_mkdir_creat.cpp
hejian@ubuntu0006:/media/hankin/vdb/TransferStation$ ./a.out
file is not exist, errno[2]: No such file or directory
mkdir /home/socket failed , errno[13]: Permission denied
creat file failed, errno[2]: No such file or directory
ret: -1
hejian@ubuntu0006:/media/hankin/vdb/TransferStation$ exit
exit
[root@ubuntu0006:/media/hankin/vdb/TransferStation] #./a.out
file is not exist, errno[2]: No such file or directory
ret: 3
*/