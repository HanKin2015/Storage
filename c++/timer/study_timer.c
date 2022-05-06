#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

static int count = 0;
static struct itimerval oldtv;

void set_timer()
{
	struct itimerval itv;
	itv.it_interval.tv_sec = 1;	// 间隔1秒执行一次信号函数
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, &oldtv);
}

void signal_handler(int m)
{
	count++;
	printf("count = %d (count < 10)\n", count);
}

int main()
{
	signal(SIGALRM, signal_handler);
	set_timer();
	while(count < 10);
	exit(0);
	return 1;
}
