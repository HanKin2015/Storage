/*******************************************************************************
* 文 件 名: string_example.cpp
* 文件描述: 字符串那些事儿
* 备    注: 
* 作    者: HanKin
* 创建日期: 2021.08.24
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>
using namespace std;

#define a "b" "234"

// 指针可以自增自减，指向上一个地址或下一个地址
void fun(const char *str)
{
    cout << "str = " << str << endl;
    cout << *str << endl;
    str++;
    cout << *str << endl;
    return;
}

void init()
{
    std::string str(5, '3');
    std::cout << str << std::endl;  // 33333
    return;
}

void C()
{
	char *str = "abcdefgde";
	char c = 'd';
	
	// 1、字符查找
	char *a = strchr(str, c);
	char *b = strrchr(str, c);
	printf("%s %s\n", a, b);
	
	// 2、
	return;
}

void CPLUSPLUS()
{
	string source_str = "abcdefgde";
	string object_str = "de";
	
	string str1 = "abcdefgde";
	string str2 = "de";
	
	// 1、字符串查找
	int a = str1.find(str2);         		//查找str1中第一次出现str2的位置，并返回（包括0）
	int b = str1.rfind(str2);        		//查找str1中最后次出现str2的位置，并返回（包括0）
	int c = str1.find_first_of(str2);		//查找在str2中任意一个·字符·在str1中第一次出现的位置，并返回（包括0）
	int d = str1.find_last_of(str2);		//查找在str2中任意一个·字符·在str1中最后一次出现的位置，并返回（包括0）
	int e = str1.find_first_not_of(str2);	//查找str1中第一个不属于str2中的·字符·的位置，并返回（包括0）
	int f = str1.find_last_not_of(str2);	//查找str1中最后一个不属于str2中的·字符·的位置，并返回（包括0）
	printf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
	
	// 2、字符串截取
	basic_string<char> g = str1.substr(2, 4);	//截取s中从pos开始（包括0）的n个字符的子串，并返回
	string h = str1.substr(2);					//截取s中从从pos开始（包括0）到末尾的所有字符的子串，并返回
	printf("%s %s\n", g.c_str(), h.data());
	
	// 3、字符串替换
	string i = str1.replace(2, 4, str2);	//用str2替换str1中从pos开始（包括0）的n个字符的子串
	printf("%s\n", i.data());
	
	// 4、字符串比较
	
	// 5、字符串拼接
	return;
}

// 不写头文件strings.h也是能正常编译的
void OTHER()
{
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	char *c = "abKLDSHAJ";
	if (!strcasecmp(a, b)) {
		printf("%s = %s\n", a, b);
	}
	if (!strncasecmp(a, c, 2)) {
		printf("%s = %s\n", a, c);
	}
	return;
}

int main()
{
    init();
    C();
	CPLUSPLUS();
	OTHER();
    
    // 字符串可以自动拼接
    cout << a << endl;
    cout << "dsad" "12345" << endl;
    
	// string类型empty函数
    string sn = "";
    string mac = "";
    string msg = sn + "," + mac;
    if (sn.empty() && mac.empty()) {
        msg = "";
        cout << "null" << endl;
    }
    cout << sn << ' ' << mac << ' ' << msg << endl;

    // 忽然之间想不出来是哪种不能拼接
    string hj = "" + mac;
    cout << "hj = " << hj << endl;
    
    string jh = sn + mac;
    cout << "jh = " << jh << endl;
    
    string h = ' ' + mac;
    cout << "h = " << h << endl;
    
    const char *c = "hello";
    string j = "1" + std::string(c);
    cout << "j = " << j << endl;

    fun("abc");

    // char2int
    int i = 'a';
    cout << i << endl;
    return 0;
}
