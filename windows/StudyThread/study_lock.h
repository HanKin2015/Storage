#pragma once

#include <iostream>
#include <thread>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <list>
#include <mutex>
#include <queue>
#include <shared_mutex>

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
* 
* lock_gurad�����scoped_ptr�����Ŀ�������͸��ƹ��춼��ɾ���ˣ��������ں����������ݻ��߷��ع����У�ֻ�����ڼ򵥵��ٽ�������εĻ�������С�
* ��unique_lock���������unique_ptr���������������ڼ򵥵��ٽ����εĻ�������У��������ں������ù����С�
* �ܵ���˵������ʹ��unique_lock��
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
void task(int index)
{
	while (!isReady) {
		cout << "index = " << index << " yield(�ó���ǰ��CPUʱ��Ƭ, �ȴ���һ�ε���)" << endl;
		std::this_thread::yield(); // �߳��ó���ǰ��CPUʱ��Ƭ���ȴ���һ�ε���
	}

	for (int i = 0; i < 10; ++i) {
		cout << "index = " << index << " mycount = " << mycount << endl;
		mycount++;
	}
}

/*
* CASԭ�Ӳ�������Ϊ���Ĳ����ǱȽ��أ��������ٽ���������������Ƚϸ��ӣ��Ƚ϶ࡣ����������CAS����֤�����--������ԭ�����ԡ�ͬʱ��Ҳ������������
*/
void study_CAS()
{
	list<std::thread> tlist;
	for (int i = 0; i < 5; ++i) {
		tlist.push_back(std::thread(task, i));
	}

	cout << "now isReady = " << boolalpha << isReady << endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	isReady = true;
	cout << "now isReady = " << boolalpha << isReady << endl;

	for (std::thread& t : tlist) {
		t.join();
	}
	cout << "mycount:" << mycount << endl;
	return;
}

/*
* �߳�ͨ�š���������������ģ������
*/
std::mutex pc_mtx;			// ���廥���������̼߳�Ļ������
std::condition_variable cv; // �����������������̼߳��ͬ��ͨ�Ų���
/*
* ����������ߺ������ߵ���queue
* 
* ����������һ����Ʒ��֪ͨ����������һ�����������ˣ���������֪ͨ�����߼���������Ʒ
*/
class Queue
{
public:
	void put(int val)	// ������Ʒ
	{
		//lock_guard<std::mutex> guard(pc_mtx); // scoped_ptr
		unique_lock<std::mutex> lck(pc_mtx);	// unique_ptr
		while (!que.empty()) {
			// que��Ϊ�գ�������Ӧ��֪ͨ������ȥ���ѣ��������ˣ��ټ�������
			// �������߳̽���#1�ȴ�״̬������#2��pc_mtx�������ͷŵ�
			cv.wait(lck);  // lck.lock() -->> lck.unlock
		}
		que.push(val);
		/* notify_one:֪ͨ�����һ���̵߳� notify_all:֪ͨ���������̵߳� ֪ͨ�������е��̣߳���������һ����Ʒ�����ǸϽ����Ѱ� �����̵߳õ���֪ͨ���ͻ�ӵȴ�״̬ =�� ����״̬ =�� ��ȡ���������ܼ���ִ�� */
		cv.notify_all();
		cout << "������ ����:" << val << "����Ʒ" << endl;
		return;
	}

