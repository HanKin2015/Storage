/**
* 文 件 名: ref_example2.cpp
* 文件描述: ref函数的使用
* 备    注: https://blog.csdn.net/m0_51551385/article/details/123965079
* 作    者: HanKin
* 创建日期: 2023.09.01
* 修改日期：2023.09.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>
#include<vector>

using namespace std;

//std::ref主要是考虑函数式编程（如std::bind）在使用时，是对参数直接拷贝，而不是引用
void f(int& a, int& b, int& c)
{
    cout << "in function a = " << a << "  b = " << b << "  c = " << c << endl;
    cout << "in function a = " << &a << "  b = " << &b << "  c = " << &c << endl;
    a += 1;
    b += 10;
    c += 100;
}

int main() {

    int n1 = 1, n2 = 10, n3 = 100;
    int& r1 = n1;
    int& r2 = n2;

    function<void()> f1 = bind(f, r1, r2, ref(n3));		
    //前两个参数即便是引用类型，bind 传入的还是其值的拷贝，第三个参数传入 reference_wrapper 对象，该对象可隐式的转换为值的引用

    f1();
    cout << "out function a = " << n1 << "  b = " << n2 << "  c = " << n3 << endl;
    cout << "out function a = " << &n1 << "  b = " << &n2 << "  c = " << &n3 << endl;
    f1();
    cout << "out function a = " << n1 << "  b = " << n2 << "  c = " << n3 << endl;
    cout << "out function a = " << &n1 << "  b = " << &n2 << "  c = " << &n3 << endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
in function a = 1  b = 10  c = 100
in function a = 0x25bdc34  b = 0x25bdc30  c = 0x7fff230c72ec
out function a = 1  b = 10  c = 200
out function a = 0x7fff230c72e4  b = 0x7fff230c72e8  c = 0x7fff230c72ec
in function a = 2  b = 20  c = 200
in function a = 0x25bdc34  b = 0x25bdc30  c = 0x7fff230c72ec
out function a = 1  b = 10  c = 300
out function a = 0x7fff230c72e4  b = 0x7fff230c72e8  c = 0x7fff230c72ec
*/
