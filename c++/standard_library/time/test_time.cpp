#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main()
{
    //struct tm tm_obj = {0, 0, 8, 1, 1-1, 1970-1900};
    struct tm tm_obj = {0, 0, 7, 14, 4, 2021-1900};
    //1970年之前计算出来的是负值
    //注意不要使用lu，虽然减的是1900，但是计算的却是从1970开始的
    printf("from 1970.01.01 total seconds: %ld\n", mktime(&tm_obj));
    printf("%d %d %d %d %d %d %d %d %d %ld %s\n", tm_obj.tm_sec,
        tm_obj.tm_min, tm_obj.tm_hour, tm_obj.tm_mday,
        tm_obj.tm_mon, tm_obj.tm_year, tm_obj.tm_wday,
        tm_obj.tm_yday, tm_obj.tm_isdst, tm_obj.tm_gmtoff,
        tm_obj.tm_zone);
    printf("%ld\n", LONG_MAX);
    return 0;
}
