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
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread1!" << endl;

	// 获取线程id
	std::cout << "inside thread :: ID = " << std::this_thread::get_id() << std::endl;
}
void threadHandle2(int time)
{
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread2!" << endl;
}

/*
* 当线程启动后，一定要在和线程相关联的std::thread对象销毁前，对线程运用join()或者detach()方法。
* 
* 体现一下join和detach的重要性。
* 
* 在一般情况下，如果主线程结束，就代表整个进程结束，如果这时有子线程还未结束就会出现运行错误。
* 当设置子线程为分离线程，主线程结束，子线程也自动结束。
*/
void test_join_detach()
{
	// 创建了一个线程对象,传入一个线程函数,新线程就开始运行了
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

std::mutex mtx;			// 全局的一把互斥锁
int ticketCount = 100;	// 车站有100张车票，由三个窗口一起卖票

/*
* 模拟卖票的线程函数 lock_guard unique_lock
* 
* lock_gurad类比于scoped_ptr，它的拷贝构造和复制构造都被删除了，不可用在函数参数传递或者返回过程中，只能用在简单的临界区代码段的互斥操作中。
* 而unique_lock可以类比于unique_ptr，它不仅可以用在简单的临界代码段的互斥操作中，还能用在函数调用过程中。
* 总的来说，建议使用unique_lock。
*/
void sellTicket(int index)
{
	while (ticketCount > 0) { // ticketCount=1 锁+双重判断
		// 保证所有线程都能释放锁，防止死锁问题的发生 scoped_ptr
		lock_guard<std::mutex> lock(mtx);	// 把锁包装成了一个类，保证能出函数一定会释放锁
		if (ticketCount > 0) {
			// 临界区代码段 =》 原子操作 =》 线程间互斥操作了 =》 mutex
			cout << "窗口:" << index << "卖出第:" << ticketCount << "张票!" << endl;
			ticketCount--;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}

/*
* 多线程编程：假设有车站的三个买票窗口来卖100张票。
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
	cout << "所有窗口卖票结束!" << endl;
	return;
}

// volatile保证了每次数据都是从内存拿，而不是有一定安全性风险的寄存器
volatile std::atomic_bool isReady = false;
volatile std::atomic_int mycount = 0;
void task(int index)
{
	while (!isReady) {
		cout << "index = " << index << " yield(让出当前的CPU时间片, 等待下一次调度)" << endl;
		std::this_thread::yield(); // 线程让出当前的CPU时间片，等待下一次调度
	}

	for (int i = 0; i < 10; ++i) {
		cout << "index = " << index << " mycount = " << mycount << endl;
		mycount++;
	}
}

/*
* CAS原子操作：因为锁的操作是比较重，而且在临界区代码做的事情比较复杂，比较多。所以引入了CAS来保证上面的--操作的原子特性。同时这也是无锁操作。
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
* 线程通信——生产者消费者模型问题
*/
std::mutex pc_mtx;			// 定义互斥锁，做线程间的互斥操作
std::condition_variable cv; // 定义条件变量，做线程间的同步通信操作
/*
* 定义出生产者和消费者的类queue
* 
* 生产者生产一个物品，通知消费者消费一个；消费完了，消费者再通知生产者继续生产物品
*/
class Queue
{
public:
	void put(int val)	// 生产物品
	{
		//lock_guard<std::mutex> guard(pc_mtx); // scoped_ptr
		unique_lock<std::mutex> lck(pc_mtx);	// unique_ptr
		while (!que.empty()) {
			// que不为空，生产者应该通知消费者去消费，消费完了，再继续生产
			// 生产者线程进入#1等待状态，并且#2把pc_mtx互斥锁释放掉
			cv.wait(lck);  // lck.lock() -->> lck.unlock
		}
		que.push(val);
		/* notify_one:通知另外的一个线程的 notify_all:通知其它所有线程的 通知其它所有的线程，我生产了一个物品，你们赶紧消费吧 其它线程得到该通知，就会从等待状态 =》 阻塞状态 =》 获取互斥锁才能继续执行 */
		cv.notify_all();
		cout << "生产者 生产:" << val << "号物品" << endl;
		return;
	}

	int get() // 消费物品
	{
		//lock_guard<std::mutex> guard(pc_mtx); // scoped_ptr
		unique_lock<std::mutex> lck(pc_mtx);	// unique_ptr
		while (que.empty()) {
			// 消费者线程发现que是空的，通知生产者线程先生产物品
			// #1 进入等待状态 # 把互斥锁pc_mtx释放
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all(); // 通知其它线程我消费完了，赶紧生产吧
		cout << "消费者 消费:" << val << "号物品" << endl;
		return val;
	}

private:
	queue<int> que;
};

/*
* 定义生产者和消费者的线程函数
*/
void producer(Queue* que) // 生产者线程
{
	for (int i = 1; i <= 10; i++) {
		que->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}
void consumer(Queue* que) // 消费者线程
{
	for (int i = 1; i <= 10; ++i) {
		que->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return;
}

/*
* 创建两个线程
*/
void producer_consumer_problem()
{
	Queue que; // 两个线程共享的队列

	std::thread t1(producer, &que);
	std::thread t2(consumer, &que);

	t1.join();
	t2.join();
	return;
}

/*
* shared_mutex读写锁把对共享资源的访问者划分成读者和写者，多个读线程能同时读取共享资源，但只有一个写线程能同时读取共享资源。
* shared_mutex通过lock_shared，unlock_shared进行读者的锁定与解锁；通过lock，unlock进行写者的锁定与解锁。
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
* std::mutex和std::lock_guard都在<mutex>头文件中声明
*/
mutex m;//实例化m对象，不要理解为定义变量
void proc1(int a)
{
	m.lock();
	cout << "proc1函数正在改写a" << endl;
	cout << "原始a为" << a << endl;
	cout << "现在a为" << a + 2 << endl;
	m.unlock();
}
/*
* 其原理是：声明一个局部的std::lock_guard对象，在其构造函数中进行加锁，在其析构函数中进行解锁。
* 最终的结果就是：创建即加锁，作用域结束自动解锁。从而使用std::lock_guard()就可以替代lock()与unlock()。
* 通过设定作用域，使得std::lock_guard在合适的地方被析构（在互斥量锁定到互斥量解锁之间的代码叫做临界区
* （需要互斥访问共享资源的那段代码称为临界区），临界区范围应该尽可能的小，即lock互斥量后应该尽早unlock），
* 通过使用{}来调整作用域范围，可使得互斥量m在合适的地方被解锁。
*/
void proc2(int a)
{
	{
		//m.lock();
		lock_guard<mutex> g(m);//用此语句替换了m.lock()；lock_guard传入一个参数时，该参数为互斥量，此时调用了lock_guard的构造函数，申请锁定m
		cout << "proc2函数正在改写a" << endl;
		cout << "原始a为" << a << endl;
		cout << "现在a为" << a + 1 << endl;
		//m.unlock();	//此时不需要写m.unlock(),g1出了作用域被释放，自动调用析构函数，于是m被解锁
	}	//通过使用{}来调整作用域范围，可使得m在合适的地方被解锁
	cout << "作用域外的内容3" << endl;
	cout << "作用域外的内容4" << endl;
	cout << "作用域外的内容5" << endl;
}
/*
* std::lock_gurad也可以传入两个参数，第二个参数为adopt_lock标识时，表示构造函数中不再进行互斥量锁定，因此此时需要提前手动锁定。
*/
void proc3(int a)
{
	m.lock();//手动锁定
	lock_guard<mutex> g(m, adopt_lock);
	cout << "proc1函数正在改写a" << endl;
	cout << "原始a为" << a << endl;
	cout << "现在a为" << a + 2 << endl;
}//自动解锁
void proc4(int a)
{
	unique_lock<mutex> g1(m, defer_lock);//始化了一个没有加锁的mutex
	cout << "xxxxdefer_lockxxxx" << endl;
	g1.lock();//手动加锁，注意，不是m.lock();注意，不是m.lock(),m已经被g1接管了;
	cout << "proc1函数正在改写a" << endl;
	cout << "原始a为" << a << endl;
	cout << "现在a为" << a + 2 << endl;
	g1.unlock();//临时解锁
	cout << "xxxdefer_lockxx" << endl;
	g1.lock();
	cout << "xxxdefer_lockxxx" << endl;
}//自动解锁

void proc5(int a)
{
	unique_lock<mutex> g2(m, try_to_lock);//尝试加锁一次，但如果没有锁定成功，会立即返回，不会阻塞在那里，且不会再次尝试锁操作。
	if (g2.owns_lock()) {//锁成功
		cout << "proc2函数正在改写a" << endl;
		cout << "原始a为" << a << endl;
		cout << "现在a为" << a + 1 << endl;
	}
	else {//锁失败则执行这段语句
		cout << "try_to_lock failed!" << endl;
	}
}//自动解锁
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
	// 1、学习join和detach的重要性
	//test_join_detach();
	
	// 2、多线程编程--买票
	//multi_thread_tickets();

	// 3、原子操作
	//study_CAS();
	
	// 4、生产者消费者模型问题
	//producer_consumer_problem();

	// 5、读写锁
	//study_shared_lock();

	// 6、lock和lock_guard区别
	study_mutex_lock_guard();
	return;
}