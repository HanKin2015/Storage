/**
* 文 件 名: reflection_by_RTTI.cpp
* 文件描述: C++使用RTTI来实现基本的反射功能
* 作    者: HanKin
* 创建日期: 2024.09.23
* 修改日期：2024.09.23
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

void identify(Base* b) {
    if (typeid(*b) == typeid(Derived)) {
        std::cout << "Object is of type Derived" << std::endl;
    } else {
        std::cout << "Object is of unknown type" << std::endl;
    }
}

int main() {
    Base* b = new Derived();
    identify(b);
    delete b;
    return 0;
}
/*
Object is of type Derived
*/