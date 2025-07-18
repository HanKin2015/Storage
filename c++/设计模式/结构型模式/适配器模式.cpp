/*******************************************************************************
* 文 件 名: 适配器模式.cpp
* 文件描述: 定义创建对象的接口，让子类决定实例化哪个类。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.18
* 修改日期：2025.07.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 目标接口
class Target {
public:
    virtual void request() = 0;
    virtual ~Target() = default;
};

// 适配者类
class Adaptee {
public:
    void specificRequest() { std::cout << "Adaptee's specific request." << std::endl; }
};

// 类适配器（多继承实现）
class Adapter : public Target, private Adaptee {
public:
    void request() override { specificRequest(); }
};

// 对象适配器（组合实现）
class Adapter2 : public Target {
private:
    Adaptee* adaptee;
public:
    Adapter2(Adaptee* a) : adaptee(a) {}
    void request() override { adaptee->specificRequest(); }
};