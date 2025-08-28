#include "config.h"
#include <iostream>

void config1_print()
{
    const int *p = &kMaxSize;
    std::cout << p << ' ' << kMaxSize << std::endl;
}