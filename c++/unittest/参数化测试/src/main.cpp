#include <iostream>
#include "compare_strings.h"

int main()
{
    std::cout << std::boolalpha << compare_strings("hello", "hello") << std::endl;
    std::cout << compare_strings("he llo", "hello") << std::endl;
    return 0;
}