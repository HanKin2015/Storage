#include <iostream>
#include <inttypes.h>
#include <string.h>
using namespace std;

int main()
{
	// 解决高字节和低字节的拼接
	uint8_t data[] = {0x09, 0x02, 0xa2, 0x09, 0x04, 0x01, 0x00, 0x80};
	//uint16_t total_length = (data[2] | data[3] << 8);
	uint16_t total_length = data[2] + (data[3] << 8);
	cout << total_length << endl;
	
#define MAXN 255
	char str[MAXN * 3];
	cout << strlen(str) << endl;
	cout << sizeof(str) << endl;
	
	// 论初始化的重要性
	memset(str, 0, sizeof(str));
	cout << strlen(str) << endl;
	cout << sizeof(str) << endl;

	// 使用后使用strlen
	strncat(str, "12345", 5);
	cout << strlen(str) << endl;
	cout << sizeof(str) << endl;

	// sizeof通用，忘记了你曾经叱咤ACM的时光了吗
	int nums[24];
	memset(nums, 0, sizeof(nums));
	return 0;
}
/*
2466
6
765
5
765
0
765

口诀：
1、未使用的数组使用sizeof准没错
2、strlen只能给字符串去使用
3、使用的字符串数组必须要使用strlen
4、sizeof只会判断最开始分配的大小，即基本上结果不会改变
*/
