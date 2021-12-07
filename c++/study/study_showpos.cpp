// 启用或禁用加号的显示。'+'在非负整数输出中。对输入没有影响。
#include <iostream>

int main()
{
	std::cout << "showpos: " << std::showpos << 42 << ' ' << 3.14 << ' ' << 0 << '\n'
		<< "noshowpos: " << std::noshowpos << 42 << ' ' << 3.14 << ' ' << 0 << '\n';
	
	std::cout << std::showpos << -4 << ' ' << 4 << '\n';
	return 0;
}
