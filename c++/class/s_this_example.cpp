/*******************************************************************************
* 文 件 名: s_this_example.cpp
* 文件描述: 静态this指针
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class MyClass {
private:
    int nonStaticData;
    static MyClass* currentInstance;  // 静态指针，指向当前实例

public:
    MyClass(int data) : nonStaticData(data) {
        currentInstance = this;  // 记录当前实例
    }

    // 静态成员函数，通过回调访问当前实例
    static void staticFunc() {
        if (currentInstance) {
            std::cout << currentInstance->nonStaticData << std::endl;
        }
    }
};

// 静态指针初始化
MyClass* MyClass::currentInstance = nullptr;

// 使用示例
int main()
{
    MyClass obj(42);
    MyClass::staticFunc();  // 输出: 42
    return 0;
}