/**
* 文 件 名: study_strchr_strtok.cpp
* 文件描述: split函数使用及实战，判断字符串-符号后面部分是否有相同
* 作    者: HanKin
* 创建日期: 2021.10.18
* 修改日期：2021.10.18
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

/*
const char * strchr(const char * str, int character);
功能： 查找字符串s中首次出现c字符的位置
说明： 返回首次出现c的位置的指针，返回的地址是被查找的字符串指针开始的第一个与c相同字符的指针，若s中不存在c则返回NULL。
返回值： 成功返回要查找的字符第一次出现的位置，否则返回NULL。

char *strrchr(const char *s, int c)
功能： 查找一个字符c在一个字符串s中最后一次出现的位置（也就是从s的右侧开始查找字符c首次出现的位置），并返回从字符串中的字符c所在的位置开始直到字符串s结束的所有字符。 若没有找到字符c，则返回NULL。

char *strtok(char s[], const char *delim);
功能：分解字符串为一组字符串。s为要分解的字符串，delim为分隔符字符串。

char *strtok_r(char *str, const char *delim, char **saveptr);
strtok_r函数是strtok函数的可重入版本。str为要分解的字符串，delim为分隔符字符串。char **saveptr参数是一个指向char *的指针变量，用来在strtok_r内部保存切分时的上下文，以应对连续调用分解相同源字符串。
第一次调用strtok_r时，str参数必须指向待提取的字符串，saveptr参数的值可以忽略。连续调用时，str赋值为NULL，saveptr为上次调用后返回的值，不要修改。一系列不同的字符串可能会同时连续调用strtok_r进行提取，要为不同的调用传递不同的saveptr参数。
strtok_r实际上就是将strtok内部隐式保存的this指针，以参数的形式与函数外部进行交互。由调用者进行传递、保存甚至是修改。需要调用者在连续切分相同源字符串时，除了将str参数赋值为NULL，还要传递上次切分时保存下的saveptr。
*/

#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	// strtok可以作为split函数，线程安全函数strtok_r
    char ip[] = "199.200.250.20";
    char *ret = NULL;
    ret = strtok(ip, ".");
    while (ret != NULL) {
        cout << ret << endl;
        ret = strtok(NULL, ".");
    }
	
	// strchr 对你没有看错，第二个参数就是int类型：https://cplusplus.com/reference/cstring/strchr/?kw=strchr
    // error: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]
    // 返回值需要加const否则就会有上面这个错误，函数原型const char * strchr ( const char * str, int character );
	const char *str = "abcdefgghijkl";
	const char *index1 = strchr(str, 'g');
	cout << index1 << endl;
	
	// strrchar
	const char *index2 = strrchr(str, 'g');
	cout << index2 << endl;
    
    // strtok_r
    char tmp[] = "1.2.3.4";
    char *save_ptr = NULL;
    char *num = strtok_r(tmp, ".", &save_ptr);
    while (num != NULL) {
        cout << num << ' ' << save_ptr << endl;
        num = strtok_r(NULL, ".", &save_ptr);
    }
    return 0;
}

/*
199
200
250
20
gghijkl
ghijkl
1 2.3.4
2 3.4
3 4
4
*/