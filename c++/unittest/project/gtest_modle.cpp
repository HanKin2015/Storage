#include <gtest/gtest.h>
#include "modle.hpp"

TEST(add, add1) {
	EXPECT_EQ(5, add(2, 3, 0));
	EXPECT_NE(3, add(3, 4, 0));
	//EXPECT_EQ(2, add(1, 2, 0));
}
// 如果在此处不写main函数，那么在链接库的时候还需要链接-lgtest_main, 否则只需链接-lgtest即可。
#if 0
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif

