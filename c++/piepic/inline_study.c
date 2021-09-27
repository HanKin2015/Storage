#include <stdio.h>
#include "common.h"
//inline void func();
//void func();

static inline void func()
{
    printf("hello world!\n");
}

int main()
{
    func();

    printf("hj = %d\n", hj);
    return 0;
}
