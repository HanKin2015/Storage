#include <iostream>
using namespace std;

class fruit
{
	fruit(){}
	~fruit(){}

public:
	void eat();
	int get_num();
	
}

class A
{
   virtual void foo();
   void bar();
};
class B : A
{
   void foo() const override; 	// 错误： B::foo 不覆写 A::foo
                              	// （签名不匹配）
   void foo() override;			// OK ： B::foo 覆写 A::foo
   void bar() override;			// 错误： A::bar 非虚
};

int main()
{
	cout << "hello wolrd!" << endl;
	return 0;
}