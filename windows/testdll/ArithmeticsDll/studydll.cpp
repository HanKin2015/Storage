#include "pch.h"
#include "studydll.h"
using namespace std;

double DLL_TRAINING_API arithmetics_operation::Add(double a, double b) {
    return a + b;
}

double DLL_TRAINING_API arithmetics_operation::Sub(double a, double b) {
    return a - b;
}

double DLL_TRAINING_API arithmetics_operation::Multi(double a, double b) {
    return a * b;
}

double DLL_TRAINING_API arithmetics_operation::Div(double a, double b) {
    return a / b;
}

int DLL_TRAINING_API Export333() {
    return 333;
}

int DLL_TRAINING_API ExportN(int n) {
	return n;
}

arithmetics_operation DLL_TRAINING_API ArithmeticsInstance1()
{
	arithmetics_operation instance;
	return instance;
}

arithmetics_operation DLL_TRAINING_API *ArithmeticsInstance2()
{
	arithmetics_operation instance;
	return &instance;
}