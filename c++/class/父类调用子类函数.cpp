/*******************************************************************************
* 文 件 名: 父类调用子类函数.cpp
* 文件描述: 子类函数被外部调用是否需要在父类声明后才能调用
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.14
* 修改日期：2025.04.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

class Father {
public:
    Father() { printf("%d: %s\n", __LINE__, __FUNCTION__); }
    ~Father() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    virtual void PrintId() = 0;

};

class Son: public Father {
public:
    Son() { printf("%d: %s\n", __LINE__, __FUNCTION__); }
    ~Son() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    static Son* Instance() {
        static Son instance_;
        return &instance_;
    }

    void PrintId() override
    {
        printf("%d: %s id %d\n", __LINE__, __FUNCTION__, id);
        return;
    }

    void PrintNumber()
    {
        printf("%d: %s number %d\n", __LINE__, __FUNCTION__, number);
        return;
    }

private:
    int id;
    int number;
};


int main()
{
    Father *obj = new Son();
    obj->PrintId();
    //obj->PrintNumber(); // error: ‘class Father’ has no member named ‘PrintNumber’
    
    // 方法一：使用static_cast（已知类型安全时）
    static_cast<Son*>(obj)->PrintNumber();
    
    // 方法二：使用dynamic_cast（运行时类型检查，需父类有虚函数）
    if (Son* son = dynamic_cast<Son*>(obj)) {
        son->PrintNumber();
    }
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #g++ class_override.cpp -std=c++11
[root@ubuntu0006:/media/vdb] #./a.out
16: Father
25: Son
35: PrintId id 0
*/