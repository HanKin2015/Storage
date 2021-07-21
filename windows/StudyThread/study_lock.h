#pragma once

#include <iostream>
#include <thread>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <list>
#include <mutex>

using namespace std;

void threadHandle1(int time)
{
	// �����߳�˯��time��
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread1!" << endl;

	// ��ȡ�߳�id
	std::cout << "inside thread :: ID = " << std::this_thread::get_id() << std::endl;
}
void threadHandle2(int time)
{
	// �����߳�˯��time��
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread2!" << endl;
}

/*
* ���߳�������һ��Ҫ�ں��߳��������std::thread��������ǰ�����߳�����join()����detach()������
* 
* ����һ��join��detach����Ҫ�ԡ�
* 
* ��һ������£�������߳̽������ʹ����������̽����������ʱ�����̻߳�δ�����ͻ�������д���
* ���������߳�Ϊ�����̣߳����߳̽��������߳�Ҳ�Զ�������
*/
void test_join_detach()
{
	// ������һ���̶߳���,����һ���̺߳���,���߳̾Ϳ�ʼ������
	std::thread t1(threadHandle1, 2);
	std::cout << "t1 thread :: ID = " << t1.get_id() << std::endl;

	std::thread t2(threadHandle2, 3);
	//t1.join();
	t1.detach();
	//t2.join();
	t2.detach();
	cout << __FUNCTION__ << " done!" << endl;
	return;
}

std::mutex mtx;			// ȫ�ֵ�һ�ѻ�����
int ticketCount = 100;	// ��վ��100�ų�Ʊ������������һ����Ʊ

/*
* ģ����Ʊ���̺߳��� lock_guard unique_lock
*/
void sellTicket(int index)
{
	while (ticketCount > 0) { // ticketCount=1 ��+˫���ж�
		// ��֤�����̶߳����ͷ�������ֹ��������ķ��� scoped_ptr
		lock_guard<std::mutex> lock(mtx);	// ������װ����һ���࣬��֤�ܳ�����һ�����ͷ���
		if (ticketCount > 0) {
			// �ٽ�������� =�� ԭ�Ӳ��� =�� �̼߳以������� =�� mutex
			cout << "����:" << index << "������:" << ticketCount << "��Ʊ!" << endl;
			ticketCount--;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}

/*
* ���̱߳�̣������г�վ��������Ʊ��������100��Ʊ��
*/
void multi_thread_tickets()
{
	list<std::thread> tlist;
	for (int i = 1; i <= 3; ++i) {
		tlist.push_back(std::thread(sellTicket, i));
	}

	for (std::thread& t : tlist) {
		t.join();
	}
	cout << "���д�����Ʊ����!" << endl;
	return;
}

// volatile��֤��ÿ�����ݶ��Ǵ��ڴ��ã���������һ����ȫ�Է��յļĴ���
volatile std::atomic_bool isReady = false;
volatile std::atomic_int mycount = 0;
void task()
{

	while (!isReady)
	{

		std::this_thread::yield(); // �̳߳��õ�ǰ��CPUʱ��Ƭ���ȴ���һ�ε���
	}

	for (int i = 0; i < 100; ++i)
	{

		mycount++;
	}
}

/*
* CASԭ�Ӳ�������Ϊ���Ĳ����ǱȽ��أ��������ٽ���������������Ƚϸ��ӣ��Ƚ϶ࡣ����������CAS����֤�����--������ԭ�����ԡ�ͬʱ��Ҳ������������
*/
void study_CAS()
{
	list<std::thread> tlist;
	for (int i = 0; i < 10; ++i) {
		tlist.push_back(std::thread(task));
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));
	isReady = true;

	for (std::thread& t : tlist) {
		t.join();
	}
	cout << "mycount:" << mycount << endl;

	return;
}


void test_study_lock()
{
	//test_join_detach();
	//multi_thread_tickets();
	study_CAS();
	return;
}