/*******************************************************************************
* 文 件 名: data_to_struct.c
* 文件描述: uint8_t *转struct
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.03
* 修改日期：2025.01.03
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(1)

struct MyStruct {
    uint8_t field1;  // 1 byte
    uint16_t field2; // 2 bytes
    uint8_t field3;  // 1 byte
    uint32_t field4; // 4 bytes
};

void test()
{
    uint8_t data[10] = {1, 0, 2, 0, 3, 0, 0, 0, 4, 0}; // 示例数据
    struct MyStruct myStruct;

    // 注意sizeof(myStruct)和sizeof(struct MyStruct)的区别
    //memcpy(&myStruct, data, sizeof(myStruct));
    memcpy(&myStruct, data, sizeof(struct MyStruct));

    printf("%ld %ld\n", sizeof(myStruct), sizeof(struct MyStruct));

    // 打印结构体的内容
    printf("field1: %u\n", myStruct.field1);
    printf("field2: %u\n", myStruct.field2);
    printf("field3: %u\n", myStruct.field3);
    printf("field4: %u\n", myStruct.field4);

    return;
}

int main()
{
    uint8_t data[10] = {1, 0, 2, 0, 3, 0, 0, 0, 4, 0}; // 示例数据

    // double free问题
    //struct MyStruct *myStruct = (struct MyStruct *)malloc(sizeof(struct MyStruct));
    //myStruct = (struct MyStruct *)data;

    struct MyStruct *myStruct = (struct MyStruct *)data;

    printf("field1: %u\n", myStruct->field1);
    printf("field2: %u\n", myStruct->field2);
    printf("field3: %u\n", myStruct->field3);
    printf("field4: %u\n", myStruct->field4);

    //free(myStruct);
    //myStruct = NULL;

    return 0;
}
/*
[root@ubuntu0006:~/cmake/hj] #gcc h.c
[root@ubuntu0006:~/cmake/hj] #./a.out
field1: 1
field2: 512
field3: 0
field4: 3
*** Error in `./a.out': double free or corruption (out): 0x00007ffc6a186370 ***
======= Backtrace: =========
/lib/x86_64-linux-gnu/libc.so.6(+0x777f5)[0x7f0b3a4927f5]
/lib/x86_64-linux-gnu/libc.so.6(+0x8038a)[0x7f0b3a49b38a]
/lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f0b3a49f58c]
./a.out[0x4007c5]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f0b3a43b840]
./a.out[0x400559]
======= Memory map: ========
00400000-00401000 r-xp 00000000 fd:01 2653659                            /root/cmake/hj/a.out
00600000-00601000 r--p 00000000 fd:01 2653659                            /root/cmake/hj/a.out
00601000-00602000 rw-p 00001000 fd:01 2653659                            /root/cmake/hj/a.out
00817000-00838000 rw-p 00000000 00:00 0                                  [heap]
7f0b34000000-7f0b34021000 rw-p 00000000 00:00 0
7f0b34021000-7f0b38000000 ---p 00000000 00:00 0
7f0b3a205000-7f0b3a21b000 r-xp 00000000 fd:01 3019227                    /lib/x86_64-linux-gnu/libgcc_s.so.1
7f0b3a21b000-7f0b3a41a000 ---p 00016000 fd:01 3019227                    /lib/x86_64-linux-gnu/libgcc_s.so.1
7f0b3a41a000-7f0b3a41b000 rw-p 00015000 fd:01 3019227                    /lib/x86_64-linux-gnu/libgcc_s.so.1
7f0b3a41b000-7f0b3a5db000 r-xp 00000000 fd:01 3019223                    /lib/x86_64-linux-gnu/libc-2.23.so
7f0b3a5db000-7f0b3a7db000 ---p 001c0000 fd:01 3019223                    /lib/x86_64-linux-gnu/libc-2.23.so
7f0b3a7db000-7f0b3a7df000 r--p 001c0000 fd:01 3019223                    /lib/x86_64-linux-gnu/libc-2.23.so
7f0b3a7df000-7f0b3a7e1000 rw-p 001c4000 fd:01 3019223                    /lib/x86_64-linux-gnu/libc-2.23.so
7f0b3a7e1000-7f0b3a7e5000 rw-p 00000000 00:00 0
7f0b3a7e5000-7f0b3a80b000 r-xp 00000000 fd:01 3019174                    /lib/x86_64-linux-gnu/ld-2.23.so
7f0b3a9ed000-7f0b3a9f0000 rw-p 00000000 00:00 0
7f0b3aa09000-7f0b3aa0a000 rw-p 00000000 00:00 0
7f0b3aa0a000-7f0b3aa0b000 r--p 00025000 fd:01 3019174                    /lib/x86_64-linux-gnu/ld-2.23.so
7f0b3aa0b000-7f0b3aa0c000 rw-p 00026000 fd:01 3019174                    /lib/x86_64-linux-gnu/ld-2.23.so
7f0b3aa0c000-7f0b3aa0d000 rw-p 00000000 00:00 0
7ffc6a168000-7ffc6a189000 rw-p 00000000 00:00 0                          [stack]
7ffc6a1b4000-7ffc6a1b6000 r--p 00000000 00:00 0                          [vvar]
7ffc6a1b6000-7ffc6a1b8000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
已放弃
[root@ubuntu0006:~/cmake/hj] #gcc h.c -fsanitize=address -lasan
[root@ubuntu0006:~/cmake/hj] #./a.out
field1: 1
field2: 512
field3: 0
field4: 3
=================================================================
==1152==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x7ffc32209bb0 in thread T0
    #0 0x7f0fdd1162ca in __interceptor_free (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x982ca)
    #1 0x400ed3 in main (/root/cmake/hj/a.out+0x400ed3)
    #2 0x7f0fdccd483f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)
    #3 0x400988 in _start (/root/cmake/hj/a.out+0x400988)

AddressSanitizer can not describe address in more detail (wild memory access suspected).
SUMMARY: AddressSanitizer: bad-free ??:0 __interceptor_free
==1152==ABORTING
[root@ubuntu0006:~/cmake/hj] #gcc h.c -fsanitize=address
[root@ubuntu0006:~/cmake/hj] #./a.out
field1: 1
field2: 512
field3: 0
field4: 3
=================================================================
==1631==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x7ffc0aabbb40 in thread T0
    #0 0x7f972eacb2ca in __interceptor_free (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x982ca)
    #1 0x400ed3 in main (/root/cmake/hj/a.out+0x400ed3)
    #2 0x7f972e68983f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)
    #3 0x400988 in _start (/root/cmake/hj/a.out+0x400988)

AddressSanitizer can not describe address in more detail (wild memory access suspected).
SUMMARY: AddressSanitizer: bad-free ??:0 __interceptor_free
==1631==ABORTING
*/
