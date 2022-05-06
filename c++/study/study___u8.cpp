#include <iostream>
#include <cstdio>
#include <asm-generic/int-l64.h>

#if 0
typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;

typedef __signed__ long __s64;
typedef unsigned long __u64;
#endif

int main()
{
	__u8 bLength = static_cast<__u8>(1234);
	//printf("(string) bLength = %s\n", bLength); 段错误
	printf("(char)   bLength = %c\n", bLength);
	printf("(0x)   bLength = 0x%x\n", bLength);
	return 0;
}

