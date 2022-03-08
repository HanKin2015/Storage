/**
* 文 件 名: init_struct.cpp
* 文件描述: 初始化结构体
* 作    者: HanKin
* 创建日期: 2021.08.24
* 修改日期：2022.02.28
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

// linux结构体可以采用乱序初始化，即用成员变量前加（.）符号；
// 乱序初始化是C99标准新加的，比较直观的一种初始化方式。相比顺序初始化而言，乱序初始化就如其名，成员可以不按照顺序初始化，而且可以只初始化部分成员，扩展性较好。linux内核中采用这种方式初始化struct。

#ifdef __cplusplus
extern "C" {
#endif

struct node {
    int x;
    int y;
	int z;
};
static void test1()
{
    // 声明
    struct node t1;
    
    // 顺序初始化
    struct node t2 = {1, 2};
    struct node t3 = {1, 2, 3,};
    
    // 乱序初始化(不支持)
    const struct node t4 = {
        .x = 3,
        .y = 4,
		.z = 5,
    };

	struct node t5 = {
		.y = 4,
		.z = 5,
	};
    
    cout << t1.x << ' ' << t1.y << ' ' << t1.z << endl;
    cout << t2.x << ' ' << t2.y << ' ' << t2.z << endl;
    cout << t3.x << ' ' << t3.y << ' ' << t3.z << endl;
    cout << t4.x << ' ' << t4.y << ' ' << t4.z << endl;
    cout << t5.x << ' ' << t5.y << ' ' << t5.z << endl;
	return;
}

struct st_node {
    int x;
    int y;
};
static void test2()
{
    //st_node a(1, 2);  错误
    st_node a;
    a.x = 5;
    a.y = 8;
    printf("(%d, %d)\n", a.x, a.y);

    st_node b = {
        .x = 2,
        .y = 5
    };
    printf("(%d, %d)\n", b.x, b.y);

    st_node c = {1, 3};
    printf("(%d, %d)\n", c.x, c.y);
	return;
}

typedef struct _USB_NODE_CONNECTION_INFORMATION {
	int x;
	int y;
    int data[0];
} USB_NODE_CONNECTION_INFORMATION, *PUSB_NODE_CONNECTION_INFORMATION;
static void test3()
{
	int info_size = 123;
	
	PUSB_NODE_CONNECTION_INFORMATION info1 = (PUSB_NODE_CONNECTION_INFORMATION)malloc(info_size);
	memset(info1, 0, info_size);
	printf("info1 x: %d, y: %d\n", info1->x, info1->y); 
	
	PUSB_NODE_CONNECTION_INFORMATION info2 = (PUSB_NODE_CONNECTION_INFORMATION)malloc(info_size);
	//这行有问题，注释掉正常，不注释编译通过，运行段错误，注释掉printf，则报terminated
	memset(&info2, 0, info_size);
	//*** stack smashing detected ***: ./a.out terminated
	printf("info2 x: %d, y: %d\n", info2->x, info2->y);
	
	USB_NODE_CONNECTION_INFORMATION info3 = { 0 };
	printf("info3 x: %d, y: %d\n", info3.x, info3.y);
	
	USB_NODE_CONNECTION_INFORMATION info4;
	memset(&info4, 0, sizeof(info4));
	printf("info4 x: %d, y: %d\n", info4.x, info4.y);
	
	//其实从这里可以看出，memset第一个参数是指针，因此普通struct是需要取地址，指针struct则是本身
	//error: cannot convert ‘USB_NODE_CONNECTION_INFORMATION {aka _USB_NODE_CONNECTION_INFORMATION}’ to ‘void*’ for argument ‘1’ to ‘void* memset(void*, int, size_t)’
	USB_NODE_CONNECTION_INFORMATION info5;
	//memset(info5, 0, sizeof(info5));
	printf("info5 x: %d, y: %d\n", info5.x, info5.y);
	return;
}

int main()
{
	test1();
	test2();
	test3();
    return 0;
}

#ifdef __cplusplus
}
#endif
