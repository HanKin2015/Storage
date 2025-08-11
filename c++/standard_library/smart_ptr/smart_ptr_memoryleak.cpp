/*******************************************************************************
* 文 件 名: smart_ptr_memoryleak.cpp
* 文件描述: 智能指针中的内存泄漏
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

// shared_ptr的循环引用（最常见）
class B; // 前置声明
class A {
public:
    std::shared_ptr<B> b_ptr; // A持有B的shared_ptr
    ~A() { std::cout << "A被销毁" << std::endl; }
};

class B {
public:
    std::shared_ptr<A> a_ptr; // B持有A的shared_ptr
    ~B() { std::cout << "B被销毁" << std::endl; }
};

void circular_reference()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b_ptr = b; // a引用b
    b->a_ptr = a; // b引用a（形成循环）
    // 离开作用域时，a和b的引用计数均为1（互相引用），不会调用析构函数
    // 最终没有输出“A被销毁”和“B被销毁”
    return;
}

// shared_ptr管理非动态内存
void double_delete()
{
    int x = 10;
    std::shared_ptr<int> ptr(&x); // 错误：管理栈内存
    // 离开作用域时，ptr会调用delete &x，导致未定义行为（可能崩溃或内存泄露）
    return;
}

// 自定义删除器的疏漏
void bad_deleter(FILE* fp) {
    // 错误：忘记调用fclose释放文件资源
    // fclose(fp);
    std::cout << "自定义删除器的疏漏" << std::endl;
}
void custom_deleter()
{
    FILE* fp = fopen("test.txt", "w");
    std::shared_ptr<FILE> ptr(fp, bad_deleter); // 删除器未释放资源
    // 离开作用域时，文件句柄未关闭，导致资源泄露
    return;
}

// weak_ptr使用不当
void weak_ptr_example()
{
    auto parent = std::make_shared<int>();
    std::cout << parent.use_count() << std::endl;   // 1

    std::weak_ptr<int> child = parent;
    std::cout << parent.use_count() << std::endl;   // 1
}

int main()
{
    circular_reference();
    //double_delete();
    custom_deleter();
    return 0;
}