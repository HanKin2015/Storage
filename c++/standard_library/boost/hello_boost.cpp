#include <iostream>
#include "boost/version.hpp"

int main()
{
    std::cout << BOOST_LIB_VERSION << std::endl;
    std::cout << BOOST_VERSION << std::endl;
}
/*
[root@ubuntu0006:/media/hankin/vdb/boost] #./a.out
1_79
107900
*/
