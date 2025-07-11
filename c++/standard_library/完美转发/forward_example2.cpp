/*******************************************************************************
* 文 件 名: forward_example2.cpp
* 文件描述: 进一步理解
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <utility>
#include <iostream>

int wrapper1(int x)
{
	return x;
}

int wrapper2(int y)
{
	return std::forward<int>(y);
}

int main()
{
    int a = 42, b = 111;

    std::cout << wrapper1(a) << std::endl;
    std::cout << wrapper2(b) << std::endl;
	return 0;
}
/*
在不需要完美转发的场景下使用 std::forward，容易引发错误或者让代码变得复杂。所以，只有在模板函数里处理转发引用时，才有必要使用 std::forward。
*/