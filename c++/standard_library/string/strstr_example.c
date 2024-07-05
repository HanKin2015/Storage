/**
* 文 件 名: strstr_example.c
* 文件描述: 注意strstr函数的返回值
* 作    者: HanKin
* 创建日期: 2024.07.04
* 修改日期：2024.07.04
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("argv[0]: %s\n", argv[0]);
    printf("strstr(argv[0], \"arecord\"): %s\n", strstr(argv[0], "arecord"));
    
    if (strstr(argv[0], "arecord")) {
        printf("arecord\n");
    } else if (strstr(argv[0], "aplay")) {
        printf("aplay\n");
    } else {
        printf("command should be named either arecord or aplay\n");
        return 1;
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #gcc l.c -o hjarecorddds
[root@ubuntu0006:~/cmake] #./hjarecorddds
argv[0]: ./hjarecorddds
strstr(argv[0], "arecord"): arecorddds
arecord
[root@ubuntu0006:~/cmake] #mv hjarecorddds jj
[root@ubuntu0006:~/cmake] #./jj
argv[0]: ./jj
strstr(argv[0], "arecord"): (null)
command should be named either arecord or aplay
*/