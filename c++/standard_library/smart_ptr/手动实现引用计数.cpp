/*******************************************************************************
* 文 件 名: 手动实现引用计数.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class RefCount
{
private:
	int count = 0;

public:
	void increment() { ++count; }
	int decrement() { return --count; }
	int getCount() const { return count; }
};

template<typename T>
class SmartPtr
{
private:
	T *ptr;
	RefCount *ref;

public:
	explicit SmartPtr(T *p = nullptr): ptr(p)
	{
		ref = new RefCount();
		ref->increment();	// 初始化引用计数为1
	}
	
	// 拷贝构造函数
	SmartPtr(const SmartPtr& other): ptr(other.ptr), ref(other.ref)
	{
		ref->increment();	// 引用计数+1
	}
	
	// 析构函数
	~SmartPtr()
	{
		if (ref->decrement() == 0) {	// 引用计数-1
			delete ref;
			ref = nullptr;
			delete ptr;
			ptr = nullptr;
		}
	}
	
	// 赋值运算符重载
	SmartPtr& operator=(const SmartPtr& other)
	{
		if (this != &other) {
			// 释放当前资源
			if (ref->decrement() == 0) {
				delete ref;
				ref = nullptr;
				delete ptr;
				ptr = nullptr;
			}
			// 复制新资源
			ref = other.ref;
			ptr = other.ptr;
			ref->increment();
		}
		return *this;
	}
	
	// 重载解引用运算符
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};

// 使用示例
int main()
{
    SmartPtr<int> ptr1(new int(42));
    SmartPtr<int> ptr2 = ptr1; // 引用计数变为2

    *ptr2 = 99;
    std::cout << *ptr1 << std::endl; // 输出: 99

    // ptr1和ptr2离开作用域时，引用计数归零，内存自动释放
}