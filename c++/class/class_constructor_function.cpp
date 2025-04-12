/*******************************************************************************
* 文 件 名: class_constructor_function.cpp
* 文件描述: 构造函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.12
* 修改日期：2025.04.12
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
    Test::Instance()->PrintId();
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #./a.out
16: Test
26: PrintId id 0
17: ~Test
*/