# 面试学习

## 1、需求
实现一个包含三个进程（A、B、C）的通信 demo，使用 TCP socket 进行进程间通信，并使用 nlohmann/json 处理 JSON 消息。整个流程是 A→B→C→B→A 的消息传递链。

首先，我们需要创建四个文件：
- 共用的消息定义和工具函数（message_utils.h）
- 进程 A 的代码（process_a.cpp）
- 进程 B 的代码（process_b.cpp）
- 进程 C 的代码（process_c.cpp）
- CMakeLists.txt 构建文件

