#include "pch.h"
#include "studydll.h"

#define DLL_TRAINING_API _declspec(dllexport)

using namespace std;

double DLL_TRAINING_API arithmetic_operation::Add(double a, double b) {
    return a + b;
}

double DLL_TRAINING_API arithmetic_operation::Sub(double a, double b) {
    return a - b;
}

double DLL_TRAINING_API arithmetic_operation::Multi(double a, double b) {
    return a * b;
}

double DLL_TRAINING_API arithmetic_operation::Div(double a, double b) {
    return a / b;
}

int DLL_TRAINING_API export333() {
    return 333;
}