#include <stdio.h>

//inline void func();
//void func();

static inline void func()
{
    printf("hello world!\n");
}

int main()
{
    func();
    return 0;
}
