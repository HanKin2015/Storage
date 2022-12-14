/**
* 文 件 名: c_out_of_order_init.c
* 文件描述: C语言支持乱序初始化
* 作    者: HanKin
* 创建日期: 2022.10.14
* 修改日期：2022.12.13
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/
// 

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int b[10] = {
    [2] = 2,
    [3] = 3,
    [4] = 4,
};

int main()
{
	int a[10] = {
		[2] = 2,
		[3] = 3,
		[4] = 4,
	};

    // 可以通过gcc init_struct.c -std=c89
    // error: ‘for’ loop initial declarations are only allowed in C99 or C11 mode
	for (int i = 0; i < 10; i++) {
		printf("%d\n", b[i]);
	}
	return 0;
}

#ifdef __cplusplus
}
#endif
