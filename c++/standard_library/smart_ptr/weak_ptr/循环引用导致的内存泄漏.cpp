/*******************************************************************************
* 文 件 名: 循环引用导致的内存泄漏.cpp
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

class Child;  // 前向声明

class Parent {
public:
    std::shared_ptr<Child> child;  // Parent持有Child的shared_ptr
    ~Parent() { std::cout << "Parent destroyed" << std::endl; }
};

class Child {
public:
    std::shared_ptr<Parent> parent;  // Child持有Parent的shared_ptr
    ~Child() { std::cout << "Child destroyed" << std::endl; }
};

int main() {
    auto parent = std::make_shared<Parent>();
    auto child = std::make_shared<Child>();
    
    // 形成循环引用
    parent->child = child;
    child->parent = parent;
    
    std::cout << parent.use_count() << std::endl;
    std::cout << child.use_count() << std::endl;
    
    // 离开作用域时，parent和child的引用计数均为1（互相引用）
    // 因此两者都不会被销毁，导致内存泄漏
    return 0;
}