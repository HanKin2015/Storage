// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*
 * 记得要将testlib.h头文件和testlib.lib库文件放在此工程的目录下，否则编译链接会失败。我们生成可执行文件main.exe之后，就不需要这个testlib.lib库文件了。
  * 这就是静态库来由，exe不需要，dll动态库需要。
  * 目前来看开发这个最好是使用VS软件。
  * 
  * h头文件必须,lib文件也必须,如果头文件增加cpp则需要把引用的其他头文件也要弄进来
 */
#include <iostream>
#include "StaticLib.h"
//#include "StaticLib.cpp"

#pragma comment(lib, "StaticLib.lib")

int main()
{
    std::cout << "Hello World!\n";
    printf("fnStaticLib1() return value is %d\n", fnStaticLib1());
    printf("fnStaticLib2() return value is %d\n", fnStaticLib2());
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
