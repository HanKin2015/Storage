/**
* 文 件 名: class_template_example.cpp
* 文件描述: 针对不同的数据类型 比较两个数据的大小
* 作    者: HanKin
* 创建日期: 2022.09.26
* 修改日期：2022.09.26
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <list>

/*********************************************************
*T可以是任意类型
*模板实参也可以是一个int或enum类型的常量 size_t实际是int类型
*n是编译时定义的常量
*n可以有默认值
*size_t类型的成员变量可以用n初始化
***********************************************************/
const std::size_t DefaultStackSize = 1024;
template <typename T, std::size_t n=DefaultStackSize>
class Stack
{
public:
    void Push(const T &element);
    int Pop(T &element);
    //int Top(T &element) const;
    
private:
    std::vector<T> m_Members;
    std::size_t m_mMaxSize = n; 
};
 
template <typename T, std::size_t nMaxSize>
void Stack<T, nMaxSize>::Push(const T &element)
{
    if(m_mMaxSize <= m_Members.size()) {
        std::cout << "m_Members.size greater than m_mMaxSize" << std::endl;
        return;
    }
    m_Members.push_back(element);
}
 
template <typename T, std::size_t nMaxSize>
int Stack<T, nMaxSize>::Pop(T& element)
{
    if(m_Members.empty()) {
        std::cout << "m_Members is empty" << std::endl;
        return -1;
    }
    element = m_Members.back();
    m_Members.pop_back();
    return 0;
}

static void test1()
{
    Stack<int> stack;
    Stack<int, 100> stack1;
    for(int i = 0; i < 100; i++) {
        stack.Push(i);
    }
    
    int i;  // 目的是输出弹出的数值
    stack.Pop(i);
    std::cout << i << std::endl;
    stack.Pop(i);
    std::cout << i << std::endl;
    return;
}

typedef std::string TT;
template <>
class Stack<std::string>
{
public:
    void Push(const TT &element);
    int Pop(TT &element);
    //int Top(T &element) const;
private:
    std::list<std::string> m_Members;
    std::size_t m_mMaxSize; 
};

// 类模板特化
static void test2()
{
    Stack<int> stack;
    Stack<int, 100> stack1;
    for(int i = 0; i < 100; i++) {
        stack.Push(i);
    }
    
    int i;  // 目的是输出弹出的数值
    stack.Pop(i);
    std::cout << i << std::endl;
    stack.Pop(i);
    std::cout << i << std::endl;
    return;
}

// 类模板也可以偏特化 
template <typename T1,typename T2> 
class MyClass
{
};
 
//偏特化
template <typename T>
class MyClass<T,T>
{};
 
template <typename T1,typename T2>
class MyClass<T1*,T2*>
{};
 
 
template <typename T>
class MyClass<T,int>
{};

int main()
{
    test1();
    test2();
    return 0;
}