#include "modle.hpp"

// 位运算
int add1(int num1, int num2)
{ 
	if (0 == num2) {
		return num1;
	}
	int sum = num1 ^ num2;
	int carry = (num1 & num2) << 1; 
	return add1(sum, carry);
}

// 普通加法
int add2(int x, int y)
{
	return x + y;
}

// 利用减号
int add3(int x, int y)
{
	return -(-x-y);
}

// 自加
int add4(int x, int y)
{
	while (x--) {
		y++;
	}
	return y;
}

// 利用printf返回值
int add5(int x, int y)
{
	// 输出x+y个空格
	return printf("%*c%*c", x, ' ', y, ' ');
}

// 对外暴露的接口
int add(int x, int y, int index)
{
	static p_add func[ADD_METHOD_CNT] = {
		add1,
		add2,
		add3,
		add4,
		add5
	};
	return func[index](x, y);
}

