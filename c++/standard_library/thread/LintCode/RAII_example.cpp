/**
* 文 件 名: RAII_example.cpp
* 文件描述: 将线程的 join() 加入 RAII 类中。在该情况下，主线程结束后，raii 作为局部对象即将被回收，此时会触发 RAII 类的析构函数，在这个析构函数中我们对线程的状态进行了一个判断，随后将该线程调用 join()，使其能够执行完线程的全部内容
* 备    注：g++ RAII_example.cpp -std=c++11 -lpthread
* 作    者: HanKin
* 创建日期: 2022.06.08
* 修改日期：2023.06.08
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <thread>

using namespace std;

// thread guard
class RAII {
    thread& th;

public:
    explicit RAII(thread& _t) : th(_t){};

    ~RAII() {
        if (th.joinable()) {
            th.join();
        }
    }

    RAII(const RAII&) = delete;
    RAII& operator=(const RAII&) = delete;
};

int main() {
    thread t([] {
        for (int i = 0; i < 10; i++) {
            cout << i;
        }
    });
    RAII raii(t);
    return 0;
}