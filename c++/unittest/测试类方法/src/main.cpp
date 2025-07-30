#include <iostream>
#include <memory>
#include "calculator.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<Calculator> obj = std::make_shared<Calculator>();
    obj->set_value(100);
    std::cout << obj->get_value() << std::endl;
    obj->add(123);
    std::cout << obj->get_value() << std::endl;
    return 0;
}