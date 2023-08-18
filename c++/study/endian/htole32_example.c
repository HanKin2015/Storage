#include <stdio.h>
#include <arpa/inet.h>

int main()
{
	unsigned long a = 0x12345678;
	unsigned char *p = (unsigned char *)(&a);

	printf("主机字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);

	unsigned long b = htonl(a);  //将主机字节序转化成了网络字节序

	p = (unsigned char *)(&b);

	printf("网络字节序:%0x    %0x   %0x   %0x (大端字节序)\n",  p[0], p[1], p[2], p[3]);
	return 0;
}