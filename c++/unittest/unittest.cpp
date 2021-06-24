#include <stdio.h>

#define ADD_METHOD_CNT 5	// 两数求和方式数量

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
	return printf("%*c%*c", x, ' ', y, ' ');
}

// typedef函数指针用法
typedef int (*p_add)(int x, int y);

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

int main()
{
	int x = 3, y = 4;
	for (int i = 0; i < ADD_METHOD_CNT; i++) {
		printf("%d + %d = %d\n", x, y, add(x, y, i));
	}
	return 0;
}