	int get() // ������Ʒ
	{
		//lock_guard<std::mutex> guard(pc_mtx); // scoped_ptr
		unique_lock<std::mutex> lck(pc_mtx);	// unique_ptr
		while (que.empty()) {
			// �������̷߳���que�ǿյģ�֪ͨ�������߳���������Ʒ
			// #1 ����ȴ�״̬ # �ѻ�����pc_mtx�ͷ�
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all(); // ֪ͨ�����߳����������ˣ��Ͻ�������
		cout << "������ ����:" << val << "����Ʒ" << endl;
		return val;
	}

private:
	queue<int> que;
};

/*
* ���������ߺ������ߵ��̺߳���
*/
void producer(Queue* que) // �������߳�
{
	for (int i = 1; i <= 10; i++) {
		que->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}
void consumer(Queue* que) // �������߳�
{
	for (int i = 1; i <= 10; ++i) {
		que->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}

/*
* ���������߳�
*/
void producer_consumer_problem()
{
	Queue que; // �����̹߳���Ķ���

	std::thread t1(producer, &que);
	std::thread t2(consumer, &que);

	t1.join();
	t2.join();
	return;
}

/*
* shared_mutex��д���ѶԹ�����Դ�ķ����߻��ֳɶ��ߺ�д�ߣ�������߳���ͬʱ��ȡ������Դ����ֻ��һ��д�߳���ͬʱ��ȡ������Դ��
* shared_mutexͨ��lock_shared��unlock_shared���ж��ߵ������������ͨ��lock��unlock����д�ߵ������������
*/
shared_mutex s_m;
std::string book;
void read()
{
	s_m.lock_shared();
	cout << "book = " << book << endl;
	s_m.unlock_shared();
}
void write()
{
	s_m.lock();
	book = "new context";
	s_m.unlock();
}
void study_shared_lock()
{
	std::thread t1(read);
	std::thread t2(write);

	t1.join();
	t2.join();
	return;
}

/*
* std::mutex��std::lock_guard����<mutex>ͷ�ļ�������
*/
mutex m;//ʵ����m���󣬲�Ҫ���Ϊ�������
void proc1(int a)
{
	m.lock();
	cout << "proc1�������ڸ�дa" << endl;
	cout << "ԭʼaΪ" << a << endl;
	cout << "����aΪ" << a + 2 << endl;
	m.unlock();
}
/*
* ��ԭ���ǣ�����һ���ֲ���std::lock_guard�������乹�캯���н��м������������������н��н�����
* ���յĽ�����ǣ�����������������������Զ��������Ӷ�ʹ��std::lock_guard()�Ϳ������lock()��unlock()��
* ͨ���趨������ʹ��std::lock_guard�ں��ʵĵط����������ڻ���������������������֮��Ĵ�������ٽ���
* ����Ҫ������ʹ�����Դ���Ƕδ����Ϊ�ٽ��������ٽ�����ΧӦ�þ����ܵ�С����lock��������Ӧ�þ���unlock����
* ͨ��ʹ��{}������������Χ����ʹ�û�����m�ں��ʵĵط���������
*/
void proc2(int a)
{
	{
		//m.lock();
		lock_guard<mutex> g(m);//�ô�����滻��m.lock()��lock_guard����һ������ʱ���ò���Ϊ����������ʱ������lock_guard�Ĺ��캯������������m
		cout << "proc2�������ڸ�дa" << endl;
		cout << "ԭʼaΪ" << a << endl;
		cout << "����aΪ" << a + 1 << endl;
		//m.unlock();	//��ʱ����Ҫдm.unlock(),g1�����������ͷţ��Զ�������������������m������
	}	//ͨ��ʹ��{}������������Χ����ʹ��m�ں��ʵĵط�������
	cout << "�������������3" << endl;
	cout << "�������������4" << endl;
	cout << "�������������5" << endl;
}
/*
* std::lock_guradҲ���Դ��������������ڶ�������Ϊadopt_lock��ʶʱ����ʾ���캯���в��ٽ��л�������������˴�ʱ��Ҫ��ǰ�ֶ�������
*/
void proc3(int a)
{
	m.lock();//�ֶ�����
	lock_guard<mutex> g(m, adopt_lock);
	cout << "proc1�������ڸ�дa" << endl;
	cout << "ԭʼaΪ" << a << endl;
	cout << "����aΪ" << a + 2 << endl;
}//�Զ�����
void proc4(int a)
{
	unique_lock<mutex> g1(m, defer_lock);//ʼ����һ��û�м�����mutex
	cout << "xxxxdefer_lockxxxx" << endl;
	g1.lock();//�ֶ�������ע�⣬����m.lock();ע�⣬����m.lock(),m�Ѿ���g1�ӹ���;
	cout << "proc1�������ڸ�дa" << endl;
	cout << "ԭʼaΪ" << a << endl;
	cout << "����aΪ" << a + 2 << endl;
	g1.unlock();//��ʱ����
	cout << "xxxdefer_lockxx" << endl;
	g1.lock();
	cout << "xxxdefer_lockxxx" << endl;
}//�Զ�����

void proc5(int a)
{
	unique_lock<mutex> g2(m, try_to_lock);//���Լ���һ�Σ������û�������ɹ������������أ���������������Ҳ����ٴγ�����������
	if (g2.owns_lock()) {//���ɹ�
		cout << "proc2�������ڸ�дa" << endl;
		cout << "ԭʼaΪ" << a << endl;
		cout << "����aΪ" << a + 1 << endl;
	}
	else {//��ʧ����ִ��������
		cout << "try_to_lock failed!" << endl;
	}
}//�Զ�����
void study_mutex_lock_guard()
{
	int a = 0;
	thread t1(proc1, a);
	thread t2(proc2, a);
	thread t3(proc3, a);
	thread t4(proc4, a);
	thread t5(proc5, a);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return;
}

void test_study_lock()
{
	// 1��ѧϰjoin��detach����Ҫ��
	//test_join_detach();
	
	// 2�����̱߳��--��Ʊ
	//multi_thread_tickets();

	// 3��ԭ�Ӳ���
	//study_CAS();
	
	// 4��������������ģ������
	//producer_consumer_problem();

	// 5����д��
	//study_shared_lock();

	// 6��lock��lock_guard����
	study_mutex_lock_guard();
	return;
}