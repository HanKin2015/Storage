/**
* 文 件 名: variadic_template.cpp
* 文件描述: C++11 引入了变参模板（Variadic Template），它允许函数或类模板接受任意数量的参数
* 作    者: HanKin
* 创建日期: 2024.01.22
* 修改日期：2024.01.22
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>

// 使用变参模板实现递归打印函数
void print() {
    std::cout << std::endl;
}

template<typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(args...);
}

int main() {
    print(1, 2, 3, "Hello", 4.5);  // 调用变参模板函数 print

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
1 2 3 Hello 4.5
*/