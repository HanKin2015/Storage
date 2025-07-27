/*******************************************************************************
* 文 件 名: 银行转账场景的死锁.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>

// 银行账户类
class Account {
private:
    int balance;          // 账户余额
    std::mutex mtx;       // 保护余额的互斥锁

public:
    Account(int bal) : balance(bal) {}

    // 转账函数：从当前账户转出amount到目标账户
    void transfer(Account& target, int amount) {
        // 锁定当前账户和目标账户（关键步骤）
        std::lock_guard<std::mutex> lock1(mtx);          // 锁定自己
        std::this_thread::sleep_for(std::chrono::ms(10)); // 模拟处理延迟，放大死锁概率
        std::lock_guard<std::mutex> lock2(target.mtx);    // 锁定目标

        if (balance >= amount) {
            balance -= amount;
            target.balance += amount;
            std::cout << "转账成功！" << std::endl;
        } else {
            std::cout << "余额不足，转账失败！" << std::endl;
        }
    }

    int getBalance() const { return balance; }
};

int main()
{
    Account A(1000);  // 账户A初始余额1000
    Account B(2000);  // 账户B初始余额2000

    // 线程1：A向B转账200
    std::thread t1(&Account::transfer, &A, std::ref(B), 200);
    // 线程2：B向A转账300
    std::thread t2(&Account::transfer, &B, std::ref(A), 300);

    t1.join();
    t2.join();

    std::cout << "最终A余额：" << A.getBalance() << std::endl;
    std::cout << "最终B余额：" << B.getBalance() << std::endl;

    return 0;
}