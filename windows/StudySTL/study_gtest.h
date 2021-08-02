#pragma once

#include "gtest/gtest.h"

#pragma comment(lib, "library/gtestlib/gtest.lib")

/*
* ������������ֵ
* 
* ����ǰһ����ֵ
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
* 1.����->C/C++->����Ŀ¼ ����gtest��include�ļ��У������Ų����ƻ���������ļ�����
* 2.����->C/C++->��������->���п�->���߳� DLL (/MD) �޸�Ϊ ���߳� (/MT)
*/
int test_study_gtest(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}