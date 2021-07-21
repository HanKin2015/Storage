#pragma once

#include <iostream>
#include <string.h>
#include <iostream>
#include <ostream>
#include <istream>
#include <sstream>
using namespace std;

/*
1.atoi不检查字符串中错误。这对使用API的程序员而言意味着他必须检查错误，或者必须判断出错误在实际使用中总是不存在或者是可以被程序忍受的。
2.atoi的替代版本strtol检查字符串的错误，但使用的是POSIX中的标准方式，设置errno。这意味着使用strtol的程序员如果要检测字符串中的错误，需要在调用strtol后检测全局变量errno。
3.sprintf不负责任何的内存管理。通常情况下，程序员都会被告诫使用snprintf或者其它有内存边界检查的版本替代sprintf。这样一来会减少发生缓冲区溢出的可能性。不过总的来说这只是一种编程中的防御手段，从程序员的角度而言，内存管理的烦恼依然存在。

在C++98中，增加了字符串流对象。
在C++11中，标准增加了全局函数std::to_string，以及std::stoi/stol/stoll等等函数。
*/

/*
* 数值和字符串之间转换
*/
static void number2string()
{
	int num = 12345;
	char str[1024] = { 0 };
	
	_itoa(num, str, 10);
	cout << "str = " << str << endl;

	ostringstream oss;
	oss << 15 << " is int, " << 3.14f << " is float." << endl;
	cout << oss.str();

	string s;
	s += to_string(12) + " is int, ";
	s += to_string(3.14f) + " is float.";
	cout << s << endl;
	return;
}
static void string2number()
{
	char str[] = "12345";
	int num = 0;

	num = atoi(str);
	cout << "num = " << num << endl;
	// 除去strtol会在出错时设置全局的errno外，其效果与atoi系列中的atol则几乎是完全等同的。
	num = strtol(str, NULL, 10);
	cout << "num = " << num << endl;

	istringstream iss("12 14.1f");
	int a;
	float b;
	iss >> a >> b;
	cout << a << " " << b << endl;

	string s("1223");
	int i = stoi(s);
	cout << i << endl;
	return;
}

int test_safe_function()
{
	number2string();
	string2number();
	return 0;
}









