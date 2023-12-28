#pragma once

#ifdef __cplusplus               // if used by C++ code
extern "C" {                     // we need to export the C interface
#endif

#define DLL_TRAINING_API _declspec(dllexport)
#ifndef DLL_TRAINING_API                                                                           
#define DLL_TRAINING_API _declspec(dllimport)   //当编译时，头文件不参加编译，所以.cpp文件中先定义，后头文件被包含进来，因此外部使用时，为dllimport，而在内部编译时，则为dllexport
#endif  

class DLL_TRAINING_API arithmetics_operation     //需要被外界调用的类（父类）
{
public:
    double Add(double a, double b);
    double Sub(double a, double b);
    double Multi(double a, double b);
    double Div(double a, double b);
};

// 外部使用返回333
int DLL_TRAINING_API Export333();
int DLL_TRAINING_API ExportN(int n);

// 这种方案不可行
arithmetics_operation DLL_TRAINING_API ArithmeticsInstance1();
// 这种方案也不可行，并且还有一点的是这个*号只能放在函数名前，不能放在类型后面
arithmetics_operation DLL_TRAINING_API *ArithmeticsInstance2();

// 必须得这样（需要多此一举封装一层重复代码（boilerplate））
arithmetics_operation arithmetics_instance;
double DLL_TRAINING_API Add(double a, double b) { return arithmetics_instance.Add(a, b); }
double DLL_TRAINING_API Sub(double a, double b) { return arithmetics_instance.Sub(a, b); }
double DLL_TRAINING_API Multi(double a, double b) { return arithmetics_instance.Multi(a, b); }
double DLL_TRAINING_API Div(double a, double b) { return arithmetics_instance.Div(a, b); }

#ifdef __cplusplus
}
#endif