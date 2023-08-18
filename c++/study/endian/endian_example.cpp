/**
* 文 件 名: endian_example.c
* 文件描述: scsi指令学习
* 备    注: gcc bulk_transfer_example.c -lusb-1.0
* 作    者: HanKin
* 创建日期: 2023.08.16
* 修改日期：2023.08.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <stdio.h>
using namespace std;

static union {
    int i;
    char c;
}endian={1};

const char test = 'k';
#if (test == 'k')
#define YES
#else
#define NO
#endif

int main()
{
#ifdef YES
    cout << "YES" << endl;
#endif

#ifdef NO
    cout << "NO" << endl;
#endif

    if (test == 'k') {
        cout << "HEJIAN" << endl;
    }


    cout << "c = " << endian.c << endl;
    printf("%d\n", endian.c);
    if (endian.c == 1) {
        cout << "little endian" << endl;
    }

    const char c = 65; //A
    cout << c << endl;
    printf("%c\n", c);

    // 神奇不神奇,把B赋值给i结果输出到c中
    endian.i = 66;
    cout << endian.c << endl;
    return 0;
}
/*
NO
HEJIAN
c =
1
little endian
A
A
B
*/