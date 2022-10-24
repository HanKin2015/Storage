/**
* 文 件 名: N-scale_Notation.cpp
* 文件描述: 二进制、八进制和十六进制表示
* 作    者: HanKin
* 创建日期: 2022.10.21
* 修改日期：2022.10.21
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

// 并没有二进制对应的输出格式，所以需要我们手动来实现
#define uint32 unsigned int
#define uint8 unsigned char
void itoa_func_output_bin(uint32 value)
{
    char str[32] = { 0 };   //形参类型uint32最大为32位，因此我这里定义了大小为32的字符串数组存放
    itoa(value, str, 2);  
    printf("库函数得到的二进制为：%s\r\n", str);
    return;
}
/*
itoa函数原型：char *itoa( int value, char *string,int radix)
功能：将整形数据value转化成需要的进制radix，然后将之以字符串的形式存放在string中；
返回值：转化成对应进制后的字符串的地址，也可以不使用返回值；
它的三个参数依次为：
value：需要转化的整形数据；
string：转化成对应进制后的字符串的地址；
radix ：需要转化的进制（我这里需要转化为2进制，所以填2）；

itoa并不是一个标准的C函数，它是Windows特有的，如果要写跨平台的程序，请用sprintf。
这个其实是C/C++非标准库中的函数，而是Windows平台下扩展的，标准库中有sprintf（注意是标准库），功能比这个强的多的啦，用法跟printf有点神似。
sprintf不支持二进制。

可以自己实现一个类似itoa的函数_itoa，哈哈。
*/

//用短除法的思想得到二进制，之后将数据从后往前读取 
void short_div_output_bin(uint32 input)
{
    uint8 temp[33] = {0};  
    int i = 0;
    printf("短除法得到的二进制为：");
    while (input) {
        temp[i] = input % 2;	//取余数存放到数组中，此为得到的二进制数
        input = (uint32)input / 2;  //短除，while中判断是否除尽
        i++;  //存储了一个二进制数，自加存储下一个
    }
    for (i--; i >= 0; i--) {  //由于最后一次input为0无效，i还是自加了，因此最后一次自加的值是无用的，所以先自减，然后将余数从后往前读取
        printf("%d", temp[i]);
    }
    printf("\r\n");
    return;
}

// 八进制由 0~7 八个数字组成，使用时必须以0开头（注意是数字 0，不是字母 o）
static void octal_number_system()
{
    printf("********* %s[%d] *********\n", __FUNCTION__, __LINE__);
    
    // 合法的八进制数
    int a = 015;        // 换算成十进制为 13
    int b = -0101;      // 换算成十进制为 -65
    int c = 0177777;    // 换算成十进制为 65535
    printf("%d %d %d\n", a, b, c);

    // 非法的八进制
    //int m = 256;    // 无前缀 0，相当于十进制
    //int n = 03A2;   // A不是有效的八进制数字(error: invalid suffix "A2" on integer constant)
    //printf("%d %d\n", m, n);
    return;
}

// 十六进制由数字 0~9、字母 A~F 或 a~f（不区分大小写）组成，使用时必须以0x或0X（不区分大小写）开头
static void hexadecimal()
{
    printf("********* %s[%d] *********\n", __FUNCTION__, __LINE__);
    
    // 合法的十六进制
    int a = 0X2A;   // 换算成十进制为 42
    int b = -0XA0;  // 换算成十进制为 -160
    int c = 0xffff; // 换算成十进制为 65535
    printf("%d %d %d\n", a, b, c);

    // 非法的十六进制
    //int m = 5A;     // 没有前缀 0X，是一个无效数字(error: invalid suffix "A" on integer constant)
    //int n = 0X3H;   // H不是有效的十六进制数字(error: invalid suffix "H" on integer constant)
    //printf("%d %d\n", m, n);
    return;
}

// 进制输出
static void printf_N_scale_notation()
{
    int x = 1911;

    cout << "x的十进制表示：   " << std::dec << x << endl;
    cout << "x的八进制表示：   " << std::oct << x << endl;
    cout << "x的十六进制表示： " << std::hex << x << endl;
    
    printf("x的十进制表示：%d\n", x);
    printf("x的八进制表示：%o\n", x);
    printf("x的十六进制表示：%x\n", x);
    return;
}

int main(int argc, char *argv[])
{
    octal_number_system();
    hexadecimal();
    printf_N_scale_notation();
    itoa_func_output_bin(1911);
	short_div_output_bin(1911);	
    return 0;
}
