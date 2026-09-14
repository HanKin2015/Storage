#include <iostream>
#include <cstdio>

struct Node {
    int x;
    int y;
    // 默认构造函数
    Node () : x (0), y (0) { printf ("默认构造函数 \n"); }
    // 带参数的构造函数
    Node (int x_, int y_) : x (x_), y (y_) { printf ("带参数的构造函数 \n"); }
    // 拷贝构造函数（如果不写，编译器会自动生成一个逐成员拷贝的版本）
    Node (const Node& other) : x (other.x), y (other.y) { printf ("拷贝构造函数 \n"); }
    // 移动构造函数（C++11 起，若不写则自动生成）
    Node (Node&& other) noexcept : x (other.x), y (other.y) { printf ("移动构造函数 \n"); }
    // 赋值运算符等也可以根据需要添加...
};

int main ()
{
    Node a (2, 5);
    Node& b (a);
    printf ("0x% x == 0x% x\n", &a, &b);
    b.x = 999;
    std::cout << a.x << std::endl; // 输出 999，证明 b 就是 a 本身
    Node c (a);
    Node d (std::move (a));
    Node& e = a;
    Node f = a;
    return 0;
}
/*
[10356856@LIN-EB1ACC025D1 hj]$ ./a.out
带参数的构造函数
0x6c419538 == 0x6c419538
999
拷贝构造函数
移动构造函数
拷贝构造函数
*/