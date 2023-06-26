/**
* 文 件 名: repeat_define.c
* 文件描述: define重复定义不报错吗？
* 作    者: HanKin
* 创建日期: 2023.06.26
* 修改日期：2023.06.26
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include "repeat_define.h"

#define ID_LEN 2
#define ID_LEN 3
#ifndef ID_LEN
#define ID_LEN 4
#endif

int main(int argc, char *argv[])
{
    printf("ID_LEN = %d\n", ID_LEN);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #gcc repeat_define.c
repeat_define.c:14:0: warning: "ID_LEN" redefined
 #define ID_LEN 2
 ^
In file included from repeat_define.c:12:0:
repeat_define.h:5:0: note: this is the location of the previous definition
 #define ID_LEN 1
 ^
repeat_define.c:15:0: warning: "ID_LEN" redefined
 #define ID_LEN 3
 ^
repeat_define.c:14:0: note: this is the location of the previous definition
 #define ID_LEN 2
 ^
[root@ubuntu0006:~/cmake] #./a.out
ID_LEN = 3
*/