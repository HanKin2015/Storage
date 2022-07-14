#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _NODE {
	int x;
	int y;
	short z;
	int w;
} NODE;

// 普通指针
static void test1()
{
	char *data = NULL;
	data = (char *)"hello world";
	char *tmp = NULL;
	tmp = data;
	printf("data: %p, tmp: %p\n", data, tmp);
	printf("data: %s, tmp: %s\n", data, tmp);
	
	tmp = (char *)malloc(20);
	memset(tmp, 0, 20);
	*tmp = *data;
	printf("data: %p, tmp: %p\n", data, tmp);
	printf("data: %s, tmp: %s\n", data, tmp);
	return;
}

// 结构体指针(直接段错误)
static void test2()
{
	NODE *data = NULL;
	data->x = 123;
	return;
}

/*
结构体指针

sizeof NODE: 16
data: 0x13e7010, tmp: 0x13e7010
data: 0x13e7010, tmp: 0x13e7010
data->x: 520, tmp->x: 520
data->z: 123, tmp->z: 123
*tmp: 520, *data: 123
*data: 520, *tmp: 123
*data: 520
*tmp: 520
*/
static void test3()
{
	NODE *data = NULL;
	data = (NODE *)malloc(sizeof(NODE));
	printf("sizeof NODE: %lu\n", sizeof(NODE));
	data->x = 520;
	data->z = 123;
	
	NODE *tmp = NULL;
	tmp = data;
	printf("data: %p, tmp: %p\n", data, tmp);
	*tmp = *data;	// 没有前面的赋值会出现段错误
	printf("data: %p, tmp: %p\n", data, tmp);
	printf("data->x: %d, tmp->x: %d\n", data->x, tmp->x);
	printf("data->z: %d, tmp->z: %d\n", data->z, tmp->z);
	
	// 输出这个就特别有意思了
	printf("*tmp: %d, *data: %d\n", *tmp, *data);	// 520 123
	printf("*data: %d, *tmp: %d\n", *data, *tmp);	// 520 123
	printf("*data: %d\n", *data);					// 520
	printf("*tmp: %d\n", *tmp);						// 520
	return;
}

/*
结构体指针(实践表明两种赋值方式都是可行的，只不过一个是浅拷贝一个是深拷贝)

sizeof NODE: 16
data: 0xc51010, tmp: 0xc51440
data->x: 520, data->z: 123
tmp->x: 520, tmp->z: 123
data->x: 520, tmp->x: 520
data->z: 123, tmp->z: 123
*tmp: 520, *data: 123
*data: 520, *tmp: 123
*data: 520
*tmp: 520
*/
static void test4()
{
	NODE *data = NULL;
	data = (NODE *)malloc(sizeof(NODE));
	printf("sizeof NODE: %lu\n", sizeof(NODE));
	data->x = 520;
	data->z = 123;
	
	NODE *tmp = NULL;
	tmp = (NODE *)malloc(sizeof(NODE));
	*tmp = *data;
	printf("data: %p, tmp: %p\n", data, tmp);
	
	printf("data->x: %d, data->z: %d\n", data->x, data->z);
	printf("tmp->x: %d, tmp->z: %d\n", tmp->x, tmp->z);
	
	printf("data->x: %d, tmp->x: %d\n", data->x, tmp->x);
	printf("data->z: %d, tmp->z: %d\n", data->z, tmp->z);
	
	// 输出这个就特别有意思了
	printf("*tmp: %d, *data: %d\n", *tmp, *data);	// 520 123
	printf("*data: %d, *tmp: %d\n", *data, *tmp);	// 520 123
	printf("*data: %d\n", *data);					// 520
	printf("*tmp: %d\n", *tmp);						// 520
	return;
}

/*
结构体指针

data: (nil), tmp: 0x1f83010
data: (nil), tmp: (nil)
*/
static void test5()
{
	NODE *data = NULL;
	
	NODE *tmp = NULL;
	tmp = (NODE *)malloc(sizeof(NODE));
	printf("data: %p, tmp: %p\n", data, tmp);
	//*tmp = *data;	// 深拷贝，一定需要双方都有内存分配
	tmp = data;		// 浅拷贝，永远不会出现段错误，只拷贝指针地址
	printf("data: %p, tmp: %p\n", data, tmp);
	return;
}

int main()
{
	test5();
	return 0;
}