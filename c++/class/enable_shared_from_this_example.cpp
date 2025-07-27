/*******************************************************************************
* 文 件 名: enable_shared_from_this_example.cpp
* 文件描述: 用于让类的成员函数安全地获取指向当前对象的 std::shared_ptr，避免因手动管理引用计数导致的内存问题
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

class Bad {
public:
    std::shared_ptr<Bad> getShared() {
        return std::shared_ptr<Bad>(this);  // 错误：未通过shared_ptr创建this
    }
    ~Bad() { printf("Bad destroyed\n"); }
};
/*
root@hankin:~/opencv# ./a.out 
Bad destroyed
double free or corruption (out)
已中止 (核心已转储)
*/

class Good: public std::enable_shared_from_this<Good> {
public:
    std::shared_ptr<Good> getShared() {
        return shared_from_this();  // 安全获取指向当前对象的shared_ptr
    }
    ~Good() { printf("Good destroyed\n"); }
};

int main()
{
    auto obj = std::make_shared<Good>();
    auto another = obj->getShared();  // 两个独立的shared_ptr管理同一对象
    
    // obj和another离开作用域时，双重释放同一内存
    return 0;
}