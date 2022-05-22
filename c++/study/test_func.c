#include <stdio.h>
#define SYSTEM(cmd) \
do { \
    a = 1024; \
    printf("hello!\n"); \
} while(0)

int 
func(a, b)
	int a;
	int b;
{
	return a + b;
}

int main()
{
	int c = func(3, 6);
	printf("%d\n", c);
	
    int a;
    SYSTEM(1);
    return 0;
}
