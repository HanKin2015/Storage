#pragma once

#include "common.h"

static void study_vector()
{
	vector<int> v(5);	// �ȼ���int v[5]
	cout << v.size() << endl;
	v.clear();
	cout << v.size() << endl;
	v.reserve(10);
	cout << v.size() << endl;
	v.resize(10);
	cout << v.size() << endl;

	/*
	* �������ߺ���������ı�Ԫ��ֵ
	* reserver����������vectorԤ����洢����С����capacity��ֵ ������û�и�����ڴ���г�ʼ����reserve �Ĳ���n���Ƽ�Ԥ�����ڴ�Ĵ�С��ʵ�ʷ���Ŀ��ܵ��ڻ�������ֵ����n����capacity��ֵ���ͻ�reallocate�ڴ� capacity��ֵ����ڻ��ߵ���n ����������ector����push_back����ʹ��size ����ԭ����Ĭ�Ϸ����capacityֵʱ �������ڴ��ط��俪����
	* ��Ҫע����ǣ�reserve ��������������ڴ�ռ䣬ֻ�Ǳ�ʾvector���������ⲿ���ڴ棬��vector������Ч�ط�����Щ�ڴ�ռ䣬���ʵ�ʱ��ͻ����Խ�����󣬵��³��������
	* 
	* resize�������·����С���ı������Ĵ�С�����Ҵ�������
	* ��nС�ڵ�ǰsize()ֵʱ��vector���Ȼ����size()ֵ ����ǰn��Ԫ�أ�Ȼ�󽫳���n��Ԫ��ɾ��(remove and destroy)
	* ��n���ڵ�ǰsize()ֵʱ��vector�������Ӧ������Ԫ�� ʹ��size()ֵ�ﵽn��������ЩԪ�ؽ��г�ʼ���������������ĵڶ���resize������ָ��val��vector����val����ʼ����Щ�²����Ԫ��
	* ��n����capacity()ֵ��ʱ�򣬻��Զ��������·����ڴ�洢�ռ䡣
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