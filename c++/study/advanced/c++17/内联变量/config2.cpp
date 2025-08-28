#include "config.h"
#include <iostream>

void config2_print()
{
    const int *p = &kMaxSize;
    std::cout << p << ' ' << kMaxSize << std::endl;
}