#pragma once

#include "gtest/gtest.h"

#pragma comment(lib, "library/gtestlib/gtest.lib")

/*
* 交换两个变量值
* 
* 返回前一个数值
*/
static int swap1(int x, int y)
{
	x = x + y;
	y = x - y;
	x = x - y;
	return x;
}
static int swap2(int x, int y)
{
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
	return x;
}
static int swap3(int x, int y)
{
	int tmp = x;
	x = y;
	y = tmp;
	return x;
}

TEST(swap1_eq, swap1)
{
	EXPECT_EQ(3, swap1(2, 3));
}
TEST(swap1_ne, swap1)
{
	EXPECT_NE(3, swap1(3, 4));
}
TEST(swap2_eq, swap2)
{
	EXPECT_EQ(4, swap1(3, 4));
}
TEST(swap3_eq, swap3)
{
	EXPECT_EQ(4, swap1(3, 4));
}

/*
* 1.属性->C/C++->附加目录 增加gtest的include文件夹，这样才不能破坏库的其他文件调用
* 2.属性->C/C++->代码生成->运行库->多线程 DLL (/MD) 修改为 多线程 (/MT)
*/
int test_study_gtest(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}