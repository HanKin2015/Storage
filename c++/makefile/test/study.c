#include <stdio.h>

typedef int my_int1;
#define my_int2 int

int main()
{
	my_int1 x = 100;
	my_int2 y = 200;
	printf("x = %d, y = %d\n", x, y);
	return 0;
}
