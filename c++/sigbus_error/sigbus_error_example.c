#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int memcpy_version()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 33);

    // 小端写入int
    int val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=33, mod4=%ld)\n",
           ptr + 33,
           ((unsigned long)(ptr + 33)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 33...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read1 = 0, read2 = 0, read3 = 0;
    memcpy(&read1, (unsigned char *)ptr + 33, sizeof(int));
    //printf("hejian read1 = %d\n", read1);
    memcpy(&read2, (unsigned char *)ptr + 37, sizeof(int));
    //printf("hejian read2 = %d\n", read2);
    memcpy(&read3, (unsigned char *)ptr + 41, sizeof(int));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d, %d, %d\n", read1, read2, read3);

    free(java_array);
    return 0;
}

int sigbus_version()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 33);

    // 小端写入int
    int val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=33, mod4=%ld)\n",
           ptr + 33,
           ((unsigned long)(ptr + 33)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 33...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read1 = *((int *)((unsigned char *)ptr + 33));
    //printf("hejian read1 = %d\n", read1); // 把这句打印日志注释放开后也是正常的，应该是进行了对齐
    int read2 = *((int *)((unsigned char *)ptr + 37));
    //printf("hejian read2 = %d\n", read2);
    int read3 = *((int *)((unsigned char *)ptr + 41));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d, %d, %d\n", read1, read2, read3);

    free(java_array);
    return 0;
}

int sigbus_version_optnone1()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 33);

    // 小端写入int
    int val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=33, mod4=%ld)\n",
           ptr + 33,
           ((unsigned long)(ptr + 33)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 33...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read1 = *((volatile int *)((unsigned char *)ptr + 33));
    //printf("hejian read1 = %d\n", read1); // 把这句打印日志注释放开后也是正常的，应该是进行了对齐
    int read2 = *((int *)((unsigned char *)ptr + 37));
    //printf("hejian read2 = %d\n", read2);
    int read3 = *((int *)((unsigned char *)ptr + 41));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d, %d, %d\n", read1, read2, read3);

    free(java_array);
    return 0;
}

#pragma clang optimize off
int sigbus_version_optnone2()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 33);

    // 小端写入int
    int val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=33, mod4=%ld)\n",
           ptr + 33,
           ((unsigned long)(ptr + 33)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 33...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read1 = *((int *)((unsigned char *)ptr + 33));
    int read2 = *((int *)((unsigned char *)ptr + 37));
    int read3 = *((int *)((unsigned char *)ptr + 41));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d, %d, %d\n", read1, read2, read3);

    free(java_array);
    return 0;
}
#pragma clang optimize on

int sigbus_version_printf()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 33);

    // 小端写入int
    int val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=33, mod4=%ld)\n",
           ptr + 33,
           ((unsigned long)(ptr + 33)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 33...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read1 = *((int *)((unsigned char *)ptr + 33));
    printf("hejian read1 = %d\n", read1); // 把这句打印日志注释放开后也是正常的，应该是进行了对齐
    int read2 = *((int *)((unsigned char *)ptr + 37));
    //printf("hejian read2 = %d\n", read2);
    int read3 = *((int *)((unsigned char *)ptr + 41));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d, %d, %d\n", read1, read2, read3);

    free(java_array);
    return 0;
}

int sigbus_version_printf_add()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 29);

    // 小端写入int
    int val0 = 0, val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 29, &val0, 4);
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=29, mod4=%ld)\n",
           ptr + 29,
           ((unsigned long)(ptr + 29)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 29...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read0 = *((int *)((unsigned char *)ptr + 29));
    printf("hejian read1 = %d\n", read0);

    int read1 = *((int *)((unsigned char *)ptr + 33));
    int read2 = *((int *)((unsigned char *)ptr + 37));
    int read3 = *((int *)((unsigned char *)ptr + 41));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d %d, %d, %d\n", read0, read1, read2, read3);

    free(java_array);
    return 0;
}

//__attribute__((optimize("O0")))
__attribute__((optnone))
int sigbus_version_optnone3()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 45) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 29);

    // 小端写入int
    int val0 = 0, val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 29, &val0, 4);
    memcpy(java_array + 33, &val1, 4);
    memcpy(java_array + 37, &val2, 4);
    memcpy(java_array + 41, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=29, mod4=%ld)\n",
           ptr + 29,
           ((unsigned long)(ptr + 29)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 29...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read0 = *((int *)((unsigned char *)ptr + 29));
    printf("hejian read1 = %d\n", read0);

    int read1 = *((int *)((unsigned char *)ptr + 33));
    int read2 = *((int *)((unsigned char *)ptr + 37));
    int read3 = *((int *)((unsigned char *)ptr + 41));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d %d, %d, %d\n", read0, read1, read2, read3);

    free(java_array);
    return 0;
}

int normal_version()
{
    printf("%s[%d]\n", __FUNCTION__, __LINE__);
    // 1. 模拟Java byte[]：总长度 = 33 (string) + 12 (3个int) = 45字节
    // 使用 posix_memalign 确保起始地址是 8字节对齐 (模拟Java堆的典型对齐)
    unsigned char *java_array;
    if (posix_memalign((void**)&java_array, 8, 44) != 0) {
        perror("posix_memalign failed");
        return 1;
    }

    // 2. 初始化数据：前33字节填 'A'，后面填3个int (值分别为1, 2, 3)
    memset(java_array, 'A', 32);

    // 小端写入int
    int val1 = 1, val2 = 2, val3 = 3;
    memcpy(java_array + 32, &val1, 4);
    memcpy(java_array + 36, &val2, 4);
    memcpy(java_array + 40, &val3, 4);

    printf("Base addr: %p (mod4=%ld, mod8=%ld)\n",
           java_array,
           ((unsigned long)java_array) % 4,
           ((unsigned long)java_array) % 8);

    unsigned char *ptr = java_array;
    printf("Target addr for 1st int: %p (offset=33, mod4=%ld)\n",
           ptr + 33,
           ((unsigned long)(ptr + 32)) % 4);

    // 3. 模拟C代码解析：直接强转解引用 (危险操作!)
    printf("Attempting unaligned access at offset 32...\n");

    // 这里在ARM64上必崩，在ARM32上可能不崩，在x86上不崩
    int read1 = *((int *)((unsigned char *)ptr + 32));
    //printf("hejian read1 = %d\n", read1);
    int read2 = *((int *)((unsigned char *)ptr + 36));
    //printf("hejian read2 = %d\n", read2);
    int read3 = *((int *)((unsigned char *)ptr + 40));
    printf("hejian read3 = %d\n", read3);

    printf("Success (unexpected on ARM64!): %d, %d, %d\n", read1, read2, read3);

    free(java_array);
    return 0;
}

