/*******************************************************************************
* 文 件 名: va_list_example.cpp
* 文件描述: 可变参数指的是函数能够接收数量不固定的参数
* 备    注: 必须明确指定参数的数量（像示例中的count）。
*			不具备类型检查功能，容易引发运行时错误。
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdarg>

// 计算多个整数的和
int sum(int count, ...)
{
    va_list args;
    va_start(args, count); // 必须传入最后一个固定参数名（即count）

    int total = 0;
    for (int i = 0; i < count; ++i) {
		int tmp = va_arg(args, int); // 获取下一个int类型的参数
		std::cout << tmp << std::endl;
        total += tmp;
    }

    va_end(args);
    return total;
}

// 假如这里参数int a, int b, ...则正常应该传入b，你传入a的话就会把b计算进去
int sum_error(int count, int a, ...)
{
    va_list args;
	
	// 测试发现结果还是6，但是永远不要依赖未定义行为！
    va_start(args, count);	// 可能在不同的环境（如调试器、不同编译器版本）下测试，得到不同结果

    int total = 0;
    for (int i = 0; i < count; ++i) {
		int tmp = va_arg(args, int); // 获取下一个int类型的参数
		std::cout << tmp << std::endl;
        total += tmp;
    }

    va_end(args);
    return total;
}

int main()
{
    std::cout << sum(3, 1, 2, 3) << std::endl; // 输出6
    std::cout << sum(5, 10, 20, 30, 40, 50) << std::endl; // 输出150
	std::cout << sum(5, 10, 20, "30", 40, 50) << std::endl; // 输出150
	
	std::cout << sum_error(3, 100, 1, 2, 3) << std::endl;
    return 0;
}
/*
1
2
3
6
10
20
30
40
50
150
10
20
4202512
40
50
4202632
*/