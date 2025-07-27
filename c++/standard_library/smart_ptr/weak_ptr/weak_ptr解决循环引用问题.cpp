/*******************************************************************************
* 文 件 名: weak_ptr解决循环引用问题.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

class Child;

class Parent {
public:
    std::shared_ptr<Child> child;  // Parent持有Child的shared_ptr
    ~Parent() { std::cout << "Parent destroyed" << std::endl; }
};

class Child {
public:
    std::weak_ptr<Parent> parent;  // Child持有Parent的weak_ptr
    ~Child() { std::cout << "Child destroyed" << std::endl; }
};

int main() {
    auto parent = std::make_shared<Parent>();
    auto child = std::make_shared<Child>();
    
    parent->child = child;
    child->parent = parent;  // weak_ptr不增加引用计数
    
    std::cout << parent.use_count() << std::endl;
    std::cout << child.use_count() << std::endl;
    
    // 离开作用域时：
    // 1. child的引用计数降为0，Child对象被销毁
    // 2. parent的引用计数降为0，Parent对象被销毁
    return 0;
}