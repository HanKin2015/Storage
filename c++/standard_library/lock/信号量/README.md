在 C++ 中，信号量（Semaphore）是一种用于线程同步的机制，通过一个计数器控制对共享资源的访问，可实现线程间的顺序控制、资源并发访问限制等功能。C++20 正式将信号量纳入标准库（<semaphore> 头文件），在此之前通常依赖平台特定实现（如 POSIX 信号量或 Windows 信号量）。

C++20 提供了两种信号量：
std::counting_semaphore<MaxCount>：计数信号量，计数器可在 [0, MaxCount] 范围内变化（MaxCount 是模板参数，需为非负整数）。
std::binary_semaphore：二进制信号量，等价于 std::counting_semaphore<1>，计数器只能是 0 或 1（类似互斥锁，但可由不同线程释放）。

核心操作
acquire()：尝试获取信号量。若计数器 > 0，则计数器减 1 并返回；若计数器 = 0，则阻塞当前线程，直到计数器 > 0。
try_acquire()：非阻塞版本的 acquire()。若计数器 > 0，减 1 并返回 true；否则直接返回 false。
release(n = 1)：释放信号量，计数器增加 n（n 需满足计数器最终 ≤ MaxCount）。若有线程阻塞在 acquire()，会唤醒一个或多个线程。