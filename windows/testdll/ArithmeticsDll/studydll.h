#pragma once

#ifdef __cplusplus               // if used by C++ code
extern "C" {                     // we need to export the C interface
#endif

#define DLL_TRAINING_API _declspec(dllexport)
#ifndef DLL_TRAINING_API                                                                           
#define DLL_TRAINING_API _declspec(dllimport)   //������ʱ��ͷ�ļ����μӱ��룬����.cpp�ļ����ȶ��壬��ͷ�ļ�����������������ⲿʹ��ʱ��Ϊdllimport�������ڲ�����ʱ����Ϊdllexport
#endif  

class DLL_TRAINING_API arithmetics_operation     //��Ҫ�������õ��ࣨ���ࣩ
{
public:
    double Add(double a, double b);
    double Sub(double a, double b);
    double Multi(double a, double b);
    double Div(double a, double b);
};

// �ⲿʹ�÷���333
int DLL_TRAINING_API Export333();
int DLL_TRAINING_API ExportN(int n);

// ���ַ���������
arithmetics_operation DLL_TRAINING_API ArithmeticsInstance1();
// ���ַ���Ҳ�����У����һ���һ��������*��ֻ�ܷ��ں�����ǰ�����ܷ������ͺ���
arithmetics_operation DLL_TRAINING_API *ArithmeticsInstance2();

// �������������Ҫ���һ�ٷ�װһ���ظ����루boilerplate����
arithmetics_operation arithmetics_instance;
double DLL_TRAINING_API Add(double a, double b) { return arithmetics_instance.Add(a, b); }
double DLL_TRAINING_API Sub(double a, double b) { return arithmetics_instance.Sub(a, b); }
double DLL_TRAINING_API Multi(double a, double b) { return arithmetics_instance.Multi(a, b); }
double DLL_TRAINING_API Div(double a, double b) { return arithmetics_instance.Div(a, b); }

#ifdef __cplusplus
}
#endif