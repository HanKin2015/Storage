#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>
using namespace std;

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

int study_async_thread()
{
    study_async();
    return 0;
}