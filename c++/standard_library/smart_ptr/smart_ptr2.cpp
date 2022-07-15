#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

int main()
{
	shared_ptr<int> sp(new int(10));
	assert(sp.use_count() == 1);
	weak_ptr<int> wp(sp); 	//从 shared_ptr 创建 weak_ptr
	assert(wp.use_count() == 1);
	if (!wp.expired())		//判断 weak_ptr 观察的对象是否失效
	{
		shared_ptr<int> sp2 = wp.lock();//获得一个shared_ptr
		*sp2 = 100;
		assert(wp.use_count() == 2);    //好神奇
	}
	assert(wp.use_count() == 1);        //好神奇
	cout << "int:" << *sp << endl;
    return 0;
}
