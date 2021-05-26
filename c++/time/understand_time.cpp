#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#include <limits.h>

static inline void rel_time(struct timespec& tim, uint64_t delta_nano)
{
#ifdef WIN32
        struct _timeb now;
        _ftime_s(&now);
        tim.tv_sec = (long)now.time;
        tim.tv_nsec = now.millitm * 1000 * 1000;
        printf("line: %d\n", __LINE__);
#elif defined(HAVE_CLOCK_GETTIME)
        clock_gettime(CLOCK_MONOTONIC, &tim);
        printf("line: %d\n", __LINE__);
#else
        struct timeval tv;
        gettimeofday(&tv,NULL);
        printf("line: %d\n", __LINE__);
        
        struct tm *p = localtime(&tv.tv_sec); 
        printf("time_now: %d-%d-%d %d:%d:%d.%ld\n", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);
        //理解到了，sec和usec并不是等价的，不是当前时间两种精确度问题，而是把当前时间分成两部分
        printf("current time: %ld %ld\n", tv.tv_sec, tv.tv_usec);
        
        tim.tv_sec = tv.tv_sec;
        tim.tv_nsec = tv.tv_usec*1000;
#endif
        printf("before transfer delta_nano: %s, %lu\n", asctime(localtime(&tim.tv_sec)), tim.tv_sec);
        printf("before sec: %lu\n", tim.tv_sec);

        delta_nano += (uint64_t)tim.tv_sec * 1000 * 1000 * 1000;
        delta_nano += tim.tv_nsec;
        tim.tv_sec = long(delta_nano / (1000 * 1000 * 1000));
        tim.tv_nsec = long(delta_nano % (1000 * 1000 * 1000));
        printf("after sec: %lu\n", tim.tv_sec);

        printf("detla_nano: %lu\n", delta_nano);
        printf("current OS sizeof(long): %ld %ld\n", sizeof(long), LONG_MAX);
        printf("current OS sizeof(int) : %lu %d \n", sizeof(int),  INT_MAX );
}

int main()
{
        uint64_t nano = 1e10;

        struct timespec tim;
        rel_time(tim, nano);

        time_t current_time;
        time(&current_time); /*获取time_t类型的当前时间*/
        /*用gmtime将time_t类型的时间转换为struct tm类型的时间按，／／没有经过时区转换的UTC时间
          然后再用asctime转换为我们常见的格式 Fri Jan 11 17:25:24 2008
         */

        printf("after transfer delta_nano: %s, %lu\n", asctime(localtime(&tim.tv_sec)), tim.tv_sec);
        printf("current time: %s\n", ctime(&current_time));
        printf("%lu\n", tim.tv_nsec);

        //timeval和time_t的秒数相差8小时???
        struct timeval tv;
        gettimeofday(&tv, NULL);
        struct tm *p = localtime(&tv.tv_sec); 
        printf("time_now: %d-%d-%d %d:%d:%d.%ld\n", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);
        printf("timeval: %s\n", asctime(localtime(&tv.tv_sec))); 
        
        //tv.tv_sec = 0x7fb8965f94e0;
        tv.tv_sec = 1617788484;
        printf("timeval: %s\n", asctime(localtime(&tv.tv_sec))); 
        return 0;
}
