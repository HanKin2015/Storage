/**
* 文 件 名: dynamic_cast.cpp
* 文件描述: 学习dynamic_cast的使用
* 备    注: 想知道向下转型后会不会给派生类新的成员赋值
* 作    者: HanKin
* 创建日期: 2022.07.02
* 修改日期：2022.07.02
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <typeinfo>
#include <string>
#include <cstdio>
#include <cstring>
#include <cxxabi.h>
using namespace std;

// 基类
class base
{
public:
    // 构造函数
    base() {
        //cout << "base~~~" << endl;
    }
    
    // 析构函数
    virtual ~base() {}

    // 虚函数
    virtual void print() {
        cout << "we are in base" << endl;
    }
    
    void *extend;
    
protected:
private:
};

// 派生类
class derived : public base
{
public:
    derived() {}
    ~derived() {}

    void print() {
        cout << "we are in derived" << endl;
    }
    
    int *element;
protected:
private:
};

/*
向下转换失败
*/
static int failed()
{
    base *base_obj = new base;
    cout << typeid(*base_obj).name() << endl;                   // 注意这里需要添加*
    
    int tmp = 123;
    base_obj->extend = &tmp;
    printf("%p, %d\n", base_obj->extend, *((int *)base_obj->extend));
    
    derived *derived_obj = dynamic_cast<derived *>(base_obj);   //base_obj实际指向base，不能转化为derived
    if (derived_obj == NULL) {
        printf("dynamic_cast failed!\n");
        return -1;
    }
    
    derived_obj->print();
    printf("%p\n",derived_obj->element);
    printf("%d\n", *(derived_obj->element));
    return 0;
}


/*
向下转换成功

7derived
0x7fff9fddba74, 123
0x7fff9fddba74, 123
we are in derived
(nil)
段错误
*/
static int succeed()
{
	// 百度发现只能使用派生类初始化对象才能向下转换
	// 这岂不是一个迷惑行为，相当于是先把派生类转换成基类，即向上转换
    base *base_obj = new derived;
    cout << typeid(*base_obj).name() << endl;
    
    int tmp = 123;
    base_obj->extend = &tmp;
    printf("%p, %d\n", base_obj->extend, *((int *)base_obj->extend));
	
	/*
	dynamic_cast.cpp: In function ‘int main()’:
	dynamic_cast.cpp:100:31: error: ‘class base’ has no member named ‘element’
	  printf("%p, %d\n", base_obj->element, *((int *)base_obj->element));
								   ^
	dynamic_cast.cpp:100:59: error: ‘class base’ has no member named ‘element’
	  printf("%p, %d\n", base_obj->element, *((int *)base_obj->element));
															   ^

	printf("%p, %d\n", base_obj->element, *((int *)base_obj->element));
	*/
	
    derived *derived_obj = dynamic_cast<derived *>(base_obj);
    if (derived_obj == NULL) {
        printf("dynamic_cast failed!\n");
        return -1;
    }
    
    printf("%p, %d\n", derived_obj->extend, *((int *)derived_obj->extend));
    derived_obj->print();
    printf("%p\n",derived_obj->element);
    printf("%d\n", *(derived_obj->element));
    return 0;
}


int main()
{
	derived *son1 = new derived;
	son1->element = (int *)malloc(sizeof(int));
	*(son1->element) = 520;
	printf("son1: %p, %d\n", son1->element, *(son1->element));
	
	base *parent = son1;
	int tmp = 123;
	parent->extend = &tmp;
	printf("parent: %p, %d\n", parent->extend, *((int *)parent->extend));
	
	/*
	dynamic_cast.cpp: In function ‘int main()’:
	dynamic_cast.cpp:141:45: error: ‘class base’ has no member named ‘element’
	  printf("parent element: %p, %d\n", parent->element, *(parent->element));
												 ^
	dynamic_cast.cpp:141:64: error: ‘class base’ has no member named ‘element’
	  printf("parent element: %p, %d\n", parent->element, *(parent->element));
																	^

	printf("parent element: %p, %d\n", parent->element, *(parent->element));
	*/

	// 原来多态真的可以子类转父类后，父类是无法访问子类成员，但是子类能访问父类成员
	// 父类再转换成子类后，子类成员就能访问了
	derived *son2 = dynamic_cast<derived *>(parent);
    if (son2 == NULL) {
        printf("dynamic_cast failed!\n");
        return -1;
    }
	printf("son2 element: %p, %d\n", son2->element, *(son2->element));
	printf("son2 extend: %p, %d\n", son2->extend, *((int *)son2->extend));
    return 0;
}