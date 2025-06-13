#include <iostream>

int main()
{
#ifdef CLIENT_TYPE_MAC
    std::cout << "CLIENT_TYPE_MAC is defined!" << std::endl;
#else
    std::cout << "CLIENT_TYPE_MAC is not defined." << std::endl;
#endif

#ifdef CLIENT_TYPE_UNIX
    std::cout << "CLIENT_TYPE_UNIX is defined!" << std::endl;
#else
    std::cout << "CLIENT_TYPE_UNIX is not defined." << std::endl;
#endif
    return 0;
}
