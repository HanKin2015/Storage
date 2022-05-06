#include <stdio.h>
#include <stdlib.h>
 
 int main(int argc, char **argv)
 {
	// C语言中获取函数名，一般是__func__,GCC还支持__FUNCTION__.同时，__PRETTY_FUNCTION__对函数的打印会带上参数。
	// 实际使用时还要注意，__PRETTY_FUNCTION__需要使用g++编译才行
	printf("%s %s %s\r\n",__func__,__FUNCTION__,__PRETTY_FUNCTION__);
	/*
	main main int main(int, char**)
	*/
	
	return 0;
 }
