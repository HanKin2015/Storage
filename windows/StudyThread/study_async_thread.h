#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>
#include <queue>
#include <condition_variable>
using namespace std;

// 域空间解决不同文件之间相同变量或者相同函数问题
namespace study_async_thread {
	/*
	* std::async是一个函数模板，用来启动一个异步任务，它返回一个std::future类模板对象，future对象起到了占位的作用（记住这点就可以了）。
	* 开始实例化的future是没有储存值的，但在调用std::future对象的get()成员函数时，主线程会被阻塞直到异步线程执行结束，
	* 并把返回结果传递给std::future，即通过FutureObject.get()获取函数返回值。
	*
	* 即隐藏调用了一个join函数
	*
	* std::future与std::shard_future的用途都是为了占位，但是两者有些许差别。std::future的get()成员函数是转移数据所有权;
	* std::shared_future的get()成员函数是复制数据。 因此： future对象的get()只能调用一次；无法实现多个线程等待同一个异步线程，
	* 一旦其中一个线程获取了异步线程的返回值，其他线程就无法再次获取。 std::shared_future对象的get()可以调用多次；
	* 可以实现多个线程等待同一个异步线程，每个线程都可以获取异步线程的返回值。
	*/
	double t1(const double a, const double b)
	{
		double c = a + b;
		Sleep(3000);//假设t1函数是个复杂的计算过程，需要消耗3秒
		return c;
	}
	void study_async()
	{
		double a = 2.3;
		double b = 6.7;
		future<double> fu = async(t1, a, b);//创建异步线程线程，并将线程的执行结果用fu占位；
		cout << "正在进行计算" << endl;
		cout << "计算结果马上就准备好，请您耐心等待" << endl;
		cout << "计算结果：" << fu.get() << endl;//阻塞主线程，直至异步线程return
		//cout << "计算结果：" << fu.get() << endl;//取消该语句注释后运行会报错，因为future对象的get()方法只能调用一次。
		return;
	}

	/*
	* 生产者-消费者模型是经典的多线程并发协作模型。
	* 生产者与消费者不能直接交互,它们之间所共享的数据使用队列结构来实现。
	*/
	//缓冲区存储的数据类型 
	typedef struct
	{
		//商品id 
		int id;
		//商品属性 
		string data;
	}CacheData;

	queue<CacheData> Q;
	//缓冲区最大空间 
	const int MAX_CACHEDATA_LENGTH = 10;
	//互斥量，生产者之间，消费者之间，生产者和消费者之间，同时都只能一个线程访问缓冲区 
	mutex m;
	condition_variable condConsumer;
	condition_variable condProducer;
	//全局商品id 
	int ID = 1;

	//消费者动作 
	void ConsumerActor()
	{
		unique_lock<mutex> lockerConsumer(m);
		cout << "[" << this_thread::get_id() << "] 获取了锁" << endl;
		while (Q.empty())
		{
			cout << "因为队列为空，所以消费者Sleep" << endl;
			cout << "[" << this_thread::get_id() << "] 不再持有锁" << endl;
			//队列空， 消费者停止，等待生产者唤醒 
			condConsumer.wait(lockerConsumer);
			cout << "[" << this_thread::get_id() << "] Weak, 重新获取了锁" << endl;
		}
		cout << "[" << this_thread::get_id() << "] ";
		CacheData temp = Q.front();
		cout << "- ID:" << temp.id << " Data:" << temp.data << endl;
		Q.pop();
		condProducer.notify_one();
		cout << "[" << this_thread::get_id() << "] 释放了锁" << endl;
	}

	//生产者动作 
	void ProducerActor()
	{
		unique_lock<mutex> lockerProducer(m);
		cout << "[" << this_thread::get_id() << "] 获取了锁" << endl;
		while (Q.size() > MAX_CACHEDATA_LENGTH)
		{
			cout << "因为队列为满，所以生产者Sleep" << endl;
			cout << "[" << this_thread::get_id() << "] 不再持有锁" << endl;
			//对列慢，生产者停止，等待消费者唤醒 
			condProducer.wait(lockerProducer);
			cout << "[" << this_thread::get_id() << "] Weak, 重新获取了锁" << endl;
		}
		cout << "[" << this_thread::get_id() << "] ";
		CacheData temp;
		temp.id = ID++;
		temp.data = "*****";
		cout << "+ ID:" << temp.id << " Data:" << temp.data << endl;
		Q.push(temp);
		condConsumer.notify_one();
		cout << "[" << this_thread::get_id() << "] 释放了锁" << endl;
	}

	//消费者 
	void ConsumerTask()
	{
		while (1)
		{
			ConsumerActor();
		}
	}

	//生产者 
	void ProducerTask()
	{
		while (1)
		{
			ProducerActor();
		}
	}

	//管理线程的函数 
	void Dispatch(int ConsumerNum, int ProducerNum)
	{
		vector<thread> thsC;
		for (int i = 0; i < ConsumerNum; ++i)
		{
			thsC.push_back(thread(ConsumerTask));
		}

		vector<thread> thsP;
		for (int j = 0; j < ProducerNum; ++j)
		{
			thsP.push_back(thread(ProducerTask));
		}

		for (int i = 0; i < ConsumerNum; ++i)
		{
			if (thsC[i].joinable())
			{
				thsC[i].join();
			}
		}

		for (int j = 0; j < ProducerNum; ++j)
		{
			if (thsP[j].joinable())
			{
				thsP[j].join();
			}
		}
	}
	void producer_consumer_problem()
	{
		//一个消费者线程，5个生产者线程，则生产者经常要等待消费者 
		Dispatch(1, 5);
		return;
	}
}

int test_study_async_thread()
{
	// 1、异步线程
    //study_async_thread::study_async();

	// 2、生产者和消费者问题
	study_async_thread::producer_consumer_problem();
	
	return 0;
}