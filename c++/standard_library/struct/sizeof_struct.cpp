#include <iostream>
#include <cstdio>
using namespace std;

typedef struct _NODE {
    int x;
    int y;
    int z;
} NODE, *PNODE;

int main()
{
    PNODE pitem;
    NODE item;
    printf("%lu %lu %lu\n", sizeof(pitem), sizeof(&pitem), sizeof(item));
    print("%lu %lu\n", sizeof(int), sizeof(*pitem));
    printf("%lu, %lu\n", sizeof(&NODE), sizeof(*PNODE));    // 都是错误的演示
    printf("%lu\n", sizeof(NODE));
    return 0;
}
/*
8 8 12
4 12
*/