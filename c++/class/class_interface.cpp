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

    virtual std::string GetType() = 0; // 标准的纯虚函数抽象接口类
    virtual void Swim(std::string location) { (void)location; }    // 无返回值，只给tiger使用
    virtual int GetFlags() {
        // 使用断言确保只有特定子类会调用
        assert(false && "Override this method in the specific subclass only!");
        // 或抛出异常（根据项目规范选择）：
        // throw std::runtime_error("Unimplemented pure virtual method called");
        return 0;
    }    // 显式返回无效值，表明不可达路径，只给cat使用（但是返回0有点毫无意义）
};

class Cat: public IAnimal {
public:
    Cat(std::string type, int flags, int colour): m_type(type), m_flags(flags), m_colour(colour)
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
    }
    ~Cat() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    std::string GetType() override
    {
        printf("%d: %s m_type %s\n", __LINE__, __FUNCTION__, m_type.c_str());
        return m_type;
    }

    int GetFlags() override
    {
        printf("%d: %s m_flags %d\n", __LINE__, __FUNCTION__, m_flags);
        return m_flags;
    }

    // 正确的做法
    int GetColour()
    {
        printf("%d: %s m_colour %d\n", __LINE__, __FUNCTION__, m_colour);
        return m_colour;
    }

private:
    std::string m_type;
    int m_flags;
    int m_colour;
};

class Tiger: public IAnimal {
public:
    Tiger(std::string type): m_type(type)
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
    }
    ~Tiger() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    std::string GetType() override
    {
        printf("%d: %s m_type %s\n", __LINE__, __FUNCTION__, m_type.c_str());
        return m_type;
    }

    void Swim(std::string location) override
    {
        printf("%d: %s location %s\n", __LINE__, __FUNCTION__, location.c_str());
        return;
    }

private:
    std::string m_type;
};


int main()
{
    IAnimal *cat = new Cat("cat", 123, 321);
    IAnimal *tiger = new Tiger("tiger");

    std::list<IAnimal *> animals;
    animals.push_back(cat);
    animals.push_back(tiger);

    /*
    for (const auto& animal : animals) {
        if (animal->GetType() == "tiger") {
            animal->Swim("sanya");
        } else if (animal->GetType() == "cat") {
            animal->GetFlags();
            // error: ‘class IAnimal’ has no member named ‘GetColour’
            //animal->GetColour();
        }
    }
    */

    for (const auto& animal : animals) {
        auto ptr1 = dynamic_cast<Tiger *>(animal);
        if (ptr1) {
            ptr1->Swim("sanya");
            continue;
        }
        auto ptr2 = dynamic_cast<Cat *>(animal);
        if (ptr2) {
            ptr2->GetFlags();
            ptr2->GetColour();  // 这样就能调用到独特的方法了
        }
    }
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