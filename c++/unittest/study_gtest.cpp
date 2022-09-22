#include <iostream>
#include <gtest/gtest.h>

int sum(int a, int b) {
	return a + b;
}

TEST(sum, testSum) {
	EXPECT_EQ(5, sum(2, 3));	// 求和2+3=5
	EXPECT_NE(3, sum(3, 4));	// 求和3+4!=3
	EXPECT_EQ(2, sum(1, 2));	// 求和1+2=2
}
/**
 * 如果在此处不写main函数，那么在链接库的时候还需要链接-lgtest_main, 否则只需链接-lgtest即可。
 *
 * 否则报错：
 * /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o：在函数‘_start’中：
 * (.text+0x20)：对‘main’未定义的引用
 * collect2: error: ld returned 1 exit status
 */
#if 0
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif

