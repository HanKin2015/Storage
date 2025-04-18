/*******************************************************************************
* 文 件 名: class_private_function.cpp
* 文件描述: 外部通过对象实例是否可以访问私有函数
* 备    注: 只有在定义该类的内部可以访问，外部代码和派生类都无法访问
* 作    者: HanKin
* 创建日期: 2025.04.14
* 修改日期：2025.04.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

class Test {
public:
    Test() { printf("%d: %s\n", __LINE__, __FUNCTION__); }
    ~Test() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    static Test* Instance() {
        static Test instance_;
        return &instance_;
    }

private:
    void PrintId()
    {
        printf("%d: %s id %d\n", __LINE__, __FUNCTION__, id);
        return;
    }

private:
    int id;
};

int main()
{
    //Test::Instance()->PrintId();
    Test *t = new Test();
    t->PrintId();
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #g++ class_private_function.cpp
l.cpp: In function ‘int main()’:
l.cpp:25:10: error: ‘void Test::PrintId()’ is private
     void PrintId()
          ^
l.cpp:39:16: error: within this context
     t->PrintId();
*/