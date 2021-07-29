#include <iostream>
#include <cstdio>
#include "test_swig.hpp"
using namespace std;

int main()
{
    int x = 10, y = 8;
    
    printf("x = %d, y = %d\n", x, y);
    printf("x + y = %d\n", add(x, y));
    printf("x - y = %d\n", sub(x, y));
    return 0;
}