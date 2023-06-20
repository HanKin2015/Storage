# 状态机

## 1、了解ACM中的状态机模型
感觉像是动态规划：
有限状态机和动态规划是两种不同的算法思想。

有限状态机是一种描述离散系统行为的数学模型，它由一组状态、一组输入和一组输出组成。状态机根据输入和当前状态的转移规则，产生输出并转移到下一个状态。有限状态机通常用于描述计算机程序、电路和通信协议等离散系统。

动态规划是一种解决优化问题的算法思想，它通常用于求解具有重叠子问题和最优子结构性质的问题。动态规划将问题分解为若干个子问题，并保存子问题的解，以避免重复计算。动态规划通常用于求解最长公共子序列、背包问题、最短路径等问题。

虽然有限状态机和动态规划都涉及到状态和转移，但它们的应用场景和解决问题的方法不同。有限状态机通常用于描述离散系统的行为，而动态规划通常用于求解优化问题。在某些情况下，有限状态机和动态规划可以结合使用，例如在自然语言处理中，有限状态机可以用于词法分析，而动态规划可以用于句法分析。

能把不同的状态之间的关系使用状态机来表示，就可以使用状态机模型来处理，不同的状态之间有先后的时序。

参考：https://blog.csdn.net/m0_49959202/article/details/108637194

## 2、实际中的状态机
参考：https://blog.csdn.net/qq_30519005/article/details/122562055
用c++的状态模式写状态机
状态是固定的，事件可扩展
由事件触发，然后根据状态有不同的处理

fsm: Finite State Machine

运行结果：
```
[root@ubuntu0006:~/cmake/build] #./main
OnEventHandle cur state: 0
---- ConnectEvent Enter
connect start
connect success
==== ConnectEvent Exit
OnEventHandle cur state: 2
---- ConnectEvent Enter
connect_success
==== ConnectEvent Exit
not init log file path, use default log file path, ./log/project.log.
create log directory success.
2023-06-19 15:34:28 [INFO] [26311:26311] [/root/cmake/event_supply.cpp:78:OnEventHandle] OnEventHandle cur state: 对接成功
2023-06-19 15:34:28 [INFO] [26311:26311] [/root/cmake/event_supply.cpp:71:OnEventEnter] ---- SupplyEvent Enter
2023-06-19 15:34:28 [INFO] [26311:26311] [/root/cmake/event_supply.cpp:34:supply] supply start
2023-06-19 15:34:31 [INFO] [26311:26311] [/root/cmake/event_supply.cpp:39:supply] supply success
2023-06-19 15:34:31 [INFO] [26311:26311] [/root/cmake/event_supply.cpp:91:OnEventExit] ==== SupplyEvent Exit
OnEventHandle cur state: 5
---- StopSupplyEvent Enter
stop_supply start
stop_supply success
==== StopSupplyEvent Exit
OnEventHandle cur state: 8
---- DisconnectEvent Enter
disconnect start
disconnect success
==== DisconnectEvent Exit
cur state: 0
```
使用当前的状态值，连接下一个状态的函数进行状态转换调用。

## 3、写成cmake版本





