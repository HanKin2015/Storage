/*******************************************************************************
* 文 件 名: intptr_t_example.c
* 文件描述: intptr_t 本质是整数类型，但它是专门设计用来安全存储指针转换后的整数值的特殊整数类型（长度与系统指针长度一致）
C99 标准为其定义了专用的格式化宏 PRIdPTR（用于有符号 intptr_t）和 PRIuPTR（用于无符号 uintptr_t），这些宏定义在 <inttypes.h> 头文件中
* 作    者: HanKin
* 备    注: u_short是 unsigned short int 的typedef别名，在 <sys/types.h> 或 <stdint.h> 中声明
* 创建日期: 2023.09.19
* 修改日期：2025.09.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

int main()
{
    int x = 10;
    int* ptr = &x;
    
    // 指针转整数（安全）
    intptr_t num = (intptr_t)ptr;
    printf("num=%ld\n", num);
    // 打印 intptr_t 的值
    printf("指针转换为 intptr_t 的值：%" PRIdPTR "\n", num);
    
    // 也可以用十六进制打印（更直观表示地址）
    printf("十六进制形式：0x%" PRIxPTR "\n", num);
    
    int xx = (intptr_t)num;
    printf("xx=%d\n", xx);
    
    printf("ptr=%p\n", ptr);
    
    // 整数转回指针（安全）
    int* ptr2 = (int*)num;
    printf("*ptr2=%d\n", *ptr2);
    
    // 上面是指针转整数，因此num存储的其实是指针值额
    void *arg = (void *)(intptr_t)x;
    int ret = (intptr_t)arg;
    printf("ret=%d\n", ret);
    return 0;
}