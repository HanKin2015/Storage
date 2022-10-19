#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

// 求两个数之间的和
int sum(int a, int b);

// 求两个数之间的和
int sum(int a, int b)
{
    return a + b;
}

// 输出hello world
static void hello()
{
    printf("hello world!\n");
}

int main(int argc, char *argv[])
{
    hello();
    int ret = sum(3, 5);
    printf("ret = %d\n", ret);
    return 0;
}
