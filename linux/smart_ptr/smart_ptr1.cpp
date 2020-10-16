#include <iostream>
#include <string>
#include <memory>

// 运行时出错
//#define SMARTPTR auto_ptr

// 编译时出错
//#define SMARTPTR unique_ptr

// 正确
#define SMARTPTR shared_ptr
using namespace std;

int main() {
	SMARTPTR<string> films[5] ={
	SMARTPTR<string> (new string("Fowl Balls")),
	SMARTPTR<string> (new string("Duck Walks")),
	SMARTPTR<string> (new string("Chicken Runs")),
	SMARTPTR<string> (new string("Turkey Errors")),
	SMARTPTR<string> (new string("Goose Eggs"))
	};

    SMARTPTR<string> pwin;     
    pwin = films[2]; // films[2] loses ownership. 将所有权从films[2]转让给pwin，此时films[2]不再引用该字符串从而变成空指针

	cout << "The nominees for best avian baseballl film are\n";
	for(int i = 0; i < 5; ++i)
	{
		cout << *films[i] << endl;
	}
 	cout << "The winner is " << *pwin << endl;
	return 0;
}
