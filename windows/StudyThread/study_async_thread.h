#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>
#include <queue>
#include <condition_variable>
using namespace std;

// ��ռ�����ͬ�ļ�֮����ͬ����������ͬ��������
namespace study_async_thread {
	/*
	* std::async��һ������ģ�壬��������һ���첽����������һ��std::future��ģ�����future��������ռλ�����ã���ס���Ϳ����ˣ���
	* ��ʼʵ������future��û�д���ֵ�ģ����ڵ���std::future�����get()��Ա����ʱ�����̻߳ᱻ����ֱ���첽�߳�ִ�н�����
	* ���ѷ��ؽ�����ݸ�std::future����ͨ��FutureObject.get()��ȡ��������ֵ��
	*
	* �����ص�����һ��join����
	*
	* std::future��std::shard_future����;����Ϊ��ռλ������������Щ����std::future��get()��Ա������ת����������Ȩ;
	* std::shared_future��get()��Ա�����Ǹ������ݡ� ��ˣ� future�����get()ֻ�ܵ���һ�Σ��޷�ʵ�ֶ���̵߳ȴ�ͬһ���첽�̣߳�
	* һ������һ���̻߳�ȡ���첽�̵߳ķ���ֵ�������߳̾��޷��ٴλ�ȡ�� std::shared_future�����get()���Ե��ö�Σ�
	* ����ʵ�ֶ���̵߳ȴ�ͬһ���첽�̣߳�ÿ���̶߳����Ի�ȡ�첽�̵߳ķ���ֵ��
	*/
	double t1(const double a, const double b)
	{
		double c = a + b;
		Sleep(3000);//����t1�����Ǹ����ӵļ�����̣���Ҫ����3��
		return c;
	}
	void study_async()
	{
		double a = 2.3;
		double b = 6.7;
		future<double> fu = async(t1, a, b);//�����첽�߳��̣߳������̵߳�ִ�н����fuռλ��
		cout << "���ڽ��м���" << endl;
		cout << "���������Ͼ�׼���ã��������ĵȴ�" << endl;
		cout << "��������" << fu.get() << endl;//�������̣߳�ֱ���첽�߳�return
		//cout << "��������" << fu.get() << endl;//ȡ�������ע�ͺ����лᱨ����Ϊfuture�����get()����ֻ�ܵ���һ�Ρ�
		return;
	}

	/*
	* ������-������ģ���Ǿ���Ķ��̲߳���Э��ģ�͡�
	* �������������߲���ֱ�ӽ���,����֮�������������ʹ�ö��нṹ��ʵ�֡�
	*/
	//�������洢���������� 
	typedef struct
	{
		//��Ʒid 
		int id;
		//��Ʒ���� 
		string data;
	}CacheData;

	queue<CacheData> Q;
	//���������ռ� 
	const int MAX_CACHEDATA_LENGTH = 10;
	//��������������֮�䣬������֮�䣬�����ߺ�������֮�䣬ͬʱ��ֻ��һ���̷߳��ʻ����� 
	mutex m;
	condition_variable condConsumer;
	condition_variable condProducer;
	//ȫ����Ʒid 
	int ID = 1;

	//�����߶��� 
	void ConsumerActor()
	{
		unique_lock<mutex> lockerConsumer(m);
		cout << "[" << this_thread::get_id() << "] ��ȡ����" << endl;
		while (Q.empty())
		{
			cout << "��Ϊ����Ϊ�գ�����������Sleep" << endl;
			cout << "[" << this_thread::get_id() << "] ���ٳ�����" << endl;
			//���пգ� ������ֹͣ���ȴ������߻��� 
			condConsumer.wait(lockerConsumer);
			cout << "[" << this_thread::get_id() << "] Weak, ���»�ȡ����" << endl;
		}
		cout << "[" << this_thread::get_id() << "] ";
		CacheData temp = Q.front();
		cout << "- ID:" << temp.id << " Data:" << temp.data << endl;
		Q.pop();
		condProducer.notify_one();
		cout << "[" << this_thread::get_id() << "] �ͷ�����" << endl;
	}

	//�����߶��� 
	void ProducerActor()
	{
		unique_lock<mutex> lockerProducer(m);
		cout << "[" << this_thread::get_id() << "] ��ȡ����" << endl;
		while (Q.size() > MAX_CACHEDATA_LENGTH)
		{
			cout << "��Ϊ����Ϊ��������������Sleep" << endl;
			cout << "[" << this_thread::get_id() << "] ���ٳ�����" << endl;
			//��������������ֹͣ���ȴ������߻��� 
			condProducer.wait(lockerProducer);
			cout << "[" << this_thread::get_id() << "] Weak, ���»�ȡ����" << endl;
		}
		cout << "[" << this_thread::get_id() << "] ";
		CacheData temp;
		temp.id = ID++;
		temp.data = "*****";
		cout << "+ ID:" << temp.id << " Data:" << temp.data << endl;
		Q.push(temp);
		condConsumer.notify_one();
		cout << "[" << this_thread::get_id() << "] �ͷ�����" << endl;
	}

	//������ 
	void ConsumerTask()
	{
		while (1)
		{
			ConsumerActor();
		}
	}

	//������ 
	void ProducerTask()
	{
		while (1)
		{
			ProducerActor();
		}
	}

	//�����̵߳ĺ��� 
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
		//һ���������̣߳�5���������̣߳��������߾���Ҫ�ȴ������� 
		Dispatch(1, 5);
		return;
	}
}

int test_study_async_thread()
{
	// 1���첽�߳�
    //study_async_thread::study_async();

	// 2�������ߺ�����������
	study_async_thread::producer_consumer_problem();
	
	return 0;
}