/*******************************************************************************
* 文 件 名: advanced_example.cpp
* 文件描述: 高级用法杂烩
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.02.02
* 修改日期：2024.02.02
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <shared_mutex>
#include <utility>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iterator> 

constexpr int constexpr_example(int n)
{
    if (n <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += i;
    }
    return sum;
}

auto sum1(int i)
{
    if (i <= 1) {
        return i;               // 返回值被推导为int
    } else {
        return sum1(i - 1) + i;  // sum的返回值已经被推导出来了，所以这里是没有问题的
    }
}

// 一旦在函数中看到return语句，从该语句推导出的返回类型就可以在函数的其余部分中使用，包括在其他return语句中
// 这个一定需要使用decltype指明函数返回类型
auto sum2(int i) -> decltype(i)
{
    if (i <= 1) {
        return sum2(i - 1) + i;
    } else {
        return i;
    }
}

[[deprecated]]
void deprecated_example()
{
    std::cout << "hello world!" << std::endl;
    return;
}

std::shared_timed_mutex mtx;
void shared_lock_example()
{
    // 加读锁，离开作用域时自动解锁
    std::shared_lock<std::shared_timed_mutex> lck(mtx);
    
    // do something
    
    return;
}

void exchange_example()
{
    std::string s1 = "hello";
    std::string s2 = "world";
    std::exchange(s1, s2);
    std::cout << s1 << " " << s2 << std::endl;
    
    // 第二个值是纯右值
    std::exchange(s1, "world");
    std::cout << s1 << std::endl;

    std::string s3 = "hello world";
    // 第二个值通过move语义转成右值
    std::exchange(s1, std::move(s3));
    std::cout << s1 << " | " << s3 << std::endl;
    
    std::vector<int> v = {5, 6, 7};
    std::exchange(v, { 1,2,3,4 });
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    return;
}

// std::quoted 仅适用于输入输出流中的字符串操作，对于其他类型的数据，如数字等，不适用
void quoted_example()
{
    std::string str = "H\"el\nlo\t, \World!";
    std::cout << std::quoted(str) << std::endl;
    std::cout << "str: " << str << std::endl;
    /*
    "H\"el
    lo      , World!"
    str: H"el
    lo      , World!
    */
    
    std::string input;
    std::cin >> std::quoted(input);  // 输入："Hello, World!"
    std::cout << "Input: " << input << std::endl;  // 输出："Hello, World!"
    return;
}

void for_each_example()
{
    auto glambda = [](auto& a) { std::cout << a << " "; };
    int a[] = { 4, 2, 6, 3, 7, 5 };
    std::for_each(a, a + sizeof(a) / sizeof(int), glambda);
    std::cout << std::endl;
    return;
}

int main()
{
    // 1、可以使用0b或者0B开头直接定义二进制变量
    int val1 = 0b1011;
    int val2 = 0B1000;
    printf("%d %d\n", val1, val2);
    
    // 2、c++11中constexpr修饰函数限制严格
    constexpr_example(123);
    
    // 3、数字分隔符
    int val3 = 100000000;
    int val4 = 100'000'000;
    int val5 = 100'00'0'0'0'0;
    std::cout << val3 << " " << val4 << " " << val5 << std::endl;
    
    // 4、函数返回值推导
    sum1(5);
    
    // 5、[[deprecated]]标记
    deprecated_example();
    
    // 6、std::exchange
    exchange_example();
    
    // 7、std::quoted 
    quoted_example();
    
    // 8、for_each
    for_each_example();
    return 0;
}
