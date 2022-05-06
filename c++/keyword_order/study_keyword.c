#include <stdio.h>

// -Wold-style-declaration只对C文件生效
int main()
{
	const static int a = 12;
	static const int b = 12;
	printf("%d %d\n", a, b);
	return 0;
}
