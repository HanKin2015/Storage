#include <iostream>
#include <cstdio>
#include <cstdlib>

int main()
{
    int *p = new int;
    *p = 123;
    printf("*p = %d\n", *p);
    
    delete p;
    p = nullptr;
    return 0;
}
