/*******************************************************************************
* 文 件 名: factory_pattern_basic1.cpp
* 文件描述: 工厂函数基础版本
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <utility> // For std::forward
#include <iostream>

class MyClass
{
public:
    MyClass() { std::cout << "构造函数\n"; }
    ~MyClass() { std::cout << "析构函数\n"; }
    int get_data() { return data; }

private:
    int data;
};

template<typename T, typename Arg>
T* factory(Arg arg)
{
    std::cout << __func__ << std::endl;
    return new T(arg);  // 终于理解了，这个地方其实是先new一个对象，然后将arg赋值给这个新对象
}

int main()
{
    MyClass x = MyClass();
    std::cout << x.get_data() << std::endl;

    std::cout << "Creating with rvalue:\n";
    MyClass* p1 = factory<MyClass>(MyClass()); // Calls Move constructor

    std::cout << "\nCreating with lvalue:\n";
    MyClass obj;
    std::cout << "---------\n";
    MyClass* p2 = factory<MyClass>(obj); // Calls Copy constructor
    std::cout << "---------\n";
    
    delete p1;
    std::cout << "---------\n";
    delete p2;
    std::cout << "---------\n";

    // 后面会自动析构静态创建的对象
    return 0;
}