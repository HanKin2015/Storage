//设置一个1s延时信号，再注册一个
#include <stdio.h>
#include <signal.h>
 
void timer(int sig)
{
    if(SIGALRM == sig)
    {
        printf("timer\n");
        alarm(1);       //重新继续定时1s
    }
    
    return ;
}
 
int main()
{
    signal(SIGALRM, timer); //注册安装信号
    
    alarm(1);       //触发定时器
    
    getchar();
    
    return 0;
}