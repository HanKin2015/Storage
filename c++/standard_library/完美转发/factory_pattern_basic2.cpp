/*******************************************************************************
* 文 件 名: factory_pattern_basic2.cpp
* 文件描述: 工厂函数基础上一步一步优化
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
    //MyClass(int data = 100): m_data(data) { std::cout << "构造函数\n"; }
    MyClass(std::string str = ""): m_str(str) { std::cout << "构造函数\n"; }
    ~MyClass() { std::cout << "析构函数\n"; }
    int get_data() { return m_data; }

private:
    // int基本数据类型的const属性可以被忽略（拷贝传递时不影响安全性）。
    // 但如果构造函数接收的是非const的自定义类型引用，则会触发你提到的编译错误
    int m_data;
    std::string m_str;
};

// 尝试1：使用左值引用
template<typename T, typename Arg>
T* factory1(Arg& arg)
{
    std::cout << __LINE__ << __func__ << std::endl;
    return new T(arg);
}
// 问题：无法接收右值， factory<MyClass>(MyClass()) 编译失败。
// error: cannot bind non-const lvalue reference of type ‘MyClass&’ to an rvalue of type ‘MyClass’

// 尝试2：使用const左值引用
template<typename T, typename Arg>
T* factory2(const Arg& arg)
{
    std::cout << __LINE__ << __func__ << std::endl;
    return new T(arg);
}
// 问题：虽然能同时接收左值和右值，但所有参数都变成了const，
// 如果构造函数需要非const参数，则编译失败。
// 构造函数参数需要添加引用符号

// 尝试3：重载
template<typename T, typename Arg>
T* factory3(Arg& arg)
{
    std::cout << __LINE__ << __func__ << std::endl;
    return new T(arg);
}

template<typename T, typename Arg>
T* factory3(Arg&& arg)
{
    std::cout << __LINE__ << __func__ << std::endl;
    return new T(arg);
}
// 问题：如果参数不止一个，你需要为每种参数组合编写 2^N 个重载版本，这会引发组合爆炸。

int main()
{
    MyClass x = MyClass();
    std::cout << x.get_data() << std::endl;

    std::cout << "Creating with rvalue:\n";
    //MyClass* p1 = factory2<MyClass, std::string>(std::string("test")); // Calls Move constructor
    MyClass* p1 = factory3<MyClass>(MyClass()); // Calls Move constructor
    // 第一个是通过test字符串传递给构造函数new对象，而第二个则是对象赋值给new对象

    std::cout << "\nCreating with lvalue:\n";
    MyClass obj;
    std::cout << "---------\n";
    MyClass* p2 = factory3<MyClass>(obj); // Calls Copy constructor
    std::cout << "---------\n";
    
    delete p1;
    std::cout << "---------\n";
    delete p2;
    std::cout << "---------\n";

    // 后面会自动析构静态创建的对象
    return 0;
}