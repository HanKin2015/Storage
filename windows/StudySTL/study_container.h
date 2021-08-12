#pragma once

#include "common.h"

static void study_vector()
{
	vector<int> v(5);	// 等价于int v[5]
	cout << v.size() << endl;
	v.clear();
	cout << v.size() << endl;
	v.reserve(10);
	cout << v.size() << endl;
	v.resize(10);
	cout << v.size() << endl;

	/*
	* 首先两者函数都不会改变元素值
	* reserver函数用来给vector预分配存储区大小，即capacity的值 ，但是没有给这段内存进行初始化。reserve 的参数n是推荐预分配内存的大小，实际分配的可能等于或大于这个值，即n大于capacity的值，就会reallocate内存 capacity的值会大于或者等于n 。这样，当ector调用push_back函数使得size 超过原来的默认分配的capacity值时 避免了内存重分配开销。
	* 需要注意的是：reserve 函数分配出来的内存空间，只是表示vector可以利用这部分内存，但vector不能有效地访问这些内存空间，访问的时候就会出现越界现象，导致程序崩溃。
	* 
	* resize函数重新分配大小，改变容器的大小，并且创建对象
	* 当n小于当前size()值时候，vector首先会减少size()值 保存前n个元素，然后将超出n的元素删除(remove and destroy)
	* 当n大于当前size()值时候，vector会插入相应数量的元素 使得size()值达到n，并对这些元素进行初始化，如果调用上面的第二个resize函数，指定val，vector会用val来初始化这些新插入的元素
	* 当n大于capacity()值的时候，会自动分配重新分配内存存储空间。
	*/
	v.clear();
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.reserve(3);
	for (int elem : v) {
		cout << elem << ' ';
	}
	cout << v.size() << endl;
	v.resize(3);
	for (int elem : v) {
		cout << elem << ' ';
	}
	cout << v.size() << endl;
	v.resize(5);
	for (int elem : v) {
		cout << elem << ' ';
	}
	cout << v.size() << endl;
	return;
}

int test_study_container()
{
	study_vector();
	return 0;
}