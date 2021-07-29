/* study_string.cpp
 *
 * 学习string库
 *
 * author: hankin
 * date  : 2021.07.09
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#pragma once

#include <iostream>
#include <string>
using namespace std;

/*
但是如果频繁用到路径检索的时候，“\\”需要手动添加十分麻烦，这里介绍一种C++的新特性——源码转译。
*/
static void study_R()
{
	string skr = "";
	int t = 9;
	for (int i = 0; i < 5; i++)
		skr += to_string(t) + "_";

	cout << skr << endl;
	cout << R"()" << endl;

    //string s0 = "C:\Users\Administrator\Desktop\RWtest\write.txt";
    string s = "C:\\Users\\Administrator\\Desktop\\RWtest\\write.txt";
    string s1 = R"(C:\Users\Administrator\Desktop\RWtest\write.txt)";
    //cout << s0.data() << endl;
    cout << s.data() << endl;
    cout << s1.data() << endl;
    return;
}

/*
* 运行结果如下： 
* hello
* hello
* Worl
* llo
* cccccccccc
*/
static void study_assign()
{
    string str1("hello");
    string str2, str3, str4, str5;

    str2.assign(str1);      // str1赋值给str2
    str3.assign("World", 4);// 把前4个字符赋值给str3
    str4.assign(str1, 2, 3);// 从第2个位置开始赋值3个连续字符
    str5.assign(10, 'c');   // 赋值10个'c'字符给str5

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    return;
}

/*
* C语言版split函数
*/
static void study_strtok()
{
    char sentence[] = "This is a sentence with 7 tokens";
    cout << "The string to be tokenized is:\n" << sentence << "\n\nThe tokens are:\n\n";
    char *tokenPtr = strtok(sentence, " ");
    while (tokenPtr != NULL) {
        cout << tokenPtr << endl;
        tokenPtr = strtok(NULL, " ");
    }
    return;
}

static void study_others()
{
    // 2、重载函数
    std::string my_str = "holiday";
    //std::string my_str_add = "error" + "error";//错误 
    std::string my_str_add2 = my_str + "right";
    std::string my_str_add3 = my_str + "right" + "right";
    std::string my_str_add4 = "right" + my_str;
    //std::string my_str_add5 = "error" + "error" + my_str;//错误
    
    // 1、push_back函数
    //my_str.push_back("123");//错误
    my_str.push_back('1');//ok
}

int test_study_string()
{
	study_R();
    study_assign();
    study_strtok();
	return 0;
}

/*
函数原型：
string to_string (int val);
string to_string (long val);
string to_string (long long val);
string to_string (unsigned val);
string to_string (unsigned long val);
string to_string (unsigned long long val);
string to_string (float val);
string to_string (double val);
string to_string (long double val);

功能：

将数值转化为字符串。返回对应的字符串。

原型：void pop_back();
说明：删除源字符串的最后一个字符，有效的减少它的长度。

原型：string& erase (size_t pos = 0, size_t len = npos);
说明：删除源字符串以下标为pos开始的len个字符，返回修改后的字符串。
原型：iterator erase (const_iterator p);
说明：删除源字符串中迭代器p指向的字符，返回删除后迭代器的位置。
原型：iterator erase (const_iterator first, const_iterator last);
说明：删除源字符串迭代器范围为[first，last）内的所有字符，返回删除后迭代器的位置。

原型：void clear() noexcept;
说明：将字符串的内容清空，让源字符串成为一个空字符串（长度为0个字符）。
*/
