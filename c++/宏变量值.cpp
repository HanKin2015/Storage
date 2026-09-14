[10356856@LIN-EB1ACC025D1 hj]$ ./a.out
0 1 2
CLOCKS_PER_SEC = 1000000
CLOCK_BOOTTIME = 7
helloworld
e
input = 0x65
input = 0x0a
This is a 64-bit LP64 environment.
Size of int: 4 bytes
Size of long: 8 bytes
Size of pointer: 8 bytes
[10356856@LIN-EB1ACC025D1 hj]$ cat q.cpp
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#define X "hello"
#define Y X "world"

//`a##b` → **预处理器记号粘合**，用来拼接标识符（变量名），**不能直接拼字符串字面量**

int main()
{
printf("%d %d %d\n", SEEK_SET, SEEK_CUR, SEEK_END); // 0 1 2
printf("CLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);
printf("CLOCK_BOOTTIME = %d\n", CLOCK_BOOTTIME);
printf("%s\n", Y);  // helloworld
char input;
int cnt = 2;
while (cnt--) {
input = getchar();
printf("input = 0x%02x\n", input);
}
#ifdef **LP64**
std::cout << "This is a 64-bit LP64 environment." << std::endl;
std::cout <<"Size of int:" << sizeof (int) << "bytes" << std::endl;      // 通常是 4
std::cout << "Size of long:" << sizeof (long) << "bytes" << std::endl;    // 一定是 8
std::cout << "Size of pointer:" << sizeof (void*) << "bytes" << std::endl; // 一定是 8
#else
std::cout << "This is a 32-bit or non-LP64 environment." << std::endl;
#endif
return 0;
}