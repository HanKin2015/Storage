/*
两种指针数组的写法比较

推荐使用int *p
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAXN 256
#define RAND 5

int main()
{
    int *p;
    int *q[MAXN];
    
    p = NULL;
    //q = NULL;
    
    p = new int[MAXN];
    //q = (int *[])malloc(MAXN * sizeof(int *));
    for (int i = 0; i < MAXN; i++) {
        q[i] = (int *)malloc(sizeof(int));
    }
    
    int n = 1234;
    int *tmp = (p + RAND);
    printf("%p %p\n", tmp, p+RAND);
    *tmp = n;
    p[RAND] = n;
    q[RAND] = &n;
    
    if (p) {
        printf("*p[%d] = %d\n", RAND, *(p+RAND));
    }
    if (q) {
        printf("*q[%d] = %d\n", RAND, *q[RAND]);
    }
    if (tmp) {
        printf("*tmp = %d\n", *tmp);
    }
    printf("%p %p %p\n", p+RAND, q[RAND], tmp);
    return 0;
}
