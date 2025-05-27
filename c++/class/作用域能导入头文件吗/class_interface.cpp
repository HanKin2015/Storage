/*******************************************************************************
* 文 件 名: class_interface.cpp
* 文件描述: 接口类继承时某些子类有特定的实现方法，方法具有返回值
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.13
* 修改日期：2025.05.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <list>
#include <cassert>

class IAnimal {
public:
    IAnimal() { printf("%d: %s\n", __LINE__, __FUNCTION__); }
    ~IAnimal() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    enum class HCType {
        HC_TYPE_NONE = 0,
        HC_TYPE_UHCI,
        HC_TYPE_EHCI,
        HC_TYPE_XHCI
    };
};

int main()
{
    printf("%d\n", IAnimal::HCType::HC_TYPE_UHCI);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
7: IAnimal
19: Cat
7: IAnimal
52: Tiger
25: GetType m_type cat
25: GetType m_type cat
31: GetFlags m_flags 123
58: GetType m_type tiger
64: Swim location sanya

[root@ubuntu0006:~/cmake] #./a.out
7: IAnimal
19: Cat
7: IAnimal
52: Tiger
31: GetFlags m_flags 123
38: GetColour m_colour 321
64: Swim location sanya
*/