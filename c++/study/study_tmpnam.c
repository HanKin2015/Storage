/**
 * 文 件 名: study_tmpnam.c
 * 文件描述: 学习tmpnam函数
 * 作    者: HanKin
 * 创建日期: 2021.09.06
 * 修改日期：2021.09.06
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
┌───────────┬───────────────┬──────────────────────────┐
│Interface  │ Attribute     │ Value                    │
├───────────┼───────────────┼──────────────────────────┤
│tmpnam()   │ Thread safety │ MT-Unsafe race:tmpnam/!s │
├───────────┼───────────────┼──────────────────────────┤
│tmpnam_r() │ Thread safety │ MT-Safe                  │
├───────────┼───────────────┼──────────────────────────┤
│mkstemp()  │ Thread safety │ MT-Safe                  │
│mkostemp() │               │                          │
│mkstemps() │               │                          │
│mkostemps()│               │                          │
└───────────┴───────────────┴──────────────────────────┘

char *tmpnam_r(char *s)
{
   return s ? tmpnam(s) : NULL;
}

使用tmpnam函数
L_tmpnam: 20, buffer: p@
临时名称 1: /tmp/file1xMarT
临时名称 2: /tmp/filePXtBhT

使用tmpnam_r函数
L_tmpnam: 20, buffer: p@
临时名称 1: /tmp/file2qdU6v
临时名称 2: (null)

/tmp/ccG1VOQv.o：在函数‘main’中：
study_tmpnam.c:(.text+0x1f): 警告： the use of `tmpnam' is dangerous, better use `mkstemp'

使用mkstemp函数
L_tmpnam: 20, buffer:  @
临时名称 1: ./tmpfile

tmpnam在申请一个临时文件时，并没有实际创建该文件，而是在调用该文件时生成该文件，这两个事件中间的事件差会产生一些安全漏洞（例如：另一个进程创建了一个同名的链接）。而mkstemp在申请一个临时文件时，已生成该文件。
*/

int main()
{
    char buffer[L_tmpnam];
    char *ptr;

    printf("L_tmpnam: %d, buffer: %s\n", L_tmpnam, buffer);
    
    memset(buffer, 0, sizeof(buffer));
    const char *tmpfile = "/tmp/tmpfileXXXXXX";
    strncpy(buffer, tmpfile, L_tmpnam - 1);
    printf("临时名称 1: %s\n", buffer);

    int ret = mkstemp(buffer);    // 只需要修改函数名即可
    if (ret == -1) {
        printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        return -1;
    }

    //ptr = mkstemp(NULL);
    //printf("临时名称 2: %s\n", ptr);

    return(0);
}