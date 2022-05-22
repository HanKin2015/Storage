/**
* 文 件 名: string_example.cpp
* 文件描述: 字符串那些事儿
* 作    者: HanKin
* 创建日期: 2021.08.24
* 修改日期：2021.10.18
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

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

int main()
{
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
    string j = "1" + c;
    cout << "j = " << j << endl;

    fun("abc");

    // char2int
    int i = 'a';
    cout << i << endl;
    return 0;
}
