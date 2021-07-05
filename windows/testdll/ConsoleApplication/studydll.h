#pragma once
#ifdef DLL_TRAINING_API
#else                                                                            
#define DLL_TRAINING_API _declspec(dllimport) //当编译时，头文件不参加编译，所以.cpp文件中先定义，后头文件被包含进来，因此外部使用时，为dllimport，而在内部编译时，则为dllexport
#endif  

class DLL_TRAINING_API arithmetic_operation              //需要被外界调用的类（父类）
{
public:
    double Add(double a, double b);
    double Sub(double a, double b);
    double Multi(double a, double b);
    double Div(double a, double b);
};

// 外部使用返回333
int DLL_TRAINING_API export333();