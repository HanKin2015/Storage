## 1、C++多线程+线程池（全详解）
https://zhuanlan.zhihu.com/p/650522122

## 2、Linux下如何使用gettid函数且和pthread_self()的区别
gettid函数被定义在<sys./types.h>头文件中，但在程序中使用时发现没有gettid函数。
```
#include<sys/syscall.h>
syscall(SYS_gettid); //该函数和gettid等价。


在编写程序时可以使用上述函数。也可以将其封装一下。
pid_t gettid()
{
	return syscall(SYS_gettid);
} 
```

详解见：https://blog.csdn.net/weixin_42250655/article/details/105234980

## 3、20240828
后续继续研究：https://zhuanlan.zhihu.com/p/598993031
