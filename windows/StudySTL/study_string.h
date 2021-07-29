/* study_string.cpp
 *
 * ѧϰstring��
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
�������Ƶ���õ�·��������ʱ�򣬡�\\����Ҫ�ֶ����ʮ���鷳���������һ��C++�������ԡ���Դ��ת�롣
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
* ���н�����£� 
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

    str2.assign(str1);      // str1��ֵ��str2
    str3.assign("World", 4);// ��ǰ4���ַ���ֵ��str3
    str4.assign(str1, 2, 3);// �ӵ�2��λ�ÿ�ʼ��ֵ3�������ַ�
    str5.assign(10, 'c');   // ��ֵ10��'c'�ַ���str5

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    return;
}

/*
* C���԰�split����
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
    // 2�����غ���
    std::string my_str = "holiday";
    //std::string my_str_add = "error" + "error";//���� 
    std::string my_str_add2 = my_str + "right";
    std::string my_str_add3 = my_str + "right" + "right";
    std::string my_str_add4 = "right" + my_str;
    //std::string my_str_add5 = "error" + "error" + my_str;//����
    
    // 1��push_back����
    //my_str.push_back("123");//����
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
����ԭ�ͣ�
string to_string (int val);
string to_string (long val);
string to_string (long long val);
string to_string (unsigned val);
string to_string (unsigned long val);
string to_string (unsigned long long val);
string to_string (float val);
string to_string (double val);
string to_string (long double val);

���ܣ�

����ֵת��Ϊ�ַ��������ض�Ӧ���ַ�����

ԭ�ͣ�void pop_back();
˵����ɾ��Դ�ַ��������һ���ַ�����Ч�ļ������ĳ��ȡ�

ԭ�ͣ�string& erase (size_t pos = 0, size_t len = npos);
˵����ɾ��Դ�ַ������±�Ϊpos��ʼ��len���ַ��������޸ĺ���ַ�����
ԭ�ͣ�iterator erase (const_iterator p);
˵����ɾ��Դ�ַ����е�����pָ����ַ�������ɾ�����������λ�á�
ԭ�ͣ�iterator erase (const_iterator first, const_iterator last);
˵����ɾ��Դ�ַ�����������ΧΪ[first��last���ڵ������ַ�������ɾ�����������λ�á�

ԭ�ͣ�void clear() noexcept;
˵�������ַ�����������գ���Դ�ַ�����Ϊһ�����ַ���������Ϊ0���ַ�����
*/
