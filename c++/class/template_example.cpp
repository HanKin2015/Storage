/*******************************************************************************
* 文 件 名: template_example.cpp
* 文件描述: 类模板
* 备    注: 可以在一个文件中多次重名T
* 作    者: HanKin
* 创建日期: 2024.01.29
* 修改日期：2024.01.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
using namespace std;

// 使用typename等价于class
template <class T>
T min(T& x, T& y)
{
    return ( x < y) ? x : y;
}

template<typename T>
T * My_find(T *array,T n,T x)
{
    T* p = array;
    int i;
    for(i=0; i<n; i++) {
        if(*p == x){
            return p;
        }
        p++;
    }
    return 0;
}

template<class T>
class Operate
{
public:
    static T add(T a, T b)
    {
        return a + b;
    }
    static T Mul(T a, T b)
    {
        return a * b;
    }
    static T Judge(T a, T b = 1)
    {
        if ( a>= 0) {
            return a;
        } else {
            return a / b;
        }
    }
};

int main( )
{
    int n1 = 2, n2 = 10;
    double d1 = 1.5, d2 = 5.6;
    cout<< "较小整数:" << min(n1, n2) << endl;
    cout<< "较小实数:" << min(d1, d2) << endl;
    cout<< "较小整数:" << min<int>(n1, n2) << endl;
    cout<< "较小实数:" << min<double>(d1, d2) << endl;
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
    int *result = My_find<int>(arr, 10, 3);
    cout << (*result) << endl;  // 3
    
    int a = 3, b = 4;
    int x = Operate<int>::add(a, b);
    int y = Operate<int>::Mul(a, b);
    int z = Operate<int>::Judge(a, b);
    cout << x << " " << y << " " << z << " " << endl; // 7 12 3
    return 0;
} 