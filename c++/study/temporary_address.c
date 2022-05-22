#include <stdio.h>

// 用this 指针，可以区分到底哪一个对象被构建和销毁
struct A {
    int v;
    A(int x) 
    {
        v=x;
        printf("construct! v:%d, p:%p\n", v, this);
    }
    A()
    {
        v=0;
        printf("construct! 0, p:%p\n", this);
    }
    A(const A& a)
    {
        v=a.v;
        printf("copyed! v:%d, p:%p\n", v, this);
    }
    A& operator=(const A& a)
    {
        v=a.v;
        printf("assigned! v:%d, p:%p\n", v, this);
    }
    ~A()
    {
        printf("destructed! p:%p\n", this);
    }
};

/* 研究对象创建方式， 尤其是临时对象的生命周期
 * 打开，关闭相关的注释，编译运行可以了解其工作实质
 */
int main()
{
    //A(1);		    //临时对象, 在该行创建，在该行又销毁
    
    //A a1 = A(1);	//临时对象被优化掉，仅进行一次整数构造
    
    //A a1;		    //默认构造;
    //a1 = A(1);	//赋值构造，临时对象被创建，在该行又被销毁
    
    //A a2(2);	    //整数构造
    //a1 = a2;	    //赋值构造
    void *p = &A(2);	//产生错误  error: taking address of temporary [-fpermissive]

    printf("-------main函数结束分割线-------\n");
    //printf("what's this %p\n", &a1);
    return 0;
}
