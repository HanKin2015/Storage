/**
* 文 件 名: reflection_by_define_and_template.cpp
* 文件描述: C++使用宏和模板来实现基本的反射功能
* 备    注: g++ reflection_by_define_and_template.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.23
* 修改日期：2024.09.23
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

class Reflectable {
public:
    virtual ~Reflectable() {}
    virtual std::string getTypeName() const = 0;
};

#define REFLECTABLE(className) \
public: \
    static std::string staticTypeName() { return #className; } \
    virtual std::string getTypeName() const override { return staticTypeName(); }

class MyClass : public Reflectable {
    REFLECTABLE(MyClass)
};

class AnotherClass : public Reflectable {
    REFLECTABLE(AnotherClass)
};

void printTypeName(const Reflectable& obj) {
    std::cout << "Type: " << obj.getTypeName() << std::endl;
}

int main() {
    MyClass myObj;
    AnotherClass anotherObj;

    printTypeName(myObj);
    printTypeName(anotherObj);

    return 0;
}
/*
Type: MyClass
Type: AnotherClass
*/