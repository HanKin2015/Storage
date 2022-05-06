#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class A {
public:
	A(int x) {_x = x;}
	A() {}
	~A() {}
	

	static int sqrt(int x)
	{
		printf("this is class A, ");
		return x * x;
	}

private:
	int _x;
};

namespace hj {
	int sqrt(int x) 
	{
		printf("this is namespace hj, ");
		return x + x;
	}
}

#if 0
int sqrt(int x) 
{
	printf("this is namespace hj, ");
	return x + x;
}
#endif

int main()
{
	int a = 4;
	int b = sqrt(a);
	//::cout << b << std::endl;
	std::cout << b << std::endl;

	// 首先在当前文件全局搜索，然后再在头文件里搜索
	int c = ::sqrt(a);
	std::cout << c << std::endl;
	
	int d = hj::sqrt(a);
	std::cout << d << std::endl;

	A num(5);
	std::cout << num.sqrt(8) << std::endl;
	std::cout << A::sqrt(9) << std::endl;
	return 0;
}
