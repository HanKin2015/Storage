#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
int kMicroSecondsPerSecond = 1000 * 1000;
int64_t NMicroSecondsPerSecond = 1000 * 1000 * 1000;
int64_t now1()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
  printf("%ld\n",seconds);
  return seconds * kMicroSecondsPerSecond + tv.tv_usec;
  //返回一个Timestamp结构体，相当于创建一个当前时间的Timestamp结构体
}
 
int64_t now2()
{
  struct timespec tv;
  clock_gettime(CLOCK_MONOTONIC, &tv);
  int64_t seconds = tv.tv_sec;
  printf("%ld\n",seconds);
  return seconds * kMicroSecondsPerSecond + tv.tv_nsec/1000;
  //返回一个Timestamp结构体，相当于创建一个当前时间的Timestamp结构体
}
 
void translate(int64_t microSecondsSinceEpoch_)
{
    char buf[32] = {0};
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);//将总秒数转换成————年-月-日-小时-分-秒为单位，并且还会自动加上1970年1月1日时间 
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
    tm_time.tm_year+1900, tm_time.tm_mon + 1, tm_time.tm_mday,
    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
    microseconds);//总秒数加上1900年1月1日然后转换成固定格式
    printf("%s\n",buf);
}
 
 
int main()
{
    int64_t microSecondsSinceEpoch1_ = now1();
    translate(microSecondsSinceEpoch1_);
    int64_t microSecondsSinceEpoch2_ = now2();
    translate(microSecondsSinceEpoch2_);
    translate(0);
    return 0;
}