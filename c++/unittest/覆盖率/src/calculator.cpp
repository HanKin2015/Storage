// calculator.cpp
#include "calculator.h"

Calculator::Calculator() : value(0) {}

void Calculator::set_value(int val) {
    value = val;
}

int Calculator::get_value() const {
    return value;
}

void Calculator::add(int val) {
    value += val;
}