int main()
{
    normal_version();
    memcpy_version();
    sigbus_version_printf();
    sigbus_version_optnone1();
    sigbus_version_optnone2();
    sigbus_version_optnone3();
    sigbus_version_printf_add();
    sigbus_version();
    return 0;
}
/*
hejian@android-PowerEdge-R920:~/hj/NDK/test/sigbus$ cat Makefile
HOST_TAG ?= linux-x86_64
ARCH ?= arm
API ?= 21
TRIPLE := armv7a-linux-androideabi
TOOLCHAIN := /home/hejian/hj/NDK/android-ndk-r25c/toolchains/llvm/prebuilt/$(HOST_TAG)/bin
CC := $(TOOLCHAIN)/$(TRIPLE)$(API)-clang
CXX := $(TOOLCHAIN)/$(TRIPLE)$(API)-clang++

CFLAGS := -O2 -fPIE -fno-tree-vectorize
LDFLAGS := -pie

SRC := sigbus.c
TARGET := sigbus

all:$(TARGET)

$(TARGET):$(SRC)
        $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
        rm -rf $(TARGET)

.PHONY:all clean
hejian@android-PowerEdge-R920:~/hj/NDK/test/sigbus$ make
/home/hejian/hj/NDK/android-ndk-r25c/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang -O2 -fPIE -fno-tree-vectorize sigbus.c -o sigbus -pie
hejian@android-PowerEdge-R920:~/hj/NDK/test/sigbus$ /home/hejian/hj/NDK/android-ndk-r25c/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-objdump -d sigbus

sigbus: file format elf32-littlearm

Disassembly of section .text:

00001700 <_start>:
    1700: 00 b0 a0 e3   mov     r11, #0
    1704: 00 e0 a0 e3   mov     lr, #0
    1708: 0d 00 a0 e1   mov     r0, sp
    170c: ff ff ff ea   b       0x1710 <_start_main>    @ imm = #-4

00001710 <_start_main>:
    1710: 00 48 2d e9   push    {r11, lr}
    1714: 0d b0 a0 e1   mov     r11, sp
    1718: 10 d0 4d e2   sub     sp, sp, #16
    171c: 30 10 9f e5   ldr     r1, [pc, #48]           @ 0x1754 <$d.1>
    1720: 04 30 8d e2   add     r3, sp, #4
    1724: 01 10 9f e7   ldr     r1, [pc, r1]
    1728: 0c 10 8d e5   str     r1, [sp, #12]
    172c: 24 10 9f e5   ldr     r1, [pc, #36]           @ 0x1758 <$d.1+0x4>
    1730: 01 10 9f e7   ldr     r1, [pc, r1]
    1734: 08 10 8d e5   str     r1, [sp, #8]
    1738: 1c 10 9f e5   ldr     r1, [pc, #28]           @ 0x175c <$d.1+0x8>
    173c: 01 10 9f e7   ldr     r1, [pc, r1]
    1740: 04 10 8d e5   str     r1, [sp, #4]
    1744: 00 10 a0 e3   mov     r1, #0
    1748: 10 20 9f e5   ldr     r2, [pc, #16]           @ 0x1760 <$d.1+0xc>
    174c: 02 20 9f e7   ldr     r2, [pc, r2]
    1750: fe 02 00 eb   bl      0x2350 <$a>             @ imm = #3064

00001754 <$d.1>:
    1754:       a4 1d 00 00     .word   0x00001da4
    1758:       9c 1d 00 00     .word   0x00001d9c
    175c:       94 1d 00 00     .word   0x00001d94
    1760:       88 1d 00 00     .word   0x00001d88

00001764 <__atexit_handler_wrapper>:
    1764: 00 00 50 e3   cmp     r0, #0
    1768: 1e ff 2f 01   bxeq    lr
    176c: 10 ff 2f e1   bx      r0

00001770 <atexit>:
    1770: 00 10 a0 e1   mov     r1, r0
    1774: 0c 00 9f e5   ldr     r0, [pc, #12]           @ 0x1788 <$d.3>
    1778: 0c 20 9f e5   ldr     r2, [pc, #12]           @ 0x178c <$d.3+0x4>
    177c: 00 00 8f e0   add     r0, pc, r0
    1780: 02 20 8f e0   add     r2, pc, r2
    1784: f5 02 00 ea   b       0x2360 <$a>             @ imm = #3028

00001788 <$d.3>:
    1788:       e0 ff ff ff     .word   0xffffffe0
    178c:       84 2d 00 00     .word   0x00002d84

00001790 <memcpy_version>:
    1790: 70 4c 2d e9   push    {r4, r5, r6, r10, r11, lr}
    1794: 10 b0 8d e2   add     r11, sp, #16
    1798: 08 d0 4d e2   sub     sp, sp, #8
    179c: f0 00 9f e5   ldr     r0, [pc, #240]          @ 0x1894 <$d.1>
    17a0: 08 20 a0 e3   mov     r2, #8
    17a4: ec 10 9f e5   ldr     r1, [pc, #236]          @ 0x1898 <$d.1+0x4>
    17a8: 00 00 8f e0   add     r0, pc, r0
    17ac: 01 10 8f e0   add     r1, pc, r1
    17b0: ee 02 00 eb   bl      0x2370 <$a>             @ imm = #3000
    17b4: 04 00 8d e2   add     r0, sp, #4
    17b8: 08 10 a0 e3   mov     r1, #8
    17bc: 2d 20 a0 e3   mov     r2, #45
    17c0: ee 02 00 eb   bl      0x2380 <$a>             @ imm = #3000
    17c4: 00 00 50 e3   cmp     r0, #0
    17c8: 2b 00 00 1a   bne     0x187c <memcpy_version+0xec> @ imm = #172
    17cc: 04 40 9d e5   ldr     r4, [sp, #4]
    17d0: 21 10 a0 e3   mov     r1, #33
    17d4: 41 20 a0 e3   mov     r2, #65
    17d8: 04 00 a0 e1   mov     r0, r4
    17dc: c9 02 00 eb   bl      0x2308 <__aeabi_memset8> @ imm = #2852
    17e0: b8 00 9f e5   ldr     r0, [pc, #184]          @ 0x18a0 <$d.1+0xc>
    17e4: 03 10 a0 e3   mov     r1, #3
    17e8: 29 10 84 e5   str     r1, [r4, #41]
    17ec: 02 10 a0 e3   mov     r1, #2
    17f0: 25 10 84 e5   str     r1, [r4, #37]
    17f4: 01 10 a0 e3   mov     r1, #1
    17f8: 00 00 8f e0   add     r0, pc, r0
    17fc: 03 20 04 e2   and     r2, r4, #3
    1800: 07 30 04 e2   and     r3, r4, #7
    1804: 21 10 84 e5   str     r1, [r4, #33]
    1808: 04 10 a0 e1   mov     r1, r4
    180c: d7 02 00 eb   bl      0x2370 <$a>             @ imm = #2908
    1810: 04 60 9d e5   ldr     r6, [sp, #4]
    1814: 88 00 9f e5   ldr     r0, [pc, #136]          @ 0x18a4 <$d.1+0x10>
    1818: 21 10 86 e2   add     r1, r6, #33
    181c: 00 00 8f e0   add     r0, pc, r0
    1820: 03 20 01 e2   and     r2, r1, #3
    1824: d1 02 00 eb   bl      0x2370 <$a>             @ imm = #2884
    1828: 78 00 9f e5   ldr     r0, [pc, #120]          @ 0x18a8 <$d.1+0x14>
    182c: 00 00 8f e0   add     r0, pc, r0
    1830: d6 02 00 eb   bl      0x2390 <$a>             @ imm = #2904
    1834: 70 00 9f e5   ldr     r0, [pc, #112]          @ 0x18ac <$d.1+0x18>
    1838: 21 40 96 e5   ldr     r4, [r6, #33]
    183c: 25 50 96 e5   ldr     r5, [r6, #37]
    1840: 00 00 8f e0   add     r0, pc, r0
    1844: 29 60 96 e5   ldr     r6, [r6, #41]
    1848: 06 10 a0 e1   mov     r1, r6
    184c: c7 02 00 eb   bl      0x2370 <$a>             @ imm = #2844
    1850: 58 00 9f e5   ldr     r0, [pc, #88]           @ 0x18b0 <$d.1+0x1c>
    1854: 04 10 a0 e1   mov     r1, r4
    1858: 05 20 a0 e1   mov     r2, r5
    185c: 06 30 a0 e1   mov     r3, r6
    1860: 00 00 8f e0   add     r0, pc, r0
    1864: c1 02 00 eb   bl      0x2370 <$a>             @ imm = #2820
    1868: 04 00 9d e5   ldr     r0, [sp, #4]
    186c: cb 02 00 eb   bl      0x23a0 <$a>             @ imm = #2860
    1870: 00 00 a0 e3   mov     r0, #0
    1874: 10 d0 4b e2   sub     sp, r11, #16
    1878: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}
    187c: 18 00 9f e5   ldr     r0, [pc, #24]           @ 0x189c <$d.1+0x8>
    1880: 00 00 8f e0   add     r0, pc, r0
    1884: c9 02 00 eb   bl      0x23b0 <$a>             @ imm = #2852
    1888: 01 00 a0 e3   mov     r0, #1
    188c: 10 d0 4b e2   sub     sp, r11, #16
    1890: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}

00001894 <$d.1>:
    1894:       96 ed ff ff     .word   0xffffed96
    1898:       2c ee ff ff     .word   0xffffee2c
    189c:       02 ee ff ff     .word   0xffffee02
    18a0:       08 ed ff ff     .word   0xffffed08
    18a4:       28 ec ff ff     .word   0xffffec28
    18a8:       6c ee ff ff     .word   0xffffee6c
    18ac:       1e ed ff ff     .word   0xffffed1e
    18b0:       5c ec ff ff     .word   0xffffec5c

000018b4 <sigbus_version>:
    18b4: 70 4c 2d e9   push    {r4, r5, r6, r10, r11, lr}
    18b8: 10 b0 8d e2   add     r11, sp, #16
    18bc: 08 d0 4d e2   sub     sp, sp, #8
    18c0: ec 00 9f e5   ldr     r0, [pc, #236]          @ 0x19b4 <$d.3>
    18c4: 38 20 a0 e3   mov     r2, #56
    18c8: e8 10 9f e5   ldr     r1, [pc, #232]          @ 0x19b8 <$d.3+0x4>
    18cc: 00 00 8f e0   add     r0, pc, r0
    18d0: 01 10 8f e0   add     r1, pc, r1
    18d4: a5 02 00 eb   bl      0x2370 <$a>             @ imm = #2708
    18d8: 04 00 8d e2   add     r0, sp, #4
    18dc: 08 10 a0 e3   mov     r1, #8
    18e0: 2d 20 a0 e3   mov     r2, #45
    18e4: a5 02 00 eb   bl      0x2380 <$a>             @ imm = #2708
    18e8: 00 00 50 e3   cmp     r0, #0
    18ec: 2a 00 00 1a   bne     0x199c <sigbus_version+0xe8> @ imm = #168
    18f0: 04 40 9d e5   ldr     r4, [sp, #4]
    18f4: 21 10 a0 e3   mov     r1, #33
    18f8: 41 20 a0 e3   mov     r2, #65
    18fc: 04 00 a0 e1   mov     r0, r4
    1900: 80 02 00 eb   bl      0x2308 <__aeabi_memset8> @ imm = #2560
    1904: b4 00 9f e5   ldr     r0, [pc, #180]          @ 0x19c0 <$d.3+0xc>
    1908: 03 10 a0 e3   mov     r1, #3
    190c: 29 10 84 e5   str     r1, [r4, #41]
    1910: 02 10 a0 e3   mov     r1, #2
    1914: 25 10 84 e5   str     r1, [r4, #37]
    1918: 01 10 a0 e3   mov     r1, #1
    191c: 00 00 8f e0   add     r0, pc, r0
    1920: 03 20 04 e2   and     r2, r4, #3
    1924: 07 30 04 e2   and     r3, r4, #7
    1928: 21 10 84 e5   str     r1, [r4, #33]
    192c: 04 10 a0 e1   mov     r1, r4
    1930: 8e 02 00 eb   bl      0x2370 <$a>             @ imm = #2616
    1934: 04 60 9d e5   ldr     r6, [sp, #4]
    1938: 84 00 9f e5   ldr     r0, [pc, #132]          @ 0x19c4 <$d.3+0x10>
    193c: 21 10 86 e2   add     r1, r6, #33
    1940: 00 00 8f e0   add     r0, pc, r0
    1944: 03 20 01 e2   and     r2, r1, #3
    1948: 88 02 00 eb   bl      0x2370 <$a>             @ imm = #2592
    194c: 74 00 9f e5   ldr     r0, [pc, #116]          @ 0x19c8 <$d.3+0x14>
    1950: 00 00 8f e0   add     r0, pc, r0
    1954: 8d 02 00 eb   bl      0x2390 <$a>             @ imm = #2612
    1958: 6c 00 9f e5   ldr     r0, [pc, #108]          @ 0x19cc <$d.3+0x18>
    195c: 21 60 86 e2   add     r6, r6, #33
    1960: 00 00 8f e0   add     r0, pc, r0
    1964: 70 00 96 e8   ldm     r6, {r4, r5, r6}
    1968: 06 10 a0 e1   mov     r1, r6
    196c: 7f 02 00 eb   bl      0x2370 <$a>             @ imm = #2556
    1970: 58 00 9f e5   ldr     r0, [pc, #88]           @ 0x19d0 <$d.3+0x1c>
    1974: 04 10 a0 e1   mov     r1, r4
    1978: 05 20 a0 e1   mov     r2, r5
    197c: 06 30 a0 e1   mov     r3, r6
    1980: 00 00 8f e0   add     r0, pc, r0
    1984: 79 02 00 eb   bl      0x2370 <$a>             @ imm = #2532
    1988: 04 00 9d e5   ldr     r0, [sp, #4]
    198c: 83 02 00 eb   bl      0x23a0 <$a>             @ imm = #2572
    1990: 00 00 a0 e3   mov     r0, #0
    1994: 10 d0 4b e2   sub     sp, r11, #16
    1998: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}
    199c: 18 00 9f e5   ldr     r0, [pc, #24]           @ 0x19bc <$d.3+0x8>
    19a0: 00 00 8f e0   add     r0, pc, r0
    19a4: 81 02 00 eb   bl      0x23b0 <$a>             @ imm = #2564
    19a8: 01 00 a0 e3   mov     r0, #1
    19ac: 10 d0 4b e2   sub     sp, r11, #16
    19b0: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}

000019b4 <$d.3>:
    19b4:       72 ec ff ff     .word   0xffffec72
    19b8:       ca ec ff ff     .word   0xffffecca
    19bc:       e2 ec ff ff     .word   0xffffece2
    19c0:       e4 eb ff ff     .word   0xffffebe4
    19c4:       04 eb ff ff     .word   0xffffeb04
    19c8:       48 ed ff ff     .word   0xffffed48
    19cc:       fe eb ff ff     .word   0xffffebfe
    19d0:       3c eb ff ff     .word   0xffffeb3c

000019d4 <sigbus_version_optnone1>:
    19d4: 70 4c 2d e9   push    {r4, r5, r6, r10, r11, lr}
    19d8: 10 b0 8d e2   add     r11, sp, #16
    19dc: 08 d0 4d e2   sub     sp, sp, #8
    19e0: f0 00 9f e5   ldr     r0, [pc, #240]          @ 0x1ad8 <$d.5>
    19e4: 67 20 a0 e3   mov     r2, #103
    19e8: ec 10 9f e5   ldr     r1, [pc, #236]          @ 0x1adc <$d.5+0x4>
    19ec: 00 00 8f e0   add     r0, pc, r0
    19f0: 01 10 8f e0   add     r1, pc, r1
    19f4: 5d 02 00 eb   bl      0x2370 <$a>             @ imm = #2420
    19f8: 04 00 8d e2   add     r0, sp, #4
    19fc: 08 10 a0 e3   mov     r1, #8
    1a00: 2d 20 a0 e3   mov     r2, #45
    1a04: 5d 02 00 eb   bl      0x2380 <$a>             @ imm = #2420
    1a08: 00 00 50 e3   cmp     r0, #0
    1a0c: 2b 00 00 1a   bne     0x1ac0 <sigbus_version_optnone1+0xec> @ imm = #172
    1a10: 04 40 9d e5   ldr     r4, [sp, #4]
    1a14: 21 10 a0 e3   mov     r1, #33
    1a18: 41 20 a0 e3   mov     r2, #65
    1a1c: 04 00 a0 e1   mov     r0, r4
    1a20: 38 02 00 eb   bl      0x2308 <__aeabi_memset8> @ imm = #2272
    1a24: b8 00 9f e5   ldr     r0, [pc, #184]          @ 0x1ae4 <$d.5+0xc>
    1a28: 03 10 a0 e3   mov     r1, #3
    1a2c: 29 10 84 e5   str     r1, [r4, #41]
    1a30: 02 10 a0 e3   mov     r1, #2
    1a34: 25 10 84 e5   str     r1, [r4, #37]
    1a38: 01 10 a0 e3   mov     r1, #1
    1a3c: 00 00 8f e0   add     r0, pc, r0
    1a40: 03 20 04 e2   and     r2, r4, #3
    1a44: 07 30 04 e2   and     r3, r4, #7
    1a48: 21 10 84 e5   str     r1, [r4, #33]
    1a4c: 04 10 a0 e1   mov     r1, r4
    1a50: 46 02 00 eb   bl      0x2370 <$a>             @ imm = #2328
    1a54: 04 60 9d e5   ldr     r6, [sp, #4]
    1a58: 88 00 9f e5   ldr     r0, [pc, #136]          @ 0x1ae8 <$d.5+0x10>
    1a5c: 21 10 86 e2   add     r1, r6, #33
    1a60: 00 00 8f e0   add     r0, pc, r0
    1a64: 03 20 01 e2   and     r2, r1, #3
    1a68: 40 02 00 eb   bl      0x2370 <$a>             @ imm = #2304
    1a6c: 78 00 9f e5   ldr     r0, [pc, #120]          @ 0x1aec <$d.5+0x14>
    1a70: 00 00 8f e0   add     r0, pc, r0
    1a74: 45 02 00 eb   bl      0x2390 <$a>             @ imm = #2324
    1a78: 70 00 9f e5   ldr     r0, [pc, #112]          @ 0x1af0 <$d.5+0x18>
    1a7c: 21 40 96 e5   ldr     r4, [r6, #33]
    1a80: 25 50 96 e5   ldr     r5, [r6, #37]
    1a84: 00 00 8f e0   add     r0, pc, r0
    1a88: 29 60 96 e5   ldr     r6, [r6, #41]
    1a8c: 06 10 a0 e1   mov     r1, r6
    1a90: 36 02 00 eb   bl      0x2370 <$a>             @ imm = #2264
    1a94: 58 00 9f e5   ldr     r0, [pc, #88]           @ 0x1af4 <$d.5+0x1c>
    1a98: 04 10 a0 e1   mov     r1, r4
    1a9c: 05 20 a0 e1   mov     r2, r5
    1aa0: 06 30 a0 e1   mov     r3, r6
    1aa4: 00 00 8f e0   add     r0, pc, r0
    1aa8: 30 02 00 eb   bl      0x2370 <$a>             @ imm = #2240
    1aac: 04 00 9d e5   ldr     r0, [sp, #4]
    1ab0: 3a 02 00 eb   bl      0x23a0 <$a>             @ imm = #2280
    1ab4: 00 00 a0 e3   mov     r0, #0
    1ab8: 10 d0 4b e2   sub     sp, r11, #16
    1abc: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}
    1ac0: 18 00 9f e5   ldr     r0, [pc, #24]           @ 0x1ae0 <$d.5+0x8>
    1ac4: 00 00 8f e0   add     r0, pc, r0
    1ac8: 38 02 00 eb   bl      0x23b0 <$a>             @ imm = #2272
    1acc: 01 00 a0 e3   mov     r0, #1
    1ad0: 10 d0 4b e2   sub     sp, r11, #16
    1ad4: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}

00001ad8 <$d.5>:
    1ad8:       52 eb ff ff     .word   0xffffeb52
    1adc:       f8 ea ff ff     .word   0xffffeaf8
    1ae0:       be eb ff ff     .word   0xffffebbe
    1ae4:       c4 ea ff ff     .word   0xffffeac4
    1ae8:       e4 e9 ff ff     .word   0xffffe9e4
    1aec:       28 ec ff ff     .word   0xffffec28
    1af0:       da ea ff ff     .word   0xffffeada
    1af4:       18 ea ff ff     .word   0xffffea18

00001af8 <sigbus_version_optnone2>:
    1af8: 00 48 2d e9   push    {r11, lr}
    1afc: 0d b0 a0 e1   mov     r11, sp
    1b00: 28 d0 4d e2   sub     sp, sp, #40
    1b04: a4 01 9f e5   ldr     r0, [pc, #420]          @ 0x1cb0 <$d.7>
    1b08: 00 00 8f e0   add     r0, pc, r0
    1b0c: a0 11 9f e5   ldr     r1, [pc, #416]          @ 0x1cb4 <$d.7+0x4>
    1b10: 01 10 8f e0   add     r1, pc, r1
    1b14: 97 20 00 e3   movw    r2, #151
    1b18: 14 02 00 eb   bl      0x2370 <$a>             @ imm = #2128
    1b1c: 08 00 4b e2   sub     r0, r11, #8
    1b20: 08 10 00 e3   movw    r1, #8
    1b24: 2d 20 00 e3   movw    r2, #45
    1b28: 14 02 00 eb   bl      0x2380 <$a>             @ imm = #2128
    1b2c: 00 00 50 e3   cmp     r0, #0
    1b30: 07 00 00 0a   beq     0x1b54 <sigbus_version_optnone2+0x5c> @ imm = #28
    1b34: 90 01 9f e5   ldr     r0, [pc, #400]          @ 0x1ccc <$d.7+0x1c>
    1b38: 00 00 8f e0   add     r0, pc, r0
    1b3c: 1b 02 00 eb   bl      0x23b0 <$a>             @ imm = #2156
    1b40: 01 00 00 e3   movw    r0, #1
    1b44: 04 00 0b e5   str     r0, [r11, #-4]
    1b48: 01 00 00 e3   movw    r0, #1
    1b4c: 0c 00 0b e5   str     r0, [r11, #-12]
    1b50: 53 00 00 ea   b       0x1ca4 <sigbus_version_optnone2+0x1ac> @ imm = #332
    1b54: 08 00 1b e5   ldr     r0, [r11, #-8]
    1b58: 41 10 00 e3   movw    r1, #65
    1b5c: ff 10 01 e2   and     r1, r1, #255
    1b60: 21 20 00 e3   movw    r2, #33
    1b64: 15 02 00 eb   bl      0x23c0 <$a>             @ imm = #2132
    1b68: 01 00 00 e3   movw    r0, #1
    1b6c: 10 00 0b e5   str     r0, [r11, #-16]
    1b70: 02 00 00 e3   movw    r0, #2
    1b74: 14 00 8d e5   str     r0, [sp, #20]
    1b78: 03 00 00 e3   movw    r0, #3
    1b7c: 10 00 8d e5   str     r0, [sp, #16]
    1b80: 08 00 1b e5   ldr     r0, [r11, #-8]
    1b84: 10 10 5b e5   ldrb    r1, [r11, #-16]
    1b88: 21 10 c0 e5   strb    r1, [r0, #33]
    1b8c: 0f 10 5b e5   ldrb    r1, [r11, #-15]
    1b90: 22 10 c0 e5   strb    r1, [r0, #34]
    1b94: 0e 10 5b e5   ldrb    r1, [r11, #-14]
    1b98: 23 10 c0 e5   strb    r1, [r0, #35]
    1b9c: 0d 10 5b e5   ldrb    r1, [r11, #-13]
    1ba0: 24 10 c0 e5   strb    r1, [r0, #36]
    1ba4: 08 00 1b e5   ldr     r0, [r11, #-8]
    1ba8: 14 10 dd e5   ldrb    r1, [sp, #20]
    1bac: 25 10 c0 e5   strb    r1, [r0, #37]
    1bb0: 15 10 dd e5   ldrb    r1, [sp, #21]
    1bb4: 26 10 c0 e5   strb    r1, [r0, #38]
    1bb8: 16 10 dd e5   ldrb    r1, [sp, #22]
    1bbc: 27 10 c0 e5   strb    r1, [r0, #39]
    1bc0: 17 10 dd e5   ldrb    r1, [sp, #23]
    1bc4: 28 10 c0 e5   strb    r1, [r0, #40]
    1bc8: 08 00 1b e5   ldr     r0, [r11, #-8]
    1bcc: 10 10 dd e5   ldrb    r1, [sp, #16]
    1bd0: 29 10 c0 e5   strb    r1, [r0, #41]
    1bd4: 11 10 dd e5   ldrb    r1, [sp, #17]
    1bd8: 2a 10 c0 e5   strb    r1, [r0, #42]
    1bdc: 12 10 dd e5   ldrb    r1, [sp, #18]
    1be0: 2b 10 c0 e5   strb    r1, [r0, #43]
    1be4: 13 10 dd e5   ldrb    r1, [sp, #19]
    1be8: 2c 10 c0 e5   strb    r1, [r0, #44]
    1bec: 08 10 1b e5   ldr     r1, [r11, #-8]
    1bf0: 08 00 1b e5   ldr     r0, [r11, #-8]
    1bf4: 03 20 00 e2   and     r2, r0, #3
    1bf8: 08 00 1b e5   ldr     r0, [r11, #-8]
    1bfc: 07 30 00 e2   and     r3, r0, #7
    1c00: c0 00 9f e5   ldr     r0, [pc, #192]          @ 0x1cc8 <$d.7+0x18>
    1c04: 00 00 8f e0   add     r0, pc, r0
    1c08: d8 01 00 eb   bl      0x2370 <$a>             @ imm = #1888
    1c0c: 08 00 1b e5   ldr     r0, [r11, #-8]
    1c10: 0c 00 8d e5   str     r0, [sp, #12]
    1c14: 0c 00 9d e5   ldr     r0, [sp, #12]
    1c18: 21 10 80 e2   add     r1, r0, #33
    1c1c: 0c 00 9d e5   ldr     r0, [sp, #12]
    1c20: 21 00 80 e2   add     r0, r0, #33
    1c24: 03 20 00 e2   and     r2, r0, #3
    1c28: 94 00 9f e5   ldr     r0, [pc, #148]          @ 0x1cc4 <$d.7+0x14>
    1c2c: 00 00 8f e0   add     r0, pc, r0
    1c30: ce 01 00 eb   bl      0x2370 <$a>             @ imm = #1848
    1c34: 84 00 9f e5   ldr     r0, [pc, #132]          @ 0x1cc0 <$d.7+0x10>
    1c38: 00 00 8f e0   add     r0, pc, r0
    1c3c: cb 01 00 eb   bl      0x2370 <$a>             @ imm = #1836
    1c40: 0c 00 9d e5   ldr     r0, [sp, #12]
    1c44: 21 00 90 e5   ldr     r0, [r0, #33]
    1c48: 08 00 8d e5   str     r0, [sp, #8]
    1c4c: 0c 00 9d e5   ldr     r0, [sp, #12]
    1c50: 25 00 90 e5   ldr     r0, [r0, #37]
    1c54: 04 00 8d e5   str     r0, [sp, #4]
    1c58: 0c 00 9d e5   ldr     r0, [sp, #12]
    1c5c: 29 00 90 e5   ldr     r0, [r0, #41]
    1c60: 00 00 8d e5   str     r0, [sp]
    1c64: 00 10 9d e5   ldr     r1, [sp]
    1c68: 4c 00 9f e5   ldr     r0, [pc, #76]           @ 0x1cbc <$d.7+0xc>
    1c6c: 00 00 8f e0   add     r0, pc, r0
    1c70: be 01 00 eb   bl      0x2370 <$a>             @ imm = #1784
    1c74: 08 10 9d e5   ldr     r1, [sp, #8]
    1c78: 04 20 9d e5   ldr     r2, [sp, #4]
    1c7c: 00 30 9d e5   ldr     r3, [sp]
    1c80: 30 00 9f e5   ldr     r0, [pc, #48]           @ 0x1cb8 <$d.7+0x8>
    1c84: 00 00 8f e0   add     r0, pc, r0
    1c88: b8 01 00 eb   bl      0x2370 <$a>             @ imm = #1760
    1c8c: 08 00 1b e5   ldr     r0, [r11, #-8]
    1c90: c2 01 00 eb   bl      0x23a0 <$a>             @ imm = #1800
    1c94: 00 00 00 e3   movw    r0, #0
    1c98: 04 00 0b e5   str     r0, [r11, #-4]
    1c9c: 01 00 00 e3   movw    r0, #1
    1ca0: 0c 00 0b e5   str     r0, [r11, #-12]
    1ca4: 04 00 1b e5   ldr     r0, [r11, #-4]
    1ca8: 0b d0 a0 e1   mov     sp, r11
    1cac: 00 88 bd e8   pop     {r11, pc}

00001cb0 <$d.7>:
    1cb0:       36 ea ff ff     .word   0xffffea36
    1cb4:       36 ea ff ff     .word   0xffffea36
    1cb8:       38 e8 ff ff     .word   0xffffe838
    1cbc:       f2 e8 ff ff     .word   0xffffe8f2
    1cc0:       57 e8 ff ff     .word   0xffffe857
    1cc4:       18 e8 ff ff     .word   0xffffe818
    1cc8:       fc e8 ff ff     .word   0xffffe8fc
    1ccc:       4a eb ff ff     .word   0xffffeb4a

00001cd0 <sigbus_version_printf>:
    1cd0: 70 4c 2d e9   push    {r4, r5, r6, r10, r11, lr}
    1cd4: 10 b0 8d e2   add     r11, sp, #16
    1cd8: 08 d0 4d e2   sub     sp, sp, #8
    1cdc: 00 01 9f e5   ldr     r0, [pc, #256]          @ 0x1de4 <$d.9>
    1ce0: c5 20 a0 e3   mov     r2, #197
    1ce4: fc 10 9f e5   ldr     r1, [pc, #252]          @ 0x1de8 <$d.9+0x4>
    1ce8: 00 00 8f e0   add     r0, pc, r0
    1cec: 01 10 8f e0   add     r1, pc, r1
    1cf0: 9e 01 00 eb   bl      0x2370 <$a>             @ imm = #1656
    1cf4: 04 00 8d e2   add     r0, sp, #4
    1cf8: 08 10 a0 e3   mov     r1, #8
    1cfc: 2d 20 a0 e3   mov     r2, #45
    1d00: 9e 01 00 eb   bl      0x2380 <$a>             @ imm = #1656
    1d04: 00 00 50 e3   cmp     r0, #0
    1d08: 2f 00 00 1a   bne     0x1dcc <sigbus_version_printf+0xfc> @ imm = #188
    1d0c: 04 40 9d e5   ldr     r4, [sp, #4]
    1d10: 21 10 a0 e3   mov     r1, #33
    1d14: 41 20 a0 e3   mov     r2, #65
    1d18: 04 00 a0 e1   mov     r0, r4
    1d1c: 79 01 00 eb   bl      0x2308 <__aeabi_memset8> @ imm = #1508
    1d20: c8 00 9f e5   ldr     r0, [pc, #200]          @ 0x1df0 <$d.9+0xc>
    1d24: 03 10 a0 e3   mov     r1, #3
    1d28: 29 10 84 e5   str     r1, [r4, #41]
    1d2c: 02 10 a0 e3   mov     r1, #2
    1d30: 25 10 84 e5   str     r1, [r4, #37]
    1d34: 01 10 a0 e3   mov     r1, #1
    1d38: 00 00 8f e0   add     r0, pc, r0
    1d3c: 03 20 04 e2   and     r2, r4, #3
    1d40: 07 30 04 e2   and     r3, r4, #7
    1d44: 21 10 84 e5   str     r1, [r4, #33]
    1d48: 04 10 a0 e1   mov     r1, r4
    1d4c: 87 01 00 eb   bl      0x2370 <$a>             @ imm = #1564
    1d50: 04 60 9d e5   ldr     r6, [sp, #4]
    1d54: 98 00 9f e5   ldr     r0, [pc, #152]          @ 0x1df4 <$d.9+0x10>
    1d58: 21 10 86 e2   add     r1, r6, #33
    1d5c: 00 00 8f e0   add     r0, pc, r0
    1d60: 03 20 01 e2   and     r2, r1, #3
    1d64: 81 01 00 eb   bl      0x2370 <$a>             @ imm = #1540
    1d68: 88 00 9f e5   ldr     r0, [pc, #136]          @ 0x1df8 <$d.9+0x14>
    1d6c: 00 00 8f e0   add     r0, pc, r0
    1d70: 86 01 00 eb   bl      0x2390 <$a>             @ imm = #1560
    1d74: 80 00 9f e5   ldr     r0, [pc, #128]          @ 0x1dfc <$d.9+0x18>
    1d78: 21 40 96 e5   ldr     r4, [r6, #33]
    1d7c: 00 00 8f e0   add     r0, pc, r0
    1d80: 04 10 a0 e1   mov     r1, r4
    1d84: 79 01 00 eb   bl      0x2370 <$a>             @ imm = #1508
    1d88: 70 00 9f e5   ldr     r0, [pc, #112]          @ 0x1e00 <$d.9+0x1c>
    1d8c: 25 50 96 e5   ldr     r5, [r6, #37]
    1d90: 29 60 96 e5   ldr     r6, [r6, #41]
    1d94: 00 00 8f e0   add     r0, pc, r0
    1d98: 06 10 a0 e1   mov     r1, r6
    1d9c: 73 01 00 eb   bl      0x2370 <$a>             @ imm = #1484
    1da0: 5c 00 9f e5   ldr     r0, [pc, #92]           @ 0x1e04 <$d.9+0x20>
    1da4: 04 10 a0 e1   mov     r1, r4
    1da8: 05 20 a0 e1   mov     r2, r5
    1dac: 06 30 a0 e1   mov     r3, r6
    1db0: 00 00 8f e0   add     r0, pc, r0
    1db4: 6d 01 00 eb   bl      0x2370 <$a>             @ imm = #1460
    1db8: 04 00 9d e5   ldr     r0, [sp, #4]
    1dbc: 77 01 00 eb   bl      0x23a0 <$a>             @ imm = #1500
    1dc0: 00 00 a0 e3   mov     r0, #0
    1dc4: 10 d0 4b e2   sub     sp, r11, #16
    1dc8: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}
    1dcc: 18 00 9f e5   ldr     r0, [pc, #24]           @ 0x1dec <$d.9+0x8>
    1dd0: 00 00 8f e0   add     r0, pc, r0
    1dd4: 75 01 00 eb   bl      0x23b0 <$a>             @ imm = #1492
    1dd8: 01 00 a0 e3   mov     r0, #1
    1ddc: 10 d0 4b e2   sub     sp, r11, #16
    1de0: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}

00001de4 <$d.9>:
    1de4:       56 e8 ff ff     .word   0xffffe856
    1de8:       85 e8 ff ff     .word   0xffffe885
    1dec:       b2 e8 ff ff     .word   0xffffe8b2
    1df0:       c8 e7 ff ff     .word   0xffffe7c8
    1df4:       e8 e6 ff ff     .word   0xffffe6e8
    1df8:       2c e9 ff ff     .word   0xffffe92c
    1dfc:       0b e8 ff ff     .word   0xffffe80b
    1e00:       ca e7 ff ff     .word   0xffffe7ca
    1e04:       0c e7 ff ff     .word   0xffffe70c
    1e08:       00 f0 20 e3     .word   0xe320f000
    1e0c:       00 f0 20 e3     .word   0xe320f000

00001e10 <sigbus_version_printf_add>:
    1e10: f0 48 2d e9   push    {r4, r5, r6, r7, r11, lr}
    1e14: 10 b0 8d e2   add     r11, sp, #16
    1e18: 08 d0 4d e2   sub     sp, sp, #8
    1e1c: 2c 01 9f e5   ldr     r0, [pc, #300]          @ 0x1f50 <$d.11+0x10>
    1e20: f4 20 a0 e3   mov     r2, #244
    1e24: 28 11 9f e5   ldr     r1, [pc, #296]          @ 0x1f54 <$d.11+0x14>
    1e28: 00 00 8f e0   add     r0, pc, r0
    1e2c: 01 10 8f e0   add     r1, pc, r1
    1e30: 4e 01 00 eb   bl      0x2370 <$a>             @ imm = #1336
    1e34: 04 00 8d e2   add     r0, sp, #4
    1e38: 08 10 a0 e3   mov     r1, #8
    1e3c: 2d 20 a0 e3   mov     r2, #45
    1e40: 4e 01 00 eb   bl      0x2380 <$a>             @ imm = #1336
    1e44: 00 00 50 e3   cmp     r0, #0
    1e48: 34 00 00 1a   bne     0x1f20 <sigbus_version_printf_add+0x110> @ imm = #208
    1e4c: 04 10 9d e5   ldr     r1, [sp, #4]
    1e50: 41 21 04 e3   movw    r2, #16705
    1e54: e4 00 8f e2   add     r0, pc, #228
    1e58: 41 21 44 e3   movt    r2, #16705
    1e5c: ef 0a 60 f4   vld1.64 {d16, d17}, [r0:128]
    1e60: 41 30 a0 e3   mov     r3, #65
    1e64: f0 00 9f e5   ldr     r0, [pc, #240]          @ 0x1f5c <$d.11+0x1c>
    1e68: 04 20 81 e5   str     r2, [r1, #4]
    1e6c: 08 20 81 e5   str     r2, [r1, #8]
    1e70: 00 00 8f e0   add     r0, pc, r0
    1e74: 0c 20 81 e5   str     r2, [r1, #12]
    1e78: 10 20 81 e5   str     r2, [r1, #16]
    1e7c: 14 20 81 e5   str     r2, [r1, #20]
    1e80: 18 20 81 e5   str     r2, [r1, #24]
    1e84: 00 20 81 e5   str     r2, [r1]
    1e88: 1d 20 81 e2   add     r2, r1, #29
    1e8c: 1c 30 c1 e5   strb    r3, [r1, #28]
    1e90: 07 30 01 e2   and     r3, r1, #7
    1e94: 0f 0a 42 f4   vst1.8  {d16, d17}, [r2]
    1e98: 03 20 01 e2   and     r2, r1, #3
    1e9c: 33 01 00 eb   bl      0x2370 <$a>             @ imm = #1228
    1ea0: 04 70 9d e5   ldr     r7, [sp, #4]
    1ea4: b4 00 9f e5   ldr     r0, [pc, #180]          @ 0x1f60 <$d.11+0x20>
    1ea8: 1d 10 87 e2   add     r1, r7, #29
    1eac: 00 00 8f e0   add     r0, pc, r0
    1eb0: 03 20 01 e2   and     r2, r1, #3
    1eb4: 2d 01 00 eb   bl      0x2370 <$a>             @ imm = #1204
    1eb8: a4 00 9f e5   ldr     r0, [pc, #164]          @ 0x1f64 <$d.11+0x24>
    1ebc: 00 00 8f e0   add     r0, pc, r0
    1ec0: 32 01 00 eb   bl      0x2390 <$a>             @ imm = #1224
    1ec4: 9c 00 9f e5   ldr     r0, [pc, #156]          @ 0x1f68 <$d.11+0x28>
    1ec8: 1d 40 97 e5   ldr     r4, [r7, #29]
    1ecc: 00 00 8f e0   add     r0, pc, r0
    1ed0: 04 10 a0 e1   mov     r1, r4
    1ed4: 25 01 00 eb   bl      0x2370 <$a>             @ imm = #1172
    1ed8: 8c 00 9f e5   ldr     r0, [pc, #140]          @ 0x1f6c <$d.11+0x2c>
    1edc: 21 70 87 e2   add     r7, r7, #33
    1ee0: 00 00 8f e0   add     r0, pc, r0
    1ee4: e0 00 97 e8   ldm     r7, {r5, r6, r7}
    1ee8: 07 10 a0 e1   mov     r1, r7
    1eec: 1f 01 00 eb   bl      0x2370 <$a>             @ imm = #1148
    1ef0: 78 00 9f e5   ldr     r0, [pc, #120]          @ 0x1f70 <$d.11+0x30>
    1ef4: 04 10 a0 e1   mov     r1, r4
    1ef8: 05 20 a0 e1   mov     r2, r5
    1efc: 06 30 a0 e1   mov     r3, r6
    1f00: 00 00 8f e0   add     r0, pc, r0
    1f04: 00 70 8d e5   str     r7, [sp]
    1f08: 18 01 00 eb   bl      0x2370 <$a>             @ imm = #1120
    1f0c: 04 00 9d e5   ldr     r0, [sp, #4]
    1f10: 22 01 00 eb   bl      0x23a0 <$a>             @ imm = #1160
    1f14: 00 00 a0 e3   mov     r0, #0
    1f18: 10 d0 4b e2   sub     sp, r11, #16
    1f1c: f0 88 bd e8   pop     {r4, r5, r6, r7, r11, pc}
    1f20: 30 00 9f e5   ldr     r0, [pc, #48]           @ 0x1f58 <$d.11+0x18>
    1f24: 00 00 8f e0   add     r0, pc, r0
    1f28: 20 01 00 eb   bl      0x23b0 <$a>             @ imm = #1152
    1f2c: 01 00 a0 e3   mov     r0, #1
    1f30: 10 d0 4b e2   sub     sp, r11, #16
    1f34: f0 88 bd e8   pop     {r4, r5, r6, r7, r11, pc}
    1f38: 00 f0 20 e3   nop
    1f3c: 00 f0 20 e3   nop

00001f40 <$d.11>:
    1f40:       00 00 00 00     .word   0x00000000
    1f44:       01 00 00 00     .word   0x00000001
    1f48:       02 00 00 00     .word   0x00000002
    1f4c:       03 00 00 00     .word   0x00000003
    1f50:       16 e7 ff ff     .word   0xffffe716
    1f54:       f8 e6 ff ff     .word   0xffffe6f8
    1f58:       5e e7 ff ff     .word   0xffffe75e
    1f5c:       90 e6 ff ff     .word   0xffffe690
    1f60:       3b e7 ff ff     .word   0xffffe73b
    1f64:       08 e8 ff ff     .word   0xffffe808
    1f68:       bb e6 ff ff     .word   0xffffe6bb
    1f6c:       7e e6 ff ff     .word   0xffffe67e
    1f70:       a9 e6 ff ff     .word   0xffffe6a9

00001f74 <sigbus_version_optnone3>:
    1f74: 00 48 2d e9   push    {r11, lr}
    1f78: 0d b0 a0 e1   mov     r11, sp
    1f7c: 38 d0 4d e2   sub     sp, sp, #56
    1f80: f4 01 9f e5   ldr     r0, [pc, #500]          @ 0x217c <$d.13>
    1f84: 00 00 8f e0   add     r0, pc, r0
    1f88: f0 11 9f e5   ldr     r1, [pc, #496]          @ 0x2180 <$d.13+0x4>
    1f8c: 01 10 8f e0   add     r1, pc, r1
    1f90: 27 21 00 e3   movw    r2, #295
    1f94: f5 00 00 eb   bl      0x2370 <$a>             @ imm = #980
    1f98: 08 00 4b e2   sub     r0, r11, #8
    1f9c: 08 10 00 e3   movw    r1, #8
    1fa0: 2d 20 00 e3   movw    r2, #45
    1fa4: f5 00 00 eb   bl      0x2380 <$a>             @ imm = #980
    1fa8: 00 00 50 e3   cmp     r0, #0
    1fac: 07 00 00 0a   beq     0x1fd0 <sigbus_version_optnone3+0x5c> @ imm = #28
    1fb0: e4 01 9f e5   ldr     r0, [pc, #484]          @ 0x219c <$d.13+0x20>
    1fb4: 00 00 8f e0   add     r0, pc, r0
    1fb8: fc 00 00 eb   bl      0x23b0 <$a>             @ imm = #1008
    1fbc: 01 00 00 e3   movw    r0, #1
    1fc0: 04 00 0b e5   str     r0, [r11, #-4]
    1fc4: 01 00 00 e3   movw    r0, #1
    1fc8: 0c 00 0b e5   str     r0, [r11, #-12]
    1fcc: 67 00 00 ea   b       0x2170 <sigbus_version_optnone3+0x1fc> @ imm = #412
    1fd0: 08 00 1b e5   ldr     r0, [r11, #-8]
    1fd4: 41 10 00 e3   movw    r1, #65
    1fd8: ff 10 01 e2   and     r1, r1, #255
    1fdc: 1d 20 00 e3   movw    r2, #29
    1fe0: f6 00 00 eb   bl      0x23c0 <$a>             @ imm = #984
    1fe4: 00 00 00 e3   movw    r0, #0
    1fe8: 10 00 0b e5   str     r0, [r11, #-16]
    1fec: 01 00 00 e3   movw    r0, #1
    1ff0: 14 00 0b e5   str     r0, [r11, #-20]
    1ff4: 02 00 00 e3   movw    r0, #2
    1ff8: 18 00 0b e5   str     r0, [r11, #-24]
    1ffc: 03 00 00 e3   movw    r0, #3
    2000: 1c 00 8d e5   str     r0, [sp, #28]
    2004: 08 00 1b e5   ldr     r0, [r11, #-8]
    2008: 10 10 5b e5   ldrb    r1, [r11, #-16]
    200c: 1d 10 c0 e5   strb    r1, [r0, #29]
    2010: 0f 10 5b e5   ldrb    r1, [r11, #-15]
    2014: 1e 10 c0 e5   strb    r1, [r0, #30]
    2018: 0e 10 5b e5   ldrb    r1, [r11, #-14]
    201c: 1f 10 c0 e5   strb    r1, [r0, #31]
    2020: 0d 10 5b e5   ldrb    r1, [r11, #-13]
    2024: 20 10 c0 e5   strb    r1, [r0, #32]
    2028: 08 00 1b e5   ldr     r0, [r11, #-8]
    202c: 14 10 5b e5   ldrb    r1, [r11, #-20]
    2030: 21 10 c0 e5   strb    r1, [r0, #33]
    2034: 13 10 5b e5   ldrb    r1, [r11, #-19]
    2038: 22 10 c0 e5   strb    r1, [r0, #34]
    203c: 12 10 5b e5   ldrb    r1, [r11, #-18]
    2040: 23 10 c0 e5   strb    r1, [r0, #35]
    2044: 11 10 5b e5   ldrb    r1, [r11, #-17]
    2048: 24 10 c0 e5   strb    r1, [r0, #36]
    204c: 08 00 1b e5   ldr     r0, [r11, #-8]
    2050: 18 10 5b e5   ldrb    r1, [r11, #-24]
    2054: 25 10 c0 e5   strb    r1, [r0, #37]
    2058: 17 10 5b e5   ldrb    r1, [r11, #-23]
    205c: 26 10 c0 e5   strb    r1, [r0, #38]
    2060: 16 10 5b e5   ldrb    r1, [r11, #-22]
    2064: 27 10 c0 e5   strb    r1, [r0, #39]
    2068: 15 10 5b e5   ldrb    r1, [r11, #-21]
    206c: 28 10 c0 e5   strb    r1, [r0, #40]
    2070: 08 00 1b e5   ldr     r0, [r11, #-8]
    2074: 1c 10 dd e5   ldrb    r1, [sp, #28]
    2078: 29 10 c0 e5   strb    r1, [r0, #41]
    207c: 1d 10 dd e5   ldrb    r1, [sp, #29]
    2080: 2a 10 c0 e5   strb    r1, [r0, #42]
    2084: 1e 10 dd e5   ldrb    r1, [sp, #30]
    2088: 2b 10 c0 e5   strb    r1, [r0, #43]
    208c: 1f 10 dd e5   ldrb    r1, [sp, #31]
    2090: 2c 10 c0 e5   strb    r1, [r0, #44]
    2094: 08 10 1b e5   ldr     r1, [r11, #-8]
    2098: 08 00 1b e5   ldr     r0, [r11, #-8]
    209c: 03 20 00 e2   and     r2, r0, #3
    20a0: 08 00 1b e5   ldr     r0, [r11, #-8]
    20a4: 07 30 00 e2   and     r3, r0, #7
    20a8: e8 00 9f e5   ldr     r0, [pc, #232]          @ 0x2198 <$d.13+0x1c>
    20ac: 00 00 8f e0   add     r0, pc, r0
    20b0: ae 00 00 eb   bl      0x2370 <$a>             @ imm = #696
    20b4: 08 00 1b e5   ldr     r0, [r11, #-8]
    20b8: 18 00 8d e5   str     r0, [sp, #24]
    20bc: 18 00 9d e5   ldr     r0, [sp, #24]
    20c0: 1d 10 80 e2   add     r1, r0, #29
    20c4: 18 00 9d e5   ldr     r0, [sp, #24]
    20c8: 1d 00 80 e2   add     r0, r0, #29
    20cc: 03 20 00 e2   and     r2, r0, #3
    20d0: bc 00 9f e5   ldr     r0, [pc, #188]          @ 0x2194 <$d.13+0x18>
    20d4: 00 00 8f e0   add     r0, pc, r0
    20d8: a4 00 00 eb   bl      0x2370 <$a>             @ imm = #656
    20dc: ac 00 9f e5   ldr     r0, [pc, #172]          @ 0x2190 <$d.13+0x14>
    20e0: 00 00 8f e0   add     r0, pc, r0
    20e4: a1 00 00 eb   bl      0x2370 <$a>             @ imm = #644
    20e8: 18 00 9d e5   ldr     r0, [sp, #24]
    20ec: 1d 00 90 e5   ldr     r0, [r0, #29]
    20f0: 14 00 8d e5   str     r0, [sp, #20]
    20f4: 14 10 9d e5   ldr     r1, [sp, #20]
    20f8: 8c 00 9f e5   ldr     r0, [pc, #140]          @ 0x218c <$d.13+0x10>
    20fc: 00 00 8f e0   add     r0, pc, r0
    2100: 9a 00 00 eb   bl      0x2370 <$a>             @ imm = #616
    2104: 18 00 9d e5   ldr     r0, [sp, #24]
    2108: 21 00 90 e5   ldr     r0, [r0, #33]
    210c: 10 00 8d e5   str     r0, [sp, #16]
    2110: 18 00 9d e5   ldr     r0, [sp, #24]
    2114: 25 00 90 e5   ldr     r0, [r0, #37]
    2118: 0c 00 8d e5   str     r0, [sp, #12]
    211c: 18 00 9d e5   ldr     r0, [sp, #24]
    2120: 29 00 90 e5   ldr     r0, [r0, #41]
    2124: 08 00 8d e5   str     r0, [sp, #8]
    2128: 08 10 9d e5   ldr     r1, [sp, #8]
    212c: 54 00 9f e5   ldr     r0, [pc, #84]           @ 0x2188 <$d.13+0xc>
    2130: 00 00 8f e0   add     r0, pc, r0
    2134: 8d 00 00 eb   bl      0x2370 <$a>             @ imm = #564
    2138: 14 10 9d e5   ldr     r1, [sp, #20]
    213c: 10 20 9d e5   ldr     r2, [sp, #16]
    2140: 0c 30 9d e5   ldr     r3, [sp, #12]
    2144: 08 c0 9d e5   ldr     r12, [sp, #8]
    2148: 34 00 9f e5   ldr     r0, [pc, #52]           @ 0x2184 <$d.13+0x8>
    214c: 00 00 8f e0   add     r0, pc, r0
    2150: 00 c0 8d e5   str     r12, [sp]
    2154: 85 00 00 eb   bl      0x2370 <$a>             @ imm = #532
    2158: 08 00 1b e5   ldr     r0, [r11, #-8]
    215c: 8f 00 00 eb   bl      0x23a0 <$a>             @ imm = #572
    2160: 00 00 00 e3   movw    r0, #0
    2164: 04 00 0b e5   str     r0, [r11, #-4]
    2168: 01 00 00 e3   movw    r0, #1
    216c: 0c 00 0b e5   str     r0, [r11, #-12]
    2170: 04 00 1b e5   ldr     r0, [r11, #-4]
    2174: 0b d0 a0 e1   mov     sp, r11
    2178: 00 88 bd e8   pop     {r11, pc}

0000217c <$d.13>:
    217c:       ba e5 ff ff     .word   0xffffe5ba
    2180:       eb e4 ff ff     .word   0xffffe4eb
    2184:       5d e4 ff ff     .word   0xffffe45d
    2188:       2e e4 ff ff     .word   0xffffe42e
    218c:       8b e4 ff ff     .word   0xffffe48b
    2190:       3a e5 ff ff     .word   0xffffe53a
    2194:       13 e5 ff ff     .word   0xffffe513
    2198:       54 e4 ff ff     .word   0xffffe454
    219c:       ce e6 ff ff     .word   0xffffe6ce

000021a0 <normal_version>:
    21a0: 70 4c 2d e9   push    {r4, r5, r6, r10, r11, lr}
    21a4: 10 b0 8d e2   add     r11, sp, #16
    21a8: 08 d0 4d e2   sub     sp, sp, #8
    21ac: 04 01 9f e5   ldr     r0, [pc, #260]          @ 0x22b8 <$d.15>
    21b0: 56 2f a0 e3   mov     r2, #344
    21b4: 00 11 9f e5   ldr     r1, [pc, #256]          @ 0x22bc <$d.15+0x4>
    21b8: 00 00 8f e0   add     r0, pc, r0
    21bc: 01 10 8f e0   add     r1, pc, r1
    21c0: 6a 00 00 eb   bl      0x2370 <$a>             @ imm = #424
    21c4: 04 00 8d e2   add     r0, sp, #4
    21c8: 08 10 a0 e3   mov     r1, #8
    21cc: 2c 20 a0 e3   mov     r2, #44
    21d0: 6a 00 00 eb   bl      0x2380 <$a>             @ imm = #424
    21d4: 00 00 50 e3   cmp     r0, #0
    21d8: 30 00 00 1a   bne     0x22a0 <normal_version+0x100> @ imm = #192
    21dc: 04 10 9d e5   ldr     r1, [sp, #4]
    21e0: 41 21 04 e3   movw    r2, #16705
    21e4: 41 21 44 e3   movt    r2, #16705
    21e8: d4 00 9f e5   ldr     r0, [pc, #212]          @ 0x22c4 <$d.15+0xc>
    21ec: 07 30 01 e2   and     r3, r1, #7
    21f0: 04 20 81 e5   str     r2, [r1, #4]
    21f4: 00 00 8f e0   add     r0, pc, r0
    21f8: 08 20 81 e5   str     r2, [r1, #8]
    21fc: 0c 20 81 e5   str     r2, [r1, #12]
    2200: 10 20 81 e5   str     r2, [r1, #16]
    2204: 14 20 81 e5   str     r2, [r1, #20]
    2208: 18 20 81 e5   str     r2, [r1, #24]
    220c: 1c 20 81 e5   str     r2, [r1, #28]
    2210: 00 20 81 e5   str     r2, [r1]
    2214: 03 20 a0 e3   mov     r2, #3
    2218: 28 20 81 e5   str     r2, [r1, #40]
    221c: 02 20 a0 e3   mov     r2, #2
    2220: 24 20 81 e5   str     r2, [r1, #36]
    2224: 01 20 a0 e3   mov     r2, #1
    2228: 20 20 81 e5   str     r2, [r1, #32]
    222c: 03 20 01 e2   and     r2, r1, #3
    2230: 4e 00 00 eb   bl      0x2370 <$a>             @ imm = #312
    2234: 04 60 9d e5   ldr     r6, [sp, #4]
    2238: 88 00 9f e5   ldr     r0, [pc, #136]          @ 0x22c8 <$d.15+0x10>
    223c: 20 20 86 e2   add     r2, r6, #32
    2240: 21 10 86 e2   add     r1, r6, #33
    2244: 00 00 8f e0   add     r0, pc, r0
    2248: 03 20 02 e2   and     r2, r2, #3
    224c: 47 00 00 eb   bl      0x2370 <$a>             @ imm = #284
    2250: 74 00 9f e5   ldr     r0, [pc, #116]          @ 0x22cc <$d.15+0x14>
    2254: 00 00 8f e0   add     r0, pc, r0
    2258: 4c 00 00 eb   bl      0x2390 <$a>             @ imm = #304
    225c: 6c 00 9f e5   ldr     r0, [pc, #108]          @ 0x22d0 <$d.15+0x18>
    2260: 20 60 86 e2   add     r6, r6, #32
    2264: 00 00 8f e0   add     r0, pc, r0
    2268: 70 00 96 e8   ldm     r6, {r4, r5, r6}
    226c: 06 10 a0 e1   mov     r1, r6
    2270: 3e 00 00 eb   bl      0x2370 <$a>             @ imm = #248
    2274: 58 00 9f e5   ldr     r0, [pc, #88]           @ 0x22d4 <$d.15+0x1c>
    2278: 04 10 a0 e1   mov     r1, r4
    227c: 05 20 a0 e1   mov     r2, r5
    2280: 06 30 a0 e1   mov     r3, r6
    2284: 00 00 8f e0   add     r0, pc, r0
    2288: 38 00 00 eb   bl      0x2370 <$a>             @ imm = #224
    228c: 04 00 9d e5   ldr     r0, [sp, #4]
    2290: 42 00 00 eb   bl      0x23a0 <$a>             @ imm = #264
    2294: 00 00 a0 e3   mov     r0, #0
    2298: 10 d0 4b e2   sub     sp, r11, #16
    229c: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}
    22a0: 18 00 9f e5   ldr     r0, [pc, #24]           @ 0x22c0 <$d.15+0x8>
    22a4: 00 00 8f e0   add     r0, pc, r0
    22a8: 40 00 00 eb   bl      0x23b0 <$a>             @ imm = #256
    22ac: 01 00 a0 e3   mov     r0, #1
    22b0: 10 d0 4b e2   sub     sp, r11, #16
    22b4: 70 8c bd e8   pop     {r4, r5, r6, r10, r11, pc}

000022b8 <$d.15>:
    22b8:       86 e3 ff ff     .word   0xffffe386
    22bc:       b7 e4 ff ff     .word   0xffffe4b7
    22c0:       de e3 ff ff     .word   0xffffe3de
    22c4:       0c e3 ff ff     .word   0xffffe30c
    22c8:       00 e2 ff ff     .word   0xffffe200
    22cc:       f3 e3 ff ff     .word   0xffffe3f3
    22d0:       fa e2 ff ff     .word   0xffffe2fa
    22d4:       38 e2 ff ff     .word   0xffffe238

000022d8 <main>:
    22d8: 00 48 2d e9   push    {r11, lr}
    22dc: 0d b0 a0 e1   mov     r11, sp
    22e0: ae ff ff eb   bl      0x21a0 <normal_version> @ imm = #-328
    22e4: 29 fd ff eb   bl      0x1790 <memcpy_version> @ imm = #-2908
    22e8: 78 fe ff eb   bl      0x1cd0 <sigbus_version_printf> @ imm = #-1568
    22ec: b8 fd ff eb   bl      0x19d4 <sigbus_version_optnone1> @ imm = #-2336
    22f0: 00 fe ff eb   bl      0x1af8 <sigbus_version_optnone2> @ imm = #-2048
    22f4: 1e ff ff eb   bl      0x1f74 <sigbus_version_optnone3> @ imm = #-904
    22f8: c4 fe ff eb   bl      0x1e10 <sigbus_version_printf_add> @ imm = #-1264
    22fc: 6c fd ff eb   bl      0x18b4 <sigbus_version> @ imm = #-2640
    2300: 00 00 a0 e3   mov     r0, #0
    2304: 00 88 bd e8   pop     {r11, pc}

00002308 <__aeabi_memset8>:
    2308: 01 30 a0 e1   mov     r3, r1
    230c: 02 10 a0 e1   mov     r1, r2
    2310: 03 20 a0 e1   mov     r2, r3
    2314: 29 00 00 ea   b       0x23c0 <$a>             @ imm = #164

00002318 <__aeabi_memclr8>:
    2318: 01 20 a0 e1   mov     r2, r1
    231c: 00 10 b0 e3   movs    r1, #0
    2320: 26 00 00 ea   b       0x23c0 <$a>             @ imm = #152

Disassembly of section .plt:

00002330 <$a>:
    2330: 04 e0 2d e5   str     lr, [sp, #-4]!
    2334: 00 e6 8f e2   add     lr, pc, #0, #12
    2338: 01 ea 8e e2   add     lr, lr, #4096
    233c: ac f1 be e5   ldr     pc, [lr, #428]!

00002340 <$d>:
    2340:       d4 d4 d4 d4     .word   0xd4d4d4d4
    2344:       d4 d4 d4 d4     .word   0xd4d4d4d4
    2348:       d4 d4 d4 d4     .word   0xd4d4d4d4
    234c:       d4 d4 d4 d4     .word   0xd4d4d4d4

00002350 <$a>:
    2350: 00 c6 8f e2   add     r12, pc, #0, #12
    2354: 01 ca 8c e2   add     r12, r12, #4096
    2358: 94 f1 bc e5   ldr     pc, [r12, #404]!

0000235c <$d>:
    235c:       d4 d4 d4 d4     .word   0xd4d4d4d4

00002360 <$a>:
    2360: 00 c6 8f e2   add     r12, pc, #0, #12
    2364: 01 ca 8c e2   add     r12, r12, #4096
    2368: 88 f1 bc e5   ldr     pc, [r12, #392]!

0000236c <$d>:
    236c:       d4 d4 d4 d4     .word   0xd4d4d4d4

00002370 <$a>:
    2370: 00 c6 8f e2   add     r12, pc, #0, #12
    2374: 01 ca 8c e2   add     r12, r12, #4096
    2378: 7c f1 bc e5   ldr     pc, [r12, #380]!

0000237c <$d>:
    237c:       d4 d4 d4 d4     .word   0xd4d4d4d4

00002380 <$a>:
    2380: 00 c6 8f e2   add     r12, pc, #0, #12
    2384: 01 ca 8c e2   add     r12, r12, #4096
    2388: 70 f1 bc e5   ldr     pc, [r12, #368]!

0000238c <$d>:
    238c:       d4 d4 d4 d4     .word   0xd4d4d4d4

00002390 <$a>:
    2390: 00 c6 8f e2   add     r12, pc, #0, #12
    2394: 01 ca 8c e2   add     r12, r12, #4096
    2398: 64 f1 bc e5   ldr     pc, [r12, #356]!

0000239c <$d>:
    239c:       d4 d4 d4 d4     .word   0xd4d4d4d4

000023a0 <$a>:
    23a0: 00 c6 8f e2   add     r12, pc, #0, #12
    23a4: 01 ca 8c e2   add     r12, r12, #4096
    23a8: 58 f1 bc e5   ldr     pc, [r12, #344]!

000023ac <$d>:
    23ac:       d4 d4 d4 d4     .word   0xd4d4d4d4

000023b0 <$a>:
    23b0: 00 c6 8f e2   add     r12, pc, #0, #12
    23b4: 01 ca 8c e2   add     r12, r12, #4096
    23b8: 4c f1 bc e5   ldr     pc, [r12, #332]!

000023bc <$d>:
    23bc:       d4 d4 d4 d4     .word   0xd4d4d4d4

000023c0 <$a>:
    23c0: 00 c6 8f e2   add     r12, pc, #0, #12
    23c4: 01 ca 8c e2   add     r12, r12, #4096
    23c8: 40 f1 bc e5   ldr     pc, [r12, #320]!

000023cc <$d>:
    23cc:       d4 d4 d4 d4     .word   0xd4d4d4d4
console:/data/hj # ./sigbus
normal_version[344]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cb1 (offset=33, mod4=0)
Attempting unaligned access at offset 32...
hejian read3 = 3
Success (unexpected on ARM64!): 1, 2, 3
memcpy_version[8]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cb1 (offset=33, mod4=1)
Attempting unaligned access at offset 33...
hejian read3 = 3
Success (unexpected on ARM64!): 1, 2, 3
sigbus_version_printf[197]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cb1 (offset=33, mod4=1)
Attempting unaligned access at offset 33...
hejian read1 = 1
hejian read3 = 3
Success (unexpected on ARM64!): 1, 2, 3
sigbus_version_optnone1[103]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cb1 (offset=33, mod4=1)
Attempting unaligned access at offset 33...
hejian read3 = 3
Success (unexpected on ARM64!): 1, 2, 3
sigbus_version_optnone2[151]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cb1 (offset=33, mod4=1)
Attempting unaligned access at offset 33...
hejian read3 = 3
Success (unexpected on ARM64!): 1, 2, 3
sigbus_version_optnone3[295]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cad (offset=29, mod4=1)
Attempting unaligned access at offset 29...
hejian read1 = 0
hejian read3 = 3
Success (unexpected on ARM64!): 0 1, 2, 3
sigbus_version_printf_add[244]
Base addr: 0xf27c0c90 (mod4=0, mod8=0)
Target addr for 1st int: 0xf27c0cad (offset=29, mod4=1)
Attempting unaligned access at offset 29...
hejian read1 = 0
Bus error
135|console:/data/hj #
*/
