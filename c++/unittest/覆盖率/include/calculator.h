// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    Calculator();
    void set_value(int val);
    int get_value() const;
    void add(int val);

private:
    int value;
};

#endif // CALCULATOR_H