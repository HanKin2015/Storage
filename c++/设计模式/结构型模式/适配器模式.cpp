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
#include <string>
#include <algorithm>

// 目标接口（Target）：客户端期望的接口
class Target {
public:
    virtual ~Target() = default;
    virtual std::string request() const {
        return "Target: The default target's behavior.";
    }
};

// 被适配者（Adaptee）：需要被适配的类
class Adaptee {
public:
    std::string specificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

// 类适配器（Class Adapter）：通过多重继承实现
class ClassAdapter : public Target, private Adaptee {
public:
    std::string request() const override {
        // 反转 Adaptee 的结果以适配 Target 接口
        std::string result = Adaptee::specificRequest();
        std::reverse(result.begin(), result.end());
        return "ClassAdapter: (TRANSLATED) " + result;
    }
};

// 对象适配器（Object Adapter）：通过组合实现
class ObjectAdapter : public Target {
private:
    Adaptee* adaptee;

public:
    ObjectAdapter(Adaptee* adaptee) : adaptee(adaptee) {}

    std::string request() const override {
        // 反转 Adaptee 的结果以适配 Target 接口
        std::string result = adaptee->specificRequest();
        std::reverse(result.begin(), result.end());
        return "ObjectAdapter: (TRANSLATED) " + result;
    }
};

// 客户端代码：使用 Target 接口
void clientCode(const Target* target) {
    std::cout << target->request() << std::endl;
}

int main() {
    std::cout << "Client: I can work just fine with the Target objects:" << std::endl;
    Target* target = new Target;
    clientCode(target);
    std::cout << std::endl;

    Adaptee* adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:" << std::endl;
    std::cout << "Adaptee: " << adaptee->specificRequest() << std::endl;
    std::cout << std::endl;

    std::cout << "Client: But I can work with it via the Adapter:" << std::endl;
    // 类适配器示例
    ClassAdapter* classAdapter = new ClassAdapter;
    clientCode(classAdapter);
    std::cout << std::endl;

    // 对象适配器示例
    ObjectAdapter* objectAdapter = new ObjectAdapter(adaptee);
    clientCode(objectAdapter);
    std::cout << std::endl;

    delete target;
    delete adaptee;
    delete classAdapter;
    delete objectAdapter;

    return 0;
}