/*
 * 记得要将testlib.h头文件和testlib.lib库文件放在此工程的目录下，否则编译链接会失败。我们生成可执行文件testLibConsole.exe之后，就不需要这个testlib.lib库文件了。
  * 这就是静态库来由，exe不需要，dll动态库需要。
  * 目前来看开发这个最好是使用vs软件。
 */

#include <iostream>
#include "testlib.hpp"
using namespace std;
 
#pragma comment(lib, "testlib.lib")
 
int main()
{
	printf("fun1() return value is %d\n",fun1());
	printf("fun2() return value is %d\n",fun2());
	return 0;
}