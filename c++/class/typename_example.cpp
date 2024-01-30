/*******************************************************************************
* 文 件 名: typename_example.cpp
* 文件描述: 相当用于泛型编程时是另一术语"class"的同义词。这个关键字用于指出模板声明（或定义）中的依赖的名称（dependent names）是类型名，而非变量名。
* 备    注: https://baike.baidu.com/item/TypeName/8832609?fr=ge_ala
            https://blog.csdn.net/www_dong/article/details/113806192
* 作    者: HanKin
* 创建日期: 2024.01.29
* 修改日期：2024.01.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
using namespace std;

template <class T>
void foo(const T& t)
{
    // 声明一个指向某个类型为T::bar的对象的指针
    // 出现上述歧义时，编译器将自动默认bar为一个变量名，而不是类型名
    //T::bar *p;
    // 使用typename关键字告诉编译器T::bar是一个类型名
    typename T::bar *p;

    // 默认识别为变量
    int q = 12;
    int y = T::x;
    int ret = (T::x *q);
    cout << ret << endl;
}

struct StructWithBarAsType
{
    typedef int bar;
    // 在C++中，静态成员变量属于类的整体，而不是类的实例。因此，当在foo函数中使用T::x时，需要确保x是一个静态成员变量，以便可以在没有类实例的情况下访问它。
    // 如果x不是静态成员变量，而是一个普通的成员变量，那么在foo函数中就无法直接通过T::x来访问它。
    static int x;
};

// 初始化静态成员变量x
int StructWithBarAsType::x = 5;

int main()
{
    StructWithBarAsType x;
    foo(x);
    return 0;
}
