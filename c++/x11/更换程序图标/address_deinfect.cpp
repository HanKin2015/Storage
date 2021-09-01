#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    // 被测代码：预埋一个栈溢出bug
    int num[5] = {0};
    num[5] = 100;
    printf("num[5] = %d\n", num[5]);
    return 0;
}
