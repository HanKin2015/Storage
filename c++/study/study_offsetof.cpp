#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
#include <stddef.h>
size_t offsetof(type, member);
C 库宏 offsetof(type, member-designator) 会生成一个类型为 size_t 的整型常量，它是一个结构成员相对于结构开头的字节偏移量。成员是由 member-designator 给定的，结构的名称是在 type 中给定的。
*/

int main(void)
{
	struct s {
		int i;
		char c;
		double d;
		char a[];
	};

	/* Output is compiler dependent */

	printf("offsets: i=%zd; c=%zd; d=%zd a=%zd\n",
			offsetof(struct s, i), offsetof(struct s, c),
			offsetof(struct s, d), offsetof(struct s, a));
	printf("sizeof(struct s)=%zd\n", sizeof(struct s));

	exit(EXIT_SUCCESS);
}

