# 系统的学习多线程
之前虽然学习了线程的多个模块，如锁、线程、线程池、条件变量、fork等，但都是零碎的。

学习地址：https://www.lintcode.com/course/99/learn/?chapterId=520&sectionId=3782

## 1、发现thread库是对pthread_create等函数的封装
```
[root@ubuntu0006:~/cmake/build] #g++ k.cpp -std=c++11
/tmp/ccvH1ojg.o：在函数‘std::thread::thread<void (&)()>(void (&)())’中：
k.cpp:(.text._ZNSt6threadC2IRFvvEJEEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEEEOT_DpOT0_]+0x7d)：对‘pthread_create’未定义的引用
collect2: error: ld returned 1 exit status
```
