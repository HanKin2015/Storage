#include <memory>
#include <cstdio>
#include "common.hpp"
#include <sstream>

void interface()
{
    std::shared_ptr<int> ptr = std::make_shared<int>();
    printf("%p\n", ptr.get());

    std::stringstream sstr;
    sstr << "hello world";
    printf("%s\n", sstr.str().c_str());
    return;
}
