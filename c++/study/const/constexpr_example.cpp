/*******************************************************************************
* 文 件 名: constexpr_example2.cpp
* 文件描述: C++ 11 新增关键字 constexpr，用来表示 “常量” 或 常量表达式，而 const 则仅仅表示 “只读”
* 备    注: https://www.cnblogs.com/yuwanxian/p/16314066.html
* 作    者: HanKin
* 创建日期: 2024.01.03
* 修改日期：2024.01.03
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <array>
#include <ctime>
#include <cstdio>
using namespace std;
// 通过对斐波拉契函数的递归实现（求斐波那契数列第n个的值），来看看constexpr具体怎么修饰函数，同时比较这样使用的好处。
/*
这才是正解。

这两个函数的复杂度都是 O(2^n)。

这是因为每次调用 fib1 或 fib2 函数时，它都会递归地调用自身两次（除非 n 小于或等于 1）。这导致了函数调用的数量呈指数级增长，因此时间复杂度为 O(2^n)。

虽然 fib1 函数被声明为 constexpr，这意味着当所有参数都是编译时常量时，它可以在编译时被求值，但这并不改变其复杂度。无论是在编译时还是在运行时，计算斐波那契数列的这种递归方法都需要大量的函数调用，因此复杂度仍然是 O(2^n)。

如果你想要更高效地计算斐波那契数列，可以考虑使用动态规划或者矩阵快速幂等方法，这些方法的时间复杂度可以达到 O(n) 或者 O(log n)。
*/

// 由于fib1函数被constexpr修饰的，因此每一次计算的结果都会作为一个常量保存下来，复杂度等同于迭代的方法，基本上为O(n)。
constexpr long int fib1(int n) 
{ 
    return (n <= 1) ? n : fib1(n-1) + fib1(n-2);
} 

// 熟悉递归函数就不难证明下面这个函数的时间复杂度为O(2^n)
long int fib2(int n)
{
    return (n <= 1) ? n : fib2(n-1) + fib2(n-2);
}

int main()
{
    // 定义如下数组时，需要明确使用constexpr来修饰的函数
    std::array<int, fib1(10)> array1;  // 编译ok
    //std::array<int, fib2(10)> array2;  // 编译出错/*题外话：相信玩过王者荣耀的小伙伴，应该知道诸葛亮“黄金分割率”这款皮肤，台词“完美的几何学者,以斐波那契数列分割战场。”斐波那契数列：0，1，1，2，3，5，8，13，21，34，55，89，114...这个数列从第3项开始，每一项都等于前两项之和，如果设an为该数列的第n项，n属于N，那么这句话可以写成如下形式：an = an-1 + an-2。有趣的是，这样一个完全是自然数的数列，通项公式却是用无理数来表达的。而且当趋向于无穷大时，前一项与后一项的比值越来越逼近黄金分割0.618，所以它也被称为黄金数列！*/
    
    time_t timestamp;
    time(&timestamp);
    printf("当前时间戳为：%ld\n", timestamp);
    char *timestr = ctime(&timestamp);
    printf("当前时间为：%s", timestr);
    clock_t start, end;
    start = clock();    // 得到程序开始的时间
    
    //printf("fib2(45) = %ld\n", fib2(45)); // 花了8s左右
    //printf("fib1(45) = %ld\n", fib1(45)); // 花了8s左右
    constexpr long int result = fib1(45);   // 花了4ns左右
    //constexpr long int result = fib2(45); // error: call to non-constexpr function ‘long int fib2(int)’
    //long int result = fib1(45);           // 花了8s左右
    printf("result = fib1(45) = %ld\n", result);
    
    end = clock();      // 得到程序结束的时间
    time(&timestamp);
    printf("当前时间戳为：%ld\n", timestamp);
    timestr = ctime(&timestamp);
    printf("当前时间为：%s", timestr);
    cout << end - start << "(ns)" << endl;
    cout << end - start << "/" << CLOCKS_PER_SEC  << " (s) "<< endl;//CLOCKS_PER_SEC 的值其实是1000
    
    // 在 C++ 中，如果你想要在编译时计算一个值并在编译时就打印它，这通常是不可能的，因为打印是一个运行时操作。不过，你可以通过编译器错误或警告信息间接地在编译时输出一些信息。
    constexpr int ret = fib1(10); // 编译时计算 fib1(10)
    static_assert(ret == 55, "The 10th Fibonacci number should be 55");
    static int s_ret = fib1(10);    // error: the value of ‘s_ret’ is not usable in a constant expression
    static_assert(s_ret == 55, "The 10th Fibonacci number should be 55");   // error: non-constant condition for static assertion
    int non_ret = fib1(10);
    static_assert(non_ret == 55, "The 10th Fibonacci number should be 55");
    return 0;
}