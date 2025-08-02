// tests/test_calculator.cpp
#include <gtest/gtest.h>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        calc.set_value(10);
    }

    Calculator calc;
};

TEST_F(CalculatorTest, AddPositiveNumber) {
    calc.add(5);
    EXPECT_EQ(calc.get_value(), 15);
}

TEST_F(CalculatorTest, AddNegativeNumber) {
    calc.add(-3);
    EXPECT_EQ(calc.get_value(), 7);
}