// https://blog.csdn.net/fengxinlinux/article/details/51541003
#include <iostream>
#include <cstdio>
#include <cstdlib>

static int **func1()
{
    int (*a)[5] = (int(*)[5])malloc(sizeof(int)*4*5);
    
	int **p = NULL;
    //int (*p)[5] = a;
	//return p;
}

static int **func2()
{
    int **a = (int(**))malloc(sizeof(int*)*5);
    
	return a;
}

static int func3()
{
    const unsigned short test[][2] = {{0x1234, 0x223}, {0xabcd, 0xdcba}, {0x5434, 0x0003},};
    printf("%lu %lu %lu\n", sizeof(test), sizeof(test[0]), sizeof(test)/sizeof(test[0]));
    return 0;
}

int main()
{
    func1();
    func2();
    func3();
    return 0;
}
