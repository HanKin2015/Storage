/*******************************************************************************
* 文 件 名: 工厂模式.cpp
* 文件描述: 定义创建对象的接口，让子类决定实例化哪个类。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.18
* 修改日期：2025.07.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Product {
public:
    virtual void operation() = 0;
    virtual ~Product() = default;
};

class ConcreteProductA : public Product {
public:
    void operation() override { std::cout << "Product A" << std::endl; }
};

class ConcreteProductB : public Product {
public:
    void operation() override { std::cout << "Product B" << std::endl; }
};

class Factory {
public:
    virtual Product* createProduct() = 0;
    virtual ~Factory() = default;
};

class ConcreteFactoryA : public Factory {
public:
    Product* createProduct() override { return new ConcreteProductA(); }
};

class ConcreteFactoryB : public Factory {
public:
    Product* createProduct() override { return new ConcreteProductB(); }
};

int main(int argc, char **argv)
{
    Singleton *obj = Singleton::instance->getInstance();
    obj->print_info();
    return 0;
}