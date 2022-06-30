/**
* 文 件 名: copy_struct.c
* 文件描述: 浅拷贝、深拷贝、写时拷贝
* 作    者: HanKin
* 创建日期: 2022.06.28
* 修改日期：2022.06.28
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct _TEACHER
{
	char *name;
	int age;
} TEACHER;

// 浅拷贝
/*
t1 name: liming, age: 22
t2 name: liming, age: 22
free t1 before, t1 name address: 0xf21010, t2 name address: 0xf21010
free t1 after , t1 name address: (nil), t2 name address: 0xf21010
*** Error in `./a.out': double free or corruption (fasttop): 0x0000000000f21010 ***
*/
static void shallow_copy()
{
	TEACHER t1;
	t1.name = (char*)malloc(30);// 给name动态分配空间
	strcpy(t1.name, "liming");	// 把文字常量区的内容拷贝给t1.name
	t1.age = 22;
	printf("t1 name: %s, age: %d\n", t1.name, t1.age);
	
	TEACHER t2 = t1;			// 结构体的浅拷贝
	printf("t2 name: %s, age: %d\n", t2.name, t2.age);

	printf("free t1 before, t1 name address: %p, t2 name address: %p\n", t1.name, t2.name);
	if (t1.name != NULL) {		// 释放分配给t1.name 的堆区空间
		free(t1.name);
		t1.name = NULL;
	}
	printf("free t1 after , t1 name address: %p, t2 name address: %p\n", t1.name, t2.name);
	// C语言中不能存在二次释放，会导致程序崩溃，画出内存图，可以看到t1.name和t2.name指向同一内存
	if (t2.name != NULL) {
		free(t2.name);
		t2.name = NULL;
	} else {
		printf("t2 name is NULL\n");
	}
	return;
}

// 深拷贝
/*
t1 name: liming, age: 22
t2 name: liming, age: 22
t2 name: liming, age: 22
free t1 before, t1 name address: 0xc5f010, t2 name address: 0xc5f450
free t1 after , t1 name address: (nil), t2 name address: 0xc5f450
*/
static void deep_copy()
{
	TEACHER t1;
	t1.name = (char*)malloc(30);// 给name动态分配空间
	strcpy(t1.name, "liming");	// 把文字常量区的内容拷贝给t1.name
	t1.age = 22;
	printf("t1 name: %s, age: %d\n", t1.name, t1.age);
	
	TEACHER t2 = t1;			// 结构体的浅拷贝
	printf("t2 name: %s, age: %d\n", t2.name, t2.age);
	t2.name = (char*)malloc(30);// 给t2.name重新分配空间
	strcpy(t2.name, t1.name);
	printf("t2 name: %s, age: %d\n", t2.name, t2.age);

	printf("free t1 before, t1 name address: %p, t2 name address: %p\n", t1.name, t2.name);
	if (t1.name != NULL) {		// 释放分配给t1.name 的堆区空间
		free(t1.name);
		t1.name = NULL;
	}
	printf("free t1 after , t1 name address: %p, t2 name address: %p\n", t1.name, t2.name);
	// C语言中不能存在二次释放，会导致程序崩溃，画出内存图，可以看到t1.name和t2.name指向同一内存
	if (t2.name != NULL) {
		free(t2.name);
		t2.name = NULL;
	} else {
		printf("t2 name is NULL\n");
	}
	return;
}

// 浅拷贝
static void shallow_copy1()
{
	TEACHER t1;
	t1.name = (char*)malloc(30);// 给name动态分配空间
	strcpy(t1.name, "liming");	// 把文字常量区的内容拷贝给t1.name
	t1.age = 22;
	printf("t1 name: %s, age: %d\n", t1.name, t1.age);
	
	int len = sizeof(t1);		// 数据长度
	char *buffer = (char *)malloc(len);
	memcpy(buffer, &t1, len);   // t1为结构体数据
	//TEACHER t2 = (TEACHER)buffer;	// error: conversion to non-scalar type requested
	TEACHER *t2 = (TEACHER *)buffer;
	printf("t2 name: %s, age: %d\n", t2->name, t2->age);
	
	printf("free t1 before, t1 name address: %p, t2 name address: %p\n", t1.name, t2->name);
	if (t1.name != NULL) {		// 释放分配给t1.name 的堆区空间
		free(t1.name);
		t1.name = NULL;
	}
	printf("free t1 after , t1 name address: %p, t2 name address: %p\n", t1.name, t2->name);
	// C语言中不能存在二次释放，会导致程序崩溃，画出内存图，可以看到t1.name和t2.name指向同一内存
	if (t2->name != NULL) {
		free(t2->name);
		t2->name = NULL;
	} else {
		printf("t2 name is NULL\n");
	}
	return;
}

// 浅拷贝
/*
t1 name: liming, age: 22
len: 16
t2 name: liming, age: 22
free t1 before, t1 name address: 0x19b5010, t2 name address: 0x19b5010
free t1 after , t1 name address: (nil), t2 name address: 0x19b5010
*** Error in `./a.out': double free or corruption (fasttop): 0x00000000019b5010 ***
*/
static void shallow_copy2()
{
	TEACHER t1;
	t1.name = (char*)malloc(30);// 给name动态分配空间
	strcpy(t1.name, "liming");	// 把文字常量区的内容拷贝给t1.name
	t1.age = 22;
	printf("t1 name: %s, age: %d\n", t1.name, t1.age);
	
	int len = sizeof(t1);		// 数据长度
	printf("len: %d\n", len);
	char *buffer = (char *)malloc(len);
	TEACHER *t2 = (TEACHER *)buffer;
	t2->name = t1.name;
	t2->age = t1.age;
	printf("t2 name: %s, age: %d\n", t2->name, t2->age);
	
	printf("free t1 before, t1 name address: %p, t2 name address: %p\n", t1.name, t2->name);
	if (t1.name != NULL) {		// 释放分配给t1.name 的堆区空间
		free(t1.name);
		t1.name = NULL;
	}
	printf("free t1 after , t1 name address: %p, t2 name address: %p\n", t1.name, t2->name);
	// C语言中不能存在二次释放，会导致程序崩溃，画出内存图，可以看到t1.name和t2.name指向同一内存
	if (t2->name != NULL) {
		free(t2->name);
		t2->name = NULL;
	} else {
		printf("t2 name is NULL\n");
	}
	return;
}

int main(int argc, char *argv[])
{
	//shallow_copy();
	//deep_copy();
	//shallow_copy1();
	shallow_copy2();
	return 0;
}
