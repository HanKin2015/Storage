/**
* 文 件 名: lock_guard_example.cpp
* 文件描述: 不加lock_guard就会输出不同的结果
* 作    者: HanKin
* 创建日期: 2023.09.01
* 修改日期：2023.09.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <mutex>
#include <iostream>
#include <thread>

class Counter {
public:
    Counter() : count_(0) {}

    void increment() {
        std::lock_guard<std::mutex> lock(mtx_);
        ++count_;
    }

    void decrement() {
        std::lock_guard<std::mutex> lock(mtx_);
        --count_;
    }

    int value() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return count_;
    }

private:
    int count_;
    mutable std::mutex mtx_;
};

void worker(Counter& counter) {
    for (int i = 0; i < 100000; ++i) {
        counter.increment();
        counter.decrement();
    }
}

int main() {
    Counter counter;

    std::thread t1(worker, std::ref(counter));
    std::thread t2(worker, std::ref(counter));

    t1.join();
    t2.join();

    std::cout << "Final count: " << counter.value() << std::endl;

    return 0;
}
